#ifndef BENCH_EXPRTKMPFR_H
#define BENCH_EXPRTKMPFR_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchExprTkMPFR : public Benchmark
{
public:

   BenchExprTkMPFR();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
