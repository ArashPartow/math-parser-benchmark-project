/** @file MTParserPublic.h
	@brief Common public type and interface declarations
	@author (c) 2008 Mathieu Jacques

	*Put the implementation in this file (if needed) in order to avoid to
	have to use a .cpp file.  Clients of this file (like plug-ins) should
	not have to link with the library only to use basic services.

	*Avoid using complex third party types because there may be compatibility problems when
	developing plug-ins.  Particularly, the VC6 stl is not compatible with the
	VC7 one at the binary level.  
	
*/

#ifndef _MTPARSERPUBLIC_INCLUDED
#define _MTPARSERPUBLIC_INCLUDED

//! Enable plug-in extension.  If not needed, comment the define.
#define _MTPARSER_USE_PLUGIN

//! Enable localization.  If not needed, comment the define.
#define _MTPARSER_USE_LOCALIZATION

#pragma warning( disable : 4786 )		// disable the debug info truncated warning
#pragma warning( disable : 4290 )		// disable "c++ exception specification ignored except to indicate a function is not __declspec(nothrow)"

#include "MTUnicodeANSIDefs.h"
#include "MTParserException.h"
#include "MTGlobalString.h"
#include <vector>
#include <windows.h>

/** @brief The current interface version
	
	This number must be incremented each time an interface is changed.
	Plug-ins must have been compiled with a compatible MTParser version in
	order to be able to run properly.

	Since different objects are used in debug and release mode, the version
	string must be different. For example, a std::string in debug is not the
	same as a std::string in release.
*/
#ifdef UNICODE
	#ifdef _DEBUG	
		// Unicode Debug
		#define MTPARSER_INTERFACE_VERSION	_T("14Ud")
	#else
		// Unicode Release
		#define MTPARSER_INTERFACE_VERSION	_T("14U")			
	#endif
#else
	#ifdef _DEBUG	
		// ANSI Debug
		#define MTPARSER_INTERFACE_VERSION	_T("14d")
	#else
		// ANSI Release
		#define MTPARSER_INTERFACE_VERSION	_T("14")
	#endif	
#endif



/** @brief Expression evaluation result type

	Double should do for most of the uses.  To change this type, replace "double" by the
	desired type.    	
*/
typedef double MTDOUBLE;				

//! @brief Open bracket character 
#define MTOPEN_BRACKET '('
				
//! @brief Close bracket character
#define MTCLOSE_BRACKET ')'				

//! @brief Default function argument separator
#define MTDEFVAL_FUNCARG_SEPARATOR ','	

//! @brief Default decimal point
#define MTDEFVAL_DECIMALPOINT '.'			

//! @brief Decimal point character recognized as such by the system conversion routines
#define MTSYSTEM_DECIMALPOINT '.'			

/** @brief Operator precedence "family"

	To define an operator you must specify its precedence.
	For exemple, a division operator would have a e_MTOpPrec_MULT precedence.

	Values are based on the c++ operator precedences.

	The first element has the lower precedence.  Gaps between each item to allow
	new operator precedences to be inserted.
*/
typedef enum _EMTOpPrecedence
{
	e_MTOpPrec_LOGICAL_OR = 100,
	e_MTOpPrec_LOGICAL_AND = 200,
	e_MTOpPrec_COMPARISON_EQUAL = 300,
	e_MTOpPrec_COMPARISON_GREATERTHAN = 400,	
	e_MTOpPrec_ADD = 500,		
	e_MTOpPrec_MULT = 600,
	e_MTOpPrec_EXP = 700,
	e_MTOpPrec_UNARY = 800,
	//! Special value for functions only; must be the highest
	e_MTOpPrec_FCT = 10000

}EMTOpPrecedence;

/** @brief Define a function with an undefined number of arguments 

	Constant for function with an undefined number of arguments.
	At least 1 argument. This avoids, in most cases, having to handle
	the special case of 0 argument. 
*/
const int c_MTNbArgUndefined  = -1;

/** @brief Abstract parser items 

	Implement this interface to create new items (operators, functions, constants...).
	An item instance is owned by only one parser object at a time: it cannot be shared
	between parsers.  When a parser needs the same item as another parser, it has to
	duplicate the item, thus creating a new item instance.
*/
class MTParserItemI
{
public:

	/** @brief Get the item unique identifier 

		This identifier must be unique.  Overloaded items must have
		different identifiers.  The main purpose of this identifier
		is for localization.

		The length is unlimited.

		@return The item identifier
	*/
	virtual const MTCHAR* getID(){ return getSymbol(); }

	/** @brief Get the item symbol 

		The length is unlimited.

		@return The item name
	*/
	virtual const MTCHAR* getSymbol() = 0;
	
