#ifndef BENCH_METL_H
#define BENCH_METL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1913)
// Should be: #if __cplusplus > 201103L

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
#define ENABLE_METL

class BenchMETL : public Benchmark
{
public:

   BenchMETL();

   double DoBenchmark(const std::string& sExpr, long iCount);
};
#endif

#endif
