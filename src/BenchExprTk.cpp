#include "BenchExprTk.h"

#include <cmath>

#include "exprtk/exprtk.hpp"


//-------------------------------------------------------------------------------------------------
BenchExprTk::BenchExprTk()
: Benchmark()
{
   m_sName = "ExprTk";
}

//-------------------------------------------------------------------------------------------------
double BenchExprTk::DoBenchmark(const std::string& sExpr, long iCount)
{
   double a = 1.1;
   double b = 2.2;
   double c = 3.3;
   double x = 2.123456;
   double y = 3.123456;
   double z = 4.123456;
   double w = 5.123456;

   exprtk::symbol_table<double> symbol_table;
   exprtk::expression<double> expression;

   symbol_table.add_variable("a", a);
   symbol_table.add_variable("b", b);
   symbol_table.add_variable("c", c);

   symbol_table.add_variable("x", x);
   symbol_table.add_variable("y", y);
   symbol_table.add_variable("z", z);
   symbol_table.add_variable("w", w);

   static double e = exprtk::details::numeric::constant::e;
   symbol_table.add_variable("e", e, true);

   symbol_table.add_constants();

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
         exprtk::expression<double> test_expression;
         test_expression.register_symbol_table(symbol_table);

         exprtk::parser<double> parser;

         if (
              (!parser.compile(test.first,test_expression)) ||
              (!is_equal(test.second,test_expression.value()))
            )
         {
            test_result = false;
            break;
         }
      }

      if (!test_result)
      {
         StopTimer(std::numeric_limits<double>::quiet_NaN(),
                   std::numeric_limits<double>::quiet_NaN(),
                   1);
         return std::numeric_limits<double>::quiet_NaN();
      }
   }

   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<double> parser;

      if (!parser.compile(sExpr,expression))
      {
         StopTimer(std::numeric_limits<double>::quiet_NaN(),
                   std::numeric_limits<double>::quiet_NaN(),
                   1);
         return std::numeric_limits<double>::quiet_NaN();
      }
   }

   //Prime the I and D caches for the expression
   {
      double d0 = 0.0;
      double d1 = 0.0;

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
         if (i & 1)
            d0 += expression.value();
         else
            d1 += expression.value();
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