	/** @brief Get the helpstring 

		An helpstring gives hint to the user on how to use an item.

		@return The helpstring
	*/
	virtual const MTCHAR* getHelpString() = 0;
	
	/** @brief Get a short description 

		A description of what the item is about.

		@return The description
	*/
	virtual const MTCHAR* getDescription() = 0;

	/** @brief Indicate whether an item is constant

		A constant item can be evaluated only once and its value
		cached, thus optimizing performance.  For example, a constant
		function always returns the same result when evaluated with the same
		arguments.  An example of non-constant function is the random function.

		This method is called after the first evaluation.
		
		@return True if the item is constant	
	*/
	virtual bool isConstant() = 0;	

	/** @brief Evaluate the item

		No exception should be throwned during evaluation.  This is a performance issue
		since if exceptions were possible, then the user would have to use a try-catch clause thus
		diminishing performance.  Instead, a NaN value may be returned to indicate that
		something is wrong.

		@param	nbArgs	Number of arguments pointed by pArg
		@param	pArg	Argument buffer.  Arguments are in the same order as they appear in the expression.
		@return The evaluated result
	*/
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg) = 0;

	virtual ~MTParserItemI(){};

};

/** @brief Specialized function evaluator

	Implement this interface to create a new function.
*/
class MTFunctionI : public MTParserItemI
{
public:		

	/** @brief Get the number of arguments of this function  
	
		The number of arguments is unlimited.  The special c_MTNbArgUndefined
		value can be used to indicate a variable number of arguments.  For example, 
		the sum function have a variable number of arguments: sum(x1, x2, x3, ...).  In this
		case, the number of arguments is determined at runtime.

		@return The number of arguments	
	*/
	virtual int getNbArgs() = 0;


	/** @brief Customize the function compilation

		If this is not a "standard" function, you can provide a custom
		compiler to interpret the function arguments.

		@return	A compiler state object if needed or NULL otherwise.
	*/
	virtual class MTCompilerStateI* getCompilerState(){ return NULL; }	

	/** @brief Called just before the function needs to be used, at compilation time

		Allow the function to do just-in-time initialization like creating internal objects, only
		if needed.  If the function is never used, there will be no resource waste.
		May be called multiple times. 
		
		Although the function is not completely initialized, it
		must be able to tell its symbol, helpString, description and number of arguments. 

		@param	pCompiler	The compiler object compiling the function
		@param	pRegistrar	The registrar object owning the function
	*/
	virtual void doLateInitialization(class MTCompilerI *pCompiler, class MTRegistrarI *pRegistrar) throw(MTParserException){};

	/** @brief Create a new instance of itself

		This method is used to duplicate a parser object.

		@return A new independant object representing the same function
	*/
	virtual MTFunctionI* spawn() = 0;

	//*********************************
	// MTParserItemI interface

	// Most functions are constants
	virtual bool isConstant(){ return true; }

	
	virtual ~MTFunctionI(){};
	
};


/** @brief Specialized operator evaluator

	Implement this interface to create a new operator.
*/
class MTOperatorI : public MTParserItemI
{
public:	
		
	/** @brief Return the operator precedence 

		The operator precedence determines the evaluation
		order of a formula.

		@return The operator precedence
	*/
	virtual EMTOpPrecedence getPrecedence() = 0;	

	/** @brief Query whether this is an unary operator

		An unary operator takes only a right argument.  For example, the
		unary minus operator: -x.  Most operators are binary like: x+y.

		@return Return true if this operator is a unary operator	
	*/
	virtual bool isUnaryOp(){ return false; }	
	
	/** @brief Create a new instance of itself

		This method is used to duplicate a parser object.

		@return A new independant object representing the same operator
	*/
	virtual MTOperatorI* spawn() = 0;


	//*********************************
	// MTParserItemI interface

	// Operators are constant
	virtual bool isConstant(){ return true; }	


	virtual ~MTOperatorI(){};
	
};

/** @brief Specialized variable evaluator

	Implement this interface to create a new variable type.  For
	example, variables that get their values in a DataBase. 
*/
class MTVariableI : public MTParserItemI
{
public:	
	
	/** @brief Create a new instance of itself

		This method is used to duplicate a parser object.

		@return A new independant object representing the same variable
	*/
	virtual MTVariableI* spawn() = 0;

	//*********************************
	// MTParserItemI interface

	// Variable is not constant by definition
	virtual bool isConstant(){ return false; }

	// Variable doesn't need an helpstring
	virtual const MTCHAR* getHelpString(){ return _T(""); }
	
