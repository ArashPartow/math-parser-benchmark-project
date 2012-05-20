#include "MTParserRegistrar.h"
#include "MTTools.h"
#include "MTParser.h"
#include <windows.h>
#include <assert.h>

/*************************************************

  Steps to add a new item type:

  1) create a defineXXX method
  2) create a getNbDefinedXXX method
  3) create a getXXX method
  4) modify the spawn method
  5) modify the destructor

  *It is important not to remove items once defined.  Items can be undefined all at once
  but not individually since internal ids would not be updated.  Only variables can be
  undefined since their ids (keys) are updated.

*************************************************/

//! The type library file needing to be registered in order to instanciate plug-ins
#define MTPLUGIN_TYPELIBFILE	_T("_MTParserPlugin.tlb")


MTParserRegistrar::MTParserRegistrar()
{	
	m_pVarFactory = NULL;
	m_varKeyVersion = 0;	
}

MTRegistrarI* MTParserRegistrar::spawn() throw(MTParserException)
{
	unsigned int t;
	
	MTParserRegistrar *pObj = new MTParserRegistrar;

	// define syntax...
	pObj->setSyntax(getSyntax());	

	// Use the registerX methods instead of the defineX methods to
	// avoid doing validations again

	// define variables...
	pObj->setVarFactory(m_pVarFactory->spawn());
	
	pObj->m_variableList.reserve(m_variableList.size());
	TVariableMap::iterator it = m_variableMap.begin();	
	for( t=0; t<m_variableMap.size(); t++ )
	{
		pObj->registerVar((*it).second->pVar->spawn());
		it++;
	}

#ifdef _MTPARSER_USE_PLUGIN
	// Copy plug-in references...
	pObj->m_pluginPtr = m_pluginPtr;
#endif

	// define constants...
	pObj->m_constList = m_constList;	
	pObj->m_constMap = m_constMap;
	
	// define operators...
	pObj->m_opList.reserve( getNbDefinedOps() );	
	for( t=0; t<getNbDefinedOps(); t++ )
	{
		pObj->registerOp(getOp(t)->spawn());
	}

	// define functions...
	pObj->m_funcList.reserve( getNbDefinedFuncs() );
	for( t=0; t<getNbDefinedFuncs(); t++ )
	{
		pObj->registerFunc(getFunc(t)->spawn());
	}	

	return pObj;	
}

MTParserRegistrar::~MTParserRegistrar()
{
	unsigned int t;

	// delete operators
	unsigned int nbOps = m_opList.size();
	for( t=0; t<nbOps; t++ )
	{		
		delete m_opList[t].pOp;
		m_opList[t].pOp = NULL;	
	}

	// delete functions
	unsigned int nbFuncs = m_funcList.size();
	for( t=0; t<nbFuncs; t++ )
	{		
		delete m_funcList[t].pFunc;
		m_funcList[t].pFunc = NULL;		
	}

	undefineAllVars();	

	if( m_pVarFactory != NULL )
	{
		delete m_pVarFactory;
		m_pVarFactory = NULL;
	}
}

void MTParserRegistrar::undefineAllVars()
{
	TVariableMap::iterator it, itEnd;
	it = m_variableMap.begin();
	itEnd = m_variableMap.end();
	
	// delete all variable evaluator objects
	for( ; it != itEnd; it++ )
	{	
		delete (*it).second->pVar;
		(*it).second->pVar = NULL;	
		
		delete (*it).second;
	}
		
	m_variableMap.clear();
	m_variableList.clear();
	
	m_varKeyVersion++;	// invalidate all variable keys
}

void MTParserRegistrar::setSyntax(const MTSyntax &syntax) throw(MTParserException)
{
	defValidateSyntax(syntax);
	m_syntax = syntax;
}

