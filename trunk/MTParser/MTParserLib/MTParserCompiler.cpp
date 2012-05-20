#include "MTParserCompiler.h"
#include "MTTools.h"
#include <windows.h>	// include after all other includes to make sure unicode is defined
#include <assert.h>



MTParserCompiler::MTParserCompiler(MTRegistrarI *pRegistrar)
{	
	m_pRegistrar = pRegistrar;	
	m_pParent = NULL;
	m_pCompilerState = NULL;

	m_defCompilerStateID = addState(new MTCompilerDefState);	
	resetExpression();

}

unsigned int MTParserCompiler::addState(MTCompilerStateI *pState)
{	
	m_pStates.push_back( pState );
	return m_pStates.size()-1;
}

MTCompilerI* MTParserCompiler::spawn(MTRegistrarI *pRegistrar) throw(MTParserException)
{
	MTParserCompiler *pObj = new MTParserCompiler( pRegistrar);	
	pObj->enableAutoVarDefinition(isAutoVarDefinitionEnabled());
			
	return pObj;
}

MTParserCompiler::~MTParserCompiler()
{
	clearItemStack(m_itemStack);
	clearUsedVars();
	
	for( unsigned int t=0; t<m_pStates.size(); t++ )
	{
		delete m_pStates[t];
		m_pStates[t] = NULL;
	}

	m_pStates.clear();	
}

void MTParserCompiler::setParent( MTCompilerI *pParent )
{
	m_pParent = pParent;
}

void MTParserCompiler::clearUsedVars()
{
	// delete variable stubs
	unsigned int nbUsedVars = m_usedVariables.size();	
	for( unsigned int t=0; t<nbUsedVars; t++ )
	{		
		if( m_usedVariables[t].isOwner )
		{
			delete m_usedVariables[t].pStub;				
		}
	}	

	m_usedVariables.clear();		// reset the used variable list	
}

void MTParserCompiler::resetExpression()
{
	clearUsedVars();
	m_originalPos.clear();	
	m_originalExpr = _T("");

	m_opStack.clear();
	m_curItemTypeStack.clear();
	
	clearItemStack(m_itemStack);
	pushDummyValue();		// to avoid crashing the parser if evaluate is called
							// without an expression
}

ItemInfoStack* MTParserCompiler::getItemStack()
{
	return &m_itemStack;
}

void MTParserCompiler::enableAutoVarDefinition(bool enable)
{
	m_isAutoVarDefinitionEnabled = enable;
}

bool MTParserCompiler::isAutoVarDefinitionEnabled()const
{
	return m_isAutoVarDefinitionEnabled;
}

void MTParserCompiler::compile(const MTCHAR *expr) throw(MTParserException)
{
	
	resetExpression();	
	clearItemStack(m_itemStack);	// remove the dummy value	
	
	m_syntax = m_pRegistrar->getSyntax();
	
	m_originalExpr = expr;
		
	parseExpression(m_originalExpr);	

	// the variable puts its value directly on the val member
	unsigned int nbUsedVars = getNbUsedVars(); 
	ItemInfoStack::iterator itemIter = m_itemStack.begin();
	for( unsigned int t=0; t<nbUsedVars; t++ )
	{
		// The first real variable on the stack is the last used variable in the list
		if( m_usedVariables[nbUsedVars-1-t].isOwner )
		{
			((MTVarStub*)m_usedVariables[nbUsedVars-1-t].pStub)->setValuePtr(&itemIter->val);

			// the real variable puts its value in its value member
			itemIter->pParentItemArg = &itemIter->val;		
			itemIter++;
		}	
	}
	
	updateParentValPtr();

	// remove all evaluated items from the stack
	// since their values have already been put in their
	// parent items	(constant folding optimization)
	removeAllEvaluatedItem(m_itemStack);
	
	// allow the expression to be evaluated only if there is something
	// to be evaluated...!
	if( m_itemStack.size() > 0 )
	{
		// the last item puts its result in its own val variable
		ItemInfoStack::iterator popIter = m_itemStack.end()-1;
		popIter->pParentItemArg = &popIter->val;					
	}		
	else
	{
		// empty expression, so return a dummy result: NaN
		pushDummyValue();		
	}
}

bool MTParserCompiler::isConstant()const
{
	// if the last item is evaluated, then this is a constant expression
	return (m_itemStack.end()-1)->isEvaluated;	
}

void MTParserCompiler::onVarRedefined(MTVariableI *pVar) throw(MTParserException)
{
	// if this is a used variable, replace the variable object
	unsigned int index;
	if( findUsedVar(pVar->getSymbol(), index) )
	{
		if( m_usedVariables[index].isOwner )
		{
			// find the variable and update the pointer
			ItemInfoStack::iterator itemIter = m_itemStack.begin();
			ItemInfoStack::iterator endIter = m_itemStack.end();
			while( itemIter != endIter )
			{				
				if( lstrcmp(itemIter->pEval->getSymbol(), pVar->getSymbol())==0 )
				{
					itemIter->pEval = pVar;
					return;
				}

				itemIter++;
			}
			
			// should have found the variable...
			assert(false);
		}
		else
		{
			// can't update stack pointers... not implemented yet
			assert(false);
		}
	}
}

