/** @file MTParserPrivate.h
	@brief Internal declarations
	@author (c) 2008 Mathieu Jacques

	Put the implementation in this file (if needed) in order to avoid to
	have to use a .cpp file.  Clients of this file (like plug-ins) should
	not have to link with the library only to use basic services.
*/

#ifndef _MTPARSERPRIVATE_INCLUDED
#define _MTPARSERPRIVATE_INCLUDED

#include "MTParserPublic.h"
#include "MTParserExcepStrEng.h"
#include <windows.h>


/** @brief Throw a first exception without parent exception

	This macro puts the line number, the source file and a default description.
	
	@param	data		The data exception
*/
#define MTTHROW(/*MTExcepData */ data )													\
			{																			\
				MTSTRING desc = MTParserExcepStrEng::format(data);						\
				throw( MTChainedExceptions<MTExcepData>(	__LINE__, _T(__FILE__),		\
														0, data, desc.c_str()) );		\
			}

/** @brief Throw an exception with its parent exceptions

	This macro puts the line number, the source file and a default description.

	@param	data	The exception date to add to the chain
	@param	e		The parent exception
*/
#define MTRETHROW(/*MTExcepData */ data, /*parent MTChainedExceptions*/ e)				\
			{																			\
				MTSTRING desc = MTParserExcepStrEng::format(data);						\
				e.add(__LINE__,  _T(__FILE__), 0, data, desc.c_str()); throw(e);		\
			}												


/* @brief Structure that contains information about an expression item

	This structure is filled during the expression compilation and used by
	the evaluator.  So, this is a common structure between the compiler and the evaluator.
*/
struct SItemInfo
{
	MTParserItemI *pEval;			// item 
	
	MTDOUBLE val;					// if evaluated, the cached result
	
	bool isEvaluated;				// indicate whether this item has already been evaluated
									// if yes, then no need to evaluate it: just take the
									// cached value


	MTDOUBLE *pArg;					// argument buffer
	int nbArgs;						// number of arguments

	MTDOUBLE *pParentItemArg;		// pointer to the "parent" item argument that need the value
									// of this item to compute its value
	
	bool canDelete;					// indicate whether the object pointed by pEval must be deleted after use


	//****************************
	// variables used only during the validation step	
						
	int exprStrPos;		// for information purpose, the position of this item
						// in the expression string
	
	bool ignore;		

	//****************************		

	SItemInfo()
	{
		isEvaluated = false; 
		pEval = NULL; 
		pArg = NULL;
		nbArgs = 0;
		pParentItemArg = NULL;
		canDelete = false;		
		ignore = false;
	}	
};

typedef std::vector<SItemInfo> ItemInfoStack;
	

/** @brief Private Registrar Interface

	This is the whole registrar: client interface + interface services.
*/ 
class MTRegistrarI : public MTRegistrarPublicI
{
public:


	/** @brief Set the variable factory used to create variable object 
	
		Allows automatic variable definition.  The default factory creates variables with default values.
		@param	pFactory	Variable factory object.  This object will be automatically
							deleted at the end of the registrar life
	*/
	virtual void setVarFactory(MTVariableFactoryI *pFactory) = 0;	
	
	/** @brief Use the variable factory to create a new variable object associated with this name
		@param symbol: variable symbol to define			
	*/
	virtual void defineVar(const MTCHAR *symbol) throw(MTParserException) = 0;

	/** @brief Check whether a variable is defined
		@param	symbol	Variable symbol
		@return True if the variable is defined
	*/
	virtual bool isVarDefined(const MTCHAR *symbol)const = 0;


	/** @brief Find an operator with this symbol and this number of arguments
		@param	symbol			Operator symbol
		@param	unaryOp			Indicate if the operator must be a unaryOp
		@param	index			[out]	If an operator is found, this will be the operator index
		@return True if the operator exists
	*/
	virtual bool findOp(const MTCHAR *symbol, bool unaryOp, unsigned int &index)const = 0;
	