void MTParserRegistrar::defValidateSyntax(const MTSyntax &syntax)const throw(MTParserException)
{

	// all syntax elements must be different...
	if( syntax.argumentSeparator == syntax.decimalPoint )
	{
		throwDefExcep(MTDEFEXCEP_SyntaxArgDecConflict, _T(""));			
	}


	unsigned int t;
	
	MTSTRING itemName;
	MTCHAR conflict;

	// operators...
	unsigned int nbOps = getNbDefinedOps();
	for( t=0; t<nbOps; t++ )
	{
		itemName = getOp(t)->getSymbol();
		if( !defValidateSyntaxConflict(syntax, itemName, conflict) )
		{
			MTSTRING conflictStr;
			conflictStr = conflict;

			throwDefExcep(MTDEFEXCEP_OpNameSyntaxConflict, itemName, conflictStr);			
		}
	}


	// functions...
	unsigned int nbFuncs = getNbDefinedFuncs();
	for( t=0; t<nbFuncs; t++ )
	{
		itemName = getFunc(t)->getSymbol();
		if( !defValidateSyntaxConflict(syntax, itemName, conflict) )
		{
			MTSTRING conflictStr;
			conflictStr = conflict;

			throwDefExcep(MTDEFEXCEP_FuncNameSyntaxConflict, itemName, conflictStr);			
		}
	}

	// constants...
	unsigned int nbConsts = m_constList.size();
	for( t=0; t<nbConsts; t++ )
	{
		itemName = m_constList[t].name;
		if( !defValidateSyntaxConflict(syntax, itemName, conflict) )
		{
			MTSTRING conflictStr;
			conflictStr = conflict;

			throwDefExcep(MTDEFEXCEP_ConstNameSyntaxConflict, itemName, conflictStr);			
		}
	}
}

MTSyntax MTParserRegistrar::getSyntax()const
{
	return m_syntax;
}

bool MTParserRegistrar::defValidateSyntaxConflict(const MTSyntax &syntax, const MTSTRING &word, MTCHAR &conflict)const
{

	unsigned int size = word.size();
	MTCHAR c;
	for( unsigned int t=0; t<size; t++ )
	{
		c = word[t];
		
		// don't validate the decimal point since not used to split formula parts...
		if( c == syntax.argumentSeparator ||			
			c == MTOPEN_BRACKET ||
			c == MTCLOSE_BRACKET)
		{
			conflict = c;
			return false;		// conflict detected!
		}
	}

	return true;	// all is ok!

}


void MTParserRegistrar::defineOp(MTOperatorI *pOp) throw(MTParserException)
{
	try
	{
		defValidateOp(pOp);
	}
	catch( MTParserException &e )
	{			
		delete pOp;		

		// rethrow the same exception
		throw(e);		
	}	

	registerOp(pOp);	
}

void MTParserRegistrar::registerOp(MTOperatorI *pOp)
{
	// insert the operator in the hash table at the right position
	// to keep the vector ordered by operator symbol length.
	// This is essential in order to be able to recognize multicharacter operators

	unsigned int hashID = getOpHashKey(pOp->getSymbol());

	unsigned int nbOps = m_opHash[hashID].size();
	unsigned int symbolLength = lstrlen(pOp->getSymbol());
	unsigned int t;

	for( t=0; t<nbOps; t++ )
	{
		if( getOpByHashID(hashID, t)->symbolLength < symbolLength )
		{
			// insert the operator here
			break;
		}
	}

	SOperatorInfo opInfo;
	opInfo.pOp = pOp;	
	opInfo.symbol = pOp->getSymbol();
	opInfo.symbolLength = symbolLength;	

	m_opHash[hashID].insert(m_opHash[hashID].begin()+t, m_opList.size());
	m_opList.push_back(opInfo);

}

void MTParserRegistrar::defValidateOp(MTOperatorI *pOp)const throw(MTParserException)
{

	MTSTRING opName = pOp->getSymbol();

	// operator name can't be null
	if( opName.size() == 0 )
	{
		throwDefExcep(MTDEFEXCEP_OpNameNull, opName);		
	}

	// operator name cannot contains space characters
	unsigned int pos;
	if( MTTools::findSubStr(opName, _T(" "), pos) )
	{
		throwDefExcep(MTDEFEXCEP_OpNameSpace, opName);		
	}

	// operator precedence must be less than function precedence and greater or equal to 0
	if( pOp->getPrecedence() >= e_MTOpPrec_FCT ||
		pOp->getPrecedence() < 0)
	{
		throwDefExcep(MTDEFEXCEP_OpPrecedence, opName);
	}

	
	// validate that this symbol is not already defined...
	unsigned int index;
	if( findOp(opName.c_str(), pOp->isUnaryOp(), index) )
	{		
		throwDefExcep(MTDEFEXCEP_OpAlreadyDefined, opName);
	}

	// operator name cannot contains syntax element characters...
	MTCHAR syntaxConflict;
	if( !defValidateSyntaxConflict(getSyntax(), opName, syntaxConflict) )
	{
		MTSTRING conflictStr;
		conflictStr = syntaxConflict;
		throwDefExcep(MTDEFEXCEP_OpNameSyntaxConflict, opName, conflictStr);
	}

	// revalidate functions, variables and constants to be sure that this new operator
	// symbol will not conflict with another symbols...	

	unsigned int t;	
	MTSTRING itemName;		

	// functions...
	unsigned int nbFuncs = getNbDefinedFuncs();
	for( t=0; t<nbFuncs; t++ )
	{
		itemName = getFunc(t)->getSymbol();
		if( MTTools::findSubStr(itemName, opName, pos) )
		{
			throwDefExcep(MTDEFEXCEP_FuncNameOpConflict, itemName, opName);
		}
	}

	// constants...
	unsigned int nbConsts = m_constList.size();
	for( t=0; t<nbConsts; t++ )
	{
		itemName = m_constList[t].name;
		if( MTTools::findSubStr(itemName, opName, pos) )
		{
			throwDefExcep(MTDEFEXCEP_ConstNameOpConflict, itemName, opName);
		}
	}
}

bool MTParserRegistrar::findOp(const MTCHAR *symbol, bool unaryOp, unsigned int &index)const
{	
	unsigned int hashID = getOpHashKey(symbol);

	unsigned int nbOps = m_opHash[hashID].size();
	unsigned int t;

	for( t=0; t<nbOps; t++ )
	{
		if( lstrcmp(symbol, getOpByHashID(hashID, t)->symbol.c_str() ) == 0 &&
			getOpByHashID(hashID, t)->pOp->isUnaryOp() == unaryOp)
		{
			index = getOpIndexByHashID(hashID, t);
			return true;
		}
	}

	return false;	// not found

}

unsigned int MTParserRegistrar::getNbDefinedOps()const
{
	return m_opList.size();
}

void MTParserRegistrar::defineFunc( MTFunctionI *pFunc) throw(MTParserException)
{
	try
	{
		defValidateFunc(pFunc);
	}
	catch( MTParserException &e )
	{
		
		delete pFunc;	

		// rethrow the same exception
		throw(e);		
	}	

	registerFunc(pFunc);

}

void MTParserRegistrar::registerFunc(MTFunctionI *pFunc)
{	
	SFunctionInfo funcInfo;
	funcInfo.pFunc = pFunc;		
	funcInfo.symbol = pFunc->getSymbol();	

	m_funcMap.insert(TFuncMap::value_type(funcInfo.symbol.c_str(), m_funcList.size()));	
	m_funcList.push_back(funcInfo);
}

void MTParserRegistrar::undefineFunc(MTFunctionI *pFunc) throw(MTParserException)
{
	unsigned int index;
	if( !findFunctionExact(pFunc->getSymbol(), pFunc->getNbArgs(), index) )
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, pFunc->getSymbol());
	}
	
	m_funcList.erase(m_funcList.begin()+index);
	delete pFunc;
	rebuildFuncMap();	
}

void MTParserRegistrar::rebuildFuncMap()
{
	m_funcMap.clear();
	
	for(unsigned int t=0; t<m_funcList.size(); t++ )
	{
		m_funcMap.insert(TFuncMap::value_type(m_funcList[t].symbol.c_str(), t));
	}
}


void MTParserRegistrar::undefineOp(MTOperatorI *pOp) throw(MTParserException)
{	
	unsigned int index;
	if(!findOp(pOp->getSymbol(), pOp->isUnaryOp(), index) )
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, pOp->getSymbol());
	}	

	removeFromOpHash(pOp);
	m_opList.erase(m_opList.begin()+index);
	decreaseOpHashAfter(index);

	delete pOp;
}