	// Variable doesn't need a description
	virtual const MTCHAR* getDescription(){ return _T(""); }

	// Variable doesn't have argument
	virtual int getNbArgs(){ return 0; }
	
	virtual ~MTVariableI(){};
};

/** @brief Abstract Variable factory

	A variable factory is used with the automatic variable definition
	feature to define only the used variables.  Implement this interface to
	create a custom variable factory.
*/
class MTVariableFactoryI
{
public:	

	/** @brief Get a new variable object associated with this variable name

		NOTE: The caller is responsible to delete the object, not the factory.

		@param	newVarName	The new variable name to be created	
		@return A valid object instance or NULL if the object cannot be created
				(For example if the variable name is invalid).
				
	*/
	virtual MTVariableI* create(const MTCHAR *newVarName) = 0;
	
	/** @brief Create a new instance of itself

		This method is used to duplicate a parser object.

		@return A new independant object representing the same variable factory
	*/
	virtual MTVariableFactoryI* spawn() = 0;

	virtual ~MTVariableFactoryI(){};
};



/** @brief Configurable syntax elements for internationalization considerations
*/
struct MTSyntax
{
	//! Decimal point character
	MTCHAR decimalPoint;		
	
	//! Function argument separator character
	MTCHAR argumentSeparator;	
};

/** @brief Public Registrar Interface

	Take care of the parser language definition and consistency validation.
	Represents only the client level interface of a registrar.  

	Responsibilities:

		- Register valid expression items
		- Make sure that there is no item in conflict
		- Make sure that the whole "language" is consistent
		- Give access to the registered items
*/
class MTRegistrarPublicI
{
public:

//###############################################
/** @name Manage variables
* Define/Undefine variables, get used variables and set the auto variable definition feature
*/
	//@{
	/** @brief Define a variable associated with a custom value source
	
		Define a variable and associate a custom evaluator object
		which gets the variable value from special locations (like a database).	

		@param	pVar	Variable evaluator object.  Will be automatically deleted at the end of the
						parser life.	
		
	*/
	virtual void defineVar(MTVariableI *pVar) throw(MTParserException) = 0;

	/** @brief Redefine a defined variable

		Replace the current variable object with this variable name by a new one.  This is 
		useful to redefine variables that have been automatically defined.

		The expression is not resetted.

		@param	pVar	The new variable object.  It will be deleted after use.
	*/
	virtual void redefineVar(MTVariableI *pVar) throw(MTParserException) = 0;

	/** @brief Undefine the variable with this symbol
	
		Note: The expression is automatically reset to null to avoid
		undefining variables used in the current expression.

		@param	symbol		Variable symbol
	*/
	virtual void undefineVar(const MTCHAR *symbol) throw(MTParserException) = 0;	
	

	/** @brief Undefine all variables */
	virtual void undefineAllVars() = 0;

	/** @brief Get the variable object associated with this symbol
		@param	symbol	The variable symbol
		@return The variable object
	*/
	virtual MTVariableI* getVarBySymbol(const MTCHAR *symbol)const throw(MTParserException) = 0;

	/** @brief Get the variable object from its index
		@param	index	Requested variable index from 0 to the number
						of defined variables -1
	*/
	virtual MTVariableI* getVar(unsigned int index)const throw(MTParserException) =0;
	
	/** @brief Get the number of defined variables
	*/
	virtual unsigned int getNbDefinedVars()const = 0;
	
	
		
	//@}

//###############################################
/** @name Extend the parser
* Define custom constants, function, macros, operators and conversion functions
*/
	//@{

#ifdef _MTPARSER_USE_PLUGIN

	/** @brief Load a plugin 

		Load the constants, functions and operators defined in a plug-in DLL.

		See the following Windows' APIs: StringFromCLSID, CLSIDFromString

		@param	clsid		The plug-in clsid string (class identifier) that should  
							be provided to you by the plug-in developer.  The string has this format:
							{4C639DCD-2043-42DC-9132-4B5C730855D6}.  It can be found
							in the plug-in IDL file.
		
	*/
	virtual void loadPlugin(const MTCHAR *clsid) throw(MTParserException) = 0;
#endif

	/** @brief Define a constant

		A constant is a special symbol that is replaced by a value when evaluated. 
		Using constants instead of values help to make math formulas clearer, 
		especially for well known values. 
		The parser can also do optimizations since it knows that these values are constants. 
		Examples of constants are pi (3.14159...) and e (2.71...).

		@param	name	Constant name
		@param	val		Constant value
	*/
	virtual void defineConst(const MTCHAR *name, MTDOUBLE val) throw(MTParserException) = 0;

