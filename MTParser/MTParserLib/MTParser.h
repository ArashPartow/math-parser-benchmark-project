/** @file MTParser.h
	@brief Main parser interface file
	@author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSER_INCLUDED
#define _MTPARSER_INCLUDED

#include "MTParserPublic.h"


/** @brief Main class to evaluate mathematical string expressions 

	This class is a facade in front of a registrar and a compiler.
	Its main purpose is to ease the use of these two entities and to 
	defines special user-centred methods.

*/
class MTParser : public MTRegistrarPublicI, public MTCompilerPublicI
{
public:

//###############################################
/** @name Create and Initialize a parser object
* Use default configuration or copy an existing object configuration
*/
	//@{

	/** @brief Initialize the object with the default configuration 
	*/
	MTParser();	
	
	/** @brief Initialize the object using the configuration of an existing object. 
	
		The existing parser will be duplicated with all its defined items: functions, operators,
		constants, variables, macros, syntax and settings.  The expression is also copied.

		@param	obj		Existing parser object
	*/	
	MTParser(const MTParser &obj) throw(MTParserException);	

	/** @brief Initialize the object using this compiler and registrar
	
		The existing compiler and registrar will be duplicated with all their defined items: functions, operators,
		constants, variables, macros, syntax and settings.  The math expression is not copied.

		@param	pCompiler		Existing compiler object
		@param	pRegistrar		Existing registrar object
	*/		
	MTParser(class MTCompilerI *pCompiler, class MTRegistrarI *pRegistrar) throw(MTParserException);	
	
	/** @brief Re-initialize the object using the configuration of an existing object.
	
		The existing parser will be duplicated with all its defined items: functions, operators,
		constants, variables, macros, syntax and settings. The expression is also copied.

		@param	obj		Existing parser object
	*/	
	MTParser& operator=(const MTParser &obj) throw(MTParserException);		

	//@}


//###############################################
/** @name Evaluate mathematical expressions
* One-time evaluation, multiple evaluations with expression compilation
*/
	//@{
	
	/** @brief Compile and evaluate an expression and get the result, all in
		one call.  This is the same as calling compile first and then evaluate().

		@param	expr	A mathematical expression	
		@return	the result of the evaluation
	*/
	virtual MTDOUBLE evaluate(const MTCHAR *expr) throw(MTParserException);

	virtual void compile(const MTCHAR *expr) throw(MTParserException);

	/** @brief Evaluate the last compiled math expression 

		The expression may have been previously compiled by a call to the evaluate method with an expression
		or the compile method.

		NOTE:  No dynamic memory allocation.  Memory has been allocated during the
		compilation step.

		@return The result of the current expression evaluated with the current variable' values
	*/
	virtual MTDOUBLE evaluate()const;

	/** @brief Evaluate multiple times the last compiled expression

		This is a "batch" evaluation.  When you have a set of values this is
		the fastest way of evaluating an expression for each value.  Use the 
		MTDoubleVector class to store your variable values.

		NOTE:  No dynamic memory allocation.  Memory has been allocated during the
		compilation step.

		@param	nbEvals		The number of times to evaluate the expression
        @param	pResults	[out] The result array which will contain the result
							of each evaluation.  The array must be large enough to 
							receive all results.							
		
	*/
	virtual void evaluateBatch(unsigned int nbEvals, MTDOUBLE *pResults);

	virtual bool isConstant()const;

	/** @brief Test whether the result of the last evaluation is finite

		A finite number is greater than -INF and smaller than +INF.  A NaN value
		is infinite.  An infinite number means that an evaluation 
		error occured.  For example a division by zero yields an infinite result.

		@return true if the number is finite, else returns false
	*/
	virtual bool isFinite()const; 

	/** @brief Test whether the result of the last evaluation is a NaN value

		NaN value can be used to indicate an evaluation error or an uninitialized object.  The
		isFinite method is more general while a NaN value is a special type of infinite number.
		NaN stands for "Not a Number".
		
		@return True if this value is a NaN value
	*/
	virtual bool isNaN()const;	

	virtual MTSTRING getExpression()const;	
	virtual void resetExpression();

	//@}

//###############################################
/** @name Manage variables
* Define/Undefine variables, get used variables and set the auto variable definition feature
*/
	//@{

	/** @brief Define a variable and its value pointer. 
	
		This is the most common way of defining a variable.
		At evaluation time, value will be get from this value pointer.
		This is a mechanic used to speed up variable evaluation, and allow
		you to manage variable values of multiple expressions easily (values
		can be shared between multiple expression objects).
		At anytimes during evaluation, values are assumed to be valids (valid pointers).	

		@param	symbol	Variable symbol.  At least one alpha character
		@param	pVal	Variable value pointer		
		@return The key associated with the defined variable to allow fast access 
	*/
	virtual void defineVar(const MTCHAR *symbol, MTDOUBLE *pVal) throw(MTParserException);	
	
	virtual void defineVar(MTVariableI *pVar) throw(MTParserException);
	