void MTParserRegistrar::decreaseOpHashAfter(unsigned int index)
{	
	unsigned int hashID;
	for(hashID=0; hashID<MTREGISTRAR_OPHASHSIZE; hashID++)
	{
		unsigned int t;
		for(t=0; t<m_opHash[hashID].size(); t++)
		{
			if( m_opHash[hashID][t] > index )
			{
				m_opHash[hashID][t]--;				
			}			
		}
	}
}

void MTParserRegistrar::removeFromOpHash(MTOperatorI *pOp)
{
	unsigned int hashID = getOpHashKey(pOp->getSymbol());

	unsigned int nbOps = m_opHash[hashID].size();
	unsigned int t;

	for( t=0; t<nbOps; t++ )
	{
		if( getOpByHashID(hashID, t)->pOp == pOp )
		{			
			m_opHash[hashID].erase(	m_opHash[hashID].begin()+t );
			return;
		}
	}

	throwDefExcep(MTDEFEXCEP_ItemNotFound, pOp->getSymbol());
}


void MTParserRegistrar::defValidateFunc(MTFunctionI *pFunc)const throw(MTParserException)
{
	MTSTRING funcName = pFunc->getSymbol();

	// function name can't be null
	if( funcName.size() == 0 )
	{
		throwDefExcep(MTDEFEXCEP_FuncNameNull, funcName);		
	}
	
	// function name cannot contains space characters
	unsigned int pos;
	if( MTTools::findSubStr(funcName, _T(" "), pos) )
	{
		throwDefExcep(MTDEFEXCEP_FuncNameSpace, funcName);		
	}

	// validate that this symbol is not already defined...
	unsigned int index;
	if( findFunctionExact(funcName.c_str(), pFunc->getNbArgs(), index) )
	{		
		throwDefExcep(MTDEFEXCEP_FuncAlreadyDefined, funcName);
	}

	// function name cannot contains syntax element characters...
	MTCHAR syntaxConflict;
	if( !defValidateSyntaxConflict(getSyntax(), funcName, syntaxConflict) )
	{
		MTSTRING conflictStr;
		conflictStr = syntaxConflict;
		throwDefExcep(MTDEFEXCEP_FuncNameSyntaxConflict, funcName, conflictStr);
	}

	// function name cannot contains operator characters...
	MTSTRING opConflict;
	if( !defValidateOpSymbolConflict(funcName, opConflict) )
	{
		throwDefExcep(MTDEFEXCEP_FuncNameOpConflict, funcName, opConflict);

	}
}


bool MTParserRegistrar::defValidateOpSymbolConflict(const MTSTRING &word, MTSTRING &conflict)const
{
	unsigned int size = word.size();
	unsigned int t;
	for( t=0; t<size; t++ )
	{
		if( areNextCharsOpString(word.c_str()+t, word.size()-t, conflict) )
		{
			return false;	// conflict
		}
	}

	return true;	// no conflict
}

// This method is very often called while in the compilation step.  So performance must be high.
bool MTParserRegistrar::areNextCharsOpString(const MTCHAR *str, unsigned int strLength, MTSTRING &symbol)const
{
	// assume that the operators are ordered by symbol length (decreasing order)	
	
	unsigned int t;
	
	// compute the hash table indice
	unsigned int hashID = getOpHashKey(str);
	unsigned int nbOps = m_opHash[hashID].size();	

	for( t=0; t<nbOps; t++ )
	{
		unsigned int symbolLength = getOpByHashID(hashID, t)->symbolLength;		

		if( symbolLength <= strLength )
		{
			if( MTTools::isStrBegin(str, getOpByHashID(hashID, t)->symbol.c_str(), strLength, symbolLength) )
			{
				symbol = getOpByHashID(hashID, t)->symbol.c_str();
				return true;

			}		
		}
	}

	return false;
}


unsigned int MTParserRegistrar::getNbDefinedFuncs()const
{
	return m_funcList.size();
}

void MTParserRegistrar::setVarFactory(MTVariableFactoryI *pFactory)
{
	assert( pFactory != NULL );		// must be a valid object
	
	if( m_pVarFactory != NULL )
	{
		delete m_pVarFactory;
		m_pVarFactory = NULL;
	}

	m_pVarFactory = pFactory;
}

