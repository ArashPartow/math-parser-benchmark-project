#include "MTParser.h"
#include "MTParserDefOps.h"
#include "MTParserDefFuncs.h"
#include "MTParserRegistrar.h"
#include "MTParserCompiler.h"
#include "MTTools.h"	

#ifdef _MTPARSER_USE_PLUGIN
	#include "MTParserLocalizer.h"
#endif

#include "MTParserMacroFunc.h"
#include "MTSearchFile.h"

#ifdef _MTPARSER_USE_PLUGIN
	#import "../MTParserInfoFile/MTParserInfoFile/_MTParserInfoFile.tlb" no_namespace
#endif

MTParser::MTParser()
{	
	// object construction...
	m_pRegistrar = new MTParserRegistrar();
	m_pCompiler = new MTParserCompiler( m_pRegistrar);	

	// set the default syntax...
	MTSyntax syntax;
	syntax.argumentSeparator = MTDEFVAL_FUNCARG_SEPARATOR;
	syntax.decimalPoint = MTDEFVAL_DECIMALPOINT;	

	m_pRegistrar->setSyntax(syntax);
	m_pRegistrar->setVarFactory(new MemVariableFactory());		

	// set the default configuration...
	enableAutoVarDefinition(false);
	
	// add default operators and functions
	defineDefOps();
	defineDefFuncs();	
	defineDefConsts();	

	init();

	resetExpression();
}

MTParser::MTParser(const MTParser &obj) throw(MTParserException)
{	
	m_pCompiler = NULL;
	m_pRegistrar = NULL;

	operator=(obj);	

	init();
}

MTParser::MTParser(MTCompilerI *pCompiler, MTRegistrarI *pRegistrar) throw(MTParserException)
{
	m_pCompiler = NULL;
	m_pRegistrar = NULL;

	copy(pCompiler, pRegistrar);
	init();
}

void MTParser::init()
{		
	m_pItemStack = m_pCompiler->getItemStack();	
}

MTParser& MTParser::operator=(const MTParser &obj) throw(MTParserException)
{
	copy(obj.getCompiler(), obj.getRegistrar());

	// set the current expression
	try
	{
		compile(obj.getExpression().c_str());

	}
	catch( MTException )
	{
		// the expression is invalid so put an expty expression
		m_pCompiler->resetExpression();
	}

	computeExpressionIterator();

	return *this;
}

void MTParser::copy(MTCompilerI *pCompiler, MTRegistrarI *pRegistrar) throw(MTParserException)
{
	clean();	

	m_pRegistrar = pRegistrar->spawn();
	m_pCompiler = pCompiler->spawn(m_pRegistrar);

	m_pItemStack = m_pCompiler->getItemStack();	
	computeExpressionIterator();
}

void MTParser::defineDefOps() throw(MTParserException)
{
	defineOp(new AddOp());	
	defineOp(new UnaryAddOp());		
	defineOp(new MinusOp());	
	defineOp(new MultOp());		
	defineOp(new DivOp());	
	defineOp(new ExpOp());
	defineOp(new UnaryMinusOp());
	defineOp(new ModuloOp());
	defineOp(new GreaterThanOp());
	defineOp(new LesserThanOp());	
	defineOp(new GreaterEqualThanOp());
	defineOp(new LesserEqualThanOp());
	defineOp(new NotEqualOp());
	defineOp(new EqualOp());
	defineOp(new AndOp());
	defineOp(new OrOp());
	defineOp(new NotOp());
}

void MTParser::defineDefFuncs() throw(MTParserException)
{
	defineFunc(new RoundFct());	
	defineFunc(new SinFct());	
	defineFunc(new ArcSinFct());
	defineFunc(new SinhFct());
	defineFunc(new CosFct());
	defineFunc(new ArcCosFct());
	defineFunc(new CoshFct());
	defineFunc(new TanFct());
	defineFunc(new ArcTanFct());
	defineFunc(new TanhFct());
	defineFunc(new SqrtFct());
	defineFunc(new MinFct());
	defineFunc(new Min3Fct());			
	defineFunc(new MinUndefFct());	
	defineFunc(new MaxFct());
	defineFunc(new Max3Fct());	
	defineFunc(new MaxUndefFct());	
	defineFunc(new AbsFct());
	defineFunc(new RandFct());
	defineFunc(new RandMinMaxFct());
	defineFunc(new CeilFct());
	defineFunc(new FloorFct());
	defineFunc(new LogFct());
	defineFunc(new Log10Fct());
	defineFunc(new AvgFct());
	defineFunc(new SumFct());
	defineFunc(new FactorialFct());
	defineFunc(new IfFct());	
	defineFunc(new IsNaNFct());
	defineFunc(new IsFiniteFct());	
	defineFunc(new HexConvFunc());
	defineFunc(new BinConvFunc());		
}