void MTParserCompiler::pushDummyValue()
{
	SItemInfo exprInfo;		
	exprInfo.isEvaluated = true;
	exprInfo.val = MTTools::generateNaN();	
	m_itemStack.push_back(exprInfo);

}


// push an item type 
void MTParserCompiler::pushCurItemType()
{
	SParserCurItem itemType;
	itemType.current = e_ItemType_None;
	itemType.previous = e_ItemType_None;
	m_curItemTypeStack.push_back(itemType);
}

void MTParserCompiler::setCurItemType( EItemType type )
{
	int lastID = m_curItemTypeStack.size()-1;
	m_curItemTypeStack[lastID].previous = m_curItemTypeStack[lastID].current;
	m_curItemTypeStack[lastID].current = type;
}

MTParserCompiler::EItemType MTParserCompiler::getPrevItemType()
{
	int lastID = m_curItemTypeStack.size()-1;
	return m_curItemTypeStack[lastID].previous;
}

MTParserCompiler::EItemType MTParserCompiler::getCurItemType()
{
	int lastID = m_curItemTypeStack.size()-1;
	if( lastID != -1 )
	{
		return m_curItemTypeStack[lastID].current;		
	}
	else
	{
		return e_ItemType_None;
	}
}


void MTParserCompiler::setArgValueFlag(bool val)
{
	if( m_opStack.size() > 0 )
	{
		int t=m_opStack.size()-1;

		// if the item is a bracket, assign the value to the previous item
		if( m_opStack[t].precedence == MTOPEN_BRACKET_PRECEDENCE )
		{
			t--;
		}

		if( t>=0 )
		{
			// if this ais a bracket, assign the value anyway so that
			// the value can be propagated to the previous-previous item
			m_opStack[t].argValue = val;
		}		
	}	
}

bool MTParserCompiler::incArgCountIfArgValue(std::vector<SOpStackItem> &opStack)
{
	if( opStack.size() > 0 )
	{
		int t=opStack.size()-1;

		// if the item is a bracket, assign the value to the previous item
		if( opStack[t].precedence == MTOPEN_BRACKET_PRECEDENCE )
		{
			t--;
		}

		if( t>=0  )
		{
			// increment the argument count only if this is a function
			if( opStack[t].argValue )
			{	
				if( opStack[t].itemType == e_ItemType_Function )
				{
					opStack[t].nbArgs++;				
				}

				return true;
			}	
		}
	}

	return false;	
}

void MTParserCompiler::clearItemStack(ItemInfoStack &stack)
{
	unsigned int size = stack.size();

	for( unsigned int t=0; t<size; t++)
	{
		clearItemStackItem(stack, t);		
	}	

	stack.clear();
}

inline void MTParserCompiler::clearItemStackItem(ItemInfoStack &stack, int item)
{
	if( stack[item].pArg != NULL )
	{
		delete []stack[item].pArg;		
	}

	if( stack[item].canDelete )
	{
		delete stack[item].pEval;
	}	
}

void MTParserCompiler::pushFuncArg(const MTCHAR *arg) throw(MTParserException)
{
	unsigned int itemStackSizeBef = m_itemStack.size();
	pushCompilerVars();
	m_curItemTypeStack.clear();
	m_opStack.clear();

	parseExpression(arg);
	
	popCompilerVars();

	// must not be an empty argument!
	if( m_itemStack.size() == itemStackSizeBef )
	{
		throwParsingExcep(MTPARSINGEXCEP_InvalidSyntax, 0);
	}	
}

void MTParserCompiler::pushCompilerVars()
{
	sCompilerVar s;
	s.curPos = m_curPos;
	s.curWord = m_curWord;
	s.expression = m_expression;
	s.lastWord = m_lastWord;
	s.nextChar = m_nextChar;
	s.originalPos = m_originalPos;	
	s.opStack = m_opStack;
	s.curItemTypeStack = m_curItemTypeStack;
	s.pCompilerState = m_pCompilerState;

	m_compilerVars.push_back(s);	
}

void MTParserCompiler::popCompilerVars()
{
	unsigned int lastId = m_compilerVars.size()-1;

	m_curPos = m_compilerVars[lastId].curPos;
	m_curWord = m_compilerVars[lastId].curWord;
	m_expression = m_compilerVars[lastId].expression;
	m_lastWord = m_compilerVars[lastId].lastWord;
	m_nextChar = m_compilerVars[lastId].nextChar;
	m_originalPos = m_compilerVars[lastId].originalPos;
	m_pCompilerState = m_compilerVars[lastId].pCompilerState;	
	m_opStack = m_compilerVars[lastId].opStack;
	m_curItemTypeStack = m_compilerVars[lastId].curItemTypeStack;

	m_compilerVars.erase( m_compilerVars.begin()+lastId );	
}

