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
 ** Verson: 1.0.4                                                           **
 **                                                                         **
 ** *********************************************************************** **/

#ifndef _ATMSP_H_INCLUDED_
#define _ATMSP_H_INCLUDED_

/** Includes **/
#include <string>          // C++ strings
#include <csetjmp>         // longjump()
#include <cstdlib>         // strtod()
#include <cmath>           // Math. functions
#include "atmsp.base.h"    // Basic parser settings and stack/list-stuff


/** *********************************************************************** **
 **                                                                         **
 ** Bytecode struct. Executes the bytecode produced by the parser. Once     **
 ** the bytecode contains a valid set of instructions, it acts completely   **
 ** independent from the parser itself.                                     **
 **                                                                         **
 ** *********************************************************************** **/
template <typename T>
struct ATMSB {

	/// Push num, var and con values onto the stack
	void ppush()  { stk.push(*val[valInd++]); }

	/// Most basic operators working for nearly any type. So int's, bignums, SSE2, ..
	void padd()   { T t(stk.pop()); stk.setTop(t+stk.top()); }
	void psub()   { T t(stk.pop()); stk.setTop(stk.top()-t); }
	void pmul()   { T t(stk.pop()); stk.setTop(t*stk.top()); }
	void pdiv()   { T t(stk.pop()); t!=(T)0 ? stk.setTop(stk.top()/t) : stk.setTop(T((fltErr=1)-1)); }

	template <typename TT>
	TT     atmsb_mod(TT t0, TT t1)          { return t0 % t1; }
	double atmsb_mod(double t0, double t1)  { return std::fmod  (t0,t1); }
	float  atmsb_mod(float t0, float t1)    { return std::fmodf (t0,t1); }
	long double atmsb_mod(long double t0, long double t1) { return std::fmodld(t0,t1); }
	void pmod()   { T t(stk.pop()); t!=(T)0 ? stk.setTop(atmsb_mod(stk.top(),t)) : stk.setTop(T((fltErr=1)-1)); }
	   
	void pchs()   { stk.setTop(-stk.top()); }

	#if !defined(COMPLEX) && !defined(MPFR)
	void pabs()   { stk.setTop(std::abs(stk.top())); }
	#else
	void pabs()   { stk.setTop(abs(stk.top())); }
	#endif

	#if !defined(COMPLEX)
	void psqrt()  { T t(stk.top()); t>=(T)0 ? stk.setTop(sqrt(t)) : stk.setTop(T((fltErr=1)-1)); }
	#else
	void psqrt()  { stk.setTop(sqrt(stk.top())); }
	#endif

	void ppow()   { T t(stk.pop()); stk.setTop(pow(stk.top(), t)); }
	void ppow2()  { stk.setTop(stk.top()*stk.top()); }
	void ppow3()  { stk.setTop(stk.top()*stk.top()*stk.top()); }
	void ppow4()  { stk.setTop((stk.top()*stk.top()) * (stk.top()*stk.top())); }

	/// Basic operators even working for compilers like MSVC
	void psin()   { stk.setTop(sin(stk.top())); }
	void pcos()   { stk.setTop(cos(stk.top())); }
	void ptan()   { stk.setTop(tan(stk.top())); }

	void psinh()  { stk.setTop(sinh(stk.top())); }
	void ptanh()  { stk.setTop(tanh(stk.top())); }
	void pcosh()  { stk.setTop(cosh(stk.top())); }

	void pexp()   { stk.setTop(exp(stk.top())); }
	void plog()   { stk.setTop(log(stk.top())); }
	void plog10() { stk.setTop(log10(stk.top())); }
	void plog2()  { stk.setTop(log10(stk.top())/log10((T)2)); }

	/// More basic operators, but not for complex
	#if !defined(COMPLEX)
	void pasin()  { T t(stk.top()); t>=(T)-1 && t<=(T)1 ? stk.setTop(asin(stk.top())) : stk.setTop(T((fltErr=1)-1)); }
	void pacos()  { T t(stk.top()); t>=(T)-1 && t<=(T)1 ? stk.setTop(acos(stk.top())) : stk.setTop(T((fltErr=1)-1)); }
	void patan()  { stk.setTop(atan(stk.top())); }
	void patan2() { T t(stk.pop()); stk.setTop(atan2(stk.top(), t)); }

