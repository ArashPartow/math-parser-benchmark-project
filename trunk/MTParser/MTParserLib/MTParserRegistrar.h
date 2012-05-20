/** @file MTParserRegistrar.h
  @brief Default Registrar File
  @author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSERREGISTRAR_INCLUDED
#define _MTPARSERREGISTRAR_INCLUDED

#include "MTParserPrivate.h"
#include <map>

#ifdef _MTPARSER_USE_PLUGIN
	#import "../Plugins/MTParserPlugin/MTParserPlugin/_MTParserPlugin.tlb" no_namespace 
#endif

//! Size of the operator hash table
#define MTREGISTRAR_OPHASHSIZE		26

/** @brief Concrete Registrar 

	Algorithms:

	hash table for operators:	The first operator symbol is the hash key.
								The compiler needs to detect operators since they are
								separator items.  Because of this, giving the beginning of
								a formula chunk, the areNextCharsOpString method needs to
								tell whether it is an operator symbol.  So only the first
								character can be considered by the hashing function and multiple
								operators can have the same first character.								
	
	Multimap for functions:		The function symbol is the ordering key.  Multiple functions can have the
								same symbol.  

	Map for variables:			The variable symbol is the ordering key.  All variable symbols are unique.								

	Map for constants:			The constant symbol is the ordering key.  All constant symbols are unique.


*/
class MTParserRegistrar : public MTRegistrarI
{
public:
	
	//******************************************
	// MTRegistrarPublicI implementation
	
	virtual void setSyntax(const MTSyntax &syntax) throw(MTParserException);	
	virtual MTSyntax getSyntax()const;	
	virtual void defineVar(MTVariableI *pVar) throw(MTParserException);	
	virtual void redefineVar(MTVariableI *pVar) throw(MTParserException);
	virtual void undefineVar(const MTCHAR *symbol) throw(MTParserException);		
	virtual void undefineAllVars();	
	virtual MTVariableI* getVarBySymbol(const MTCHAR *symbol)const throw(MTParserException);			
	virtual MTVariableI* getVar(unsigned int index)const throw(MTParserException);
	virtual unsigned int getNbDefinedVars()const;	

#ifdef _MTPARSER_USE_PLUGIN
	virtual void loadPlugin(const MTCHAR *clsid) throw(MTParserException);
#endif

	virtual void defineConst(const MTCHAR *name, MTDOUBLE val) throw(MTParserException);
	virtual unsigned int getNbDefinedConsts()const;
	virtual void getConst(unsigned int index, MTSTRING &constName, MTDOUBLE &val)const throw(MTParserException);	
	virtual void undefineConst(const MTCHAR *name) throw(MTParserException);
	virtual void defineOp( MTOperatorI *pOp) throw(MTParserException);	
	virtual unsigned int getNbDefinedOps()const;	
	virtual MTOperatorI* getOp(unsigned int index)const throw(MTParserException);	
	virtual void undefineOp(MTOperatorI *pOp) throw(MTParserException);
	virtual void defineFunc( MTFunctionI *pFunc) throw(MTParserException);
	virtual unsigned int getNbDefinedFuncs()const;
	virtual MTFunctionI* getFunc(unsigned int index)const throw(MTParserException);	
	virtual void undefineFunc(MTFunctionI *pFunc) throw(MTParserException);
	
	//******************************************
	// MTRegistrarI implementation	
	
	virtual void setVarFactory(MTVariableFactoryI *pFactory);		
	virtual void defineVar(const MTCHAR *symbol) throw(MTParserException);		
	virtual bool isVarDefined(const MTCHAR *symbol)const;	
	virtual bool findOp(const MTCHAR *symbol, bool unaryOp, unsigned int &index)const;	
	virtual bool isAFunction(const MTCHAR *word, unsigned int &index)const;		
	virtual bool findFunction(const MTCHAR *word, int nbArgs, unsigned int &index)const;
	virtual std::vector<MTFunctionI*> findFunctions(const MTCHAR *symbol)const;
	virtual bool findFunctionExact(const MTCHAR *word, int nbArgs, unsigned int &index)const;
	virtual bool findConst(const MTCHAR *constName, unsigned int &index)const;
	virtual bool areNextCharsOpString(const MTCHAR *str, unsigned int strLength, MTSTRING &symbol)const;
	virtual MTRegistrarI* spawn() throw(MTParserException);
	
	
	MTParserRegistrar();
	virtual ~MTParserRegistrar();

private:

	/** Informations about a defined operator */
	struct SOperatorInfo
	{		
		MTOperatorI *pOp;		
		MTSTRING symbol;			// performance optimization: cached value
		unsigned int symbolLength;	// performance optimization: cached value 		

		SOperatorInfo(){pOp = NULL; }

	};	
	

	/** Informations about a defined function */
	struct SFunctionInfo
	{		
		MTFunctionI *pFunc;
		MTSTRING symbol;		// performance optimization: cached value 		
		SFunctionInfo(){pFunc = NULL;}

	};	

	/** Information about a defined variable */
	struct SVariableInfo
	{			
		MTVariableI *pVar;	
		unsigned int index;
		
		SVariableInfo(){pVar = NULL; }