void MTParserCompiler::parseExpression(const MTSTRING &expr) throw(MTParserException)
{	
	// remove space characters...		
	MTTools::removeSpaces(expr, m_originalPos, m_expression);

	if( m_expression.size() == 0 )
	{
		return;		// nothing to parse!
	}		

	pushCurItemType();				// push a null item type to begin

	unsigned int length = m_expression.size();
	clearCurWord();
	
	MTCHAR curChar = 0;	
	m_nextChar = 0;	
	MTSTRING opSymbol;		
	m_curPos = 0;	

	setState(m_pStates[m_defCompilerStateID]);

	// Algorithm
	// two stacks: one for operators and functions (opStack)
	// and one for the ordered expression items (exprStack).  The last item will be
	// evaluated last.
	// We want to order each expression item (op, function and value) by evaluation precedence.	
	// The opStack is a temporary stack used during the parsing step only.	
		
	for( m_curPos=0; m_curPos<length; m_curPos++ )
	{
		curChar = m_expression[m_curPos];
		if( m_curPos<length-1 )
		{
			m_nextChar = m_expression[m_curPos+1];
		}
		else
		{
			m_nextChar = 0;
		}

		// ask the current compiler state to compile the char
		if( !m_pCompilerState->compileChar(curChar) )
		{
			// the state didn't process the char, so we take it 
			bool isOp = m_pRegistrar->areNextCharsOpString(&m_expression[m_curPos], length-m_curPos, opSymbol);		

			if( isOp )
			{
				m_pCompilerState->onOp(opSymbol);
			}
			else
			{
				if( curChar == m_syntax.argumentSeparator)
				{			
					m_pCompilerState->onArgSeparator();
				}
				else if(curChar == MTOPEN_BRACKET)
				{
					m_pCompilerState->onOpenBracket();
				}
				else if(curChar == MTCLOSE_BRACKET)
				{
					m_pCompilerState->onCloseBracket();
				}				
				else
				{
					m_curWord += curChar;
				}
			}
		}
	}		
	
	m_pCompilerState->onEndOfFormula();
	
	// parse the last word...
	parseWord();

	// destack remaining operators, beginning by the end
	unsigned int nbOps = m_opStack.size();
	unsigned int invT = nbOps - 1;
	
	for( unsigned int t=0; t<nbOps; t++, invT-- )
	{
		
		int curOpPrecedence = m_opStack[invT].precedence;
		if( curOpPrecedence == MTOPEN_BRACKET_PRECEDENCE )
		{			
			throwParsingExcep(MTPARSINGEXCEP_MissingCloseBracket, m_opStack[invT].exprStrPos);
		}		
		
		pushOnExprStack(m_opStack[invT]);
	}		
	
}

void MTParserCompiler::setState(MTCompilerStateI *pState)
{	
	m_pCompilerState = pState;
	pState->enter(this, getRegistrar());
}

void MTParserCompiler::setState(unsigned int stateID)
{
	setState(m_pStates[stateID]);
}

void MTParserCompiler::exitState()
{
	// select the default state...
	setState(m_pStates[m_defCompilerStateID]);
}

void MTParserCompiler::removeAllEvaluatedItem(ItemInfoStack &stack)
{
	unsigned int size = stack.size();

	if( size > 0 )
	{
		// we don't remove the last item
		// because this is the result
		size--;

		for( unsigned int t=0; t<size; t++ )
		{
			if( stack[t].isEvaluated )
			{
				clearItemStackItem(stack, t);
				stack.erase(stack.begin()+t);
				t--;
				size--;
			}
		}
	}
}

// add an operator or a function on the expression stack
void MTParserCompiler::pushOnExprStack(const SOpStackItem &item, bool findItem  ) throw(MTParserException)
{	
	SItemInfo info;
	
	info.pEval = item.pEval;	
	
	// if this is a function, we find a function with the specified number
	// of arguments
	if( item.itemType == e_ItemType_Function )
	{
		if( findItem )
		{
			unsigned int fID;
			if( !m_pRegistrar->findFunction(m_pRegistrar->getFunc(item.itemID)->getSymbol(), item.nbArgs, fID) )
			{					
				throwParsingExcep(MTPARSINGEXCEP_OverloadedFuncNotFound, item.exprStrPos, m_pRegistrar->getFunc(item.itemID)->getSymbol(), item.nbArgs);
			}

			// replace the function handler by this "maybe" overloaded function
			info.pEval = m_pRegistrar->getFunc(fID);
		}

		// just before using the function, do the late initialization...
		((MTFunctionI*)info.pEval)->doLateInitialization(this, getRegistrar());		
	}
	
	// allocate the memory for the function arguments...
	info.nbArgs = item.nbArgs;
	if( info.nbArgs > 0 )
	{
		info.pArg = new MTDOUBLE[info.nbArgs];
	}
	else
	{
		info.pArg = NULL;	// no argument
	}

	
	info.canDelete = item.canDelete;
	info.exprStrPos = item.exprStrPos;	
	m_itemStack.push_back(info);	
}


