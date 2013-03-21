#include "BenchExprTkFloat.h"

#include <windows.h>
#include <cmath>

#define exprtk_enable_all_optimizations
#include "exprtk/exprtk.hpp"

using namespace std;


//-------------------------------------------------------------------------------------------------
BenchExprTkFloat::BenchExprTkFloat()
: Benchmark(Benchmark::FLOAT)
{
   m_sName = "ExprTkFloat";
}

//-------------------------------------------------------------------------------------------------
double BenchExprTkFloat::DoBenchmark(const std::string &sExpr, long iCount)
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

   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<float> parser;
      if (!parser.compile(sExpr,expression))
      {
         StopTimer(std::numeric_limits<float>::max(),std::numeric_limits<float>::max(),0);
         return std::numeric_limits<float>::quiet_NaN();
      }
   }

   // Calculate/bench and show result finally
   double fTime = 0;
   float fRes   = 0;
   float fSum   = 0;

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
