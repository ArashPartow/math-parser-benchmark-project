/** @file MTParserException.h
	@brief Exception declarations
	@author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSEREXCEPTION_INCLUDED
#define _MTPARSEREXCEPTION_INCLUDED

#include "MTException.h"

/** @name MTParser Exception identifiers 
* String identifiers and descriptions 
*/
//@{

/** The argument separator character and the decimal point character are the same
*/
#define MTDEFEXCEP_SyntaxArgDecConflict			_T("MTDEFEXCEP_SyntaxArgDecConflict")

/** An operator with the same name and the same number of arguments is already defined 
@param itemName				The name of the defined operator
*/
#define MTDEFEXCEP_OpAlreadyDefined				_T("MTDEFEXCEP_OpAlreadyDefined")

/** The operator name is null
*/
#define MTDEFEXCEP_OpNameNull					_T("MTDEFEXCEP_OpNameNull")

/** There is a space character in the operator name
@param itemName				Operator name	
*/
#define MTDEFEXCEP_OpNameSpace					_T("MTDEFEXCEP_OpNameSpace")

/** There is a character in the operator name that is the same as a syntax element 
@param itemName				Operator name
@param conflictItemName		Syntax element
*/
#define MTDEFEXCEP_OpNameSyntaxConflict			_T("MTDEFEXCEP_OpNameSyntaxConflict")

/** The operator precedence is incorrect; must be below function precedence 
@param itemName				Operator name
*/
#define MTDEFEXCEP_OpPrecedence					_T("MTDEFEXCEP_OpPrecedence")

/** Cannot find the specified item 
@param itemName				Item id or name
*/
#define MTDEFEXCEP_ItemNotFound					_T("MTDEFEXCEP_ItemNotFound")

/** A function with the same name and the same number of arguments is already defined 
*/
#define MTDEFEXCEP_FuncAlreadyDefined			_T("MTDEFEXCEP_FuncAlreadyDefined")

/** The function name is null 
*/
#define MTDEFEXCEP_FuncNameNull					_T("MTDEFEXCEP_FuncNameNull")

/** There is a space character in the function name
@param itemName				function name	
*/
#define MTDEFEXCEP_FuncNameSpace				_T("MTDEFEXCEP_FuncNameSpace")

/** There is a character in the function name that is the same as a syntax element 
@param itemName				Function name
@param conflictItemName		Syntax element
*/
#define MTDEFEXCEP_FuncNameSyntaxConflict		_T("MTDEFEXCEP_FuncNameSyntaxConflict")

/** The function name contains an operator name
@param itemName				Function name
@param conflictItemName		Operator name
*/
#define MTDEFEXCEP_FuncNameOpConflict			_T("MTDEFEXCEP_FuncNameOpConflict")

/** A variable with the same name is already defined 
@param itemName				Variable name
@param conflictItemName		Not used
*/
#define MTDEFEXCEP_VarAlreadyDefined			_T("MTDEFEXCEP_VarAlreadyDefined")

/** The variable name is null 
*/
#define MTDEFEXCEP_VarNameNull					_T("MTDEFEXCEP_VarNameNull")

/** There is a space character in the variable name
@param itemName				variable name	
*/
#define MTDEFEXCEP_VarNameSpace					_T("MTDEFEXCEP_VarNameSpace")

/** A variable name cannot be composed of numbers only
@param itemName				Variable name
*/
#define MTDEFEXCEP_VarNameOnlyNum				_T("MTDEFEXCEP_VarNameOnlyNum")

/** The variable name is the same as a defined constant name
@param itemName				Variable name
*/
#define MTDEFEXCEP_VarNameConstConflict			_T("MTDEFEXCEP_VarNameConstConflict")


/** There is a character in the variable name that is the same as a syntax element 
@param itemName				Variable name
@param conflictItemName		Syntax element
*/
#define MTDEFEXCEP_VarNameSyntaxConflict		_T("MTDEFEXCEP_VarNameSyntaxConflict")


/** The variable name conflicts with an operator name:

@param itemName				Variable name
@param conflictItemName		Operator name
*/
#define MTDEFEXCEP_VarNameOpConflict			_T("MTDEFEXCEP_VarNameDelimConflict")