// parse a word
// It can be a function, a variable, a constant or a value
// if it is a function, add it on the opStack
// if it is a variable, a constant or a value, add it on the exprStack
bool MTParserCompiler::parseWord() throw(MTParserException)
{	

	bool ret = true;
	// parse the current m_curWord
	if( m_curWord.size() == 0 )
	{
		return ret;		
	}	

	
	int exprStrPos = m_curPos-m_curWord.size();

	if( getCurItemType() != e_ItemType_Operator &&
		getCurItemType() != e_ItemType_None)
	{	
		// this m_curWord must be preceded by an operator if this is
		// not the firt expression item.  For example, a function cannot come
		// after another function; there must be an operator between.
		throwParsingExcep(MTPARSINGEXCEP_MissingOp, exprStrPos, m_curWord.c_str());
	}


	// only functions are followed by an open bracket
	if( m_expression[m_curPos] == MTOPEN_BRACKET )
	{
		// it's a function
		// it can be a normal function or a function with a custom compiler
		unsigned int funcID;
		if( m_pRegistrar->isAFunction(m_curWord.c_str(), funcID) )
		{			
			// it's a normal function...
			setArgValueFlag(true);
			setCurItemType(e_ItemType_Function);			
			
			MTCompilerStateI *pCompilerState = m_pRegistrar->getFunc(funcID)->getCompilerState();
			if( pCompilerState == NULL )
			{
				// no custom compiler, so we have to compile this function 
				SOpStackItem item;
				item.exprStrPos = exprStrPos;
				item.precedence = e_MTOpPrec_FCT;				
				item.nbArgs = 0;		// will be incremented later...
				item.pEval = m_pRegistrar->getFunc(funcID);	
				item.argValue = false;
				item.itemType = e_ItemType_Function;
				item.itemID = funcID;
				m_opStack.push_back(item);
			}
			else
			{
				// let's the custom compiler do the hard job...!				
				setState(pCompilerState);
				ret = false;	// force the current state to exit
			}			
		}		
		else
		{		
			throwParsingExcep(MTPARSINGEXCEP_UndefinedFunc, exprStrPos, m_curWord.c_str());
		}	
		
	}
	// if only numerical characters -> value
	// so a variable name cannot be composed of numbers only
	else if( MTTools::isOnlyNum(m_curWord, m_syntax.decimalPoint) )
	{			
		// it's a numerical value
		MTDOUBLE val;
		strToVal(m_curWord.c_str(), &val);
		pushValue(val);		
	}
	else
	{
	
		// it could be a variable or a constant
		unsigned int constID;		
		if( m_pRegistrar->findConst(m_curWord.c_str(), constID) )
		{
			// it's a constant		
			MTSTRING cName;
			MTDOUBLE cVal;
			m_pRegistrar->getConst(constID, cName, cVal);
			pushValue(cVal);			
		}
		else
		{	
			// it's a variable
			try
			{
				pushVariable(m_curWord.c_str());			
			}
			catch( MTParserException )
			{
				throwParsingExcep(MTPARSINGEXCEP_UndefinedVar, exprStrPos, m_curWord.c_str()); 							
			}
		}
	}

	clearCurWord();	
	return ret;

}

void MTParserCompiler::pushValue(const MTDOUBLE &val)
{
	setCurItemType(e_ItemType_Value);

	int exprStrPos = m_curPos-m_curWord.size();

	// add it to the exprStack
	SItemInfo exprInfo;	
	exprInfo.exprStrPos = exprStrPos;
	exprInfo.isEvaluated = true;
	exprInfo.val = val;	
	m_itemStack.push_back(exprInfo);
	
	setArgValueFlag(true);
}

void MTParserCompiler::pushVariable(const MTCHAR *varName) throw(MTParserException)
{
	SItemInfo exprInfo;	
	exprInfo.isEvaluated = false;
	int exprStrPos = m_curPos-m_curWord.size();		
	exprInfo.pEval = getVar(varName);
	setCurItemType(e_ItemType_Value);
	exprInfo.exprStrPos = exprStrPos;
	
	// add it to the exprStack
	m_itemStack.push_back(exprInfo);
	setArgValueFlag(true);
}

MTVariableI* MTParserCompiler::registerUsedVariable(const MTCHAR *symbol) throw(MTParserException)
{
	// add this variable to the used variable list	(don't add twice the same variable)		
	unsigned int index;
	if( !findUsedVar(symbol, index) )
	{		
		// the variable is not already used so create a stub and
		// link it to the real variable object
		sUsedVar usedVar;		
		MTVarStub *pStub = new MTVarStub;
		usedVar.pStub = pStub;
		usedVar.isOwner = true;
		usedVar.symbol = symbol;
		m_usedVariables.push_back(usedVar);
		
		// push the real variable on the stack		
		SItemInfo exprInfo;		
		exprInfo.exprStrPos = 0;
		exprInfo.isEvaluated = false;				
		exprInfo.pEval = m_pRegistrar->getVarBySymbol(symbol);						
		exprInfo.ignore = true;
		m_itemStack.insert(m_itemStack.begin(), exprInfo);					

		return pStub;
	}
	else
	{
		// variable already registered
		return m_usedVariables[index].pStub;		
	}
}

