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
    mecFloat_t fRes(0);
    mecFloat_t a(1.1);
    mecFloat_t b(2.2);
    mecFloat_t c(3.3);
    mecFloat_t d(4.4);
    mecFloat_t x(2.123456);
    mecFloat_t y(3.123456);
    mecFloat_t z(4.123456);
    mecFloat_t w(5.123456);
    mecFloat_t buf(0);
    double fSum(0);

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

    return m_fTime1;
}

std::string BenchMuParserSSE::GetShortName() const
{
   return "muparserSSE";
}