	/** @brief Get the number of defined constants 
		@return The number of defined constants
	*/
	virtual unsigned int getNbDefinedConsts()const = 0;

	/** @brief Get a constant name and value
		@param	index				Requested constant index.  Range from 0 to the number of defined constants-1.
		@param	constName	[out]	The constant name
		@param	val			[out]	The constant value
	*/
	virtual void getConst(unsigned int index, MTSTRING &constName, MTDOUBLE &val)const throw(MTParserException) = 0;	

	/** @brief Undefine the constant with this name
	
		Note: The expression is automatically resetted 

		@param	name		Constant name
	*/
	virtual void undefineConst(const MTCHAR *name) throw(MTParserException) = 0;
	
	/** @brief Define a function	
		@param	pFunc	Function object.  Will be automatically deleted at the end of the
						parser life.	
	*/
	virtual void defineFunc( MTFunctionI *pFunc) throw(MTParserException) = 0;	

	/** @brief Get the number of defined functions 
		@return The number of defined functions
	*/
	virtual unsigned int getNbDefinedFuncs()const = 0;

	/** @brief Get the function object associed with this index
		@param	index	Requested function index. Range from 0 to the number of defined functions-1.	
		@return The function object
	*/
	virtual MTFunctionI* getFunc(unsigned int index)const throw(MTParserException) = 0;

	/** @brief Undefine the function with this symbol
	
		Note: The expression is automatically resetted 

		@param	symbol		Function symbol
	*/
	virtual void undefineFunc(MTFunctionI *pFunc) throw(MTParserException) = 0;

	/** @brief Define an operator
		@param	pOp		Operator object. Will be automatically destroyed at the end of the
						parser life.	
	*/
	virtual void defineOp( MTOperatorI *pOp) throw(MTParserException) = 0;
	
	/** @brief Get the number of defined operators 
		@return The number of defined operators
	*/
	virtual unsigned int getNbDefinedOps()const = 0;
	
	/** @brief Get the operator object associed with thid index
		@param	index	Requested operator index.  Range from 0 to the number of defined operators-1.
		@return The operator object
	*/
	virtual MTOperatorI* getOp(unsigned int index)const throw(MTParserException) = 0;	

	/** @brief Undefine the operator with this symbol
	
		Note: The expression is automatically resetted 

		@param	symbol		Operator symbol
	*/
	virtual void undefineOp(MTOperatorI* pOp) throw(MTParserException) = 0;

	//@}

//###############################################
/** @name Internationalize the parser
* Configure the parser syntax or use the user current settings
*/
	//@{		

	/** @brief Set a custom syntax 
		@param	syntax	The new syntax	
	*/
	virtual void setSyntax(const MTSyntax &syntax) throw(MTParserException) = 0;
	
	/** @brief Get the current syntax 
		@return The current syntax
	*/
	virtual MTSyntax getSyntax()const = 0;		

	//@}

	virtual ~MTRegistrarPublicI(){};
};


/** @brief Public Compiler Interface
	 
	Responsibilities:
	- Take an expression in the infix notation and transform it
	  to a stack whose items can be evaluated sequentially
	- Validate the expression syntax

*/
class MTCompilerPublicI
{
public:

	
	/** @brief Query the automatic variable definition feature state	
		@return Return true if the automatic variable definition feature is on 
	*/
	virtual bool isAutoVarDefinitionEnabled()const = 0;

	/** @brief Compile the expression to speed up the following evaluations.	
		@param	expr	A mathematical expression		
	*/	
	virtual void compile(const MTCHAR *expr) throw(MTParserException) = 0;

	/** @brief Return whether the expression is constant or not 
	
		A constant expression returns the same result all times it is
		evaluated.
	*/
	virtual bool isConstant()const = 0;
	
	/** @brief Get the number of used variables

		For example, if variables x, y and z are defined and the expression is
		x+2, then there is only one used variable: x. 

		@return The number of defined variables
	*/
	virtual unsigned int getNbUsedVars()const = 0;
	
	/** @brief Get a used variable symbol

		@param	index	The requested used variable.  Range from 0 to the number of
						used variables-1. 	

		@return Used variable symbol
	*/
	virtual MTSTRING getUsedVar(unsigned int index)const = 0;

	/** @brief Get the current expression */
	virtual MTSTRING getExpression()const = 0;

	/** @brief Set a null expression 

		Note: Evaluating a null expression always returns NaN.
	*/
	virtual void resetExpression() = 0;

	virtual ~MTCompilerPublicI(){};
};

/** @brief Localizer Interface

	Provides localized information about registered items.
*/
class MTParserLocalizerI
{
public:

