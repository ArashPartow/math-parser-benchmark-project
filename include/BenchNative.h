#ifndef BENCH_NATIVE_H
#define BENCH_NATIVE_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchNative : public Benchmark
{
public:

   BenchNative();

   double DoBenchmark(const std::string& sExpr, long iCount);

   static std::vector<std::string> load_native_expressions();
};

#endif
