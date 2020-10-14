#ifndef BENCH_MEXCE_H
#define BENCH_MEXCE_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchMexce : public Benchmark
{
public:

    BenchMexce();

    double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
