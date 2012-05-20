#include "MTParserLocalizer.h"

#ifdef _MTPARSER_USE_LOCALIZATION

#include "MTParserPrivate.h"
#include "MTTools.h"
#include "MTSearchFile.h"
#include "MTParserExcepStrEng.h"
#include <windows.h>
#import "../MTParserInfoFile/MTParserInfoFile/_MTParserInfoFile.tlb" no_namespace

MTParserLocalizer MTParserLocalizer::m_instance = MTParserLocalizer::MTParserLocalizer();

MTParserLocalizer* MTParserLocalizer::getInstance()
{
	return &m_instance;
}

void MTParserLocalizer::registerLibrary(const MTCHAR *infoFile) throw(MTParserException)
{
	if( findInfoFile(infoFile) )
	{
		return;		// already defined
	}

	SLibraryInfo info;
	info.infoFile = infoFile;
	
	if( m_locale != _T("") )
	{		
		defineLibrary(info, m_locale);		
	}	

	m_libraryList.push_back(info);	
}

void MTParserLocalizer::registerAllLibraries(const MTCHAR *directory, const MTCHAR *searchPattern) throw(MTParserException)
{
	MTSearchFile search;
	std::vector<MTSTRING> directories;	
	std::vector<MTSTRING> searchPatterns;
	std::vector<MTSTRING> results;

	directories.push_back(directory);
	searchPatterns.push_back(searchPattern);	
	search.search(directories, searchPatterns, results);

	MTParserException exceps;
	
	for( unsigned int t=0; t<results.size(); t++ )
	{
		try
		{
			registerLibrary(results[t].c_str());
		}
		catch( MTParserException &e )
		{
			exceps.add(e);
		}
	}

	if( exceps.size() > 0 )
	{
		throw(exceps);
	}	
}

void MTParserLocalizer::setLocale(const MTCHAR *locale) throw(MTParserException)
{
	if( lstrcmp( locale, m_locale.c_str() ) == 0 )
	{
		return;		// already this locale, so no need to update
	}

	// reload all resources
	m_funcList.clear();
	m_opList.clear();
	m_constList.clear();
	m_varList.clear();
	m_excepList.clear();

	m_locale = locale;

	MTParserException allExceps;
	
	unsigned int nbLibraries = m_libraryList.size();
	for( unsigned int t=0; t<nbLibraries; t++ )
	{
		try
		{
			defineLibrary(m_libraryList[t], locale);
		}
		catch( MTParserException &e )
		{			
			allExceps.add(e);
		}
	}

	// if exceptions occured, then throw them all
	if( allExceps.size() > 0 )
	{
		throw(allExceps);
	}
}

MTSTRING MTParserLocalizer::getLocale()
{
	return m_locale;
}

unsigned int MTParserLocalizer::getNbFuncs()const
{
	return m_funcList.size();
}
unsigned int MTParserLocalizer::getNbOps()const
{
	return m_opList.size();
}
unsigned int MTParserLocalizer::getNbConsts()const
{
	return m_constList.size();
}
unsigned int MTParserLocalizer::getNbVars()const
{
	return m_varList.size();
}

MTParserLocalizer::SFuncInfo MTParserLocalizer::getFuncInfo(unsigned int id)const throw(MTParserException)
{
	if( id < 0 || id >= getNbFuncs() )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, MTTools::longToS(id).c_str()))
	}
	
	return m_funcList[id];
}
MTParserLocalizer::SOpInfo MTParserLocalizer::getOpInfo(unsigned int id)const throw(MTParserException)
{
	if( id < 0 || id >= getNbOps() )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, MTTools::longToS(id).c_str()))
	}

	return m_opList[id];

}
MTParserLocalizer::SConstInfo MTParserLocalizer::getConstInfo(unsigned int id)const throw(MTParserException)
{
	if( id < 0 || id >= getNbOps() )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, MTTools::longToS(id).c_str()))
	}

	return m_constList[id];

}
MTParserLocalizer::SVarInfo MTParserLocalizer::getVarInfo(unsigned int id)const throw(MTParserException)
{
	if( id < 0 || id >= getNbVars() )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, MTTools::longToS(id).c_str()))
	}

	return m_varList[id];
}

MTParserLocalizer::SFuncInfo MTParserLocalizer::getFuncInfo(const MTCHAR *id)const throw(MTParserException)
{
	unsigned int nid;
	if( !findFunc(id, nid) )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, id) )
	}

	return getFuncInfo(nid);
}
MTParserLocalizer::SOpInfo MTParserLocalizer::getOpInfo(const MTCHAR *id)const throw(MTParserException)
{
	unsigned int nid;
	if( !findOp(id, nid) )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, id))
	}

	return getOpInfo(nid);

}
MTParserLocalizer::SConstInfo MTParserLocalizer::getConstInfo(const MTCHAR *symbol)const throw(MTParserException)
{
	unsigned int id;
	if( !findConst(symbol, id) )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, symbol))
	}

	return getConstInfo(id);

}
MTParserLocalizer::SVarInfo MTParserLocalizer::getVarInfo(const MTCHAR *symbol)const throw(MTParserException)
{
	unsigned int id;
	if( !findVar(symbol, id) )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, symbol))
	}

	return getVarInfo(id);

}

