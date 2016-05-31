#include "BenchChaiScript.h"
#include <cmath>

#ifdef enable_chaiscript
#include "chaiscript/chaiscript.hpp"
#endif

//-------------------------------------------------------------------------------------------------
BenchChaiScript::BenchChaiScript()
: Benchmark()
{
   m_sName = "ChaiScript";
}

//-------------------------------------------------------------------------------------------------
double BenchChaiScript::DoBenchmark(const std::string& sExpr, long iCount)
{
   StopTimerAndReport("");
   return std::numeric_limits<double>::quiet_NaN();
   /*
   double a = 1.1;
   double b = 2.2;
   double c = 3.3;
   double x = 2.123456;
   double y = 3.123456;
   double z = 4.123456;
   double w = 5.123456;

   chaiscript::ChaiScript chai;

   chai.add(chaiscript::var(a), "a");
   chai.add(chaiscript::var(b), "b");
   chai.add(chaiscript::var(c), "c");
   chai.add(chaiscript::var(x), "x");
   chai.add(chaiscript::var(y), "y");
   chai.add(chaiscript::var(z), "z");
   chai.add(chaiscript::var(w), "w");

   // Perform benchmark then return results
   double fRes  = 0;
   double fSum  = 0;

   try
   {
      fRes = chai.eval<double>(sExpr);
   }
   catch (std::exception& e)
   {
      StopTimerAndReport(e.what());
      return std::numeric_limits<double>::quiet_NaN();
   }

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      fSum += chai.eval<double>(sExpr);
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes, fSum, iCount);

   return m_fTime1;
   */
}
