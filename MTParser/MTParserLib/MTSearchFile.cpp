#include "MTSearchFile.h"
#include <windows.h>

void MTSearchFile::search(const std::vector<MTSTRING> &directories, const std::vector<MTSTRING> &searchPatterns, std::vector<MTSTRING> &results)
{      
    results.clear();
    
    for( unsigned int t=0; t < directories.size(); t++ )
    {
        // the path must end with a /
		MTSTRING dir = directories[t];

        if( dir[dir.size()-1] != '/' &&
            dir[dir.size()-1] != '\\' )
        {
            dir += _T("/");
        }

		search(dir.c_str(), searchPatterns, results);        
    }    
}

void MTSearchFile::search(const MTCHAR *directory, const std::vector<MTSTRING> &searchPatterns, std::vector<MTSTRING> &results)
{
    // file search
	for( unsigned int t=0; t<searchPatterns.size(); t++ )
	{	
		search( directory, searchPatterns[t].c_str(), results );		
	}    

	// now, we look for subfolders    
	WIN32_FIND_DATA findData;
    HANDLE hFind;
	MTSTRING curLookIn = directory;
	curLookIn += _T("*.*");
    
	hFind = FindFirstFile( curLookIn.c_str() , &findData);
    
    if( hFind != INVALID_HANDLE_VALUE )
    {
        do
        {        
			// if this is a sub-folder then search it
            if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
                findData.cFileName[0] != '.' )                
            {
                MTSTRING curLookDir = directory;
				curLookDir += findData.cFileName;
				curLookDir += _T("/");

				search( curLookDir.c_str(), searchPatterns, results );                
            }

        }while( FindNextFile(hFind, &findData) );        
    }     
    
    FindClose(hFind);
}

void MTSearchFile::search(const MTCHAR *directory, const MTCHAR *searchPattern, std::vector<MTSTRING> &results)
{	
    WIN32_FIND_DATA findData;
	MTSTRING curLookIn = directory;
	curLookIn += searchPattern;
	
	HANDLE hFind = FindFirstFile(curLookIn.c_str(), &findData);
    
    if( hFind != INVALID_HANDLE_VALUE )
    {
        do
        { 	
            // skip directories and special files named "."
			if( !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				findData.cFileName[0] != '.' )                
            {
				MTSTRING found = directory;
				found += findData.cFileName;
                results.push_back( found );
            }
            
        }while( FindNextFile(hFind, &findData) );        
    }

    FindClose(hFind);
}
