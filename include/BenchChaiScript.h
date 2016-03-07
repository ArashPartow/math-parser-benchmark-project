#ifndef BENCH_CHAISCRIPT_H
#define BENCH_CHAISCRIPT_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchChaiScript : public Benchmark
{
public:

   BenchChaiScript();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
