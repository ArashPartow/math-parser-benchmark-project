#ifndef BENCH_MUPARSER_H
#define BENCH_MUPARSER_H

#include "Benchmark.h"


//-------------------------------------------------------------------------------------------------
class BenchMuParserNT : public Benchmark
{
public:
  BenchMuParserNT(bool bEnableOptimizer = true);
  double DoBenchmark(const std::string &sExpr, long iCount);
  virtual std::string GetShortName() const;

private:
  bool m_bEnableOptimizer;
};

#endif