#ifndef BENCH_MuParserSSE_H
#define BENCH_MuParserSSE_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchMuParserSSE : public Benchmark
{
public:

   BenchMuParserSSE();

   double DoBenchmark(const std::string& sExpr, long iCount);

   std::string BenchMuParserSSE::GetShortName() const;
};

#endif
