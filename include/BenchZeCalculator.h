#pragma once

#include "Benchmark.h"


//-------------------------------------------------------------------------------------------------
class BenchZeCalculator : public Benchmark
{
public:

   BenchZeCalculator();

   double DoBenchmark(const std::string& sExpr, long iCount);

   std::string GetShortName() const;
};