void MTParser::defineDefConsts()
{
	defineConst(_T("NaN"), MTTools::generateNaN());
}

MTParser::~MTParser()
{	
	clean();
}

void MTParser::clean()
{
	if( m_pCompiler != NULL )
	{
		delete m_pCompiler;
		m_pCompiler = NULL;
	}

	if( m_pRegistrar != NULL )
	{
		delete m_pRegistrar;
		m_pRegistrar = NULL;
	}
}

void MTParser::useLocaleSettings() throw(MTParserException)
{
	LCID lcid = GetThreadLocale();						// get the current locale id
	MTCHAR buf[4];
	if( GetLocaleInfo(lcid, LOCALE_SDECIMAL, buf, 4) )	// get the decimal point character
	{
		MTSyntax syntax;
		syntax = getSyntax();	
		
		// make sure that the argument separator character is different
		// from the decimal point character
		syntax.argumentSeparator = ',';
		if( buf[0] == ',' )
		{
			syntax.argumentSeparator = ';';			
		}
		
		syntax.decimalPoint = buf[0];
		setSyntax(syntax);
	}

}

void MTParser::setSyntax(const MTSyntax &syntax) throw(MTParserException)
{
	m_pRegistrar->setSyntax(syntax);
}


MTSyntax MTParser::getSyntax()const
{
	return m_pRegistrar->getSyntax();
}

void MTParser::enableAutoVarDefinition(bool enable, MTVariableFactoryI *pFactory)
{
	if( pFactory == NULL )
	{
		m_pRegistrar->setVarFactory(new MemVariableFactory());		
	}
	else
	{
		m_pRegistrar->setVarFactory(pFactory);
	}

	m_pCompiler->enableAutoVarDefinition(enable);
}

bool MTParser::isAutoVarDefinitionEnabled()const
{
	return m_pCompiler->isAutoVarDefinitionEnabled();
}

void MTParser::defineVar(const MTCHAR *symbol, MTDOUBLE *pVal) throw(MTParserException)
{	
	MemVariableEvaluator *pVarEvaluator = new MemVariableEvaluator();	
	pVarEvaluator->setValPtr(pVal);
	pVarEvaluator->setSymbol(symbol);
	
	((MTRegistrarPublicI*)m_pRegistrar)->defineVar(pVarEvaluator);	
}

void MTParser::defineVar(MTVariableI *pVar) throw(MTParserException)
{
	((MTRegistrarPublicI*)m_pRegistrar)->defineVar(pVar);
}

void MTParser::redefineVar(const MTCHAR *symbol, MTDOUBLE *pVal) throw(MTParserException)
{
	MemVariableEvaluator *pVarEvaluator = new MemVariableEvaluator();
	pVarEvaluator->setValPtr(pVal);
	pVarEvaluator->setSymbol(symbol);
	
	redefineVar(pVarEvaluator);
}

void MTParser::redefineVar(MTVariableI *pVar) throw(MTParserException)
{
	try
	{
		// first update the variable in the compiler while it is still a valid object
		m_pCompiler->onVarRedefined( pVar );			
	}
	catch( MTParserException e)
	{
		m_pCompiler->resetExpression();	// the expression is now invalid

		delete pVar;	// make sure to delete the variable since we own it
		throw e;
	}	

	try
	{
		// now, redefineVar will delete the current variable object
		m_pRegistrar->redefineVar(pVar);		
	}
	catch( MTParserException e)
	{
		m_pCompiler->resetExpression();	// the expression may be invalid
		throw e;
	}
}

void MTParser::undefineVar(const MTCHAR *symbol) throw(MTParserException)
{
	m_pRegistrar->undefineVar(symbol);
	m_pCompiler->resetExpression();
}

