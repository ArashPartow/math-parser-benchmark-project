/** @file MTParserLocalizer.h
	@brief Services to get localized information about functions, operators, constants and
	variables.	
	@author (c) 2008 Mathieu Jacques
*/

#ifndef _MTPARSERLOCALIZER_INCLUDED
#define _MTPARSERLOCALIZER_INCLUDED

#include "MTParserPublic.h"

#ifdef _MTPARSER_USE_LOCALIZATION

/** @brief Concrete localizer 

	This is the place to look for information about functions, 
	operators, constants and variables.  XML files are use
	to store localized information.

	Singleton:	For memory efficiency, all parser objects share the same 
				MTParserLocalizer object (i.e. no info duplication in memory).
*/
class MTParserLocalizer : public MTParserLocalizerI
{

public:

	/** @brief Get the unique instance

		@return The singleton object
	*/
	static MTParserLocalizer* getInstance();
	
	virtual void registerLibrary(const MTCHAR *infoFile) throw(MTParserException);	
	virtual void registerAllLibraries(const MTCHAR *directory, const MTCHAR *searchPattern) throw(MTParserException);

	virtual void setLocale(const MTCHAR *locale) throw(MTParserException);	
	virtual MTSTRING getLocale();
	virtual unsigned int getNbFuncs()const;		
	virtual unsigned int getNbOps()const;	
	virtual unsigned int getNbConsts()const;	
	virtual unsigned int getNbVars()const;
	virtual SFuncInfo getFuncInfo(unsigned int id)const throw(MTParserException);	
	virtual SOpInfo getOpInfo(unsigned int id)const throw(MTParserException);
	virtual SConstInfo getConstInfo(unsigned int id)const throw(MTParserException);
	virtual SVarInfo getVarInfo(unsigned int id)const throw(MTParserException);

	virtual SFuncInfo getFuncInfo(const MTCHAR *id)const throw(MTParserException);	
	virtual SOpInfo getOpInfo(const MTCHAR *id)const throw(MTParserException);
	virtual SConstInfo getConstInfo(const MTCHAR *symbol)const throw(MTParserException);
	virtual SVarInfo getVarInfo(const MTCHAR *symbol)const throw(MTParserException);
	virtual MTSTRING getExcep(const MTExcepData &data)const throw(MTParserException);
	
	/** @brief Helper method to format the function arguments into a prototype string
	
		@param	info	The function information
		@param	syntax	The syntax to be used

		@return A string prototype like: fct(a, b)
	*/
	static MTSTRING formatFuncPrototype(const SFuncInfo &info, const MTSyntax &syntax);
	
	/** @brief Helper method to format the operator arguments into a prototype string
	
		@param	info	The operator information		

		@return A string prototype like: x+y
	*/
	static MTSTRING formatOpPrototype(const SOpInfo &info);

	
private:

	/** Information about a library */
	struct SLibraryInfo
	{
		MTSTRING infoFile;		
	};

private:

	/** @brief Private constructor to be sure no one can instanciate this class but itself */
	MTParserLocalizer(){};	
	
	bool findInfoFile(const MTCHAR *infoFile)const;
	bool findFunc(const MTCHAR *idStr, unsigned int &id)const;
	bool findOp(const MTCHAR *idStr, unsigned int &id)const;
	bool findConst(const MTCHAR *symbol, unsigned int &id)const;
	bool findVar(const MTCHAR *symbol, unsigned int &id)const;
	bool findExcep(const MTCHAR *idStr, unsigned int &id)const;
	void defineLibrary(SLibraryInfo &info, const MTSTRING &locale) throw(MTParserException);	

private:	
	
	std::vector<SFuncInfo> m_funcList;				// available functions
	std::vector<SOpInfo> m_opList;					// available operators
	std::vector<SConstInfo> m_constList;			// available constants
	std::vector<SVarInfo> m_varList;				// available variables
	std::vector<SLibraryInfo> m_libraryList;		// registered library info files

	struct SExcepInfo
	{
		MTSTRING id;
		MTSTRING desc;
	};

	std::vector<SExcepInfo> m_excepList;			// available exceptions

	MTSTRING m_locale;								// the current locale
	static MTParserLocalizer m_instance;			// the unique instance
};

#endif		// _MTPARSER_USE_LOCALIZATION

#endif