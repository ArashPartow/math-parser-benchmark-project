#ifndef BENCH_ATMSP_H
#define BENCH_ATMSP_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchATMSP : public Benchmark
{
public:

  BenchATMSP();
  virtual double DoBenchmark(const std::string &sExpr, long iCount);
  virtual void PreprocessExpr(std::vector<std::string> &vExpr);
  virtual void PreprocessExpr(std::string &vExpr);

private:

  std::string replaceAll(std::string result, 
                         const std::string& replaceWhat, 
                         const std::string& replaceWithWhat);
};

#endif
