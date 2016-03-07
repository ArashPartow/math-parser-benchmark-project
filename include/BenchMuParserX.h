#ifndef BENCH_MUPARSERX_H
#define BENCH_MUPARSERX_H

#include "Benchmark.h"


//-------------------------------------------------------------------------------------------------
class BenchMuParserX : public Benchmark
{
public:

   BenchMuParserX();

   double DoBenchmark(const std::string& sExpr, long iCount);

   std::string GetShortName() const;
};

#endif
