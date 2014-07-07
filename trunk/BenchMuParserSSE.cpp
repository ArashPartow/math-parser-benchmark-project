#include "BenchMuParserSSE.h"

#include <windows.h>
#include <cmath>
#include <cassert>

#include "muParserSSE/muParserSSE.h"
#pragma comment(lib, "muParserSSE.lib")

using namespace std;

//-------------------------------------------------------------------------------------------------
BenchMuParserSSE::BenchMuParserSSE()
: Benchmark(Benchmark::FLOAT)
{
   m_sName = "muparserSSE";
}

//-------------------------------------------------------------------------------------------------
double BenchMuParserSSE::DoBenchmark(const std::string& sExpr, long iCount)
{
   mecFloat_t fRes = mecFloat_t(0.0);
   mecFloat_t a    = mecFloat_t(1.1);
   mecFloat_t b    = mecFloat_t(2.2);
   mecFloat_t c    = mecFloat_t(3.3);
   mecFloat_t d    = mecFloat_t(4.4);
   mecFloat_t x    = mecFloat_t(2.123456);
   mecFloat_t y    = mecFloat_t(3.123456);
   mecFloat_t z    = mecFloat_t(4.123456);
   mecFloat_t w    = mecFloat_t(5.123456);
   mecFloat_t buf  = mecFloat_t(0.0);
   double     fSum = mecFloat_t(0.0);

   mecParserHandle_t hParser = mecCreate();

   mecSetExpr(hParser, sExpr.c_str());
   mecDefineVar(hParser, "a", &a);
   mecDefineVar(hParser, "b", &b);
   mecDefineVar(hParser, "c", &c);

   mecDefineVar(hParser, "x", &x);
   mecDefineVar(hParser, "y", &y);
   mecDefineVar(hParser, "z", &z);
   mecDefineVar(hParser, "w", &w);

   mecDefineConst(hParser, "pi", (mecFloat_t)M_PI);
   mecDefineConst(hParser, "e",  (mecFloat_t)M_E);

   mecEvalFun_t ptfun = mecCompile(hParser);

   if (mecError(hParser))
   {
      const char *szMsg = mecGetErrorMsg(hParser);
      StopTimerAndReport(szMsg);
   }
   else
   {
      assert(ptfun!=NULL);
      fRes = ptfun();

      StartTimer();
      for (int j = 0 ; j < iCount; j++)
      {
         fSum += ptfun();
         std::swap(a,b);
         std::swap(x,y);
      }

      StopTimer(fRes, fSum, iCount);
   }

   mecRelease(hParser);
   return m_fTime1;
}

std::string BenchMuParserSSE::GetShortName() const
{
   return "muparserSSE";
}
