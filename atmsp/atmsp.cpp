/** *********************************************************************** **
 **                                                                         **
 ** Copyright (C) 1989-2012 Heinz van Saanen                                **
 **                                                                         **
 ** This file may be used under the terms of the GNU General Public         **
 ** License version 3 or later as published by the Free Software Foundation **
 ** and appearing in the file LICENSE.GPL included in the packaging of      **
 ** this file.                                                              **
 **                                                                         **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE **
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR        **
 ** PURPOSE.                                                                **
 **                                                                         **
 ** Verson: 1.0.3                                                           **
 **                                                                         **
 ** *********************************************************************** **/

/// NOTE: do NOT compile your code with this "cpp". Its included anyway


/** *********************************************************************** **
 ** Init/error handling and little helper functions                         **
 ** *********************************************************************** **/
template <typename T>
void ATMSP<T>::init() {

	// Default functions all/complex
	funLst.push("abs");  funLst.push("cos");  funLst.push("cosh");
	funLst.push("exp");  funLst.push("log");  funLst.push("log10");
	funLst.push("log2"); funLst.push("sin");  funLst.push("sinh");
	funLst.push("sqrt"); funLst.push("tan");  funLst.push("tanh");

	// Default functions all/cmath
	#if !defined(COMPLEX)
	funLst.push("asin");  funLst.push("acos");  funLst.push("atan");
	funLst.push("atan2"); funLst.push("max");   funLst.push("min");
	funLst.push("sig");   funLst.push("floor"); funLst.push("round");
	#endif

	// Default constants
	#if !defined(MPFR)
	conLst.push(CONTYPE("$e",  T(2.718281828459045235360287471353L)));
	conLst.push(CONTYPE("$pi", T(3.141592653589793238462643383279L)));
	#else
	conLst.push(CONTYPE("$e",  exp(T(1.0))));
	conLst.push(CONTYPE("$pi", T(4.0) * (T(4.0)*atan(T(1.0)/T(5.0)) - atan(T(1.0)/T(239.0)))));
	#endif
	#if defined(COMPLEX)
	conLst.push(CONTYPE("$i", T(0.0, 1.0)));
	#endif

	// Error messages. NaN/inf needed for expressions like "1/0"
	errLst.push("Function/expression error");
	errLst.push("Variable/expression error");
	errLst.push("Constant error");
	errLst.push("Parenthesis error");
	errLst.push("Out of memory error");
	errLst.push("NaN/inf float error");
}

// Variable detection. Check if string-part after cp signs a var or function
template <typename T>
bool ATMSP<T>::isVar(const char *cp) {
	char *tmp = (char *)cp;
	while ( isalnum(*tmp) && *tmp++ );
	return (*tmp == '(' ? false : true);
}

// Variable/constant extraction. Return alphanumeric-string and advance cp
template <typename T>
std::string ATMSP<T>::skipAlphaNum() {
	char *start = cp;
	std::string alphaString(cp++);
	while ( isalnum(*cp) && *cp++ );
	return alphaString.substr(0, cp-start);
}


/** *********************************************************************** **
 ** Core parser stuff                                                       **
 ** *********************************************************************** **/
template <typename T>
size_t ATMSP<T>::parse(ATMSB<T> &bc, const std::string &exps, const std::string &vars) {

	// First always force recursion break on errors
	size_t eLevel = noErr;
	if ( (eLevel=setjmp(errJmp)) != noErr ) return eLevel;

	// Prepare clean expression and variable strings
	std::string::size_type pos, lastPos;
	std::string es(exps), vs(vars);
	pos = 0; while ( (pos=es.find(' '), pos) != std::string::npos ) es.erase(pos, 1);
	pos = 0; while ( (pos=vs.find(' '), pos) != std::string::npos ) vs.erase(pos, 1);
	if ( es.empty() ) longjmp(errJmp, funErr);
	cp = (char *) es.c_str();

	// Split comma separated variables into varLst
	// One instance can be parsed repeatedly. So clear() is vital here
	varLst.clear();
	pos = vs.find_first_of(',', lastPos = vs.find_first_not_of(',', 0));
	while ( std::string::npos != pos || std::string::npos != lastPos ) {
		if ( !varLst.push(vs.substr(lastPos, pos-lastPos)) ) longjmp(errJmp, memErr);
		pos = vs.find_first_of(',', lastPos = vs.find_first_not_of(',', pos));
	}

	// Static parenthesis check. "Abuse" free opCnt/varCnt as open/close-counters
	opCnt = varCnt = 0;
	for (size_t i=0; i<es.size(); i++)
		if ( es[i] == '(' )
			opCnt++;
		else if ( es[i] == ')' ) {
			varCnt++;
			if ( varCnt > opCnt ) longjmp(errJmp, parErr);
		}
	if ( opCnt != varCnt ) longjmp(errJmp, parErr);

	// Reset all our counters and indices
	// opCnt  = Operator count. For bytecode and memory checks
	// varCnt = Variable count. For check if we have a constant expression
	// valInd = All num, var and con values are mapped into the bytecode-val-array
	// numInd = Numerical numbers array index
	opCnt = varCnt = valInd = numInd = 0;    

	// Run it once for parsing and generating the bytecode
	expression(bc);
	bc.opCnt = opCnt;

	// No vars in expression? Evaluate at compile time then
	if ( !varCnt ) {
		bc.num[0] = bc.run();
		if ( bc.fltErr ) longjmp(errJmp, nanErr);
		bc.val[0] = &bc.num[0];
		bc.fun[0] = &ATMSB<T>::ppush;
		bc.opCnt = 1;
	}

	return noErr;
}

