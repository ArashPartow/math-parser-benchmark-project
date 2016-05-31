#include "BenchMuParserX.h"

#include <cmath>
//#include <windows.h>

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

   Value fRes((float_type)0);
   Value a((float_type)1.1);
   Value b((float_type)2.2);
   Value c((float_type)3.3);
   Value x((float_type)2.123456);
   Value y((float_type)3.123456);
   Value z((float_type)4.123456);
   Value w((float_type)5.123456);
   Value buf((float_type)0);
   double fTime(0);

   p.SetExpr(sExpr.c_str());
   p.DefineVar("a", Variable(&a));
   p.DefineVar("b", Variable(&b));
   p.DefineVar("c", Variable(&c));

   p.DefineVar("x", Variable(&x));
   p.DefineVar("y", Variable(&y));
   p.DefineVar("z", Variable(&z));
   p.DefineVar("w", Variable(&w));

   try
   {

      fRes = p.Eval(); // create bytecode on first time parsing, don't want to have this in the benchmark loop
                       // since fparser does it in Parse(...) wich is outside too
                       // (Speed of bytecode creation is irrelevant)
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

   //Prime the I and D caches for the expression
   {
      double d0 = 0.0;
      double d1 = 0.0;

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
         if (i & 1)
            d0 += p.Eval().GetFloat();
         else
            d1 += p.Eval().GetFloat();
      }

      if (
            (d0 == std::numeric_limits<double>::infinity()) &&
            (d1 == std::numeric_limits<double>::infinity())
         )
      {
         printf("\n");
      }
   }

   double fSum = 0;

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      fSum += p.Eval().GetFloat();
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes.GetFloat(), fSum, iCount);

   return m_fTime1;
}

//-------------------------------------------------------------------------------------------------
std::string BenchMuParserX::GetShortName() const
{
   return "muparserx";
}
