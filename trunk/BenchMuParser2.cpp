#include "BenchMuParser2.h"

#include <cmath>
#include <windows.h>

//-------------------------------------------------------------------------------------------------
#include "muParser2/muParser.h"

using namespace mu;


//-------------------------------------------------------------------------------------------------
BenchMuParser2::BenchMuParser2(bool bEnableOptimizer)
  :Benchmark()
{
  m_sName = "muparser2 V" + mu::Parser().GetVersion();
  m_bEnableOptimizer = bEnableOptimizer;
}
  
//-------------------------------------------------------------------------------------------------
double BenchMuParser2::DoBenchmark(const std::string &sExpr, long iCount)
{
  Parser p;
  double fRes(0), fSum(0), a(1), b(2), c(3), d(4), x(1), y(2), z(3), w(4);

  p.SetExpr(sExpr.c_str());
  p.DefineVar("a", &a);
  p.DefineVar("b", &b);
  p.DefineVar("c", &c);

  p.DefineVar("x", &x);
  p.DefineVar("y", &y);
  p.DefineVar("z", &z);
  p.DefineVar("w", &w);

  p.DefineConst("pi", (double)M_PI);
  p.DefineConst("e", (double)M_E);

  fRes = p.Eval(); // create bytecode on first time parsing, don't want to have this in the benchmark loop
                   // since fparser does it in Parse(...) wich is outside too
                   // (Speed of bytecode creation is irrelevant)

  StartTimer();
  for (int j=0; j<iCount; j++) 
  {
    std::swap(a,b);
    std::swap(x,y);
    fSum += p.Eval();
  }

  StopTimer(fRes, fSum, iCount);
  return m_fTime1;
}

//-------------------------------------------------------------------------------------------------
std::string BenchMuParser2::GetShortName() const
{
  return "muparser2.2.3";
}
