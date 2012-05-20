#ifndef BENCH_MUPARSER_2_H
#define BENCH_MUPARSER_2_H

#include "Benchmark.h"


//-------------------------------------------------------------------------------------------------
class BenchMuParser2 : public Benchmark
{
public:
  BenchMuParser2(bool bEnableOptimizer = true);
  double DoBenchmark(const std::string &sExpr, long iCount);
  virtual std::string GetShortName() const;

private:
  bool m_bEnableOptimizer;
};

#endif