void MTParser::undefineAllVars()
{
	m_pRegistrar->undefineAllVars();
	m_pCompiler->resetExpression();
}	

MTVariableI* MTParser::getVarBySymbol(const MTCHAR *symbol)const throw(MTParserException)
{
	return m_pRegistrar->getVarBySymbol(symbol);
}

MTVariableI* MTParser::getVar(unsigned int index)const throw(MTParserException)
{
	return m_pRegistrar->getVar(index);
}

unsigned int MTParser::getNbDefinedVars()const
{
	return m_pRegistrar->getNbDefinedVars();		
}

unsigned int MTParser::getNbUsedVars()const
{
	return m_pCompiler->getNbUsedVars();
}

MTSTRING MTParser::getUsedVar(unsigned int index)const
{
	return m_pCompiler->getUsedVar(index);
}

#ifdef _MTPARSER_USE_PLUGIN
void MTParser::loadPlugin(const MTCHAR *clsid) throw(MTParserException)
{
	m_pRegistrar->loadPlugin(clsid);
}
#endif

#ifdef _MTPARSER_USE_PLUGIN
void MTParser::loadAllPlugins(const MTCHAR *directory, const MTCHAR *searchPattern) throw(MTParserException)
{
	MTSearchFile search;
	std::vector<MTSTRING> directories;	
	std::vector<MTSTRING> searchPatterns;
	std::vector<MTSTRING> results;

	directories.push_back(directory);
	searchPatterns.push_back(searchPattern);	
	search.search(directories, searchPatterns, results);

	IMTParserInfoFilePtr infoFile;
	infoFile.CreateInstance(__uuidof(CATLMTParserInfoFile));	// CATLMTParserLocalizerFile is the coclass
	
	if( infoFile == NULL )
	{
		// COM object not found...		
		MTTHROW(MTExcepData (	MTLOCEXCEP_MTParserInfoObjectNotFound ) )
	}

	MTParserException exceps;	

	for(unsigned int t=0; t<results.size(); t++ )
	{
		// load the file...
		try
		{
			infoFile->load(results[t].c_str());
			SATLLibInfo libInfo = infoFile->getLib();

			MTSTRING type = UNICODETOMTSTRING(libInfo.type);
			MTSTRING clsid = UNICODETOMTSTRING(libInfo.data2);

			SysFreeString(libInfo.data1);
			SysFreeString(libInfo.data2);
			SysFreeString(libInfo.type);
			SysFreeString(libInfo.desc);
			SysFreeString(libInfo.title);
			SysFreeString(libInfo.version);			

			// if this is a plug-in, then load it
			if( lstrcmp(type.c_str(), _T("plugin"))==0)
			{
				loadPlugin(clsid.c_str());
			}
			
		}
		catch( _com_error )
		{
			// unable to open this info file...		
			MTExcepData data(	MTLOCEXCEP_InfoFileOpenFailed,
								MTEXCEPARG_ITEMNAME, results[t].c_str());
			MTSTRING desc = MTParserExcepStrEng::format(data);
			exceps.add(__LINE__,  _T(__FILE__), 0, data, desc.c_str());			
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
#endif

void MTParser::defineConst(const MTCHAR *name, MTDOUBLE val) throw(MTParserException)
{
	m_pRegistrar->defineConst(name, val);
}

unsigned int MTParser::getNbDefinedConsts()const
{
	return m_pRegistrar->getNbDefinedConsts();
}

void MTParser::getConst(unsigned int index, MTSTRING &constName, MTDOUBLE &val)const throw(MTParserException)
{
	m_pRegistrar->getConst(index, constName, val);
}

void MTParser::undefineConst(const MTCHAR *name) throw(MTParserException)
{
	m_pRegistrar->undefineConst(name);
	m_pCompiler->resetExpression();
}

void MTParser::undefineFunc(MTFunctionI *pFunc) throw(MTParserException)
{
	m_pRegistrar->undefineFunc(pFunc);
	m_pCompiler->resetExpression();
}

void MTParser::undefineFuncById(const MTCHAR *id) throw(MTParserException)
{		
	unsigned int nbFuncs = getNbDefinedFuncs();
	unsigned int index;	
	for(index=0; index<nbFuncs; index++)
	{
		if( lstrcmp(getFunc(index)->getID(), id) == 0 )
		{
			undefineFunc(getFunc(index));	
			return;
		}
	}	
}


void MTParser::undefineFuncsBySymbol(const MTCHAR *symbol) throw(MTParserException)
{	
	std::vector<MTFunctionI*> functions = m_pRegistrar->findFunctions(symbol);
	
	unsigned int index;	
	for(index=0; index<functions.size(); index++)
	{
		undefineFunc(functions[index]);
	}	
}

void MTParser::undefineOp(MTOperatorI *pOp) throw(MTParserException)
{
	m_pRegistrar->undefineOp(pOp);
	m_pCompiler->resetExpression();
}

void MTParser::undefineOpById(const MTCHAR *id) throw(MTParserException)
{		
	unsigned int nbOps = getNbDefinedOps();
	unsigned int index;	
	for(index=0; index<nbOps; index++)
	{
		if( lstrcmp(getOp(index)->getID(), id) == 0 )
		{
			undefineOp(getOp(index));	
			return;
		}
	}	
}



void MTParser::undefineOpsBySymbol(const MTCHAR *symbol) throw(MTParserException)
{
	unsigned int index;
	MTSTRING symbolStr = symbol;	

	// undefine both versions: unary and binary operator...

	if( m_pRegistrar->findOp(symbolStr.c_str(), false, index) )
	{
		undefineOp(m_pRegistrar->getOp(index));
	}

	if( m_pRegistrar->findOp(symbolStr.c_str(), true, index) )
	{
		undefineOp(m_pRegistrar->getOp(index));
	}
}


void MTParser::defineOp( MTOperatorI *pOp) throw(MTParserException)
{
	m_pRegistrar->defineOp(pOp);
}

unsigned int MTParser::getNbDefinedOps()const
{
	return m_pRegistrar->getNbDefinedOps();
}

MTOperatorI* MTParser::getOp(unsigned int index)const throw(MTParserException)
{
	return m_pRegistrar->getOp(index);
}

void MTParser::defineFunc( MTFunctionI *pFunc) throw(MTParserException)
{
	m_pRegistrar->defineFunc(pFunc);
}

void MTParser::defineMacro(const MTSTRING &prototype, const MTSTRING &macro, const MTSTRING &description ) throw(MTParserException)
{
	MTMacroFct *pFct = new MTMacroFct();

	try
	{
		pFct->create(prototype, macro, description, getCompiler(), getRegistrar());		
	}	
	catch( MTParserException &e )
	{		
		delete pFct;
		throw(e);		
	}

	try
	{		
		defineFunc(pFct);
	}	
	catch( MTParserException &e )
	{		
		// the pFct has already been deleted by the Registrar
		throw(e);		
	}
}
unsigned int MTParser::getNbDefinedFuncs()const
{
	return m_pRegistrar->getNbDefinedFuncs();
}

MTFunctionI* MTParser::getFunc(unsigned int index)const throw(MTParserException)
{
	return m_pRegistrar->getFunc(index);
}

MTDOUBLE MTParser::evaluate(const MTCHAR *expr) throw(MTParserException)
{	
	compile(expr);	
	return evaluate();
}

void MTParser::resetExpression()
{
	m_pCompiler->resetExpression();
	computeExpressionIterator();
}

void MTParser::compile(const MTCHAR *expr) throw(MTParserException)
{	
	m_pCompiler->compile(expr);	
	computeExpressionIterator();
}

bool MTParser::isConstant()const
{
	return m_pCompiler->isConstant();
}

MTSTRING MTParser::getExpression()const
{
	return m_pCompiler->getExpression();
}

void MTParser::computeExpressionIterator()
{
	m_beginIter = m_pItemStack->begin();
	m_endIter = m_pItemStack->end();
	m_itemStackSize = m_pItemStack->size();		// the size is at least 1

	// if the expression is constant, return the result immediately	
	if( (m_endIter-1)->isEvaluated)
	{
		m_constValue = (m_endIter-1)->val;
		m_itemStackSize = 0;		// 0 item to indicate a constant expression		
	}
}

void MTParser::evaluateBatch(unsigned int nbEvals, MTDOUBLE *pResults)
{
	for(unsigned int t=0; t<nbEvals; t++)
	{
		*pResults = evaluate();
		pResults++;
	}
}

// Macro to evaluate the item pointed by the iterator.  This macro
// ease the writing of inline item evaluations
#define EVALUATEITER(iter) *iter->pParentItemArg = iter->pEval->evaluate(iter->nbArgs, iter->pArg);popIter++;				

// Same thing as EVALUATEITER but doesn't increment the iterator (saves some CPU!)
#define EVALUATEITERLAST(iter) *iter->pParentItemArg = iter->pEval->evaluate(popIter->nbArgs, iter->pArg);				

// Performance note: the implementation is directly in this object because
// a delegation would hurt too much the peformance.  So, this is why there is
// no "evaluator" object like a Registrar and a Compiler.
MTDOUBLE MTParser::evaluate()const
{	
	// Fast Iterative algorithm	

	register ItemInfoStack::const_iterator popIter = m_beginIter;

	// To avoid using a for loop, the loop has been expanded for common cases.
	// The performance is greatly increased.
	switch( m_itemStackSize )
	{		
	
	case 0:
		// constant value
		return m_constValue;
	
	case 1:
		EVALUATEITERLAST(popIter)
		return popIter->val;			

	case 2:
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;		

	case 3:
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	
		
	case 4:
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;		
		
	
	case 5:
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;		

	case 6:		
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	

	case 7:		
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	

	case 8:		
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	

	case 9:		
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	
	
	case 10:		
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	

	case 11:		
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	

	case 12:		
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	

	case 13:			
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)
		return popIter->val;	

	
	case 14:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 15:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;	
		
	case 16:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 17:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 18:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 19:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 20:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 21:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 22:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 23:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 24:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 25:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 26:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)		
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 27:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)		
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 28:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)		
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;		

	case 29:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;	

	case 30:	
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITER(popIter)
		EVALUATEITERLAST(popIter)		
		return popIter->val;	

	default:		

		// handle all other cases with the loop overhead...

		for( ; popIter != m_endIter; popIter++ )
		{	
			*popIter->pParentItemArg = popIter->pEval->evaluate(popIter->nbArgs, popIter->pArg);				
		}	
		
		// the result is the last item value
		return (m_endIter-1)->val;		
	}
}


