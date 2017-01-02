#include "BenchMuParserSSE.h"

#include <cmath>
#include <cassert>

#include "muParserSSE/muParserSSE.h"

using namespace std;

//-------------------------------------------------------------------------------------------------
BenchMuParserSSE::BenchMuParserSSE()
: Benchmark(Benchmark::FLOAT)
{
   m_sName = "muparserSSE";
}

//-------------------------------------------------------------------------------------------------
double BenchMuParserSSE::DoBenchmark(const std::string& sExpr, long iCount)
{
   mecFloat_t fRes = mecFloat_t(0.0);
   mecFloat_t a    = mecFloat_t(1.1);
   mecFloat_t b    = mecFloat_t(2.2);
   mecFloat_t c    = mecFloat_t(3.3);
   mecFloat_t d    = mecFloat_t(4.4);
   mecFloat_t x    = mecFloat_t(2.123456);
   mecFloat_t y    = mecFloat_t(3.123456);
   mecFloat_t z    = mecFloat_t(4.123456);
   mecFloat_t w    = mecFloat_t(5.123456);
   mecFloat_t buf  = mecFloat_t(0.0);
   double     fSum = mecFloat_t(0.0);

   mecParserHandle_t hParser = mecCreate();

   mecSetExpr(hParser, sExpr.c_str());
   mecDefineVar(hParser, "a", &a);
   mecDefineVar(hParser, "b", &b);
   mecDefineVar(hParser, "c", &c);

   mecDefineVar(hParser, "x", &x);
   mecDefineVar(hParser, "y", &y);
   mecDefineVar(hParser, "z", &z);
   mecDefineVar(hParser, "w", &w);

   mecDefineConst(hParser, "pi", (mecFloat_t)M_PI);
   mecDefineConst(hParser, "e",  (mecFloat_t)M_E );

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
         mecParserHandle_t htestParser = mecCreate();

         mecSetExpr(htestParser, test.first.c_str());
         mecDefineVar(htestParser, "a", &a);
         mecDefineVar(htestParser, "b", &b);
         mecDefineVar(htestParser, "c", &c);

         mecDefineVar(htestParser, "x", &x);
         mecDefineVar(htestParser, "y", &y);
         mecDefineVar(htestParser, "z", &z);
         mecDefineVar(htestParser, "w", &w);

         mecEvalFun_t pttestfun = mecCompile(htestParser);

         if (
              mecError(htestParser) ||
              (!is_equal((float)test.second,pttestfun()))
            )
         {
            mecRelease(htestParser);
            test_result = false;
            break;
         }

         mecRelease(htestParser);
      }

      if (!test_result)
      {
         StopTimerAndReport("Failed variable test");
         return m_fTime1;
      }
   }

   mecEvalFun_t ptfun = mecCompile(hParser);

   if (mecError(hParser))
   {
      const char *szMsg = mecGetErrorMsg(hParser);
      StopTimerAndReport(szMsg);
   }
   else
   {
      assert(ptfun != NULL);

      //Prime the I and D caches for the expression
      {
         double d0 = 0.0;
         double d1 = 0.0;

         for (std::size_t i = 0; i < priming_rounds; ++i)
         {
            if (i & 1)
               d0 += ptfun();
            else
               d1 += ptfun();
         }

         if (
               (d0 == std::numeric_limits<double>::infinity()) &&
               (d1 == std::numeric_limits<double>::infinity())
            )
         {
            printf("\n");
         }
      }

      fRes = ptfun();

      StartTimer();

      for (int j = 0 ; j < iCount; ++j)
      {
         fSum += ptfun();
         std::swap(a,b);
         std::swap(x,y);
      }

      StopTimer(fRes, fSum, iCount);
   }

   mecRelease(hParser);

   return m_fTime1;
}

std::string BenchMuParserSSE::GetShortName() const
{
   return "muparserSSE";
}
