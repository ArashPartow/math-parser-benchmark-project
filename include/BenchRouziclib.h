#ifndef BENCH_ROUZICLIB_H
#define BENCH_ROUZICLIB_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchRouziclib : public Benchmark
{
public:

   BenchRouziclib();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
