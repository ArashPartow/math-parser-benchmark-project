#ifndef BENCH_EXPRTKFLOAT_H
#define BENCH_EXPRTKFLOAT_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchExprTkFloat : public Benchmark
{
public:

   BenchExprTkFloat();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
