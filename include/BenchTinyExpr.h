#ifndef BENCH_TINYEXPR_H
#define BENCH_TINYEXPR_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchTinyExpr : public Benchmark
{
public:

   BenchTinyExpr();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
