#include "BenchMexce.h"

#include <cmath>
#include <cstring>

#include "mexce/mexce.h"


//-------------------------------------------------------------------------------------------------
BenchMexce::BenchMexce()
: Benchmark()
{
   m_sName = "mexce";
}

//-------------------------------------------------------------------------------------------------
double BenchMexce::DoBenchmark(const std::string& sExpr, long iCount)
{
   double a = 1.1;
   double b = 2.2;
   double c = 3.3;
   double x = 2.123456;
   double y = 3.123456;
   double z = 4.123456;
   double w = 5.123456;

   mexce::evaluator ev;

   ev.bind(a, "a");
   ev.bind(b, "b");
   ev.bind(c, "c");
   ev.bind(x, "x");
   ev.bind(y, "y");
   ev.bind(z, "z");
   ev.bind(w, "w");

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
         try {
             ev.assign_expression(test.first.c_str());
         }
         catch (mexce::mexce_parsing_exception&) {
             test_result = false;
             break;
         }


         if (!is_equal(test.second, ev.evaluate() ))
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


   try {
       ev.assign_expression(sExpr.c_str());
   }
   catch (mexce::mexce_parsing_exception& e) {
       StopTimerAndReport(e.what());
       return m_fTime1;
   }


   //Prime the I and D caches for the expression
   {
      double d0 = 0.0;
      double d1 = 0.0;

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
         if (i & 1)
            d0 += ev.evaluate();
         else
            d1 += ev.evaluate();
      }

      if (
           (d0 == std::numeric_limits<double>::infinity()) &&
           (d1 == std::numeric_limits<double>::infinity())
         )
      {
         printf("\n");
      }
   }

   // Perform benchmark then return results
   double fRes = 0;
   double fSum = 0;

   fRes = ev.evaluate();

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      fSum += ev.evaluate();
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes, fSum, iCount);

   return m_fTime1;
}