void MTParserRegistrar::defineVar(const MTCHAR *symbol) throw(MTParserException)
{
	MTVariableI *pVar = m_pVarFactory->create(symbol);

	if( pVar == NULL )
	{
		// cannot create this variable!
		throwDefExcep(MTDEFEXCEP_ItemNotFound, symbol, _T(""));
	}

	defineVar(pVar);
}

void MTParserRegistrar::defineVar(MTVariableI *pVar) throw(MTParserException)
{
	MTSTRING varName = pVar->getSymbol();
	
	try
	{
		defValidateVar(varName);
	}
	catch( MTParserException &e )
	{
		
		delete pVar;		

		// rethrow the same exception
		throw(e);		
	}

	registerVar(pVar);	
}

void MTParserRegistrar::registerVar(MTVariableI *pVar)
{
	SVariableInfo *pVarInfo = new SVariableInfo;	
	pVarInfo->pVar = pVar;	
	pVarInfo->index = m_variableList.size();
	
	m_variableList.push_back(pVarInfo);
	m_variableMap.insert(TVariableMap::value_type(pVar->getSymbol(), pVarInfo));
}

const MTParserRegistrar::SVariableInfo* MTParserRegistrar::getVarInfo(const MTSTRING &varName)const
{		
	TVariableMap::const_iterator it = m_variableMap.find(varName);
	if( it !=  m_variableMap.end() )
	{
		return (*it).second;
	}
	else
	{
		return NULL;	// variable not found
	}
}

void MTParserRegistrar::defValidateVar(const MTSTRING &varName)const throw(MTParserException)
{

	// variable name can't be null
	if( varName.size() == 0 )
	{
		throwDefExcep(MTDEFEXCEP_VarNameNull, varName);		
	}

	// variable name cannot contains space characters
	unsigned int pos;
	if( MTTools::findSubStr(varName, _T(" "), pos) )
	{
		throwDefExcep(MTDEFEXCEP_VarNameSpace, varName);		
	}

	// variable name cannot be used twice!
	if( isVarDefined(varName.c_str()) != NULL )
	{		
		throwDefExcep(MTDEFEXCEP_VarAlreadyDefined, varName);
	}

	// variable name cannot contain only numbers... 
	if( MTTools::isOnlyNum(varName, m_syntax.decimalPoint) )
	{		
		throwDefExcep(MTDEFEXCEP_VarNameOnlyNum, varName);
	}	

	// variable name must not be a constant name...
	unsigned int index;
	if( findConst(varName.c_str(), index) )
	{
		throwDefExcep(MTDEFEXCEP_VarNameConstConflict, varName);
	}

	// variable name cannot contain syntax character...
	MTCHAR syntaxConflict;
	if( !defValidateSyntaxConflict(getSyntax(), varName, syntaxConflict) )
	{
		MTSTRING conflictStr;
		conflictStr = syntaxConflict;
		throwDefExcep(MTDEFEXCEP_VarNameSyntaxConflict, varName, conflictStr);
	}
	
	// variable name cannot contains operator characters...
	MTSTRING opConflict;
	if( !defValidateOpSymbolConflict(varName, opConflict) )
	{
		throwDefExcep(MTDEFEXCEP_VarNameOpConflict, varName, opConflict);

	}
}

void MTParserRegistrar::redefineVar(MTVariableI *pVar) throw(MTParserException)
{
	// try to find the variable and REPLACE it
	TVariableMap::iterator it = m_variableMap.find(pVar->getSymbol());
	if( it !=  m_variableMap.end() )
	{
		delete (*it).second->pVar;		// delete the old object
		(*it).second->pVar = pVar;		// put the new one								
	}
	else
	{
		// variable not found...
		MTSTRING symbol = pVar->getSymbol();
		delete pVar;	// delete it because we own it
		throwDefExcep(MTDEFEXCEP_ItemNotFound, symbol);
	}
}