MTVariableI* MTParserCompiler::getVar(const MTCHAR *symbol) throw(MTParserException)
{		
	if( !m_pRegistrar->isVarDefined(symbol) )
	{
		// this variable is not defined... if the autoDefine feature is on, define it
		bool isDef = false;
		if( isAutoVarDefinitionEnabled() )
		{
			try
			{
				m_pRegistrar->defineVar(symbol);
				isDef = true;										
			}
			catch( MTParserException )
			{						
				// do nothing: the variable cannot be defined...
				// so a parsing exception will be thrown
				isDef = false;
			}
		}
		
		if( !isDef && m_pParent != NULL )
		{
			// still not defined,
			// look in our parent...				
			MTVariableI *pVar = m_pParent->getVar(symbol);
			sUsedVar usedVar;
			usedVar.pStub = pVar;	
			usedVar.isOwner = false;
			usedVar.symbol = symbol;
			m_usedVariables.push_back(usedVar);
			return pVar;
		}
		else if( !isDef )
		{
			// variable not found
			throwParsingExcep(MTDEFEXCEP_ItemNotFound, symbol);			
		}
	}

	return registerUsedVariable(symbol);	
}

void MTParserCompiler::pushFunction(const MTCHAR *funcName, unsigned int nbArgs) throw(MTParserException)
{
	SOpStackItem item;
	
	unsigned int funcID;
	if( !m_pRegistrar->findFunction(funcName, nbArgs, funcID) )
	{
		throwParsingExcep(MTPARSINGEXCEP_OverloadedFuncNotFound, getCurPos(), funcName, nbArgs);
	}

	MTFunctionI *pFunc = m_pRegistrar->getFunc(funcID);
	item.exprStrPos = getCurPos();
	item.precedence = e_MTOpPrec_FCT;	
	item.nbArgs = nbArgs;
	item.pEval = pFunc;	
	item.argValue = false;
	item.itemType = e_ItemType_Function;
	item.itemID = funcID;	

	pushOnExprStack(item);

	setCurItemType(e_ItemType_Function);
	setArgValueFlag(true);

	
}

void MTParserCompiler::pushFunction(MTFunctionI *pFunc, unsigned int nbArgs) throw(MTParserException)
{	
	SOpStackItem item;
	item.exprStrPos = getCurPos();
	item.precedence = e_MTOpPrec_FCT;	
	item.nbArgs = nbArgs;
	item.pEval = pFunc;	
	item.canDelete = true;
	item.argValue = false;
	item.itemType = e_ItemType_Function;
	item.itemID = -1;	

	pushOnExprStack(item, false);

	setCurItemType(e_ItemType_Function);
	setArgValueFlag(true);	
}

void MTParserCompiler::addCurChar()
{
	m_curWord += m_expression[m_curPos];
}

void MTParserCompiler::clearCurWord()
{
	m_lastWord = m_curWord;
	m_curWord = _T("");	
}

const MTCHAR* MTParserCompiler::getCurWord()
{
	return m_curWord.c_str();
}

bool MTParserCompiler::findUsedVar(const MTCHAR *varName, unsigned int &index)const
{
	unsigned int size = m_usedVariables.size();
	for( unsigned int t=0; t<size; t++ )
	{
		if( lstrcmp( varName, m_usedVariables[t].symbol.c_str() ) == 0 )
		{
			index = t;
			return true;
		}
	}

	return false;
}

// convert a string value to a double value
void MTParserCompiler::strToVal(const MTCHAR *val, double *pVal)const
{
	MTCHAR **pEnd=NULL;
	
	// first replace the decimal point character by the one
	// specified by the current locale

	// ***** Todo investigation needed (potential bug)
	// for an unknown reason, the system conversion routine
	// doesn't take the decimal point character specified in the 
	// the locale settings.  So, temporarily we replace the decimal
	// point character specified in the syntax settings by the '.' character.
	MTCHAR localeDecimalPoint = MTSYSTEM_DECIMALPOINT;	// _wsetlocale(LC_NUMERIC, NULL);	

	// only replace if the two characters are different
	if( m_syntax.decimalPoint != localeDecimalPoint )
	{
		MTSTRING newVal = val;
		unsigned int length = newVal.size();
		for( unsigned int t=0; t<length; t++ )
		{
			if( newVal[t] == m_syntax.decimalPoint )
			{
				newVal[t] = localeDecimalPoint;
				break;				
			}
		}

		*pVal = MTSTRTOD(newVal.c_str(),pEnd);
	}
	else
	{
		*pVal = MTSTRTOD(val,pEnd);
	}
	
}

