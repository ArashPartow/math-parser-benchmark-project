#include "BenchMuParserX.h"

#include <cmath>

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
   Value    a((float_type)1.1);
   Value    b((float_type)2.2);
   Value    c((float_type)3.3);
   Value    x((float_type)2.123456);
   Value    y((float_type)3.123456);
   Value    z((float_type)4.123456);
   Value    w((float_type)5.123456);
   Value  buf((float_type)0);

   double fTime(0);

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
         ParserX test_p(pckALL_NON_COMPLEX);

         test_p.SetExpr(test.first.c_str());
         test_p.DefineVar("a", &a);
         test_p.DefineVar("b", &b);
         test_p.DefineVar("c", &c);

         test_p.DefineVar("x", &x);
         test_p.DefineVar("y", &y);
         test_p.DefineVar("z", &z);
         test_p.DefineVar("w", &w);

         try
         {
            if (!is_equal(test.second,test_p.Eval().GetFloat()))
            {
               test_result = false;
               break;
            }
         }
         catch(...)
         {
            test_result = false;
            break;
         }
      }

      if (!test_result)
      {
         StopTimerAndReport("Failed variable test");
         return m_fTime1;
      }
   }

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
      return std::numeric_limits<double>::quiet_NaN();
   }
   catch(...)
   {
      fTime = std::numeric_limits<double>::quiet_NaN();
      StopTimerAndReport("unexpected exception");
      return std::numeric_limits<double>::quiet_NaN();
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