MTSTRING MTParserLocalizer::getExcep(const MTExcepData &data)const throw(MTParserException)
{
	unsigned int id;
	if( !findExcep(data.getID(), id) )
	{		
		MTTHROW(MTExcepData (	MTDEFEXCEP_ItemNotFound,
								MTEXCEPARG_ITEMNAME, data.getID()))
	}

	return MTParserExcepStrEng::format(data, m_excepList[id].desc.c_str());

}

MTSTRING MTParserLocalizer::formatFuncPrototype(const SFuncInfo &info, const MTSyntax &syntax)
{
	MTSTRING prototype;
	prototype = info.symbol;
	prototype += MTOPEN_BRACKET;

	for( unsigned int t=0; t<info.args.size(); t++ )
	{
		prototype += info.args[t];

		if( t != info.args.size()-1 )
		{
			prototype += syntax.argumentSeparator;
			prototype += _T(" ");
		}
	}

	prototype += MTCLOSE_BRACKET;

	return prototype;
}
MTSTRING MTParserLocalizer::formatOpPrototype(const SOpInfo &info)
{
	MTSTRING prototype;

	if( info.args.size()==1 )
	{		
		prototype = info.symbol;
		prototype += info.args[0];
	}
	else
	{
		prototype = info.args[0];
		prototype += info.symbol;
		prototype += info.args[1];
	}

	return prototype;
}



bool MTParserLocalizer::findInfoFile(const MTCHAR *infoFile)const
{
	unsigned int nbFiles = m_libraryList.size();
	for( unsigned int t=0; t<nbFiles; t++ )
	{
		if( lstrcmp(m_libraryList[t].infoFile.c_str(), infoFile) == 0 )
		{
			return true;
		}
	}

	return false;
}
bool MTParserLocalizer::findFunc(const MTCHAR *idStr, unsigned int &id)const
{
	unsigned int nbFuncs = getNbFuncs();
	for( unsigned int t=0; t<nbFuncs; t++ )
	{
		if( lstrcmp(idStr, m_funcList[t].id.c_str()) == 0 )
		{
			id = t;
			return true;
		}
	}

	return false;

}
bool MTParserLocalizer::findOp(const MTCHAR *idStr, unsigned int &id)const
{
	unsigned int nbOps = getNbOps();
	for( unsigned int t=0; t<nbOps; t++ )
	{
		if( lstrcmp(idStr, m_opList[t].id.c_str()) == 0 )
		{
			id = t;
			return true;
		}
	}

	return false;

}
bool MTParserLocalizer::findConst(const MTCHAR *symbol, unsigned int &id)const
{	
	unsigned int nbConsts = getNbConsts();
	for( unsigned int t=0; t<nbConsts; t++ )
	{
		if( lstrcmp(symbol, m_constList[t].symbol.c_str()) == 0 )
		{
			id = t;
			return true;
		}
	}

	return false;

}
bool MTParserLocalizer::findVar(const MTCHAR *symbol, unsigned int &id)const
{
	unsigned int nbVars = getNbVars();
	for( unsigned int t=0; t<nbVars; t++ )
	{
		if( lstrcmp(symbol, m_varList[t].symbol.c_str()) == 0 )
		{
			id = t;
			return true;
		}
	}

	return false;
}

bool MTParserLocalizer::findExcep(const MTCHAR *idStr, unsigned int &id)const
{
	unsigned int nbExceps = m_excepList.size();
	for( unsigned int t=0; t<nbExceps; t++ )
	{
		if( lstrcmp(idStr, m_excepList[t].id.c_str()) == 0 )
		{
			id = t;
			return true;
		}
	}

	return false;

}