/** A constant with the same name is already defined
@param itemName				Constant name
*/
#define MTDEFEXCEP_ConstAlreadyDefined			_T("MTDEFEXCEP_ConstAlreadyDefined")

/** The constant name is null 
*/
#define MTDEFEXCEP_ConstNameNull				_T("MTDEFEXCEP_ConstNameNull")

/** There is a space character in the constant name
@param itemName				Constant name	
*/
#define MTDEFEXCEP_ConstNameSpace				_T("MTDEFEXCEP_ConstNameSpace")

/** A constant name cannot be composed of numbers only 
@param itemName				Constant name
*/
#define MTDEFEXCEP_ConstNameOnlyNum				_T("MTDEFEXCEP_ConstNameOnlyNum")

/** There is a character in the constant name that is the same as a syntax element 
@param itemName				Constant name
@param conflictItemName		Syntax element
*/
#define MTDEFEXCEP_ConstNameSyntaxConflict		_T("MTDEFEXCEP_ConstNameSyntaxConflict")

/** The constant name contains an operator name
@param itemName				Constant name
@param conflictItemName		Operator name
*/
#define MTDEFEXCEP_ConstNameOpConflict			_T("MTDEFEXCEP_ConstNameOpConflict")

/** The constant name is the same as a defined variable name
@param itemName				Constant name
*/
#define MTDEFEXCEP_ConstNameVarConflict			_T("MTDEFEXCEP_ConstNameVarConflict")

/** The plug-in version is incompatible with this library
@param	itemName			The plug-in clsid
@param	conflictItemName	The requested version
@param	param1				The actual incompatible version
*/
#define MTDEFEXCEP_PluginVersion				_T("MTDEFEXCEP_PluginVersion")

/** The plug-in cannot be found.  Make sure the plug-in is properly registered.
@param	itemName			The plug-in clsid
*/
#define MTDEFEXCEP_PluginNotFound				_T("MTDEFEXCEP_PluginNotFound")

/** The plug-in type lib file cannot be found.  This file describes the plug-in interface.
@param	itemName			The typelib filename
*/
#define MTDEFEXCEP_PluginTypeLibNotFound		_T("MTDEFEXCEP_PluginTypeLibNotFound")

/** The plug-in cannot be loaded because of a conflict with an already defined item.  Another exception will give details about
the conflict.
@param	itemName			The plug-in clsid
*/
#define MTDEFEXCEP_PluginDefConflict			_T("MTDEFEXCEP_PluginDefConflict")


/** The macro prototype syntax is incorrect.  The proper syntax is: macro(arg1, arg2, arg3...)

Usually there is another exception coming with this one which gives more details.

@param	pos					The position in the prototype where the exception occured	
@param	itemName			The macro prototype
*/
#define MTDEFEXCEP_MacroProtoSyntax				_T("MTDEFEXCEP_MacroProtoSyntax")

/** An operator has been detected but the syntax is incorrect 	
@param	itemName			Operator name
*/
#define MTPARSINGEXCEP_InvalidOpSyntax			_T("MTPARSINGEXCEP_InvalidOpSyntax")

/** A function argument is invalid
@param	pos					The position in the formula where the exception occured
@param	itemName			Function name
@param	param1				Argument number
*/
#define MTPARSINGEXCEP_InvalidFuncSyntax		_T("MTPARSINGEXCEP_InvalidFuncSyntax")

/** Can't use the begin variable name character when already inside a variable name 
@param	pos					The position in the formula where the exception occured
*/
#define MTPARSINGEXCEP_UnexpectedBeginVarName	_T("MTPARSINGEXCEP_UnexpectedBeginVarName")

/** Missing begin variable name character to match this end variable name character 
@param	pos					The position in the formula where the exception occured
*/
#define MTPARSINGEXCEP_UnexpectedEndVarName		_T("MTPARSINGEXCEP_UnexpectedEndVarName")

/** An operator appears at an unexpected position
@param	pos					The position in the formula where the exception occured
*/
#define MTPARSINGEXCEP_UnexpectedOp				_T("MTPARSINGEXCEP_UnexpectedOp")

