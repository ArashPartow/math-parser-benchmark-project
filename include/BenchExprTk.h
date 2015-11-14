#ifndef BENCH_EXPR_TK_H
#define BENCH_EXPR_TK_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchExprTk : public Benchmark
{
public:

  BenchExprTk();

  double DoBenchmark(const std::string &sExpr, long iCount);

};

#endif