		SVariableInfo(MTVariableI *_pVar)
		{
			pVar = _pVar;			
		}

	};		

	/** Information about a defined constant */
	struct SConstantInfo
	{	
		MTSTRING name;		
		MTDOUBLE val;			
	};	
	

private:

	/** Add this operator to the list (no validation) */
	void registerOp(MTOperatorI *pOp);
	
	/** Add this function to the list (no validation) */
	void registerFunc(MTFunctionI *pFunc);
	
	/** Add this constant to the list (no validation) */
	void registerConst(const MTCHAR *name, MTDOUBLE val);

	/** Add this variable to the list (no validation) */
	void registerVar(MTVariableI *pVar);

	/** Make sure that this operator is valid */
	void defValidateOp(MTOperatorI *pOp)const throw(MTParserException);
	
	/** Make sure that this operator is valid */
	void defValidateFunc(MTFunctionI *pFunc)const throw(MTParserException);

	/** Make sure that this variable is valid */
	void defValidateVar(const MTSTRING &varName)const throw(MTParserException);

	/** Make sure that this constant is valid */
	void defValidateConst(const MTSTRING &constName)const throw(MTParserException);
	
	
	/** Validate that there is no character in this word that is the
		same as a syntax element: decimal point character, argument separator character...

		@param syntax: syntax to use for the validation
		@param word: string to be validated
		@param conflict [out]: if there is a conflict, this will be the syntax element in conflict
		@return true if there is no conflict	
	*/
	bool defValidateSyntaxConflict(const MTSyntax &syntax, const MTSTRING &word, MTCHAR &conflict)const;
	

	/** Validate that there is no sub-string in this word equal to an operator symbol

		@param word: string to be validated
		@param conflict [out]: if there is a conflict, this will be the operator synbol in conflict
		@return true if there is no conflict
	*/
	bool defValidateOpSymbolConflict(const MTSTRING &word, MTSTRING &conflict)const;

	/** Revalidate operators,functions, variables and constants to be
		sure that there is no syntax element in their names

		@param syntax: the new syntax to be validated	
	*/
	void defValidateSyntax(const MTSyntax &syntax)const throw(MTParserException);	

	
	/** Find a variable from its name

		@param varName: name of the variable
		@return the structure if found, null if not found	
	*/
	const SVariableInfo* getVarInfo(const MTSTRING &varName)const;	

	/** Return a variable symbol from its index */
	MTSTRING getVarSymbol(unsigned int index)const throw(MTParserException);

	void removeFromOpList(MTOperatorI *pOp);
	void removeFromOpHash(MTOperatorI *pOp);

	/** Update the variable keys */
	void updateVarKeys();

	void rebuildConstMap();
	void rebuildFuncMap();
	void decreaseOpHashAfter(unsigned int index);

	/** @brief Get the hash key for this operator symbol */
	unsigned int getOpHashKey(const MTCHAR *symbol)const
	{		
		// can consider only one character since incomplete symbols
		// can be passed to this method
		return symbol[0]%MTREGISTRAR_OPHASHSIZE;
	}

	/** @brief Get the operator info by its hashID and its position in the second-order vector */
	const SOperatorInfo* getOpByHashID(unsigned int hashID, unsigned int n)const
	{
		return &m_opList[m_opHash[hashID][n]];
	}

	/** @brief Get the operator index in the operator list by its hashID and its position in the second-order vector */
	unsigned int getOpIndexByHashID(unsigned int hashID, unsigned int n)const
	{
		return m_opHash[hashID][n];
	}


	/** Helper method to throw a definition exception */
	void throwDefExcep(const MTCHAR * id, MTSTRING itemName, MTSTRING conflictItemName = _T(""))const throw(MTParserException);
	void throwDefExcep(const MTCHAR * id, int param)const throw(MTParserException);

private:		
	
	std::vector<unsigned int> m_opHash[MTREGISTRAR_OPHASHSIZE];		// defined operators (fast acces by symbol)
	std::vector<SOperatorInfo> m_opList;		// defined operators (fast acces by index)
		
	typedef std::multimap<MTSTRING, unsigned int> TFuncMap;	
	TFuncMap m_funcMap;							// defined functions (fast access by symbol)
	std::vector<SFunctionInfo> m_funcList;		// defined functions (fast acces by index)

	typedef std::map<MTSTRING, SVariableInfo*> TVariableMap;	
	TVariableMap m_variableMap;					// defined variables (fast acces by symbol)
	std::vector<SVariableInfo*> m_variableList;	// defined variables (fast acces by index)

	typedef std::map<MTSTRING, unsigned int> TConstMap;	
	TConstMap m_constMap;						// defined constants (fast access by symbol)
	std::vector<SConstantInfo> m_constList;		// defined constants (fast acces by index)
	

	MTSyntax m_syntax;							// current syntax	
	
	MTVariableFactoryI *m_pVarFactory;			// current variable factory

	unsigned int m_varKeyVersion;				// current variable key version
	
#ifdef _MTPARSER_USE_PLUGIN
	std::vector<IMTParserPluginPtr> m_pluginPtr;		// loaded plug-ins.  Must keep a reference on loaded
														// plug-ins to keep them alive.
#endif

	
};



#endif