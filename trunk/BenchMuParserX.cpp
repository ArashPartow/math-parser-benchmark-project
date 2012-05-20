#include "BenchMuParserX.h"

#include <cmath>
#include <windows.h>


//-------------------------------------------------------------------------------------------------
BenchMuParserX::BenchMuParserX()
  :Benchmark()
{
  m_sName = "muparserx" + mup::ParserX().GetVersion();
}
  
//-------------------------------------------------------------------------------------------------
double BenchMuParserX::DoBenchmark(const std::string &sExpr, long iCount)
{
  using namespace mup;

  ParserX p(pckALL_NON_COMPLEX);

  Value fRes(0);
  Value a((float_type)1.0), b((float_type)2.0), c((float_type)3.0), buf(0);
  double fTime(0);

  p.SetExpr(sExpr.c_str());
  p.DefineVar("a", Variable(&a));
  p.DefineVar("b", Variable(&b));
  p.DefineVar("c", Variable(&c));
  p.DefineConst("pi", (float_type)M_PI);
  p.DefineConst("e", (float_type)M_E);
  p.Eval(); // create bytecode on first time parsing, don't want to have this in the benchmark loop
            // since fparser does it in Parse(...) wich is outside too
            // (Speed of bytecode creation is irrelevant)

  double fSum = 0;
  fRes = p.Eval();
  StartTimer();
  for (int j=0; j<iCount; j++) 
  {
    std::swap(a,b);
    fSum += p.Eval().GetFloat();
  }

  StopTimer(fRes.GetFloat(), fSum, iCount);

  return m_fTime1;
}

//-------------------------------------------------------------------------------------------------
std::string BenchMuParserX::GetShortName() const
{
  return "muparserx";
}
