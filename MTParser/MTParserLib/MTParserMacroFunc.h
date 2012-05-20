/** @file MTParserMacroFunc.h
	@brief Implementation for macro functions
	@author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSERMACROFUNC_INCLUDED
#define _MTPARSERMACROFUNC_INCLUDED

#include "MTParserPublic.h"

/** @brief Macro function
*/
class MTMacroFct : public MTFunctionI
{
public:

	/** @brief Initialize the macro object
	@param prototype	The macro prototype: macro(arg1, arg2, arg3...)
	@param macro		The macro function
	@param description	The macro description
	@param pCompiler	The compiler template
	@param pRegistrar	The registrar template
	*/
	void create(const MTSTRING &prototype, const MTSTRING &macro, const MTSTRING &description, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar ) throw(MTParserException);
	
	// MTFunctionI implementation

	virtual const MTCHAR* getSymbol();
	virtual const MTCHAR* getHelpString();
	virtual const MTCHAR* getDescription();
	virtual int getNbArgs();
	virtual void doLateInitialization(class MTCompilerI *pCompiler, class MTRegistrarI *pRegistrar) throw(MTParserException);
	virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg);		
	virtual MTFunctionI* spawn();

	MTMacroFct();
	MTMacroFct(const MTMacroFct &obj);
	~MTMacroFct();

private:

	// free memory
	void clean();
	
	/** Parse a macro prototype string
	
		Syntax: macro(arg1, arg2, arg3...)

		@param	prototype		The prototype string
		@param	syntax			The current syntax
		@param	name			[out] The detected macro name
		@param	args			[out] The detected macro arguments
	*/
	void parsePrototype(const MTSTRING &prototype, const MTSyntax &syntax, MTSTRING &name, std::vector<MTSTRING> &args) throw(MTParserException);

private:
	
	class MTParser *m_pParser;			
	MTSTRING m_description;
	MTSTRING m_helpString;
	MTSTRING m_symbol;
	MTSTRING m_macro;
	MTSTRING m_prototype;
	unsigned int m_nbArgs;	
	MTDOUBLE *m_pVars;
	bool m_isCreated;

};


#endif