// Use a recursive algorithm to compute where each item puts its result.  This 
// allows an iterative algorithm to be used in the evaluation step.
void MTParserCompiler::updateParentValPtr()
{
	if( m_itemStack.size() == 0 )
	{
		return;		// empty expression or expression not set!	
	}	
	
	// recursively evaluate each item, beginning by the last (it will
	// also be the last to be evaluated)

	bool constant = true;
	evaluateValidate( m_itemStack.size()-1, constant);			
}

MTDOUBLE MTParserCompiler::evaluateValidate(int node, bool &constant) throw(MTParserException)
{
	SItemInfo *pExpr = &m_itemStack[node];
	
	if( pExpr->isEvaluated)
	{			
		return pExpr->val;
	}		
	
	bool isConstant = pExpr->pEval->isConstant();
	if( !isConstant )
	{
		constant = false;
	}

	m_popPtr = node-1;
	
	// pop arguments...
	int nbArgs = m_itemStack[node].nbArgs;	
	bool constantItem = isConstant;
	for( int t=nbArgs-1; t>=0; t-- )
	{		
		m_itemStack[node].pArg[t] = popValidate(&m_itemStack[node].pArg[t], constantItem);		
	}

	MTDOUBLE val = 0;
	
	// evaluate the item only if the item and its arguments are constants
	// else, the item will be evaluated at evaluation time.
	if( constantItem )
	{
		val = pExpr->pEval->evaluate(m_itemStack[node].nbArgs, m_itemStack[node].pArg);		
		pExpr->val = val;
		pExpr->isEvaluated = true;
	}		
	else
	{
		// we are not constant so the parent item isn't too
		constant = false;
	}
	
	return val;		
}


MTDOUBLE MTParserCompiler::popValidate(MTDOUBLE *pParentItemArg, bool &constant) throw(MTParserException)
{
	if( m_popPtr < 0 )
	{
		// not enough argument
		throwParsingExcep(MTPARSINGEXCEP_InternalError, -1);
	}

	MTDOUBLE val;
	SItemInfo *pExpr = &m_itemStack[m_popPtr];

	if( !pExpr->ignore )
	{		
		pExpr->pParentItemArg = pParentItemArg;

		if( pExpr->isEvaluated )
		{
			val = pExpr->val;	
			m_popPtr--;				
		}
		else
		{
			val = evaluateValidate(m_popPtr, constant);	
		}	

		return val;
	}
	else
	{
		// skip this item
		m_popPtr--;				
		return popValidate(pParentItemArg, constant);
	}
}

unsigned int MTParserCompiler::getNbUsedVars()const
{
	return m_usedVariables.size();
}

MTSTRING MTParserCompiler::getUsedVar(unsigned int varID)const
{
	if( varID < 0 || varID >= getNbUsedVars() )
	{
		throwParsingExcep(MTDEFEXCEP_ItemNotFound, varID);	
	}

	return m_usedVariables[varID].symbol;
}

MTSTRING MTParserCompiler::getExpression()const
{
	return m_originalExpr;
}

void MTParserCompiler::throwParsingExcep(const MTCHAR *id, const MTCHAR *itemName)const throw(MTParserException)
{
	MTExcepData data	(id, 						
						MTEXCEPARG_ITEMNAME, itemName );
						
	
	MTTHROW(data)	

}

void MTParserCompiler::throwParsingExcep(const MTCHAR * id, int pos, const MTCHAR *itemName, int param)const throw(MTParserException)
{
	MTExcepData data	(id, 
						MTEXCEPARG_POS, MTTools::longToS(m_originalPos[pos]).c_str(), 
						MTEXCEPARG_ITEMNAME, itemName, 
						MTEXCEPARG_PARAM1, MTTools::longToS(param).c_str()	);
	
	MTTHROW(data)

}
void MTParserCompiler::throwParsingExcep(const MTCHAR * id, int pos)const throw(MTParserException)
{
	MTExcepData data	(id, 
						MTEXCEPARG_POS, MTTools::longToS(m_originalPos[pos]).c_str() );						
	
	MTTHROW(data)

}
void MTParserCompiler::throwParsingExcep(const MTCHAR * id, int pos, const MTCHAR *itemName)const throw(MTParserException)
{	

	MTExcepData data	(id, 
						MTEXCEPARG_POS, MTTools::longToS(m_originalPos[pos]).c_str(), 
						MTEXCEPARG_ITEMNAME, itemName );
						
	
	MTTHROW(data)

}

//**************************************
// MTVarStub 

MTParserCompiler::MTVarStub::MTVarStub ()
{
	m_pValue = NULL;
}

void MTParserCompiler::MTVarStub::setValuePtr(MTDOUBLE *pValue)
{
	m_pValue = pValue;
}

