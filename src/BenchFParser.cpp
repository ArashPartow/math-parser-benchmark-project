#include "BenchFParser.h"

#include <cmath>

// fparser includes
#include "fparser/fparser.hh"

//-------------------------------------------------------------------------------------------------
BenchFParser::BenchFParser()
: Benchmark()
{
   m_sName = "FParser 4.5";
}

//-------------------------------------------------------------------------------------------------
double BenchFParser::DoBenchmark(const std::string& sExpr, long iCount)
{
   double fRes = 0.0;
   double fSum = 0.0;

   FunctionParser Parser;
   Parser.AddConstant("pi", (double)M_PI);
   Parser.AddConstant("e",  (double)M_E );

   if (Parser.Parse(sExpr.c_str(), "a,b,c,x,y,z,w") >= 0)
   {
      StopTimerAndReport(Parser.ErrorMsg());
      return m_fTime1;
   }
   else
   {
      double vals[] = {
                        1.1,
                        2.2,
                        3.3,
                        2.123456,
                        3.123456,
                        4.123456,
                        5.123456
                      };

      // Perform basic tests for the variables used
      // in the expressions
      {
         bool test_result = true;

         auto tests_list = test_expressions();

         for (auto test : tests_list)
         {
            FunctionParser TestParser;

            if (
                 (TestParser.Parse(test.first.c_str(), "a,b,c,x,y,z,w") >= 0) ||
                 (!is_equal(test.second,TestParser.Eval(vals)))
               )
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

      //Prime the I and D caches for the expression
      {
         double d0 = 0.0;
         double d1 = 0.0;

         for (std::size_t i = 0; i < priming_rounds; ++i)
         {
            if (i & 1)
               d0 += Parser.Eval(vals);
            else
               d1 += Parser.Eval(vals);
         }

         if (
               (d0 == std::numeric_limits<double>::infinity()) &&
               (d1 == std::numeric_limits<double>::infinity())
            )
         {
            printf("\n");
         }
      }

      fRes = Parser.Eval(vals);

      StartTimer();

      for (int j = 0; j < iCount; ++j)
      {
         fSum += Parser.Eval(vals);
         std::swap(vals[0], vals[1]);
         std::swap(vals[3], vals[4]);
      }

      StopTimer(fRes, fSum, iCount);
   }

   return m_fTime1;
}
