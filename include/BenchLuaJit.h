#ifndef BENCH_LUAJIT_H
#define BENCH_LUAJIT_H

#include <vector>
#include <string>

#include "Benchmark.h"

//-------------------------------------------------------------------------------------------------
class BenchLuaJit: public Benchmark
{
public:

   BenchLuaJit();

   double DoBenchmark(const std::string &sExpr, long iCount);

};

#endif
