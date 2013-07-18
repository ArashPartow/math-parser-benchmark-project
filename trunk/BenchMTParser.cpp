#include "BenchMTParser.h"

#include <cmath>
#include <Oleauto.h>
// MTParser
#include "MTParser/MTParserLib/MTParser.h"
#include "MTParser/MTParserLib/MTParserExcepStrEng.h"

#include "BenchMTParser.h"

using namespace std;


//-------------------------------------------------------------------------------------------------
BenchMTParser::BenchMTParser()
: Benchmark()
{
   m_sName = "MTParser";
}

//-------------------------------------------------------------------------------------------------
double BenchMTParser::DoBenchmark(const std::string& sExpr, long iCount)
{
   double a = 1.1;
   double b = 2.2;
   double c = 3.3;
   double x = 2.123456;
   double y = 3.123456;
   double z = 4.123456;
   double w = 5.123456;

   MTParser p;
   p.defineVar("a", &a);
   p.defineVar("b", &b);
   p.defineVar("c", &b);

   p.defineVar("x", &x);
   p.defineVar("y", &y);
   p.defineVar("z", &z);
   p.defineVar("w", &w);

   p.defineConst("e", M_E);
   p.defineConst("pi", M_PI);

   double fTime = 0;
   double fRes = 0;
   double fSum = 0;

   try
   {
      p.compile(sExpr.c_str());
      fRes = p.evaluate();
   }
   catch(...)
   {
      StopTimer(std::numeric_limits<double>::quiet_NaN(),
                std::numeric_limits<double>::quiet_NaN(),
                1);
      return std::numeric_limits<double>::quiet_NaN();
   }

   StartTimer();
   for (int j = 0;j<iCount; j++)
   {
      std::swap(a,b);
      std::swap(x,y);
      fSum += p.evaluate();
   }

   StopTimer(fRes, fSum, iCount);
   return m_fTime1;
}