	void pmax()   { T t(stk.pop()); if (t>stk.top()) stk.setTop(t); }
	void pmin()   { T t(stk.pop()); if (t<stk.top()) stk.setTop(t); }
	void psig()   { stk.top()>(T)0 ? stk.setTop((T)1) : stk.top()<(T)0 ? stk.setTop((T)-1) : stk.setTop((T)0); }

	void pfloor() { stk.setTop(floor(stk.top())); }
	void pround() { stk.setTop(floor(stk.top()+(T)0.5)); }
	#endif

	/// Indices, stack and pointers to functions for operating on bytecode
	size_t opCnt, valInd;
	ATMSP_STACK<T> stk;
	void (ATMSB<T>::*fun[ATMSP_SIZE])();

	/// All num, var and con values are consecutively mapped into the val-array.
	/// So in run() the bytecode operators work on the val-array only
	T *val[ATMSP_SIZE];
	T num[ATMSP_MAXNUM];
	T var[ATMSP_MAXVAR];
	T con[ATMSP_MAXCON];

	/// Catch NaN/inf-errors for x/0 et al. 0==success, 1 else
	size_t fltErr;

	/// Bytecode execution
	T run() {
		stk.clear(); valInd = fltErr = 0;
		for (size_t i=0; i<opCnt; i++) (*this.*fun[i])();
		return stk.top();
	}
};


/** *********************************************************************** **
 **                                                                         **
 ** Parser class. Parses a string and generates the bytecode. For certain   **
 ** kind of strings ("x^2", ...) the bytecode is optimzed for speed.        **
 **                                                                         **
 ** *********************************************************************** **/
template <typename T>
class ATMSP {

	/// Search-helper for constant list
	struct CONTYPE {
		std::string name;
		T val;

		CONTYPE() : val((T)0) {}
		CONTYPE(const std::string &n) : name(n), val((T)0) {}
		CONTYPE(const std::string &n, T v) : name(n), val(v) {}

		bool operator == (const CONTYPE &ct) { return name == ct.name; }
	};

	/// Recursive bytecode generation
	char *cp;                         // Character-pointer for parsing
	void expression(ATMSB<T> &bc);    // Handle expression as 1.st recursion level
	void term(ATMSB<T> &bc);          // Handle terms as 2.nd recursion level
	void factor(ATMSB<T> &bc);        // Handle factors as last recursion level

	/// Little helper functions
	bool isVar(const char *cp);       // Variable detection
	std::string skipAlphaNum();       // Variable/constant extraction

	/// Error handling and inits
	enum { noErr, funErr, varErr, conErr, parErr, memErr, nanErr };
	jmp_buf errJmp;                   // Buffer address for leaving recursions on error
	void init();                      // Init function, constant and error message lists

	/// Basic counters and indices
	size_t opCnt, varCnt, valInd, numInd, varInd, conInd, funInd;

	/// Lists. Note: 6/21 hardcoded here for not to waste any memory
	ATMSP_LIST<std::string, 6> errLst;               // Our 6 error messages
	ATMSP_LIST<std::string, 21> funLst;              // Our 21 recognized functions abs..tanh
	ATMSP_LIST<std::string, ATMSP_MAXVAR> varLst;    // Extracted variables from varString "x,y,.."
	ATMSP_LIST<CONTYPE, ATMSP_MAXCON> conLst;        // Our constants. $e and $pi are default

public:

	/// Constructor. Creates our lists funLst, conLst and errLst
	ATMSP() { init(); }

	/// Add constant to the parser. $pi and $e are yet default. $i for complex only
	/// Returns noErr==0 on success, error code else
	size_t addConstant(const std::string &name, T value) {
		return name[0]!='$' ? conErr : (conLst.push(CONTYPE(name, value)) ? noErr : memErr);
	}

	/// Parse and simultaneously generate bytecode
	/// Returns noErr==0 on success, error code else
	size_t parse(ATMSB<T> &bc, const std::string &exp, const std::string &vars);

	/// Message error-string for a specific error number
	const std::string errMessage(size_t errNum) { return errLst[errNum-1]; }
};


/** We use templates, so include the whole code here! **/
#include "atmsp.cpp"

#endif    // _ATMSP_H_INCLUDED_
