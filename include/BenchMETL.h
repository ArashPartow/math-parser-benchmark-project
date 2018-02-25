#ifndef BENCH_METL_H
#define BENCH_METL_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchMETL : public Benchmark
{
public:

   BenchMETL();

   double DoBenchmark(const std::string& sExpr, long iCount);
};

#endif
