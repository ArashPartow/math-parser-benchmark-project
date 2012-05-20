/** @file MTSearchFile.h
	@brief Search file utility
	@author (c) 2008 Mathieu Jacques
*/


#ifndef _MTSEARCHFILE_INCLUDED
#define _MTSEARCHFILE_INCLUDED

#include "MTUnicodeANSIDefs.h"
#include <vector>

/** @brief Search file class	
*/
class MTSearchFile
{
public:

	MTSearchFile(){};    
	
	/** @brief Search in multiple directories using multiple search patterns

	Look in subfolders.

	@param	directories		Directories where to look.  Format: C:\dos\, c:\
	@param	searchPatterns	File search patterns like *.xml or any valid patterns
	@param	results			[out] Found files	

	*/
	void search(const std::vector<MTSTRING> &directories, const std::vector<MTSTRING> &searchPatterns, std::vector<MTSTRING> &results);	    
private:

	/** @brief Search in one directory using multiple search patterns

	Look in subfolders.

	@param	directory		Directories where to look.  Format: C:\dos\, c:\
	@param	searchPatterns	File search patterns like *.xml or any valid patterns
	@param	results			[out] Found files	

	*/
	void search(const MTCHAR *directory, const std::vector<MTSTRING> &searchPatterns, std::vector<MTSTRING> &results);	
	
	/** @brief Search in one directory using one search patterns

	Doesn't look in subfolders.

	@param	directory		Directory where to look.  Format: C:\dos\, c:\
	@param	searchPattern	File search patterns like *.xml or any valid patterns
	@param	results			[out] Found files	

	*/
	void search(const MTCHAR *directory, const MTCHAR *searchPattern, std::vector<MTSTRING> &results);
   
};	   

#endif
