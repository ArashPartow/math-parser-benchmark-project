#ifndef BENCH_LEPTON_H
#define BENCH_LEPTON_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchLepton : public Benchmark
{
public:

   BenchLepton();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