	/** @brief Redefine a defined variable

		Replace a variable by a new one.  This is 
		useful to redefine variables that have been automatically defined.

		The expression is not resetted.

		@param	symbol	Variable symbol to be replaced
		@param	pVal	A new variable value pointer		
	*/
	virtual void redefineVar(const MTCHAR *symbol, MTDOUBLE *pVal) throw(MTParserException);
	
	virtual void redefineVar(MTVariableI *pVar) throw(MTParserException);
	virtual void undefineVar(const MTCHAR *symbol) throw(MTParserException);	
	virtual void undefineAllVars();
	virtual MTVariableI* getVarBySymbol(const MTCHAR *symbol)const throw(MTParserException);			
	virtual MTVariableI* getVar(unsigned int index)const throw(MTParserException);
	virtual unsigned int getNbDefinedVars()const;

	virtual unsigned int getNbUsedVars()const;
	virtual MTSTRING getUsedVar(unsigned int index)const;

	/** @brief Enable or disable the automatic variable definition feature

		The automatic variable definition feature avoid having to define all variables
		upfront.   

		@param	enable		True = Enabled, False = Disabled
		@param	pFactory	If the feature is enabled, provide a variable factory to create custom variable object type.
							Your factory will be called each time a variable need to be defined. 
							This allows you to create the right variable type, just-in-time. 
	*/	
	virtual void enableAutoVarDefinition(bool enable, MTVariableFactoryI *pFactory = NULL);

	virtual bool isAutoVarDefinitionEnabled()const;

	//@}

//###############################################
/** @name Extend the parser
* Define custom constants, function, macros and operators
*/
	//@{
	
#ifdef _MTPARSER_USE_PLUGIN
	virtual void loadPlugin(const MTCHAR *clsid) throw(MTParserException);
	
	/** @brief Load all plug-ins defined in info files
	
		Look for plug-in info files and automatically try to load them using the CLSID string
		in the info files.  Doesn't load localized resources.  Use the localizer to do so.

		@param	directory		The directory where to look for plug-in info files.  Sub-directories will be searched too.
		@param	searchPattern	File search pattern like *.xml or *.*.

		If files match the search pattern but are not valid info files then an exception will be thrown.
	*/
	virtual void loadAllPlugins(const MTCHAR *directory, const MTCHAR *searchPattern) throw(MTParserException);
#endif
	virtual void defineConst(const MTCHAR *name, MTDOUBLE val) throw(MTParserException);
	virtual unsigned int getNbDefinedConsts()const;
	virtual void getConst(unsigned int index, MTSTRING &constName, MTDOUBLE &val)const throw(MTParserException);		
	virtual void undefineConst(const MTCHAR *name) throw(MTParserException);
	virtual void defineFunc( MTFunctionI *pFunc) throw(MTParserException);

	/** @brief Define a macro function
	
		A macro can use any defined items and can have any number of arguments.  The argument
		list will be automatically created from the macro function variables.  A macro is 
		handled like a function.  So it will appear in the function list. 

		Use the undefineFunc method to undefine a macro.

		@param	prototype	The macro prototype.  The proper syntax is: macro(arg1, arg2, arg3...)
		@param	macro		The macro function
		@param	description A short macro description
	*/
	virtual void defineMacro(const MTSTRING &prototype, const MTSTRING &macro, const MTSTRING &description )throw(MTParserException);
	
	virtual unsigned int getNbDefinedFuncs()const;
	virtual MTFunctionI* getFunc(unsigned int index)const throw(MTParserException);
	virtual void undefineFunc(MTFunctionI *pFunc) throw(MTParserException);
	
	/** @brief Undefine the function with this id

		@param	id	function id
	*/
	virtual void undefineFuncById(const MTCHAR *id) throw(MTParserException);

	/** @brief Undefine all functions with this symbol

		@param	symbol	function symbol		
	*/
	virtual void undefineFuncsBySymbol(const MTCHAR *symbol) throw(MTParserException);

	virtual void defineOp( MTOperatorI *pOp) throw(MTParserException);	
	virtual unsigned int getNbDefinedOps()const;	
	virtual MTOperatorI* getOp(unsigned int index)const throw(MTParserException);	
	virtual void undefineOp(MTOperatorI *pOp) throw(MTParserException);

	/** @brief Undefine the operator with this id

		@param	id	operator id
	*/	
	virtual void undefineOpById(const MTCHAR *id) throw(MTParserException);

	/** @brief Undefine all operators with this symbol

		@param	symbol	operator symbol		
	*/	
	virtual void undefineOpsBySymbol(const MTCHAR *symbol) throw(MTParserException);
	
	//@}

	
//###############################################
/** @name Internationalize the parser
* Configure the parser syntax or use the user current settings
*/
	//@{	

	/** @brief Set the syntax accordingly to the locale settings 
	
		Actually, only the decimal and the argument separator characters are set.
		The user locale is obtained through the current thread locale. 
	*/
	virtual void useLocaleSettings() throw(MTParserException);

	virtual void setSyntax(const MTSyntax &syntax) throw(MTParserException);
	
