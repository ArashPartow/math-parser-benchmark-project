#ifndef BENCH_MATHEXPR_H
#define BENCH_MATHEXPR_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchMathExpr : public Benchmark
{
public:

   BenchMathExpr();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
