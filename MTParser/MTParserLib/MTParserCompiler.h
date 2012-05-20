/** @file MTParserCompiler.h
  @brief Default Compiler File
  @author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSERCOMPILER_INCLUDED
#define _MTPARSERCOMPILER_INCLUDED

#include "MTParserPrivate.h"

#define MTOPEN_BRACKET_PRECEDENCE -1		// must be different from all other precedences

/** @brief Concrete compiler
*/
class MTParserCompiler : public MTCompilerI
{
public:
	
	//************************************
	// MTCompilerPublicI implementation	
	
	virtual bool isAutoVarDefinitionEnabled()const;	
	virtual void compile(const MTCHAR *expr) throw(MTParserException);
	virtual bool isConstant()const;
	virtual void onVarRedefined(MTVariableI *pVar) throw(MTParserException);
	virtual unsigned int getNbUsedVars()const;
	virtual MTSTRING getUsedVar(unsigned int varID)const;
	virtual MTSTRING getExpression()const;

	virtual void resetExpression();	

	//************************************
	// MTCompilerI implementation
	
	virtual void enableAutoVarDefinition(bool enable);	
	virtual ItemInfoStack* getItemStack();	
	virtual void setParent( MTCompilerI *pParent );

	virtual void addCurChar();	
	virtual const MTCHAR* getCurWord();
	virtual void clearCurWord();
	virtual unsigned int getCurPos(){ return m_curPos; }
	virtual void pushValue(const MTDOUBLE &val);
	virtual MTVariableI* getVar(const MTCHAR *symbol) throw(MTParserException);
	virtual void pushVariable(const MTCHAR *varName) throw(MTParserException);	
	virtual void pushFunction(const MTCHAR *funcName, unsigned int nbArgs) throw(MTParserException);
	virtual void pushFunction(MTFunctionI *pFunc, unsigned int nbArgs) throw(MTParserException);
	virtual void pushFuncArg(const MTCHAR *arg) throw(MTParserException);
	virtual void exitState();

	virtual void throwParsingExcep(const MTCHAR * id, const MTCHAR *itemName)const throw(MTParserException);
	virtual void throwParsingExcep(const MTCHAR * id, int pos, const MTCHAR *itemName, int param)const throw(MTParserException);
	virtual void throwParsingExcep(const MTCHAR * id, int pos)const throw(MTParserException);
	virtual void throwParsingExcep(const MTCHAR * id, int pos, const MTCHAR *itemName)const throw(MTParserException);


	virtual MTCompilerI* spawn(class MTRegistrarI *pRegistrar) throw(MTParserException);

	MTParserCompiler( class MTRegistrarI *pRegistrar);
	virtual ~MTParserCompiler();

public:
	
	enum EItemType
	{
		e_ItemType_None,
		e_ItemType_Value,
		e_ItemType_Operator,
		e_ItemType_Function
	};

	struct SParserCurItem
	{
		EItemType previous;
		EItemType current;
	};

	// operator stack item.  Used in the parsing function.
	struct SOpStackItem
	{
		int precedence;
		int exprStrPos;
		bool endWithABlock;
		int nbArgs;
		bool argValue;			// indicate if a value has been encountered between
								// argument separator or closing bracket.  If yes, then
								// the next argument separator or closing bracket can
								// increment the argument count.
		
		EItemType itemType;		// indicate the type of this item
		int itemID;				// operator or function ID
		MTParserItemI *pEval;
		bool canDelete;			// indicate whether the object pointed by pEval must be deleted after use

		SOpStackItem(){ argValue = false; canDelete = false;}
	};
	
public:
		
	/** Push an operator or a function on the stack
		@param	item		The item description
		@param	findItem	If a function, indicates whether it must look for an object in the Registrar.
							Otherwise, the specified function object is taken 						
	*/
	void pushOnExprStack(const SOpStackItem &item, bool findItem = true ) throw(MTParserException);		
	
	/** Push a dummy value on the stack to make sure that 
		if the expression is not set, the parser will not
		crash, but will return a dummy value.
		This is a performance optimization since this condition
		doesn't need to be checked at evaluation time. 
	*/
	void pushDummyValue();
	
	/** Interpret a "word" that has been detected as it by the broker algorithm.
		If the word is a function, it will be added to the operator stack.
		Else, the word will be added to the value stack.
		
		@return true if the parsing can continue or false if the state has changed
	*/
	bool parseWord() throw(MTParserException);	
	
	void pushCurItemType();
	void setCurItemType( EItemType type );
	EItemType getPrevItemType();
	EItemType getCurItemType();	
	
	/** Indicate that there is or not an argument to the current item */
	void setArgValueFlag(bool val);
	
	/** Increment the argument count if the argValue flag is true
		@return true if the argument flag is set to true (but not necessary incremented)
	*/
	bool incArgCountIfArgValue(std::vector<SOpStackItem> &opStack);	
	
	/** Change the parsing current position */
	void setCurPos(unsigned int curPos){ m_curPos = curPos; }

	/** Return the expression length */
	unsigned int getExprLength(){ return m_expression.size(); }

