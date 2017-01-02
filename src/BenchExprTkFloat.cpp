#include "BenchExprTkFloat.h"

#include <cmath>

#include "exprtk/exprtk.hpp"


//-------------------------------------------------------------------------------------------------
BenchExprTkFloat::BenchExprTkFloat()
: Benchmark(Benchmark::FLOAT)
{
   m_sName = "ExprTkFloat";
}

//-------------------------------------------------------------------------------------------------
double BenchExprTkFloat::DoBenchmark(const std::string& sExpr, long iCount)
{
   float a = 1.1f;
   float b = 2.2f;
   float c = 3.3f;
   float x = 2.123456f;
   float y = 3.123456f;
   float z = 4.123456f;
   float w = 5.123456f;

   exprtk::symbol_table<float> symbol_table;
   exprtk::expression<float> expression;

   symbol_table.add_variable("a", a);
   symbol_table.add_variable("b", b);
   symbol_table.add_variable("c", c);

   symbol_table.add_variable("x", x);
   symbol_table.add_variable("y", y);
   symbol_table.add_variable("z", z);
   symbol_table.add_variable("w", w);

   static float e = (float)exprtk::details::numeric::constant::e;
   symbol_table.add_variable("e", e, true);

   symbol_table.add_constants();

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
         exprtk::expression<float> test_expression;
         test_expression.register_symbol_table(symbol_table);

         exprtk::parser<float> parser;

         if (
              (!parser.compile(test.first,test_expression)) ||
              (!is_equal((float)test.second,test_expression.value()))
            )
         {
            test_result = false;
            break;
         }
      }

      if (!test_result)
      {
         StopTimer(std::numeric_limits<float>::quiet_NaN(),
                   std::numeric_limits<float>::quiet_NaN(),
                   1);
         return std::numeric_limits<float>::quiet_NaN();
      }
   }

   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<float> parser;

      if (!parser.compile(sExpr,expression))
      {
         StopTimer(std::numeric_limits<double>::quiet_NaN(),
                   std::numeric_limits<double>::quiet_NaN(),
                   1);
         return std::numeric_limits<float>::quiet_NaN();
      }
   }

   //Prime the I and D caches for the expression
   {
      float d0 = 0.0;
      float d1 = 0.0;

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
         if (i & 1)
            d0 += expression.value();
         else
            d1 += expression.value();
      }

      if (
           (d0 == std::numeric_limits<float>::infinity()) &&
           (d1 == std::numeric_limits<float>::infinity())
         )
      {
         printf("\n");
      }
   }

   float  fRes = 0;
   double fSum = 0;

   fRes = expression.value();

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      fSum += expression.value();
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes, fSum, iCount);

   return m_fTime1;
}
