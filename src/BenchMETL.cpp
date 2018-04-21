#include "BenchMETL.h"

#ifdef ENABLE_METL

#include <cmath>

#include "METL/metl.h"

//-------------------------------------------------------------------------------------------------
BenchMETL::BenchMETL()
: Benchmark()
{
   m_sName = "METL";
}

//-------------------------------------------------------------------------------------------------
double BenchMETL::DoBenchmark(const std::string& sExpr, long iCount)
{
   typedef double numeric_t;

   auto compiler = metl::makeCompiler<int, numeric_t>();
   metl::setDefaults(compiler); // add default operators and functions for ints and numeric_ts.

   // required because metl would otherwise do int-division
   compiler.setOperator<int, int>("/", [](const auto& left, const auto& right)
   {
      return numeric_t(left) / right;
   });

   // metl-defaults do not provide operator<, especially not such that it returns numeric_t
   compiler.setOperator<numeric_t, numeric_t>("<", [](numeric_t left, numeric_t right) -> numeric_t
   {
      return static_cast<numeric_t>(left < right);
   });

   // a little optimization
   compiler.setFunction<numeric_t>("e^", [](numeric_t exponent) ->numeric_t
   {
      return std::exp(exponent);
   });

   numeric_t a = numeric_t(1.1     );
   numeric_t b = numeric_t(2.2     );
   numeric_t c = numeric_t(3.3     );
   numeric_t x = numeric_t(2.123456);
   numeric_t y = numeric_t(3.123456);
   numeric_t z = numeric_t(4.123456);
   numeric_t w = numeric_t(5.123456);

   compiler.setVariable("a", &a);
   compiler.setVariable("b", &b);
   compiler.setVariable("c", &c);
   compiler.setVariable("x", &x);
   compiler.setVariable("y", &y);
   compiler.setVariable("z", &z);
   compiler.setVariable("w", &w);

   // copied from exprtk::numeric::constant
   const numeric_t e  = numeric_t(2.71828182845904523536028747135266249775724709369996);
   const numeric_t pi = numeric_t(3.14159265358979323846264338327950288419716939937510);

   compiler.setConstant("e",   e);
   compiler.setConstant("pi", pi);

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
         try
         {
            auto f = compiler.build<numeric_t>(test.first);
            test_result = (f() == test.second);
         }
         catch (const std::runtime_error&)
         {
            test_result = false;
         }

         if (!test_result) break;
      }

      if (!test_result)
      {
         StopTimerAndReport("Failed variable test");
         return m_fTime1;
      }
   }


   std::function<numeric_t()> f;
   {
      try
      {
         f = compiler.build<numeric_t>(sExpr);
      }
      catch (const std::runtime_error& error)
      {
         StopTimerAndReport(error.what());
         return m_fTime1;
      }
   }

   //Prime the I and D caches for the expression.
   {
      numeric_t d0 = numeric_t(0.0);
      numeric_t d1 = numeric_t(0.0);

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
         if (i & 1)
            d0 += f();
         else
            d1 += f();
      }

      if (
           (d0 == std::numeric_limits<numeric_t>::infinity()) &&
           (d1 == std::numeric_limits<numeric_t>::infinity())
         )
      {
         printf("\n");
      }
   }

   // Perform benchmark then return results
   numeric_t fRes = numeric_t(0.0);
   numeric_t fSum = numeric_t(0.0);

   fRes = f();

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      fSum += f();
      std::swap(a, b);
      std::swap(x, y);
   }

   StopTimer(fRes, fSum, iCount);

   return m_fTime1;
}

#endif