	/** @brief Information about a function */
	struct SFuncInfo
	{
		//! The function identifier like "sin".  Not localized.
		MTSTRING id;		
		//! The function symbol like "sin".  Not localized.
		MTSTRING symbol;
		//! The function description
		MTSTRING desc;		
		//! Argument list
		std::vector<MTSTRING> args;			
		//! Argument meanings
		std::vector<MTSTRING> argDescs;		
	};

	/** @brief Information about an operator */
	struct SOpInfo
	{
		//! Operator identifier like "+". Not localized.
		MTSTRING id;	
		//! Operator symbol like "+". Not localized.
		MTSTRING symbol;
		//! Operator description
		MTSTRING desc;		
		//! Argument list
		std::vector<MTSTRING> args;		
	};

	/** @brief Information about a constant */
	struct SConstInfo
	{	
		//! Constant name. Not localized.
		MTSTRING symbol;				
		//! Constant description
		MTSTRING desc;
	};

	/** @brief Information about a variable */
	struct SVarInfo
	{
		//! Varible name. Not localized.
		MTSTRING symbol;				
		//! Variable description
		MTSTRING desc;
	};

public:	

	/** @brief Register a library info file

		Make available the information contained in this library info file.

		@param	infoFile	The library info file name		
	*/
	virtual void registerLibrary(const MTCHAR *infoFile) throw(MTParserException) = 0;

	/** @brief Register all libraries info files present in a directory

		@param	directory		The directory where to look for info files.  Sub-directories will be searched too.
		@param	searchPattern	File search pattern like *.xml or *.*.

	*/
	virtual void registerAllLibraries(const MTCHAR *directory, const MTCHAR *searchPattern) throw(MTParserException) = 0;
	
	/** @brief Set the locale

		All information will be returned in this locale.

		@param	locale		A locale string identifier like "en" for english or
							"fr" for french.
	*/
	virtual void setLocale(const MTCHAR *locale) throw(MTParserException) = 0;

	/** @brief Get the current locale */
	virtual MTSTRING getLocale() = 0;
	
	/** @brief Get the number of available functions */
	virtual unsigned int getNbFuncs()const = 0;	
	
	/** @brief Get the number of available operators */
	virtual unsigned int getNbOps()const = 0;

	/** @brief Get the number of available constants */
	virtual unsigned int getNbConsts()const = 0;
	
	/** @brief Get the number of available variables */
	virtual unsigned int getNbVars()const = 0;

	/** @brief Get the localized information about a function

		@param	index	The function index ranging from 0 to the
						number of available functions-1

		@return The information structure
	*/
	virtual SFuncInfo getFuncInfo(unsigned int index)const throw(MTParserException) = 0;
	
	/** @brief Get the localized information about an operator

		@param	index	The operator index ranging from 0 to the
						number of available operators-1

		@return The information structure
	*/
	virtual SOpInfo getOpInfo(unsigned int index)const throw(MTParserException) = 0;
	
	/** @brief Get the localized information about a constant

		@param	index	The constant index ranging from 0 to the
						number of available constants-1

		@return The information structure
	*/
	virtual SConstInfo getConstInfo(unsigned int index)const throw(MTParserException) = 0;
	
	/** @brief Get the localized information about a variable

		@param	index	The variable index ranging from 0 to the
						number of available variable-1

		@return The information structure
	*/
	virtual SVarInfo getVarInfo(unsigned int index)const throw(MTParserException) = 0;

	/** @brief Get the localized information about a function

		@param	id	The function string identifier.  Not its symbol since there are overloaded functions.

		@return The information structure
	*/
	virtual SFuncInfo getFuncInfo(const MTCHAR *id)const throw(MTParserException) = 0;	
	
	/** @brief Get the localized information about an operator

		@param	id	The operator string identifier.  Not its symbol since there are overloaded operators.

		@return The information structure
	*/
	virtual SOpInfo getOpInfo(const MTCHAR *id)const throw(MTParserException) = 0;
	
	/** @brief Get the localized information about a constant

		@param	symbol	The constantymbol

		@return The information structure
	*/
	virtual SConstInfo getConstInfo(const MTCHAR *symbol)const throw(MTParserException) = 0;
	
	/** @brief Get the localized information about a variable

		@param	symbol	The variable symbol

		@return The information structure
	*/
	virtual SVarInfo getVarInfo(const MTCHAR *symbol)const throw(MTParserException) = 0;

	/** @brief Get the localized exception text message
		
		@param	data	The exception data
		@return The exception text message
	*/
	virtual MTSTRING getExcep(const MTExcepData &data)const throw(MTParserException) = 0;

	virtual ~MTParserLocalizerI(){};
};


#endif