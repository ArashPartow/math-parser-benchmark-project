#ifndef BENCH_MTParser_H
#define BENCH_MTParser_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchMTParser : public Benchmark
{
public:

   BenchMTParser();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
