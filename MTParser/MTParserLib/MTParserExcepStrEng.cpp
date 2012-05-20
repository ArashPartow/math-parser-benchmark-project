#include "MTParserExcepStrEng.h"
#include "MTTools.h"



MTParserExcepStrEng MTParserExcepStrEng::m_instance = MTParserExcepStrEng();

MTParserExcepStrEng::MTParserExcepStrEng()
{	
	addExcep(MTDEFEXCEP_OpAlreadyDefined, _T("Operator already defined: '%itemName'"));		
	addExcep(MTDEFEXCEP_OpNameNull, _T("Operator name cannot be null"));
	addExcep(MTDEFEXCEP_OpNameSpace, _T("This operator name contains space characters: '%itemName'"));		
	addExcep(MTDEFEXCEP_OpNameSyntaxConflict, _T("Operator name '%itemName' conflicts with the syntax element character: '%conflictItemName'."));		
	addExcep(MTDEFEXCEP_OpPrecedence, _T("Operator: '%itemName'; invalid precedence."));			
	addExcep(MTDEFEXCEP_FuncAlreadyDefined, _T("Function already defined: '%itemName'"));		
	addExcep(MTDEFEXCEP_FuncNameNull, _T("Function name cannot be null"));
	addExcep(MTDEFEXCEP_FuncNameSpace, _T("This function name contains space characters: '%itemName'"));		
	addExcep(MTDEFEXCEP_FuncNameSyntaxConflict, _T("Function name '%itemName' conflicts with the syntax element character: '%conflictItemName'"));		
	addExcep(MTDEFEXCEP_FuncNameOpConflict, _T("Function name '%itemName' conflicts with the operator '%conflictItemName'"));
	addExcep(MTDEFEXCEP_ItemNotFound, _T("Cannot find the specified item: id = %itemName"));		
	addExcep(MTDEFEXCEP_VarAlreadyDefined, _T("Variable already defined: '%itemName'"));		
	addExcep(MTDEFEXCEP_VarNameNull, _T("Variable name cannot be null"));
	addExcep(MTDEFEXCEP_VarNameSpace, _T("This variable name contains space characters: '%itemName'"));		
	addExcep(MTDEFEXCEP_VarNameOnlyNum, _T("Invalid variable name: '%itemName'.  Cannot be composed only of numbers"));		
	addExcep(MTDEFEXCEP_VarNameConstConflict, _T("Variable name '%itemName' conflicts with the constant of the same name."));
	addExcep(MTDEFEXCEP_VarNameSyntaxConflict, _T("Variable name '%itemName'  conflicts with the syntax element character: '%conflictItemName'"));	
	addExcep(MTDEFEXCEP_VarNameOpConflict, _T("Variable name '%itemName' conflicts with the operator: '%conflictItemName'"));			
	addExcep(MTDEFEXCEP_ConstAlreadyDefined, _T("Constant already defined: '%itemName'"));		
	addExcep(MTDEFEXCEP_ConstNameNull, _T("Constant name cannot be null"));
	addExcep(MTDEFEXCEP_ConstNameSpace, _T("This constant name contains space characters: '%itemName'"));		
	addExcep(MTDEFEXCEP_ConstNameOnlyNum, _T("Invalid constant name: '%itemName'.  Cannot be composed only of numbers."));		
	addExcep(MTDEFEXCEP_ConstNameSyntaxConflict, _T("Constant name '%itemName' conflicts with the syntax element character: '%conflictItemName'"));
	addExcep(MTDEFEXCEP_ConstNameOpConflict, _T("Constant name '%itemName' conflicts with the operator '%conflictItemName'"));		
	addExcep(MTDEFEXCEP_ConstNameVarConflict, _T("Constant name '%itemName' conflicts with the variable of the same name"));		
	addExcep(MTDEFEXCEP_PluginVersion, _T("The plug-in version is incompatible with this library.  Plug-in CLSID = %itemName.  Requested version: %conflictItemName.  Plug-in version: %param1"));
	addExcep(MTDEFEXCEP_PluginNotFound, _T("The plug-in cannot be found.  Make sure the plug-in is properly registered. CLSID = %itemName"));
	addExcep(MTDEFEXCEP_PluginTypeLibNotFound, _T("The plug-in type lib file cannot be found: '%itemName'.  This file describes the plug-in interface."));
	addExcep(MTDEFEXCEP_PluginDefConflict, _T("The plug-in cannot be loaded because of a conflict with an already defined item.  Plug-in CLSID = %itemName"));
	addExcep(MTDEFEXCEP_MacroProtoSyntax, _T("The macro prototype syntax is incorrect: '%itemName'. The proper syntax is: macro(arg1, arg2, arg3...)."));		
	addExcep(MTPARSINGEXCEP_InvalidOpSyntax, _T("Invalid operator syntax: '%itemName'"));		
	addExcep(MTPARSINGEXCEP_InvalidFuncSyntax, _T("Invalid function argument syntax. Function name: '%itemName', argument %param1"));		
	addExcep(MTPARSINGEXCEP_UnexpectedBeginVarName, _T("Unexpected begin variable name character"));					
	addExcep(MTPARSINGEXCEP_UnexpectedEndVarName, _T("Unexpected end variable name character"));					
	addExcep(MTPARSINGEXCEP_UnexpectedOp, _T("Unexpected operator"));		
	addExcep(MTPARSINGEXCEP_MissingOpenBracket, _T("Missing opening bracket to macth closing bracket"));					
	addExcep(MTPARSINGEXCEP_InvalidArgSeparator, _T("Invalid use of an argument separator outside a function"));
	addExcep(MTPARSINGEXCEP_MissingCloseBracket, _T("Missing closing bracket to match opening bracket"));
	addExcep(MTPARSINGEXCEP_OverloadedFuncNotFound, _T("Invalid number of arguments for function '%itemName'"));
	addExcep(MTPARSINGEXCEP_InvalidSyntax, _T("Invalid syntax"));				
	addExcep(MTPARSINGEXCEP_MissingOp, _T("Missing operator before: '%itemName'"));		
	addExcep(MTPARSINGEXCEP_UndefinedFunc, _T("Undefined function: '%itemName'"));		
	addExcep(MTPARSINGEXCEP_UndefinedVar, _T("Undefined variable: '%itemName'"));		
	addExcep(MTPARSINGEXCEP_UselessArgSeparator, _T("Invalid use of an argument separator"));		
	addExcep(MTPARSINGEXCEP_InternalError, _T("Internal error"));		
	addExcep(MTLOCEXCEP_MTParserInfoObjectNotFound, _T("The MTParserInfo COM object cannot be instanciated.	Make sure it is registered."));
	addExcep(MTLOCEXCEP_InfoFileOpenFailed, _T("Unable to OPEN the library info file: '%itemName'. Make sure the file exists and that the schema and xml syntax are valids."));		
	addExcep(MTLOCEXCEP_InfoFileLoadFailed, _T("Unable to LOAD the library info file: '%itemName'. Make sure no xml attribute is missing."));		
	addExcep(MTLOCEXCEP_InfoFileLocaleFailed, _T("Locale information not available for the library info file: '%itemName'.  Locale: %conflictItemName"));		
	addExcep(MTLOCEXCEP_InfoFileBadVersion, _T("The library info file version is incorrect.  File: '%itemName'"));		
	addExcep(MTEXCEP_OutOfMemory, _T("Out of memory"));
}

void MTParserExcepStrEng::addExcep(const MTCHAR *id, const MTCHAR *msg)
{
	SExcepInfo info;
	info.id = id;
	info.msg = msg;
	m_exceps.push_back(info);
}

MTSTRING MTParserExcepStrEng::internalFormat(const MTExcepData &data)
{
	unsigned int size = m_exceps.size();

	for( unsigned int t=0; t<size; t++ )
	{
		if( lstrcmp( m_exceps[t].id.c_str(), data.getID()) == 0 )
		{
			return MTParserExcepStrEng::format(data, m_exceps[t].msg.c_str());
		}
	}

	// exception not found...
	MTSTRING msg = _T("Unknown exception: ");
	msg += data.getID();
	return msg;
}

MTSTRING MTParserExcepStrEng::format(const MTExcepData &data)
{
	return m_instance.internalFormat(data);	
}

MTSTRING MTParserExcepStrEng::format(const MTExcepData &data, const MTCHAR *msg)
{
	MTSTRING formattedMsg = msg;	
	MTSTRING argName, argVal;

	// replace all arguments by their values
	for( unsigned int t=0; t<data.getNbArgs(); t++ )
	{
		argName = data.getArgName(t);
		argVal = data.getArgVal(t);

		argName = _T("%") + argName;
		MTTools::replaceSubStr(formattedMsg, argName.c_str(), argVal.c_str());

	}	

	return formattedMsg;
}
