#ifndef _BENCHMARKER_INCLUDED
#define _BENCHMARKER_INCLUDED

// Benchmark Class template 
// You have to provide an implementation for the doWork method and
// the bench method will call it.  
class Benchmarker
{
public:

	virtual void beforeBench(){};
	virtual void doWork() = 0;

	bool bench(unsigned int minLoops, unsigned int &loops, unsigned int &elapsed);

};

#endif