	/** @brief Check whether this name corresponds to a defined function
	
		There can be multiple functions with this name (overloaded functions).
		To find a specific function, use findFunction
		
		@param	word			Function name
		@param	index			[out]	If a function is found, this will be the function index
		@return True if the function exists
	*/
	virtual bool isAFunction(const MTCHAR *word, unsigned int &index)const = 0;
	
	/** @brief Find a function with this symbol and this number of arguments

		First try to find a function with this exact number of arguments.  If there is
		a function with undefined number of args, then that function will be returned
		by default if no other overloaded function have nbArgs arguments.

		@param	word			Function name
		@param	nbArgs			Function number of arguments
		@param	index			[out]	If a function is found, this will be the function index
		@return True is the function exists
	*/
	virtual bool findFunction(const MTCHAR *word, int nbArgs, unsigned int &index)const = 0;

	/** @brief Find all functions with this symbol

		@param	symbol			Function symbol
		@return all matching function objects
	*/
	virtual std::vector<MTFunctionI*> findFunctions(const MTCHAR *symbol)const = 0;

	/** @brief Find a function with this symbol and with this EXACT number of arguments
		@param	word			Function name
		@param	nbArgs			Function number of arguments
		@param	index			[out]	If a function is found, this will be the function index
		@return True is the function exists
	*/
	virtual bool findFunctionExact(const MTCHAR *word, int nbArgs, unsigned int &index)const = 0;

	/** @brief Find a constant from its name
		@param	constName	Constant name
		@param	index		[out] If the constant is found, this will be the constant index
		@return True if the constant exists
	*/
	virtual bool findConst(const MTCHAR *constName, unsigned int &index)const = 0;

	/** @brief Determine whether the string begins with an operator symbol

		@param	str				Source string
		@param	strLength		Source string length.  
		@param	symbol	[out]	If the string begins with an operator symbol, this will
								be the symbol
		@return True is the string begins with an operator symbol
	*/
	virtual bool areNextCharsOpString(const MTCHAR *str, unsigned int strLength, MTSTRING &symbol)const = 0;

	/** @brief Create a new instance of itself

		This method is used to duplicate a parser object.

		@return A new independant object representing the same registrar object
	*/
	virtual MTRegistrarI* spawn() throw(MTParserException) = 0;

	virtual ~MTRegistrarI(){};

};

/** @brief Private Compiler interface
*/
class MTCompilerI : public MTCompilerPublicI
{
public:

	/** @brief Enable or disable the automatic variable definition feature

		The automatic variable definition feature avoid having to define all variables
		upfront.   

		@param	enable		True = Enabled, False = Disabled
	*/
	virtual void enableAutoVarDefinition(bool enable) = 0;

	/** @brief Variable redefined event 

		A variable has been replaced, so we must replace its object.

		The expression is not resetted.

		@param	pVar	The new variable object.  It will be deleted after use.
	*/
	virtual void onVarRedefined(MTVariableI *pVar) throw(MTParserException) = 0;

	/** @brief Get the item stack 

		Contains the compiled expression, ready to be evaluated

		@return The item stack
	*/
	virtual ItemInfoStack* getItemStack() = 0;

	/** @brief Set the parent compiler to allow chained behaviours
		
		@param	pParent		The parent compiler.  This object must exist as long as
							the child exists.  This is an hard agregate relation.
	*/
	virtual void setParent( MTCompilerI *pParent ) = 0;

/** @name Compiler state services
* 
*/
	//@{

	/** @brief Add the current character to the current word */
	virtual void addCurChar() = 0;

	/** @brief Clear the curWord value */
	virtual void clearCurWord() = 0;

	/** @brief Get the current word */
	virtual const MTCHAR* getCurWord() = 0;

	/** @brief Get the current parsing position in the math formula*/
	virtual unsigned int getCurPos() = 0;

