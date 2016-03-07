#ifndef BENCH_FPARSER_H
#define BENCH_FPARSER_H

#include "Benchmark.h"


//-------------------------------------------------------------------------------------------------
class BenchFParser : public Benchmark
{
public:

   BenchFParser();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif