#include "BenchExprTk.h"

#include <windows.h>
#include <cmath>

#define exprtk_enable_all_optimizations
#include "exprtk/exprtk.hpp"

using namespace std;


//-------------------------------------------------------------------------------------------------
BenchExprTk::BenchExprTk()
: Benchmark()
{
   m_sName = "ExprTk";
}

//-------------------------------------------------------------------------------------------------
double BenchExprTk::DoBenchmark(const std::string &sExpr, long iCount)
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

   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<double> parser;
      if (!parser.compile(sExpr,expression))
      {
         StopTimer(std::numeric_limits<double>::max(),std::numeric_limits<double>::max(),0);
         return std::numeric_limits<double>::max();
      }
   }

   // Calculate/bench and show result finally
   double fTime = 0;
   double fRes  = 0;
   double fSum  = 0;

   fRes = expression.value();
   StartTimer();
   for (int j = 0; j < iCount; j++)
   {
      std::swap(a,b);
      std::swap(x,y);
      fSum += expression.value();
   }
   StopTimer(fRes, fSum, iCount);
   return m_fTime1;
}
