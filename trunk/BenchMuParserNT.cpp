#include "BenchMuParserNT.h"

#include <cmath>
#include <windows.h>

//-------------------------------------------------------------------------------------------------
#include "muParser3/muParser.h"


//-------------------------------------------------------------------------------------------------
BenchMuParserNT::BenchMuParserNT(bool bEnableOptimizer)
  :Benchmark()
{
  m_sName = "muparser3 V" + mp::Parser<double>().GetVersion();
  m_bEnableOptimizer = bEnableOptimizer;
}

//-------------------------------------------------------------------------------------------------
double BenchMuParserNT::DoBenchmark(const std::string& sExpr, long iCount)
{
  mp::Parser<double, std::string> p;
  double fRes(0);
  double fSum(0);
  double a(1.1);
  double b(2.2);
  double c(3.3);
  double x(2.123456);
  double y(3.123456);
  double z(4.123456);
  double w(5.123456);

  try
  {

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

     std::stringstream ss;
     ss << p.GetByteCode().GetSize();
     m_nTotalBytecodeSize += p.GetByteCode().GetSize();

     m_sInfo = ss.str();
  }
  catch (...)
  {
     StopTimer(std::numeric_limits<double>::quiet_NaN(),
               std::numeric_limits<double>::quiet_NaN(),
               1);
     return std::numeric_limits<double>::quiet_NaN();
  }

  return m_fTime1;
}

//-------------------------------------------------------------------------------------------------
std::string BenchMuParserNT::GetShortName() const
{
  return "muparser3";
}