	virtual MTSyntax getSyntax()const;	

	//@}
	
//###############################################
/** @name Miscellaneous
* NaN value, internal objects
*/
	//@{	
	
	/** @brief Get a NaN value 

		NaN stands for "Not a Number".  A NaN value can be returned to indicate an 
		evaluation error.	 

		@return A NaN value
	*/
	virtual MTDOUBLE getNaN()const;	

	/** @brief Get the registrar */
	class MTRegistrarI* getRegistrar()const;
	
	/** @brief Get the compiler */
	class MTCompilerI* getCompiler()const;

	//@}
	
	virtual ~MTParser();
	
private:

	/** @brief Re-initialize the object using this compiler and registrar
	
		The existing compiler and registrar will be duplicated with all their defined items: functions, operators,
		constants, variables, macros, syntax and settings.  The math expression is not copied.

		@param	pCompiler		Existing compiler object
		@param	pRegistrar		Existing registrar object
	*/		
	virtual void copy(class MTCompilerI *pCompiler, class MTRegistrarI *pRegistrar);
	

private:

	/** @brief Memory Variable evaluator	

		Default variable object that gets its value through a memory pointer. 
	*/
	class MemVariableEvaluator : public MTVariableI
	{
	public:

		/** @brief Set the variable symbol represented by this object
			@param	symbol	The variable symbol
		*/
		void setSymbol( const MTCHAR *symbol ){ m_symbol = symbol; }
		
		/** @brief Set the value pointer

			The variable value will be get from this pointer

			@param	pVal	The value pointer
		*/
		void setValPtr( MTDOUBLE *pVal){m_pVal = pVal; }

		/** @brief Set the value pointer to the default intern pointer
		*/
		void setDefValPtr(){ m_pVal = &m_defValue; }

		//*********************************
		// MTVariableI interface

		virtual const MTCHAR* getSymbol(){ return m_symbol.c_str(); }		
		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg){ return *m_pVal; }
		
		virtual MTVariableI* spawn();
		

		MemVariableEvaluator(){ m_defValue = 0; }

	private:

		MTDOUBLE *m_pVal;		// value pointer
		MTSTRING m_symbol;		// variable symbol
		MTDOUBLE m_defValue;	// default value when spawning

	};

	/** @brief Memory variable factory

		Default memory variable factory
	*/
	class MemVariableFactory : public MTVariableFactoryI
	{
	public:

		//! Create a default variable object
		virtual MTVariableI* create(const MTCHAR *newVarName)
		{
			MemVariableEvaluator *pEval = new MemVariableEvaluator();
			if( pEval == NULL )
			{
				// out of memory
				return NULL;
			}
			pEval->setDefValPtr();
			pEval->setSymbol(newVarName);
			return pEval;
		}

		virtual MTVariableFactoryI* spawn();

	};

	
private:

	//! Define default operators
	void defineDefOps() throw(MTParserException);
	
	//! Define default functions
	void defineDefFuncs() throw(MTParserException);

	//! Define default constants
	void defineDefConsts();

	//! Memory clean-up
	void clean();

	//! General initialization
	void init();

	//! Compute the begin and end item iterators used in the evaluation
	void computeExpressionIterator();	

	//! Get the last evaluated result or NaN
	MTDOUBLE getLastResult()const;

private:

	class MTRegistrarI *m_pRegistrar;						// registrar object
	class MTCompilerI *m_pCompiler;							// copiler object	
	
	std::vector<struct SItemInfo> *m_pItemStack;			// compiled expression
	std::vector<struct SItemInfo>::iterator m_beginIter;	// pre-computed first item to evaluate
	std::vector<struct SItemInfo>::iterator m_endIter;		// pre-computed last item to evaluate
	unsigned int m_itemStackSize;							// cached item stack size
	
	double m_constValue;									// if the expression is constant, this is the constant value	
};


/** @brief Variable of type double with multiple values 
	
	Allows batch evaluations.

	For each evaluate call, one value in the vector will be returned.  If 
	no more value is available, then NaN is returned.
*/ 
class MTDoubleVector : public MTVariableI
{
public:

	MTDoubleVector(const MTCHAR *symbol);

	/* @brief Set the value vector
	
		@param	pValues		The value pointer.  Values are not duplicated so the pointer
							must be valid for all the variable life.
		@param	nbValues	The number of values pointed by pValues
	*/
	void setValues(MTDOUBLE *pValues, unsigned int nbValues);

	/* @brief Reset the get position to zero
		
		This is the position in the vector where the next value will
		be pulled from.
	*/
	void resetGetPosition();
	
	//*********************************
	// MTVariableI interface
	
	virtual MTVariableI* spawn();

	virtual const MTCHAR* getSymbol(){ return m_symbol.c_str(); }
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);

private:

	MTDOUBLE *m_pValues;			// value vector
	unsigned int m_nbValues;		// number of values pointed by m_pValues
	unsigned int m_pos;				// current value position
	MTSTRING m_symbol;				// variable symbol
};




#endif