void MTParserRegistrar::undefineVar(const MTCHAR *symbol) throw(MTParserException)
{	
	// try to find the variable and delete it
	TVariableMap::iterator it = m_variableMap.find(symbol);
	if( it !=  m_variableMap.end() )
	{
		delete (*it).second->pVar;
		(*it).second->pVar = NULL;				

		m_variableList.erase(m_variableList.begin()+(*it).second->index);	// use the up-to-date key	
		delete (*it).second;

		m_variableMap.erase(it);				

		m_varKeyVersion++;	// invalidate all variable keys
		updateVarKeys();
								
	}
	else
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, symbol);	// variable not found
	}

}

bool MTParserRegistrar::isVarDefined(const MTCHAR *symbol)const
{
	return getVarInfo(symbol) != NULL;
}
	
MTVariableI* MTParserRegistrar::getVarBySymbol(const MTCHAR *symbol)const throw(MTParserException)
{
	const SVariableInfo* pInfo = getVarInfo(symbol);

	if( pInfo == NULL )
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, symbol);
	}

	return pInfo->pVar;
}

MTVariableI* MTParserRegistrar::getVar(unsigned int index)const throw(MTParserException)
{
	return getVarBySymbol(getVarSymbol(index).c_str());
}

unsigned int MTParserRegistrar::getNbDefinedVars()const
{
	return m_variableList.size();
}
MTSTRING MTParserRegistrar::getVarSymbol(unsigned int index)const throw(MTParserException)
{
	if( index < 0 || index >= m_variableList.size() )
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, index);	
	}

	return m_variableList[index]->pVar->getSymbol();
}

void MTParserRegistrar::updateVarKeys()
{
	std::vector<SVariableInfo*>::iterator it = m_variableList.begin();
	std::vector<SVariableInfo*>::iterator end = m_variableList.end();

	unsigned int t=0;
	
	for( ; it!=end; it++ )
	{
		(*it)->index = t;
		t++;
	}
}


bool MTParserRegistrar::isAFunction(const MTCHAR *word, unsigned int &index)const
{
	if( m_funcMap.count(word) > 0 )
	{
		// return the first function with this symbol
		index = (*m_funcMap.find(word)).second;
		return true;
	}
	else
	{
		return false;
	}
}

bool MTParserRegistrar::findFunction(const MTCHAR *word, int nbArgs, unsigned int &index)const
{	
	unsigned int nbFuncs = m_funcMap.count(word);

	if( nbFuncs == 0 )
	{
		return false;	// no function with this name
	}
	
	int undefNbArgs = -1;
	TFuncMap::const_iterator it = m_funcMap.find(word);

	for( unsigned int t=0; t<nbFuncs; t++ )
	{
		if( m_funcList[(*it).second].pFunc->getNbArgs() == c_MTNbArgUndefined && nbArgs > 0)
		{
			// take this function if no exact match
			// the requested number of arguments
			undefNbArgs = (*it).second;					
		}
		else if( m_funcList[(*it).second].pFunc->getNbArgs() == nbArgs) 
		{			
			// exact macth! take that function
			index = (*it).second;
			return true;
		}

		it++;
	}

	if( undefNbArgs != -1 )
	{
		// return the default function with undefined number
		// of arguments
		index = undefNbArgs;
		return true;		
	}
	else
	{
		return false; // no function found
	}
}

std::vector<MTFunctionI*> MTParserRegistrar::findFunctions(const MTCHAR *symbol)const
{
	std::vector<MTFunctionI*> functions;

	unsigned int nbFuncs = m_funcMap.count(symbol);

	TFuncMap::const_iterator it = m_funcMap.find(symbol);

	for( unsigned int t=0; t<nbFuncs; t++ )
	{
		functions.push_back(getFunc((*it).second));
		it++;
	}

	return functions;
}

bool MTParserRegistrar::findFunctionExact(const MTCHAR *word, int nbArgs, unsigned int &index)const
{

	unsigned int nbFuncs = m_funcMap.count(word);

	if( nbFuncs == 0 )
	{
		return false;	// no function with this name
	}

	TFuncMap::const_iterator it = m_funcMap.find(word);

	for( unsigned int t=0; t<nbFuncs; t++ )
	{
		if( m_funcList[(*it).second].pFunc->getNbArgs() == nbArgs) 
		{			
			// exact macth! take that function
			index = (*it).second;
			return true;
		}

		it++;
	}

	return false;	// no function found
}