	/** @brief Push a value item on the stack
		@param	val	The value to be pushed
	*/
	virtual void pushValue(const MTDOUBLE &val) = 0;

	/** @brief Get the variable evaluator (stub) object associated with this variable

		This object must be used instead of the registrar variable object.  The stub
		doesn't call the evaluate method of the variable but returns a cached value.		 

		@param	symbol		The variable symbol
		@return The variable stub
	*/
	virtual MTVariableI* getVar(const MTCHAR *symbol) throw(MTParserException)= 0;

	/** @brief Push a variable item on the stack
		@param	varName	The variable name to be pushed
	*/
	virtual void pushVariable(const MTCHAR *varName) throw(MTParserException) = 0;

	/** @brief Push a function item on the stack
	
		The function arguments must have been pushed before.

		@param	funcName	The function name
		@param	nbArgs		The number of arguments actually used by the function.  May be
							different from the function definition.  For example, if the
							function takes an undefined number of arguments.
	*/
	virtual void pushFunction(const MTCHAR *funcName, unsigned int nbArgs) throw(MTParserException) = 0;

	/** @brief Push this function instance on the stack
	
		This object will be pushed on the stack.  The compiler own the object and will delete
		it when necessary. The function arguments must have been pushed before.

		@param	pFunc		The function instance
		@param	nbArgs		The number of arguments actually used by the function.  May be
							different from the function definition.  For example, if the
							function takes an undefined number of arguments.
	*/
	virtual void pushFunction(MTFunctionI *pFunc, unsigned int nbArgs) throw(MTParserException) = 0;

	/** @brief Compile a function argument and push it on the stack

		@param	arg		The argument.  This can be any expression.
	*/
	virtual void pushFuncArg(const MTCHAR *arg) throw(MTParserException) = 0;
 
	/** @brief Exit of the current compiler state
	
		Tell to the compiler that the current compiler state
		execution is finished.
	*/	
	virtual void exitState() = 0;

	/** @brief Throw a parsing exception */
	virtual void throwParsingExcep(const MTCHAR * id, const MTCHAR *itemName)const throw(MTParserException) = 0;	
	
	/** @brief Throw a parsing exception */
	virtual void throwParsingExcep(const MTCHAR * id, int pos)const throw(MTParserException) = 0;
	
	/** @brief Throw a parsing exception */
	virtual void throwParsingExcep(const MTCHAR * id, int pos, const MTCHAR *itemName)const throw(MTParserException) = 0;

	/** @brief Throw a parsing exception */
	virtual void throwParsingExcep(const MTCHAR * id, int pos, const MTCHAR *itemName, int param)const throw(MTParserException) = 0;
	

	//@}

	/** @brief Create a new instance of itself

		This method is used to duplicate a parser object.

		@return A new independant object representing the same compiler object
	*/
	virtual MTCompilerI* spawn(class MTRegistrarI *pRegistrar) throw(MTParserException) = 0;

	virtual ~MTCompilerI(){};

};

/** @brief Compiler state Interface 
	
	Allows the customization of the main compiler.  This could be used
	to define functions needing a special syntax.
*/
class MTCompilerStateI
{
public:

	MTCompilerStateI(){ m_pCompiler = NULL; m_pRegistrar = NULL; }	

	/** @brief Called when entering the state */
	virtual void enter(MTCompilerI *pCompiler, MTRegistrarI *pRegistrar)
	{
		m_pCompiler = pCompiler;
		m_pRegistrar = pRegistrar;
	}

	/** @brief Called when the end of the math formula is reached */
	virtual void onEndOfFormula(){};

	/** @brief Compile a character

		This allows a by character compilation.  If you compile a character the default
		parser will not process it and consequently, the event callbacks will not be called.

		@param	c	The current character to compile
		@return true if the character has been compiled
	*/
	virtual bool compileChar(const MTCHAR &c){ return false; }

/** @name Token Events
* Multiple parser event callbacks.
*/
	//@{
	
