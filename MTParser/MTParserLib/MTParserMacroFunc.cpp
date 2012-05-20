#include "MTParserMacroFunc.h"
#include "MTTools.h"
#include "MTParser.h"
#include "MTParserPrivate.h"


//*************************************
// MTMacroFct

MTMacroFct::MTMacroFct()
{
	m_pVars = NULL;
	m_isCreated = false;
	m_pParser = NULL;
	

}
MTMacroFct::~MTMacroFct()
{
	clean();
}


void MTMacroFct::clean()
{
	if( m_pVars != NULL )
	{
		delete []m_pVars;			
		m_pVars = NULL;
	}

	if( m_pParser != NULL )
	{
		delete m_pParser;
		m_pParser = NULL;
	}
}

void MTMacroFct::parsePrototype(const MTSTRING &prototype, const MTSyntax &syntax, MTSTRING &name, std::vector<MTSTRING> &args) throw(MTParserException)
{
	unsigned int pos;	
	bool found;
	std::vector<unsigned int> originalPos;

	MTSTRING prototype2;
	MTTools::removeSpaces(prototype, originalPos, prototype2);
	unsigned int length = prototype2.size();

	// first extract the macro name...
	found = MTTools::findCharPos(prototype2, 0, MTOPEN_BRACKET, pos);
		
	if( length == 0 || !found || prototype2[length-1] != MTCLOSE_BRACKET)
	{
		// missing open or close bracket ... bad prototype syntax		
		unsigned int p = 0;				
		if( length > 0 )
		{
			p = originalPos[length-1];
		}		
		
		MTTHROW(MTExcepData (	MTDEFEXCEP_MacroProtoSyntax,
								MTEXCEPARG_POS, MTTools::longToS(p).c_str(),
								MTEXCEPARG_ITEMNAME, prototype.c_str() ));
	}
	
	name = prototype2.substr(0, pos);

	unsigned int t = pos+1;
	MTDOUBLE varVal;		// dummy var to allow validation
	MTParser parser;

	do
	{
		found = MTTools::findCharPos(prototype2, t, syntax.argumentSeparator, pos);

		// if this is the last argument, then we must look for the closing bracket
		if( !found )
		{
			found = MTTools::findCharPos(prototype2, t, MTCLOSE_BRACKET, pos);
		}

		if( found )
		{
			MTSTRING var = prototype2.substr(t, pos-t);

			if( var.size() == 0 )
			{
				// void can only mean that the macro has no argument...
				if( prototype2[length-2] != MTOPEN_BRACKET ||
					prototype2[length-1] != MTCLOSE_BRACKET )
				{					
					
					MTTHROW(MTExcepData (	MTDEFEXCEP_MacroProtoSyntax,
											MTEXCEPARG_POS, MTTools::longToS(originalPos[t]).c_str(),
											MTEXCEPARG_ITEMNAME, prototype.c_str()))
				}
			}
			else
			{			
				// validate the variable name...
				try
				{
					parser.defineVar(var.c_str(), &varVal);
				}
				catch( MTParserException &e )
				{					

					MTRETHROW(MTExcepData (	MTDEFEXCEP_MacroProtoSyntax,
											MTEXCEPARG_POS, MTTools::longToS(originalPos[t]).c_str(),
											MTEXCEPARG_ITEMNAME, prototype.c_str()), e)
				}
				args.push_back(var);
			}
		}

		t = pos+1;
	}
	while(found && t < length );
	
}

void MTMacroFct::create(const MTSTRING &prototype, const MTSTRING &macro, const MTSTRING &description, MTCompilerI *pCompiler, MTRegistrarI *pRegistrar ) throw(MTParserException)
{
	clean();

	m_pParser = new MTParser(pCompiler, pRegistrar);

	// make sure not to use the auto var def feature...
	// all variables must be declared in the prototype
	m_pParser->enableAutoVarDefinition(false);

	MTSTRING symbol;
	std::vector<MTSTRING> args;
	parsePrototype(prototype, pRegistrar->getSyntax(), symbol, args);
	m_prototype = prototype;
	

	m_pParser->undefineAllVars();		

	m_nbArgs = args.size();
	if( m_nbArgs > 0 )
	{
		m_pVars = new MTDOUBLE[m_nbArgs];
	}
	else
	{
		m_pVars = NULL;
	}
	m_helpString = symbol;
	m_helpString += MTOPEN_BRACKET;

	// define the arguments in the parser object...
	MTSyntax syntax = m_pParser->getSyntax();
	for( unsigned int t=0; t<args.size(); t++ )
	{
		m_pVars[t] = 0;		// default value
		m_pParser->defineVar(args[t].c_str(), &m_pVars[t]);
		m_helpString += args[t];

		if( t != m_nbArgs-1 )
		{
			m_helpString += syntax.argumentSeparator;
			m_helpString += _T(" ");			
		}
	}

	m_helpString += MTCLOSE_BRACKET;
	
	m_pParser->compile(macro.c_str());	

	m_macro = macro;
	m_description = description;
	m_symbol = symbol;	

	m_isCreated = true;
}

const MTCHAR* MTMacroFct::getSymbol()
{
	return m_symbol.c_str();
}
const MTCHAR* MTMacroFct::getHelpString()
{
	return m_helpString.c_str();

}
const MTCHAR* MTMacroFct::getDescription()
{
	return m_description.c_str();

}
int MTMacroFct::getNbArgs()
{
	return m_nbArgs;

}
MTDOUBLE MTMacroFct::evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
{	
	for( unsigned int t=0; t<m_nbArgs; t++ )
	{
		m_pVars[t] = pArg[t];		
	}

	return m_pParser->evaluate();
}

MTMacroFct::MTMacroFct(const MTMacroFct &obj)
{
	// Called when spawning.  If the macro is not used in the
	// expression, then there is no need to compile the macro.
	// So do as little initialization as possible in order to
	// speed up parser duplication.		
	
	m_prototype = obj.m_prototype;
	m_description = obj.m_description;	
	m_macro = obj.m_macro;
	m_symbol = obj.m_symbol;	
	m_nbArgs = obj.m_nbArgs;		// although the macro is not created, we must be able
									// to tell how many arguments it has

	m_pParser = NULL;
	m_pVars = NULL;
	m_isCreated = false;	
}
void MTMacroFct::doLateInitialization(MTCompilerI *pCompiler, MTRegistrarI *pRegistrar) throw(MTParserException)
{
	// If the macro hasn't been used yet, then compile the function...	
	if( !m_isCreated )
	{
		create(m_prototype, m_macro, m_description, pCompiler, pRegistrar);
	}
}


MTFunctionI* MTMacroFct::spawn()
{
	MTMacroFct *pFct = new MTMacroFct(*this);	
	return pFct;
}
	

