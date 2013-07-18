#include "BenchMuParserX.h"

#include <cmath>
#include <windows.h>

#include "muparserx/mpParser.h"

//-------------------------------------------------------------------------------------------------
BenchMuParserX::BenchMuParserX()
: Benchmark()
{
   m_sName = "muparserx" + mup::ParserX().GetVersion();
}

//-------------------------------------------------------------------------------------------------
double BenchMuParserX::DoBenchmark(const std::string& sExpr, long iCount)
{
   using namespace mup;

   ParserX p(pckALL_NON_COMPLEX);

   Value fRes(0);
   Value a((float_type)1.1);
   Value b((float_type)2.2);
   Value c((float_type)3.3);
   Value x((float_type)2.123456);
   Value y((float_type)3.123456);
   Value z((float_type)4.123456);
   Value w((float_type)5.123456);
   Value buf(0);
   double fTime(0);

   try
   {
      p.SetExpr(sExpr.c_str());
      p.DefineVar("a", Variable(&a));
      p.DefineVar("b", Variable(&b));
      p.DefineVar("c", Variable(&c));

      p.DefineVar("x", Variable(&x));
      p.DefineVar("y", Variable(&y));
      p.DefineVar("z", Variable(&z));
      p.DefineVar("w", Variable(&w));

      //p.DefineConst("pi", (float_type)M_PI);
      //p.DefineConst("e", (float_type)M_E);
      p.Eval(); // create bytecode on first time parsing, don't want to have this in the benchmark loop
                // since fparser does it in Parse(...) wich is outside too
                // (Speed of bytecode creation is irrelevant)

     double fSum = 0;
     fRes = p.Eval();
     StartTimer();
     for (int j = 0; j < iCount; j++)
     {
        std::swap(a,b);
        std::swap(x,y);
        fSum += p.Eval().GetFloat();
     }

     StopTimer(fRes.GetFloat(), fSum, iCount);
  }
  catch(mup::ParserError &exc)
  {
    fTime = std::numeric_limits<double>::quiet_NaN();
    StopTimerAndReport(exc.GetMsg());
  }
  catch(...)
  {
    fTime = std::numeric_limits<double>::quiet_NaN();
    StopTimerAndReport("unexpected exception");
  }

  return m_fTime1;
}

//-------------------------------------------------------------------------------------------------
std::string BenchMuParserX::GetShortName() const
{
   return "muparserx";
}