	/** @brief Called when an operator is detected 
		@param	opSymbol	The detected operator symbol
	*/
	virtual void onOp(const MTSTRING &opSymbol){ m_pCompiler->addCurChar(); }
	
	/** @brief Called when an open bracket is detected */
	virtual void onOpenBracket(){ m_pCompiler->addCurChar(); }
	
	/** @brief Called when a close bracket is detected */
	virtual void onCloseBracket(){ m_pCompiler->addCurChar(); }	
	
	/** @brief Called when an argument separator is detected */
	virtual void onArgSeparator(){ m_pCompiler->addCurChar(); }

	//@}

	virtual ~MTCompilerStateI(){};

protected:

	MTCompilerI *m_pCompiler;
	MTRegistrarI *m_pRegistrar;
};

/** @brief Conversion Function Interface

	A conversion function is used to convert a string value to
	a double value. For example, convert an hexadecimal value to a decimal
	value.  A conversion function is constant, that is it cannot have variable
	argument.  

	This class is a template to simplify the writing of conversion functions.
	It implements a custom compiler and exposes some functions needed by conversion
	functions.
	
*/
class MTConvFunctionI : public MTFunctionI, public MTCompilerStateI
{
public:	

	/** @brief Do the conversion
	
		Convert the string value to a double value.	This method will be called
		when the compiling is done.  To indicate a conversion error, 
		call throwConversionExcep function.

		@param	val		String value to be converted
		@return The double value represented by the string	
	*/
	virtual MTDOUBLE convert(const MTSTRING &val) throw(MTParserException) = 0;


	//**********************************
	// MTCompilerStateI implementation

	virtual void enter(MTCompilerI *pCompiler, MTRegistrarI *pRegistrar)
	{			
		MTCompilerStateI::enter(pCompiler, pRegistrar);
		m_beginPos = m_pCompiler->getCurPos();
	}

	virtual void onCloseBracket(){		
		
		try
		{
			MTDOUBLE val = convert(m_pCompiler->getCurWord());
			m_pCompiler->pushValue(val);
			m_pCompiler->clearCurWord();	
			m_pCompiler->exitState();
		}
		catch( MTParserException )
		{
			m_pCompiler->throwParsingExcep(MTPARSINGEXCEP_InvalidFuncSyntax, m_pCompiler->getCurPos()-lstrlen(m_pCompiler->getCurWord()), getSymbol(), 1); 		
		}

	}

	virtual void onEndOfFormula()
	{
		// missing closing bracket!
		m_pCompiler->throwParsingExcep(MTPARSINGEXCEP_MissingCloseBracket, m_beginPos);
	}


	
	//**********************************
	// MTFunctionI implementation
	
	virtual int getNbArgs(){ return 1; }

	virtual class MTCompilerStateI* getCompilerState(){ return this; }

	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
	{
		return 0;
	}
	
	virtual ~MTConvFunctionI(){};

protected:

	/** @brief Throw a conversion exception

		Indicate that an error occured during the conversion.
	*/
	void throwConversionExcep() throw(MTParserException){
		m_pCompiler->throwParsingExcep(MTPARSINGEXCEP_InvalidFuncSyntax, 0, getSymbol(), 1); 			
	}

private:

	unsigned int m_beginPos;

};

/** @brief Function Parameter Tokenizer

	This is an helper class that separate each
	function argument and allow to acces them individually.

	Once the parameters have been parsed, the client	
	init method is called and the object is pushed into the compiler stack.  
	This way, functions can have their own state.	

	*The implementation is on the header file to allow plug-ins to only
	include this file without having to link with the library.
*/
class MTFctParamTokenizer : public MTCompilerStateI
{
public:

