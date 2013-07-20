#include "BenchMuParser2.h"

#include <cmath>
#include <windows.h>

//-------------------------------------------------------------------------------------------------
#include "muParser2/muParser.h"

using namespace mu;


//-------------------------------------------------------------------------------------------------
BenchMuParser2::BenchMuParser2(bool bUseBulkMode)
: Benchmark()
{
   m_sName = "muparser2 V" + mu::Parser().GetVersion();
   m_bUseBulkMode = bUseBulkMode;
}

//-------------------------------------------------------------------------------------------------
double BenchMuParser2::DoBenchmarkStd(const std::string &sExpr, long iCount)
{
   Parser p;

   double fRes(0);
   double fSum(0);
   double a = 1.1;
   double b = 2.2;
   double c = 3.3;
   double d = 4.4;
   double x = 2.123456;
   double y = 3.123456;
   double z = 4.123456;
   double w = 5.123456;

   try
   {
      p.SetExpr(sExpr.c_str());
      p.DefineVar("a", &a);
      p.DefineVar("b", &b);
      p.DefineVar("c", &c);

      p.DefineVar("x", &x);
      p.DefineVar("y", &y);
      p.DefineVar("z", &z);
      p.DefineVar("w", &w);

      p.DefineConst("pi", (double)M_PI);
      p.DefineConst("e", (double)M_E);

      fRes = p.Eval(); // create bytecode on first time parsing, don't want to have this in the benchmark loop
                       // since fparser does it in Parse(...) wich is outside too
                       // (Speed of bytecode creation is irrelevant)

      StartTimer();
      for (int j = 0; j < iCount; ++j)
      {
        fSum += p.Eval();
        std::swap(a,b);
        std::swap(x,y);
      }
      StopTimer(fRes, fSum, iCount);
   }
   catch(ParserError &exc)
   {
      StopTimerAndReport(exc.GetMsg());
   }
   catch(...)
   {
      StopTimerAndReport("unexpected exception");
   }

   return m_fTime1;
}

//-------------------------------------------------------------------------------------------------
void BenchMuParser2::PreprocessExpr(std::vector<std::string> &vExpr)
{
   // atmsp is using $ to mark a constant
   for (std::size_t i=0; i<vExpr.size(); ++i)
   {
      PreprocessExpr(vExpr[i]);
   }
}

//-------------------------------------------------------------------------------------------------
void BenchMuParser2::PreprocessExpr(std::string &s)
{
}

//-------------------------------------------------------------------------------------------------
double BenchMuParser2::DoBenchmarkBulk(const std::string &sExpr, long iCount)
{
   int nBulkSize = (int)iCount;

   // allocate arrays for storing the variables
   double *a = new double[nBulkSize];
   double *b = new double[nBulkSize];
   double *c = new double[nBulkSize];
   double *d = new double[nBulkSize];
   double *x = new double[nBulkSize];
   double *y = new double[nBulkSize];
   double *z = new double[nBulkSize];
   double *w = new double[nBulkSize];
   double *result = new double[nBulkSize];

   // Note: There is a bit of variable swapping going on. I use aa,bb,xx,yy as
   //       buffer variables to toggle values.
   volatile double aa = 1.1;
   volatile double bb = 2.2;
   double xx = 2.123456;
   double yy = 3.123456;

   for (int i = 0; i < nBulkSize; ++i)
   {
      a[i] = aa;
      b[i] = bb;
      c[i] = 3.3;
      d[i] = 4.4;
      x[i] = xx;
      y[i] = yy;
      z[i] = 4.123456;
      w[i] = 5.123456;

      std::swap(aa,bb);
      std::swap(xx,yy);
   }

   double fTime(0);
   try
   {
      Parser p;
      p.SetExpr(sExpr.c_str());
      p.DefineVar("a", a);
      p.DefineVar("b", b);
      p.DefineVar("c", c);
      p.DefineVar("x", x);
      p.DefineVar("y", y);
      p.DefineVar("z", z);
      p.DefineVar("w", w);
      p.DefineConst("pi", (double)M_PI);
      p.DefineConst("e", (double)M_E);

      // Do the computation
      StartTimer();

      // Needlessly waste time swapping variables for the sake of timing fairness.
      for (int i = 0; i < nBulkSize; ++i)
      {
        std::swap(aa,bb);
        std::swap(xx,yy);
      }

      p.Eval(result, nBulkSize);

      // Note: Performing the addition inside the timed section is done
      //       because all other parsers do it in their main loop too.
      double fSum(0);
      for (int j = 0; j < nBulkSize; ++j)
      {
         fSum += result[j];
      }
      StopTimer(result[0], fSum, iCount);

      fTime = m_fTime1;
   }
   catch(ParserError &exc)
   {
      fTime = std::numeric_limits<double>::quiet_NaN();
      StopTimerAndReport(exc.GetMsg());
   }
   catch(...)
   {
      fTime = std::numeric_limits<double>::quiet_NaN();
      StopTimerAndReport("unexpected exception");
   }

   delete [] a;
   delete [] b;
   delete [] c;
   delete [] d;
   delete [] x;
   delete [] y;
   delete [] z;
   delete [] w;
   delete [] result;

   return fTime;
}

//-------------------------------------------------------------------------------------------------
double BenchMuParser2::DoBenchmark(const std::string& sExpr, long iCount)
{
   if (m_bUseBulkMode)
   {
     return DoBenchmarkBulk(sExpr, iCount);
   }
   else
   {
     return DoBenchmarkStd(sExpr, iCount);
   }
}

//-------------------------------------------------------------------------------------------------
std::string BenchMuParser2::GetShortName() const
{
   if (m_bUseBulkMode)
      return "muparser 2.2.4 (omp)";
   else
      return "muparser 2.2.4";
}
