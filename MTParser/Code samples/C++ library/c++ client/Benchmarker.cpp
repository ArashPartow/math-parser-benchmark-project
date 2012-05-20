#include "Benchmarker.h"
#include <windows.h>

bool Benchmarker::bench(unsigned int minLoops, unsigned int &loops, unsigned int &elapsed)
{
	loops = minLoops;
	unsigned int t;		
	DWORD begin, end;
	elapsed = 0;
	DWORD lastElapsed = 0;


	DWORD minElapsed = 150;

	beforeBench();

	// find the minimum number of loops needed to be able to measure elapsed time accurately
	do
	{
		lastElapsed = elapsed;			

		begin = GetTickCount();				
		
		for( t=0; t<loops; t++ )
		{			
			doWork();
		}		
		
		end = GetTickCount();
		
		elapsed = end-begin;

		if( elapsed < minElapsed )
		{
			loops *= 2;
		}			
	
	}while( elapsed < minElapsed);

	
	
	// now average...
	
	unsigned int i;
	unsigned int nbAvgs = 3;
	for( i=0; i<nbAvgs; i++ )
	{
		begin = GetTickCount();	

		for( t=0; t<loops; t++ )
		{			
			doWork();
		}	

		end = GetTickCount();
		
		elapsed += end-begin;
	}


	
	elapsed /= (nbAvgs+1);

	/*

	// validation...
	unsigned int loops2 = (unsigned int)(((double)loops) * 1.5);
	unsigned int elapsed2 = 0;

	for( i=0; i<nbAvgs; i++ )
	{
		begin = GetTickCount();	

		for( t=0; t<loops2; t++ )
		{			
			doWork();
		}	

		end = GetTickCount();
		
		elapsed2 += end-begin;
	}

	elapsed2 /= nbAvgs;
	elapsed2 = (unsigned int)(((double)elapsed2) / 1.5);

	if( abs(elapsed2 - elapsed) < (0.1*elapsed) )
	{
		elapsed = (elapsed2 + elapsed) / 2;
		return true;
	}
	else
	{
		return false;
	}
	*/

	return true;

}