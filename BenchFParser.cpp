#include "BenchFParser.h"

#include <cmath>
#include <windows.h>

// fparser includes
#include "fparser/fparser.hh"

//-------------------------------------------------------------------------------------------------
BenchFParser::BenchFParser()
: Benchmark()
{
   m_sName = "FParser 4.5";
}

//-------------------------------------------------------------------------------------------------
double BenchFParser::DoBenchmark(const std::string &sExpr, long iCount)
{
   double fTime(0);
   double fRes(0), fSum(0);

   FunctionParser Parser;
   Parser.AddConstant("pi", (double)M_PI);
   Parser.AddConstant("e", (double)M_E);
   int iRet = Parser.Parse(sExpr.c_str(), "a,b,c,x,y,z,w");
   if (iRet >= 0)
   {
      return std::numeric_limits<double>::quiet_NaN();
   }

   double vals[] = {
                     1.1,
                     2.2,
                     3.3,
                     2.123456,
                     3.123456,
                     4.123456,
                     5.123456
                   };
   fRes = Parser.Eval(vals);;

   StartTimer();
   for (int j=0; j<iCount; j++)
   {
      std::swap(vals[0], vals[1]);
      std::swap(vals[3], vals[4]);
      fSum += Parser.Eval(vals);
   }

   StopTimer(fRes, fSum, iCount);
   return m_fTime1;
}