	MTRegistrarI* getRegistrar(){ return m_pRegistrar; }

	void setState(MTCompilerStateI *pState);
	void setState(unsigned int stateID);	
	
public:

	std::vector<SOpStackItem> m_opStack;			// stack used during the compiling step

	std::vector<SParserCurItem> m_curItemTypeStack;	// stack to keep track of what type of
													// item we are parsing now

	ItemInfoStack m_itemStack;						// expression stack (done during the parsing step)

	MTSyntax m_syntax;								// cached syntax value

	MTCHAR m_nextChar;								// the next character to be parsed

	unsigned int m_defCompilerStateID;				// default compiler state ID
	
	MTSTRING m_expression;							// current expression string (space characters removed)
	
private:

	/** The main parser loop */
	void parseExpression(const MTSTRING &expr) throw(MTParserException);

	/** Return true if this variable is already in the list of used variables */
	bool findUsedVar(const MTCHAR *symbol, unsigned int &index)const;		

	/** String to double conversion
		@param val:		string value
		@param pVal:	[out] double value
	*/
	void strToVal(const MTCHAR *val, double *pVal)const;		


	unsigned int addState(class MTCompilerStateI *pState);

	/** @brief Register a used variable

		If not already registered, add it at the beginning of the expression stack and
		create a stub.
		
		@param	varName		The used variable name
		@return A variable stub
	*/	
	MTVariableI* registerUsedVariable(const MTCHAR *varName) throw(MTParserException);
	
	/** @brief Compute where each item puts its value */
	void updateParentValPtr();

	/** Remove all evaluated items from the stack
		since their values have already been put in their
		parent items	
	*/
	void removeAllEvaluatedItem(ItemInfoStack &stack);

	/** Slow pop method used during the parsing step to validate the expression
		@param pParentItemArg: the popped item will be assigned this parent item
	*/
	MTDOUBLE popValidate(MTDOUBLE *pParentItemArg, bool &constant) throw(MTParserException);
		
	/** Intermediate slow evaluate method used during the 
		parsing step to validate the expression 
	*/
	MTDOUBLE evaluateValidate(int node, bool &constant) throw(MTParserException);	
	

	void pushCompilerVars();
	void popCompilerVars();
	void clearUsedVars();
	
	/** Clear all the stack */
	void clearItemStack(ItemInfoStack &stack);
	
	/** Clear one item of the stack, but don't remove it from the stack */
	void clearItemStackItem(ItemInfoStack &stack, int item);	


private:

	/** Used to save the compiler state 
	
	When compiling nested functions, the compiler state need
	to be pushed before a function and popped after. 
	*/ 
	struct sCompilerVar
	{
		MTSTRING expression;
		unsigned int curPos;						
		MTSTRING curWord, lastWord;
		MTCHAR nextChar;
		std::vector<unsigned int> originalPos;
		MTCompilerStateI *pCompilerState;
		std::vector<SOpStackItem> opStack;	
		std::vector<SParserCurItem> curItemTypeStack;
	};	

	class MTVarStub : public MTVariableI
	{
	public:

		MTVarStub();
		void setValuePtr(MTDOUBLE *pValue);		

		virtual const MTCHAR* getSymbol(){ return _T(""); }		
		virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);
		virtual MTVariableI* spawn();		

	private:
		
		MTDOUBLE *m_pValue;
	};

	
	MTSTRING m_originalExpr;						// original expression with space characters

	
	unsigned int m_curPos;							// current parsing position
	MTSTRING m_curWord, m_lastWord;

	std::vector<unsigned int> m_originalPos;		// original expression character position, before
													// the pre-processing (remove spaces)	

	std::vector<sCompilerVar> m_compilerVars;

	//! Used var information
	struct sUsedVar
	{
		MTVariableI *pStub;		// the variable evaluator
		bool isOwner;			// indicate whether we own the stub and can delete it after use
		MTSTRING symbol;		
	};	
	
	std::vector<sUsedVar> m_usedVariables;			// variables used in the current expression		
	
	std::vector<class MTCompilerStateI*> m_pStates;
	MTCompilerStateI *m_pCompilerState;	
	
	bool m_isAutoVarDefinitionEnabled;				// auto variable definition feature state
		
	
	int m_popPtr;									// current pop pointer (parsing step)

	MTRegistrarI *m_pRegistrar;						// registrar object	
	MTCompilerI *m_pParent;							// parent compiler

};

/** @brief Default compiler state */
class MTCompilerDefState : public MTCompilerStateI
{
public:

	virtual void enter(MTCompilerI *pCompiler, MTRegistrarI *pRegistrar){
		MTCompilerStateI::enter(pCompiler, pRegistrar);
		m_pParserCompiler = (MTParserCompiler*)pCompiler;	}
	virtual void onOp(const MTSTRING &opSymbol);
	virtual void onOpenBracket();
	virtual void onCloseBracket();	
	virtual void onArgSeparator();

private:

	void onCloseArgSeparator();
	MTParserCompiler *m_pParserCompiler;
	
};



#endif