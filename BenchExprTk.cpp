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
   //exprtk::pgo_primer<double>();
}

//-------------------------------------------------------------------------------------------------
double BenchExprTk::DoBenchmark(const std::string &sExpr, long iCount)
{
   double a = 1.0;
   double b = 2.0;
   double c = 3.0;

   double x = 1.0;
   double y = 2.0;
   double z = 3.0;
   double w = 4.0;

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
      parser.compile(sExpr,expression);
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