/** Missing opening bracket
@param	pos					The position of the closing bracket
*/
#define MTPARSINGEXCEP_MissingOpenBracket		_T("MTPARSINGEXCEP_MissingOpenBracket")

/** Invalid use of an argument separator: can only be used inside a function
@param	pos					The position in the formula where the exception occured
*/
#define MTPARSINGEXCEP_InvalidArgSeparator		_T("MTPARSINGEXCEP_InvalidArgSeparator")

/** Missing closing bracket	
@param	pos					The position of the openning bracket
*/
#define MTPARSINGEXCEP_MissingCloseBracket		_T("MTPARSINGEXCEP_MissingCloseBracket")

/** No defined function takes this number of arguments
@param	pos					The position in the formula where the exception occured
@param	itemName			Function name
@param	param1				The number of detected arguments
*/
#define MTPARSINGEXCEP_OverloadedFuncNotFound	_T("MTPARSINGEXCEP_OverloadedFuncNotFound")

/** Generic invalid syntax error
@param	pos					The position in the formula where the exception occured
*/
#define MTPARSINGEXCEP_InvalidSyntax			_T("MTPARSINGEXCEP_InvalidSyntax")

/** Missing operator: an operator was expected before an item
@param	pos					The position in the formula where the exception occured
@param	itemName			Item which should have been an operator
*/
#define MTPARSINGEXCEP_MissingOp				_T("MTPARSINGEXCEP_MissingOp")

/** A function has been detected but there is no defined function with this name
@param	pos					The position in the formula where the exception occured
@param	itemName			Function name
*/
#define MTPARSINGEXCEP_UndefinedFunc			_T("MTPARSINGEXCEP_UndefinedFunc")

/** A variable has been detected but there is no defined variable with this name	
@param	pos					The position in the formula where the exception occured
@param	itemName			Variable name
*/
#define MTPARSINGEXCEP_UndefinedVar				_T("MTPARSINGEXCEP_UndefinedVar")

/** Argument separator used without value. Example: fct(,,d,)
@param	pos					The position in the formula where the exception occured
*/
#define MTPARSINGEXCEP_UselessArgSeparator		_T("MTPARSINGEXCEP_UselessArgSeparator")

/** Unexpected error or error that shouldn't be shown to the user
*/
#define MTPARSINGEXCEP_InternalError			_T("MTPARSINGEXCEP_InternalError")

/** The MTParserInfo COM object cannot be instanciated.	Make sure it is registered.
*/
#define MTLOCEXCEP_MTParserInfoObjectNotFound	_T("MTLOCEXCEP_MTParserInfoObjectNotFound")

/** Unable to open a library info file.  Make sure the file exists and
that the schema and xml syntax are valids.  

@param	itemName			The library info file
*/
#define MTLOCEXCEP_InfoFileOpenFailed			_T("MTLOCEXCEP_InfoFileOpenFailed")

/** Unable to load a library info file.  Make sure no xml attribute is missing.
@param	itemName			The library info file
*/
#define MTLOCEXCEP_InfoFileLoadFailed			_T("MTLOCEXCEP_InfoFileLoadFailed")

/** Information not available in this locale 
@param	itemName			The library info file
@param	conflictItemName	The missing locale				
*/
#define MTLOCEXCEP_InfoFileLocaleFailed			_T("MTLOCEXCEP_InfoFileLocaleFailed")

/** The library info file version is incorrect
@param	itemName			The library info file
*/
#define MTLOCEXCEP_InfoFileBadVersion			_T("MTLOCEXCEP_InfoFileBadVersion")

/** Not enough memory */  
#define MTEXCEP_OutOfMemory						_T("MTEXCEP_OutOfMemory")

//@}

//###############################################
/** @name Exception arguments */
//@{
#define MTEXCEPARG_POS							_T("pos")
#define MTEXCEPARG_ITEMNAME						_T("itemName")
#define MTEXCEPARG_CONFLICTITEMNAME				_T("conflictItemName")
#define MTEXCEPARG_PARAM1						_T("param1")
#define MTEXCEPARG_PARAM2						_T("param2")
//@}

//! @brief Parser Exception runtime customizable 
typedef MTChainedExceptions<MTExcepData> MTParserException;


#endif