MTOperatorI* MTParserRegistrar::getOp(unsigned int index)const throw(MTParserException)
{
	if( index < 0 || index >= m_opList.size() )
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, index);	
	}

	return m_opList[index].pOp;
}
MTFunctionI* MTParserRegistrar::getFunc(unsigned int index)const throw(MTParserException)
{
	if( index < 0 || index >= m_funcList.size() )
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, index);	
	}

	return m_funcList[index].pFunc;
}

void MTParserRegistrar::undefineConst(const MTCHAR *name) throw(MTParserException)
{	
	TConstMap::iterator it = m_constMap.find(name);
	if( it !=  m_constMap.end() )
	{	
		m_constList.erase(m_constList.begin()+(*it).second);
		m_constMap.erase(it);				

		rebuildConstMap();
	}
	else
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, name);
	}
}

void MTParserRegistrar::rebuildConstMap()
{
	m_constMap.clear();

	
	for(unsigned int t=0; t<m_constList.size(); t++ )
	{
		m_constMap.insert(TConstMap::value_type(m_constList[t].name, t));
	}
}



#ifdef _MTPARSER_USE_PLUGIN
void MTParserRegistrar::loadPlugin(const MTCHAR *clsid) throw(MTParserException)
{
	// convert the string to a clsid...
	CLSID nClsid;
	if( CLSIDFromString((wchar_t*)MTSTRINGTOUNICODE(clsid), &nClsid) != NOERROR )
	{			
		throwDefExcep(MTDEFEXCEP_PluginNotFound, clsid);		
	}	
	
	// instanciate the plug-in...
	IMTParserPluginPtr pPlugin;	
	HRESULT hRes = pPlugin.CreateInstance(nClsid);
	if( FAILED(hRes) )
	{
		if( hRes == E_NOINTERFACE || 
			hRes == 0x80029c4a)		// error loading type library/DLL
		{
			// the most common problem for these errors is the missing tlb file
			// or that the file is not registered
			throwDefExcep(MTDEFEXCEP_PluginTypeLibNotFound, MTPLUGIN_TYPELIBFILE);
		}
		else
		{
			throwDefExcep(MTDEFEXCEP_PluginNotFound, clsid);				
		}
		
	}	

	m_pluginPtr.push_back(pPlugin);
	
	try
	{	
		// validate the parser interface version...
		// because we use directly c++ objects from the plug-in, we must
		// be sure that they implement the righ interfaces.
		BSTR version = pPlugin->getMTParserVersion();
		MTSTRING verStr = UNICODETOMTSTRING(version);
		SysFreeString(version);
		if( lstrcmp(verStr.c_str(), MTPARSER_INTERFACE_VERSION) != 0 )
		{		
			MTTHROW(MTExcepData (	MTDEFEXCEP_PluginVersion,
									MTEXCEPARG_ITEMNAME, clsid,
									MTEXCEPARG_CONFLICTITEMNAME, MTPARSER_INTERFACE_VERSION,
									MTEXCEPARG_PARAM1, verStr.c_str()))			
		}			
		
		int t;

		try
		{
			// constants loading...	
			int nbConsts = pPlugin->getNbConsts();		
			
			SMTPluginConst constInfo;
			
			for( t=0; t<nbConsts; t++ )
			{
				constInfo = pPlugin->getConst(t);
				MTSTRING constName = UNICODETOMTSTRING(constInfo.name);
				defineConst(constName.c_str(), constInfo.val);
				SysFreeString(constInfo.name);	
			}
			
			
			// operators loading...
			
			int nbOps = pPlugin->getNbOps();	
			for( t=0; t<nbOps; t++ )
			{				
				defineOp((MTOperatorI*)pPlugin->newOp(t));
			}
			

			// functions loading...	
			int nbFuncs = pPlugin->getNbFuncs();	
			for( t=0; t<nbFuncs; t++ )
			{
				defineFunc((MTFunctionI*)pPlugin->newFunc(t));
			}
		}
		catch( MTParserException &e )
		{
			MTRETHROW(MTExcepData(	MTDEFEXCEP_PluginDefConflict,
									MTEXCEPARG_ITEMNAME, clsid ), e)
									
		}		
	}
	catch( _com_error )
	{
		// something is wrong with this plug-in...must be the version!
		throwDefExcep(MTDEFEXCEP_PluginVersion, clsid, MTPARSER_INTERFACE_VERSION);					
	}	
}
#endif