// Calculate expressions
template <typename T>
void ATMSP<T>::expression(ATMSB<T> &bc) {

	// Enter next recursion level
	term(bc);

	while ( *cp=='+' || *cp=='-' )
		if ( *cp++ == '+' ) {
			term(bc);
			bc.fun[opCnt++] = &ATMSB<T>::padd;
		}
		else {
			term(bc);
			bc.fun[opCnt++] = &ATMSB<T>::psub;
		}
}

// Calculate terms
template <typename T>
void ATMSP<T>::term(ATMSB<T> &bc) {

	// Enter next recursion level
	factor(bc);

	while ( *cp=='*' || *cp=='/' )
		if ( *cp++ == '*' ) {
			factor(bc);
			bc.fun[opCnt++] = &ATMSB<T>::pmul;
		}
		else {
			factor(bc);
			bc.fun[opCnt++] = &ATMSB<T>::pdiv;
		}
}

// Calculate factors
template <typename T>
void ATMSP<T>::factor(ATMSB<T> &bc) {

	/// Check available memory
	if ( numInd>=ATMSP_MAXNUM || valInd>=ATMSP_SIZE || opCnt>=ATMSP_SIZE ) longjmp(errJmp, memErr);

	/// Handle open parenthesis and unary minus first
	if ( *cp == '(' ) {
		++cp; expression(bc);
		if ( *cp++ != ')' ) longjmp(errJmp, parErr);
	}
	else if ( *cp == '-' ) {
		++cp; factor(bc);
		bc.fun[opCnt++] = &ATMSB<T>::pchs;
	}

	/// Extract numbers starting with digit or dot
	else if ( isdigit(*cp) || *cp=='.' ) {
		char *end;
		bc.num[numInd] = (T)strtod(cp, &end);
		bc.val[valInd++] = &bc.num[numInd++];
		bc.fun[opCnt++] = &ATMSB<T>::ppush;
		cp = end;
	}

	/// Extract constants starting with $
	else if ( *cp == '$' ) {
		if ( !conLst.find(skipAlphaNum(), conInd) ) longjmp(errJmp, conErr);
		bc.con[conInd] = conLst[conInd].val;
		bc.val[valInd++] = &bc.con[conInd];
		bc.fun[opCnt++] = &ATMSB<T>::ppush;
	}

	/// Extract variables
	else if ( isVar(cp) ) {
		if ( varLst.find(skipAlphaNum(), varInd) ) varCnt++; else longjmp(errJmp, varErr);
		bc.val[valInd++] = &bc.var[varInd];
		bc.fun[opCnt++] = &ATMSB<T>::ppush;
	}

	/// Extract functions
	else {

		// Search function and advance cp behind open parenthesis
		if ( funLst.find(skipAlphaNum(), funInd) ) ++cp; else longjmp(errJmp, funErr);

		// Set operator function and advance cp
		switch ( funInd ) {
			case  0: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pabs;    break;
			case  1: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pcos;    break;
			case  2: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pcosh;   break;
			case  3: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pexp;    break;
			case  4: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::plog;    break;
			case  5: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::plog10;  break;
			case  6: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::plog2;   break;
			case  7: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::psin;    break;
			case  8: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::psinh;   break;
			case  9: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::psqrt;   break;
			case 10: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::ptan;    break;
			case 11: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::ptanh;   break;
			#if !defined(COMPLEX)
			case 12: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pasin;   break;
			case 13: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pacos;   break;
			case 14: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::patan;   break;
			case 15: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::patan2;  break;
			case 16: expression(bc); ++cp; expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pmax; break;
			case 17: expression(bc); ++cp; expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pmin; break;
			case 18: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::psig;    break;
			case 19: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pfloor;  break;
			case 20: expression(bc); bc.fun[opCnt++] = &ATMSB<T>::pround;  break;
			#endif
		}
		++cp;
	}

	/// At last handle univalent operators like ^ or % (not implemented here)
	if ( *cp == '^' ) {

		// Exponent a positive number? Try to optimize later
		bool optPow = isdigit( *++cp ) ? true : false;
		if ( *(cp+1) == '^' ) optPow = false;
		factor(bc);

		// Speed up bytecode for 2^2, x^3 ...
		if ( optPow ) {
			if ( *bc.val[valInd-1] == (T)2.0 ) {
				--valInd;
				bc.fun[opCnt-1] = &ATMSB<T>::ppow2;
			}
			else if ( *bc.val[valInd-1] == (T)3.0 ) {
				--valInd;
				bc.fun[opCnt-1] = &ATMSB<T>::ppow3;
			}
			else if ( *bc.val[valInd-1] == (T)4.0 ) {
				--valInd;
				bc.fun[opCnt-1] = &ATMSB<T>::ppow4;
			}
			// Exponent is a positive number, but not 2-4. Proceed with standard pow()
			else
				bc.fun[opCnt++] = &ATMSB<T>::ppow;
		}
		// Exponent is a not a number or negative. Proceed with standard pow()
		else
			bc.fun[opCnt++] = &ATMSB<T>::ppow;
	}

} // End of factor(bc)