MTDOUBLE MTParserCompiler::MTVarStub::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{
	return *m_pValue;		
}
MTVariableI* MTParserCompiler::MTVarStub::spawn()
{
	return new MTVarStub;
}

//**************************************
// MTCompilerDefState

void MTCompilerDefState::onOp(const MTSTRING &opSymbol)
{
	if( !m_pParserCompiler->parseWord() )
	{
		return;
	}

	m_pParserCompiler->setArgValueFlag(true);
	m_pParserCompiler->setCurItemType(MTParserCompiler::e_ItemType_Operator);

	// this is a one argument operator if there is no left
	// argument:
	bool unaryOp = false;
	if( m_pParserCompiler->getPrevItemType() == MTParserCompiler::e_ItemType_None ||
		m_pParserCompiler->getPrevItemType() == MTParserCompiler::e_ItemType_Operator )
	{		
		unaryOp = true;
	}

	unsigned int opID;
	if( !m_pParserCompiler->getRegistrar()->findOp(opSymbol.c_str(), unaryOp, opID) )
	{					
		m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_InvalidOpSyntax, m_pCompiler->getCurPos(), opSymbol.c_str());
	}				

	// advance the expression char cursor by the op symbol length
	m_pParserCompiler->setCurPos(m_pCompiler->getCurPos() + lstrlen(m_pParserCompiler->getRegistrar()->getOp(opID)->getSymbol())-1);

	// an expression cannot end with an expression...
	if( m_pCompiler->getCurPos() >= m_pParserCompiler->getExprLength()-1 )
	{					
		m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_UnexpectedOp, m_pCompiler->getCurPos());
	}


	if( m_pParserCompiler->m_opStack.size() > 0 )
	{
		int prevOpPrecedence = m_pParserCompiler->m_opStack[m_pParserCompiler->m_opStack.size()-1].precedence;
		int curOpPrecedence;
		if( prevOpPrecedence != MTOPEN_BRACKET_PRECEDENCE )
		{						
			curOpPrecedence = m_pParserCompiler->getRegistrar()->getOp(opID)->getPrecedence();

			// Special case: if the two ops have the same precedence
			// and that the previous op is an unary operator
			// then that means that the curOp is the argument of the
			// previous op.  So, we must not pop the previous op.
			if( curOpPrecedence == prevOpPrecedence &&
				m_pParserCompiler->m_opStack[m_pParserCompiler->m_opStack.size()-1].itemType == MTParserCompiler::e_ItemType_Operator &&
				((MTOperatorI*)m_pParserCompiler->m_opStack[m_pParserCompiler->m_opStack.size()-1].pEval)->isUnaryOp() )
			{
				curOpPrecedence = prevOpPrecedence+1;	// skip the while
			}

			// destack op until op precedence > previous op.
			// the destasked op will be evaluated before.
			// if the precedence is equal, the rule is to evaluate
			// from left to right, so the previous op has greater precedence also
			while( curOpPrecedence <= prevOpPrecedence )
			{
				
				m_pParserCompiler->pushOnExprStack(m_pParserCompiler->m_opStack[m_pParserCompiler->m_opStack.size()-1]);								

				// remove the last op
				m_pParserCompiler->m_opStack.erase(m_pParserCompiler->m_opStack.begin()+m_pParserCompiler->m_opStack.size()-1);

				if( m_pParserCompiler->m_opStack.size() > 0 )
				{
					prevOpPrecedence = m_pParserCompiler->m_opStack[m_pParserCompiler->m_opStack.size()-1].precedence;
					if( prevOpPrecedence == MTOPEN_BRACKET_PRECEDENCE )
					{
						break; // open bracket halts the destacking process
					}
				}
				else
				{
					break;	// no more op in the stack
				}
			}
		}
	}
	
	// push the operator on the stack...				
	MTParserCompiler::SOpStackItem item;
	item.exprStrPos = m_pCompiler->getCurPos();
	if( unaryOp )
	{
		item.nbArgs = 1;
	}
	else
	{
		item.nbArgs = 2;
	}
	item.precedence = m_pParserCompiler->getRegistrar()->getOp(opID)->getPrecedence();	
	item.pEval = m_pParserCompiler->getRegistrar()->getOp(opID);	
	item.itemType = MTParserCompiler::e_ItemType_Operator;
	item.itemID = opID;
	m_pParserCompiler->m_opStack.push_back(item);

}
void MTCompilerDefState::onOpenBracket()
{
	if( !m_pParserCompiler->parseWord() )
	{
		return;
	}

	// if the next char is a closing bracket = nothing inside brackets!
	// example: 1+()
	// only function may use the () syntax when no argument needed
	if( m_pParserCompiler->getCurItemType() != MTParserCompiler::e_ItemType_Function &&
		m_pParserCompiler->m_nextChar == MTCLOSE_BRACKET )
	{
		m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_InvalidSyntax, m_pCompiler->getCurPos());
	}
	
	// reset the value flag
	m_pParserCompiler->setArgValueFlag(false);
	
	
	MTParserCompiler::SOpStackItem item;
	item.exprStrPos = m_pCompiler->getCurPos();
	item.precedence = MTOPEN_BRACKET_PRECEDENCE;	
	item.itemType = MTParserCompiler::e_ItemType_None;
	m_pParserCompiler->m_opStack.push_back(item);
	
	m_pParserCompiler->pushCurItemType();	

}
void MTCompilerDefState::onCloseBracket()
{
	onCloseArgSeparator();

}

