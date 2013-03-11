#include "BenchATMSP.h"

#include <windows.h>
#include <cmath>

// atmsp
#include "atmsp/atmsp.h"

using namespace std;


//-------------------------------------------------------------------------------------------------
BenchATMSP::BenchATMSP()
: Benchmark()
{
   m_sName = "atmsp 1.0.3";
}

//-------------------------------------------------------------------------------------------------
std::string BenchATMSP::replaceAll(std::string result,
                                   const std::string& replaceWhat,
                                   const std::string& replaceWithWhat)
{
   int start = 0;
   while(1)
   {
      int pos = result.find(replaceWhat, start);

      if (pos==-1)
         break;

      result.replace(pos,replaceWhat.size(),replaceWithWhat);
      start = pos + replaceWithWhat.length();
   }
   return result;
}

//-------------------------------------------------------------------------------------------------
void BenchATMSP::PreprocessExpr(std::vector<std::string> &vExpr)
{
   // atmsp is using $ to mark a constant
   for (std::size_t i=0; i<vExpr.size(); ++i)
   {
      PreprocessExpr(vExpr[i]);
      //string s = vExpr[i];
      //s = replaceAll(s, string("pi"), string("$pi"));
      //s = replaceAll(s, string("-e*"), string("-$e*"));
      //s = replaceAll(s, string("/e*"), string("/$e*"));
      //s = replaceAll(s, string("(e*"), string("($e*"));
      //s = replaceAll(s, string("-e/"), string("-$e/"));
      //s = replaceAll(s, string("e^"), string("$e^"));
      //s = replaceAll(s, string("+e)"), string("+$e)"));
      //s = replaceAll(s, string("(e+"), string("($e+"));
      //s = replaceAll(s, string("(e-"), string("($e-"));
      //s = replaceAll(s, string("(-e"), string("(-$e"));
      //s = replaceAll(s, string("-e)"), string("-$e)"));
      //s = replaceAll(s, string("(e)"), string("($e)"));
      //s = replaceAll(s, string("/e)"), string("/$e)"));
      //s = replaceAll(s, string("/e/"), string("/$e/"));
      //s = replaceAll(s, string("*e+"), string("*$e+"));
      //vExpr[i] = s;
   }
}

//-------------------------------------------------------------------------------------------------
void BenchATMSP::PreprocessExpr(std::string &s)
{
  s = replaceAll(s, string("pi"), string("$pi"));
  s = replaceAll(s, string("-e*"), string("-$e*"));
  s = replaceAll(s, string("/e*"), string("/$e*"));
  s = replaceAll(s, string("(e*"), string("($e*"));
  s = replaceAll(s, string("-e/"), string("-$e/"));
  s = replaceAll(s, string("e^"), string("$e^"));
  s = replaceAll(s, string("+e)"), string("+$e)"));
  s = replaceAll(s, string("(e+"), string("($e+"));
  s = replaceAll(s, string("(e-"), string("($e-"));
  s = replaceAll(s, string("(-e"), string("(-$e"));
  s = replaceAll(s, string("-e)"), string("-$e)"));
  s = replaceAll(s, string("(e)"), string("($e)"));
  s = replaceAll(s, string("/e)"), string("/$e)"));
  s = replaceAll(s, string("/e/"), string("/$e/"));
  s = replaceAll(s, string("*e+"), string("*$e+"));
}

//-------------------------------------------------------------------------------------------------
double BenchATMSP::DoBenchmark(const std::string &sExpr, long iCount)
{
   ATMSB<double> bc;

   // Parsing/bytecode generation with error check. In a scope here JUST to
   // demonstrate that a parser-instance itself is NOT needed later on
   ATMSP<double> p;
   unsigned int err = p.parse(bc, sExpr, "a, b, c, x, y, z, w");
   if (err)
   {
      StopTimer(std::numeric_limits<double>::max(),std::numeric_limits<double>::max(),0);
      return std::numeric_limits<double>::max();
      //throw std::runtime_error(std::string("atmsp: ") + p.errMessage(err));
   }

   // Set variable values for x,y,z. Here always 1,2,3
   bc.var[0] = 1.0;
   bc.var[1] = 2.0;
   bc.var[2] = 3.0;
   bc.var[3] = 1.0;
   bc.var[4] = 2.0;
   bc.var[5] = 3.0;
   bc.var[6] = 4.0;

   // Calculate/bench and show result finally
   double fTime(0);
   double fRes(0), fSum(0);

   fRes = bc.run();

   StartTimer();
   for (int j=0; j<iCount; j++)
   {
      std::swap(bc.var[0], bc.var[1]);
      std::swap(bc.var[3], bc.var[4]);
      fSum += bc.run();
   }

   StopTimer(fRes, fSum, iCount);

   return m_fTime1;
}
