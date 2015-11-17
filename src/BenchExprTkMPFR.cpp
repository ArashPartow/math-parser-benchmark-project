#include "BenchExprTkMPFR.h"
#ifdef ENABLE_MPFR

#include <cmath>

#include "mpfr/mpreal.h"
#include "exprtk/exprtk_mpfr_adaptor.hpp"
#include "exprtk/exprtk.hpp"


//-------------------------------------------------------------------------------------------------
BenchExprTkMPFR::BenchExprTkMPFR()
: Benchmark(Benchmark::MPFR)
{
   m_sName = "ExprTkMPFR128";
}

//-------------------------------------------------------------------------------------------------
double BenchExprTkMPFR::DoBenchmark(const std::string& sExpr, long iCount)
{
   mpfr::mpreal::set_default_prec(128);

   mpfr::mpreal a = mpfr::mpreal(1.1);
   mpfr::mpreal b = mpfr::mpreal(2.2);
   mpfr::mpreal c = mpfr::mpreal(3.3);
   mpfr::mpreal x = mpfr::mpreal(2.123456);
   mpfr::mpreal y = mpfr::mpreal(3.123456);
   mpfr::mpreal z = mpfr::mpreal(4.123456);
   mpfr::mpreal w = mpfr::mpreal(5.123456);

   exprtk::symbol_table<mpfr::mpreal> symbol_table;
   exprtk::expression<mpfr::mpreal> expression;

   symbol_table.add_variable("a", a);
   symbol_table.add_variable("b", b);
   symbol_table.add_variable("c", c);

   symbol_table.add_variable("x", x);
   symbol_table.add_variable("y", y);
   symbol_table.add_variable("z", z);
   symbol_table.add_variable("w", w);

   static mpfr::mpreal e = (mpfr::mpreal)exprtk::details::numeric::constant::e;
   symbol_table.add_variable("e", e, true);

   symbol_table.add_constants();

   expression.register_symbol_table(symbol_table);

   {
      exprtk::parser<mpfr::mpreal> parser;
      if (!parser.compile(sExpr,expression))
      {
         StopTimer(std::numeric_limits<double>::quiet_NaN(),
                   std::numeric_limits<double>::quiet_NaN(),
                   1);
         return std::numeric_limits<double>::quiet_NaN();
      }
   }

   mpfr::mpreal fRes = mpfr::mpreal(0);
   double       fSum = 0.0;

   fRes = expression.value();

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      fSum += expression.value().toDouble();
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes.toDouble(), fSum, iCount);

   return m_fTime1;
}
#endif