void MTParserRegistrar::defineConst(const MTCHAR *name, MTDOUBLE val) throw(MTParserException)
{
	MTSTRING constName = name;
	defValidateConst(constName);
	
	registerConst(name, val);

}

void MTParserRegistrar::registerConst(const MTCHAR *name, MTDOUBLE val)
{
	SConstantInfo constInfo;	
	constInfo.name = name;
	constInfo.val = val;	
	
	m_constMap.insert(TConstMap::value_type(name, m_constList.size()));
	m_constList.push_back(constInfo);
}

bool MTParserRegistrar::findConst(const MTCHAR *constName, unsigned int &index)const
{
	TConstMap::const_iterator it = m_constMap.find(constName);
	if( it !=  m_constMap.end() )
	{
		index = (*it).second;
		return true;	// constant found
	}
	else
	{
		return false;	// constant not found
	}	
}
void MTParserRegistrar::defValidateConst(const MTSTRING &constName)const throw(MTParserException)
{

	// constant name can't be null
	if( constName.size() == 0 )
	{
		throwDefExcep(MTDEFEXCEP_ConstNameNull, constName);		
	}

	// constant name cannot contains space characters
	unsigned int pos;
	if( MTTools::findSubStr(constName, _T(" "), pos) )
	{
		throwDefExcep(MTDEFEXCEP_ConstNameSpace, constName);		
	}

	// constant name cannot be used twice!
	unsigned int index;
	if( findConst(constName.c_str(), index) )
	{		
		throwDefExcep(MTDEFEXCEP_ConstAlreadyDefined, constName);
	}

	// constant name cannot contains only numbers... 
	if( MTTools::isOnlyNum(constName, m_syntax.decimalPoint) )
	{		
		throwDefExcep(MTDEFEXCEP_ConstNameOnlyNum, constName);
	}

	// constant name cannot contains syntax element characters...
	MTCHAR syntaxConflict;
	if( !defValidateSyntaxConflict(getSyntax(), constName, syntaxConflict) )
	{
		MTSTRING conflictStr;
		conflictStr = syntaxConflict;
		throwDefExcep(MTDEFEXCEP_ConstNameSyntaxConflict, constName, conflictStr);
	}

	// constant name cannot contains operator characters...
	MTSTRING opConflict;
	if( !defValidateOpSymbolConflict(constName, opConflict) )
	{
		throwDefExcep(MTDEFEXCEP_ConstNameOpConflict, constName, opConflict);
	}

	// no variable can have the same name as this constant...
	if( isVarDefined(constName.c_str()) != NULL )
	{
		throwDefExcep(MTDEFEXCEP_ConstNameVarConflict, constName);
	}

}

unsigned int MTParserRegistrar::getNbDefinedConsts()const
{
	return m_constList.size();
}

void MTParserRegistrar::getConst(unsigned int index, MTSTRING &constName, MTDOUBLE &val)const throw(MTParserException)
{
	if( index < 0 || index >= m_constList.size() )
	{
		throwDefExcep(MTDEFEXCEP_ItemNotFound, index);	
	}
	
	constName = m_constList[index].name;
	val = m_constList[index].val;
}

void MTParserRegistrar::throwDefExcep(const MTCHAR * id, MTSTRING itemName, MTSTRING conflictItemName)const throw(MTParserException)
{
	MTExcepData data(	id,
						MTEXCEPARG_ITEMNAME, itemName.c_str(),
						MTEXCEPARG_CONFLICTITEMNAME, conflictItemName.c_str() );
	
	MTTHROW(data)
}

void MTParserRegistrar::throwDefExcep(const MTCHAR * id, int param)const throw(MTParserException)
{
	MTExcepData data(	id,
						MTEXCEPARG_PARAM1, MTTools::longToS(param).c_str() );						

	MTTHROW(data)
}