	/* @brief Function that use the param tokenizer services

		That kind of function can maintain its own state since there will be
		one instance for each occurence of the function in the formula.  For example,
		in the formula "fct()+fct()", there will be two fct objects.
	*/
	class ClientFctI : public MTFunctionI
	{
	public:

		ClientFctI(){ m_pTokenizer = NULL; }

		/* @brief Initialize the function

			The parameters will constitute the function state.

			@param	params		The parsed parameters
			@param	pCompiler	The current compiler object
			@param	pRegistrar	The current registrar object	
			@param	pos			The function beginning position in the math expression
		*/
		virtual void init(std::vector<MTSTRING> params, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar, unsigned int pos) throw(MTParserException) = 0;

		virtual MTCompilerStateI* getCompilerState()
		{
			if( m_pTokenizer == NULL )
			{
				m_pTokenizer = new MTFctParamTokenizer();
				if( m_pTokenizer == NULL )
				{
					// out of memory
					return NULL;
				}
			}			

			m_pTokenizer->setClient((ClientFctI*)spawn());

			return m_pTokenizer;
		}

		virtual ~ClientFctI()
		{ 
			if( m_pTokenizer != NULL )
			{				
				delete m_pTokenizer;
				m_pTokenizer = NULL;	
			}
		}
		
	private:

		MTFctParamTokenizer *m_pTokenizer;

	};
public:

	
	MTFctParamTokenizer(){ m_pFct = NULL; }

	/* @brief Set the client function

		@param	pFct	Must be a new function object.  This object will be owned by the
						compiler, so it will automatically be deleted after use.
	*/
	void setClient(ClientFctI *pFct)
	{
		clean();
		m_pFct = pFct;
	}


	//**********************************
	// MTCompilerStateI implementation

	virtual void enter(MTCompilerI *pCompiler, MTRegistrarI *pRegistrar)
	{
		MTCompilerStateI::enter(pCompiler, pRegistrar);

		m_params.clear();
		m_bracketCount = 1;	// we count the function opening bracket	
		m_beginPos = m_pCompiler->getCurPos();
	}

	virtual void onEndOfFormula()
	{
		// missing arguments!
		m_pCompiler->throwParsingExcep(MTPARSINGEXCEP_MissingCloseBracket, m_beginPos);
	}

	virtual void onOpenBracket()
	{
		m_bracketCount++;
		m_pCompiler->addCurChar();
	}
	virtual void onCloseBracket()
	{
		m_bracketCount--;
		if( m_bracketCount == 0 )
		{
			// end of function

			// add the last parameter...
			m_params.push_back(m_pCompiler->getCurWord());
			m_pCompiler->clearCurWord();
			m_pCompiler->exitState();

			// the init method can recall this compiler object with another client, so 
			// after this point we can't use actual member variable values.  
			ClientFctI *pFct = m_pFct;
			m_pFct = NULL;
								
			try
			{			
				pFct->init(m_params, m_pCompiler, m_pRegistrar, m_beginPos);
			}		
			catch( MTParserException &e )
			{			
				delete pFct;				
				throw(e);		// rethrow the same exception
			}				

			m_pCompiler->pushFunction(pFct, pFct->getNbArgs());		
		}
		else
		{
			m_pCompiler->addCurChar();
		}
	}
	virtual void onArgSeparator()
	{
		// if parsing at our function level 
		if( m_bracketCount == 1 )
		{	
			m_params.push_back(m_pCompiler->getCurWord());
			m_pCompiler->clearCurWord();
		}
		else
		{
			m_pCompiler->addCurChar();
		}
	}

	~MTFctParamTokenizer(){clean();}

private:

	void clean()
	{
		// if the function has not been used, delete it
		if( m_pFct != NULL )
		{
			delete m_pFct;
			m_pFct = NULL;
		}
	}

private:

	std::vector<MTSTRING> m_params;	
	unsigned int m_bracketCount;	
	unsigned int m_beginPos;
	ClientFctI *m_pFct;

};


#endif