inline MTDOUBLE MTParser::getLastResult()const
{	
	// the result is the last item value
	if( m_itemStackSize > 0 )
	{
		return (m_endIter-1)->val;
	}
	else
	{
		return m_constValue;
	}	
}

bool MTParser::isNaN()const
{	
	return _isnan(getLastResult()) != 0;
}

MTDOUBLE MTParser::getNaN()const
{
	return MTTools::NaN;
}

bool MTParser::isFinite()const
{
	return _finite(getLastResult()) != 0;
}

MTRegistrarI* MTParser::getRegistrar()const
{
	return m_pRegistrar;
}	

MTCompilerI* MTParser::getCompiler()const
{
	return m_pCompiler;
}

//*************************************
// MemVariableEvaluator

MTVariableI* MTParser::MemVariableEvaluator::spawn()
{ 
	MemVariableEvaluator *pObj = new MemVariableEvaluator(); 
	pObj->setSymbol(getSymbol());
	pObj->setValPtr(m_pVal);
	return pObj;			
}

//************************************
// MemVariableFactory

MTVariableFactoryI* MTParser::MemVariableFactory::spawn()
{ 
	return new MemVariableFactory(); 
}
//*************************************
// MTDoubleVector

MTDoubleVector::MTDoubleVector(const MTCHAR *symbol)
{
	m_symbol = symbol;
	m_pValues = NULL;
	m_nbValues = 0;
}

void MTDoubleVector::setValues(MTDOUBLE *pValues, unsigned int nbValues)
{
	m_pValues = pValues;
	m_nbValues = nbValues;
	m_pos = 0;
}

void MTDoubleVector::resetGetPosition()
{
	m_pos = 0;
}
	
MTVariableI* MTDoubleVector::spawn()
{
	MTDoubleVector *pVar = new MTDoubleVector(getSymbol());
	
	pVar->setValues(m_pValues, m_nbValues);
	return pVar;
}

MTDOUBLE MTDoubleVector::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{
	MTDOUBLE val = m_pValues[m_pos];
	m_pos = (m_pos+1)%m_nbValues;
	return val;
}