void MTCompilerDefState::onCloseArgSeparator()
{	
	if( !m_pParserCompiler->parseWord() )
	{
		return;
	}	

	// operator cannot be followed by a closing bracket or an argument separator
	if( m_pParserCompiler->getCurItemType() == MTParserCompiler::e_ItemType_Operator )
	{					
		m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_UnexpectedOp, m_pCompiler->getCurPos());
	}	
	
	// pop the last itemType
	m_pParserCompiler->m_curItemTypeStack.erase(m_pParserCompiler->m_curItemTypeStack.begin()+m_pParserCompiler->m_curItemTypeStack.size()-1);								

	MTCHAR curChar = m_pParserCompiler->m_expression[m_pCompiler->getCurPos()];	

	if( curChar == m_pParserCompiler->m_syntax.argumentSeparator )
	{
		// argument separators are only allowed in functions
		if( m_pParserCompiler->getCurItemType() != MTParserCompiler::e_ItemType_Function )
		{
			m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_InvalidArgSeparator, m_pCompiler->getCurPos());										
		}
		
		// the old itemType has been popped, so we
		// push a new clean itemType 
		m_pParserCompiler->pushCurItemType();

		// if the next char is a closing bracket = invalid syntax!
		// example: fct(x,y,)
		if( m_pParserCompiler->m_nextChar == MTCLOSE_BRACKET )
		{
			m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_UselessArgSeparator, m_pCompiler->getCurPos());
		}
	}

	// destack until an open bracket is found
	int curOpPrecedence;
	int nbPoppedItems = 0;
	do
	{
		if( m_pParserCompiler->m_opStack.size() == 0 )
		{
			MTSTRING msg;
			if( curChar == MTCLOSE_BRACKET )
			{
				m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_MissingOpenBracket, m_pCompiler->getCurPos());							
			}
			else
			{
				m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_InvalidArgSeparator, m_pCompiler->getCurPos());							
			}					
		}

		curOpPrecedence = m_pParserCompiler->m_opStack[m_pParserCompiler->m_opStack.size()-1].precedence;

		if( curOpPrecedence != MTOPEN_BRACKET_PRECEDENCE )
		{					
			nbPoppedItems++;
			m_pParserCompiler->pushOnExprStack(m_pParserCompiler->m_opStack[m_pParserCompiler->m_opStack.size()-1]);						

			// remove the last op
			m_pParserCompiler->m_opStack.erase(m_pParserCompiler->m_opStack.begin()+m_pParserCompiler->m_opStack.size()-1);
		}
	}while(curOpPrecedence != MTOPEN_BRACKET_PRECEDENCE);				
	 
	bool isInc = m_pParserCompiler->incArgCountIfArgValue(m_pParserCompiler->m_opStack);
				
	if( nbPoppedItems == 0  )
	{
		// if no argument but there is an argument separator character...!
		// example: avg(,)
		if(curChar == m_pParserCompiler->m_syntax.argumentSeparator && !isInc)
		{
			m_pParserCompiler->throwParsingExcep(MTPARSINGEXCEP_UselessArgSeparator, m_pCompiler->getCurPos());
		}			
	}


	// only if we got a closing bracket, we erase the opening bracket.				
	if( curChar == MTCLOSE_BRACKET )
	{
		// erase the open bracket
		m_pParserCompiler->m_opStack.erase(m_pParserCompiler->m_opStack.begin()+m_pParserCompiler->m_opStack.size()-1);

		// syntax like -(x)+3, the (x) is a value, so
		// the current item should be a value and not an operator.
		// When the current item is a function like: sin(x)+3
		// then the current item remains a function.
		if( m_pParserCompiler->getCurItemType() != MTParserCompiler::e_ItemType_Function) 
		{
			m_pParserCompiler->setCurItemType(MTParserCompiler::e_ItemType_Value);
		}					
	}			
	
	bool valueFlag = false;
	if( curChar == MTCLOSE_BRACKET && (m_pParserCompiler->m_nextChar == MTCLOSE_BRACKET || m_pParserCompiler->m_nextChar == m_pParserCompiler->m_syntax.argumentSeparator))
	{
		// propagate the value to the next item
		// example: sin((3+2)).  The argument 3+2 argument must be propagated to the sin function 
		valueFlag = isInc;					
	}						
	
	m_pParserCompiler->setArgValueFlag(valueFlag);


}

void MTCompilerDefState::onArgSeparator()
{
	onCloseArgSeparator();
}