void MTParserLocalizer::defineLibrary(SLibraryInfo &info, const MTSTRING &locale) throw(MTParserException)
{
	IMTParserInfoFilePtr infoFile;
	infoFile.CreateInstance(__uuidof(CATLMTParserInfoFile));	// CATLMTParserLocalizerFile is the coclass
	
	if( infoFile == NULL )
	{
		// COM object not found...		
		MTTHROW(MTExcepData (	MTLOCEXCEP_MTParserInfoObjectNotFound ) )
	}

	// load the file...
	try
	{
		infoFile->load(info.infoFile.c_str());
	}
	catch( _com_error )
	{
		// unable to open this info file...		
		MTTHROW(MTExcepData (	MTLOCEXCEP_InfoFileOpenFailed,
								MTEXCEPARG_ITEMNAME, info.infoFile.c_str()))
	}

	// set the locale...
	try
	{
		infoFile->setLocale(locale.c_str());
	}
	catch( _com_error )
	{
		// unable to set this locale...		
		MTTHROW(MTExcepData (	MTLOCEXCEP_InfoFileLocaleFailed,
								MTEXCEPARG_ITEMNAME, info.infoFile.c_str(),
								MTEXCEPARG_CONFLICTITEMNAME, locale.c_str()))
	}

	try
	{	
		// now, load all items...
		unsigned int t;
		
		// functions...
		unsigned int nbFuncs = infoFile->getNbFuncs();
		SATLFuncInfo atlFuncInfo;
		SFuncInfo funcInfo;
		for( t=0; t<nbFuncs; t++ )
		{
			atlFuncInfo = infoFile->getFunc(t);

			funcInfo.id = UNICODETOMTSTRING(atlFuncInfo.id);
			funcInfo.symbol = UNICODETOMTSTRING(atlFuncInfo.symbol);
			MTTools::parseString(UNICODETOMTSTRING(atlFuncInfo.args), ',', funcInfo.args);
			MTTools::parseString(UNICODETOMTSTRING(atlFuncInfo.argDescs), ',', funcInfo.argDescs);			
			funcInfo.desc = UNICODETOMTSTRING(atlFuncInfo.desc);
			
			m_funcList.push_back( funcInfo );

			SysFreeString(atlFuncInfo.id);
			SysFreeString(atlFuncInfo.symbol);
			SysFreeString(atlFuncInfo.args);
			SysFreeString(atlFuncInfo.argDescs);
			SysFreeString(atlFuncInfo.desc);
		}		

		// operators...
		unsigned int nbOps = infoFile->getNbOps();
		SATLOpInfo atlOpInfo;
		SOpInfo opInfo;
		for( t=0; t<nbOps; t++ )
		{
			atlOpInfo = infoFile->getOp(t);
			
			opInfo.id = UNICODETOMTSTRING(atlOpInfo.id);
			opInfo.symbol = UNICODETOMTSTRING(atlOpInfo.symbol);
			MTTools::parseString(UNICODETOMTSTRING(atlOpInfo.args), ',', opInfo.args);			
			opInfo.desc = UNICODETOMTSTRING(atlOpInfo.desc);	
			
			m_opList.push_back( opInfo );

			SysFreeString(atlOpInfo.id);
			SysFreeString(atlOpInfo.symbol);
			SysFreeString(atlOpInfo.args);			
			SysFreeString(atlOpInfo.desc);
		}		

		// constants...
		unsigned int nbConsts = infoFile->getNbConsts();
		SATLConstInfo atlConstInfo;
		SConstInfo constInfo;
		for( t=0; t<nbConsts; t++ )
		{
			atlConstInfo = infoFile->getConst(t);

			constInfo.symbol = UNICODETOMTSTRING(atlConstInfo.symbol);			
			constInfo.desc = UNICODETOMTSTRING(atlConstInfo.desc);	
			
			m_constList.push_back( constInfo );

			SysFreeString(atlConstInfo.symbol);			
			SysFreeString(atlConstInfo.desc);
		}		

		// variables...
		unsigned int nbVars = infoFile->getNbVars();
		SATLVarInfo atlVarInfo;
		SVarInfo varInfo;
		for( t=0; t<nbVars; t++ )
		{
			atlVarInfo = infoFile->getVar(t);

			varInfo.symbol = UNICODETOMTSTRING(atlVarInfo.symbol);			
			varInfo.desc = UNICODETOMTSTRING(atlVarInfo.desc);	
			
			m_varList.push_back( varInfo );

			SysFreeString(atlVarInfo.symbol);			
			SysFreeString(atlVarInfo.desc);
		}		

		// exceptions...
		unsigned int nbExceps = infoFile->getNbExceps();
		SATLExcepInfo atlExcepInfo;
		SExcepInfo excepInfo;
		for( t=0; t<nbExceps; t++ )
		{
			atlExcepInfo = infoFile->getExcep(t);

			excepInfo.id = UNICODETOMTSTRING(atlExcepInfo.id);			
			excepInfo.desc = UNICODETOMTSTRING(atlExcepInfo.desc);	
			
			m_excepList.push_back( excepInfo );

			SysFreeString(atlExcepInfo.id);			
			SysFreeString(atlExcepInfo.desc);
		}	
	}
	catch( _com_error )
	{
		
		MTTHROW(MTExcepData (	MTLOCEXCEP_InfoFileLoadFailed,
								MTEXCEPARG_ITEMNAME, info.infoFile.c_str()))

	}
}

#endif