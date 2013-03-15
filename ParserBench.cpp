#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "FormelGenerator.h"

// MTParser
#include "MTParser/MTParserLib/MTParser.h"
#include "MTParser/MTParserLib/MTParserExcepStrEng.h"

#include "muParserSSE/muParserSSE.h"
#pragma comment(lib, "muParserSSE.lib")

#include "Benchmark.h"
#include "BenchMuParserNT.h"
#include "BenchMuParserX.h"
#include "BenchMuParser2.h"
#include "BenchATMSP.h"
#include "BenchFParser.h"
#include "BenchExprTk.h"

using namespace std;


struct BenchMuParserSSE : Benchmark
{
   BenchMuParserSSE()
   : Benchmark()
   {
      m_sName = "muparserSSE";
   }

   double DoBenchmark(const std::string &sExpr, long iCount)
   {
      mecFloat_t fRes(0), a(1), b(2), c(3), d(4), buf(0);
      double fSum(0);

      mecParserHandle_t hParser = mecCreate();

      mecSetExpr(hParser, sExpr.c_str());
      mecDefineVar(hParser, "a", &a);
      mecDefineVar(hParser, "b", &b);
      mecDefineVar(hParser, "c", &c);

      mecDefineVar(hParser, "x", &a);
      mecDefineVar(hParser, "y", &b);
      mecDefineVar(hParser, "z", &c);
      mecDefineVar(hParser, "w", &d);


      mecDefineConst(hParser, "pi", (mecFloat_t)M_PI);
      mecDefineConst(hParser, "e", (mecFloat_t)M_E);

      mecEvalFun_t ptfun = mecCompile(hParser);

      fRes = ptfun();

      StartTimer();
      for (int j = 0 ; j < iCount; j++)
      {
         std::swap(a,b);
         fSum += ptfun();
      }

      StopTimer(fRes, fSum, iCount);
      return m_fTime1;
   }

   virtual std::string GetShortName() const
   {
      return "muparserSSE";
   }
};

struct BenchMTParser : Benchmark
{
   BenchMTParser()
   : Benchmark()
   {
      m_sName = "MTParser";
   }

   double DoBenchmark(const std::string &sExpr, long iCount)
   {
      double a(1), b(2), c(3), x(1), y(2), z(3), w(4);

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
      p.compile(sExpr.c_str());

      double fTime(0);
      double fRes(0), fSum(0);

      fRes = p.evaluate();

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
};


bool predicate( const string &s1, const string &s2 )
{
   return s1.length()<s2.length();
}

void CreateEqnList()
{
   std::ofstream ofs("bench_expr_with_functions.txt");
   char szExpr[50000];
   int iLen = 50;
   FormelGenerator   fg;

   std::vector<string> vExpr;
   for (int k=1; k < 10; ++k)
   {
      for (int i = 1; i < iLen; i++)
      {
         fg.Make(szExpr, sizeof(szExpr), i, 2);
         vExpr.push_back(szExpr);
      }
   }

   std::sort(vExpr.begin(), vExpr.end(), predicate);
   for (std::size_t i = 0;i<vExpr.size(); ++i)
   {
      ofs <<vExpr[i] << "\n";
   }
}

std::vector<string> LoadEqn(const std::string &sFile)
{
   std::vector<string> vExpr;
   std::ifstream ifs(sFile.c_str());

   char buf[10000];
   while (ifs.getline(buf, sizeof(buf)))
   {
      int len = strlen(buf);
      if (buf[0]=='#' || len==0)
         continue;

      vExpr.push_back(buf);
   }

   std::string s = vExpr.back();
   ifs.close();

   return vExpr;
}

//-------------------------------------------------------------------------------------------------
void output(FILE *pFile, const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);

  if (pFile!=nullptr)
  {
    vfprintf(pFile, fmt, args);
    fflush(pFile);
  }

  vprintf(fmt, args);

  va_end (args);
}

//-------------------------------------------------------------------------------------------------
void Shootout(std::vector<Benchmark*> vBenchmarks, std::vector<string> vExpr, int iCount, double fRefDev = 0.0001)
{
   printf("\nBenchmark (Shootout Mode)\n");

   char outstr[400], file[400];
   time_t t = time(NULL);

   sprintf(outstr, "Shootout_%%Y%%m%%d_%%H%%M%%S.txt");
   strftime(file, sizeof(file), outstr, localtime(&t));

   FILE *pRes = fopen(file, "w");
   assert(pRes);

    Benchmark *pRefBench = vBenchmarks[0];

   std::map<double, std::vector<Benchmark*>> results;
   for (std::size_t i = 0;i<vExpr.size(); ++i)
   {
      output(pRes, "\nExpression %d of %d: \"%s\"\n", (int)i, vExpr.size(), vExpr[i].c_str());

      double fRefResult = 0;
      double fRefSum = 0;
      double fRefTime = 0;

      for (std::size_t j = 0;j<vBenchmarks.size(); ++j)
      {
         Benchmark *pBench = vBenchmarks[j];

         std::string sExpr = vExpr[i];   // get the original expression anew for each parser
         pBench->PreprocessExpr(sExpr);  // some parsers use fancy characters to signal variables
         double time = 1000 * pBench->DoBenchmark(sExpr + " ", iCount);

          // The first parser is used for obtaining reference results.
          if (j==0)
          {
            fRefResult = pBench->GetRes();
            fRefSum = pBench->GetSum();
          }
          else
          {
            // Check the sum of all results and if the sum is ok, check the last result of
            // the benchmark run.
            if (std::fabs(pBench->GetSum()-fRefSum) > (std::fabs(fRefSum) * fRefDev))
            {
              pBench->AddFail(vExpr[i]);
            }
            else if (std::fabs(pBench->GetRes()-fRefResult) > (std::fabs(fRefResult)*fRefDev))
            {
              pBench->AddFail(vExpr[i]);
            }
          }

          results[time].push_back(pBench);
      }


      int ct = 1;
      for (auto it = results.begin(); it!=results.end(); ++it)
      {
         const std::vector<Benchmark*> &vBench = it->second;

         for (std::size_t i = 0;i<vBench.size(); ++i)
         {
            Benchmark *pBench = vBench[i];

            pBench->AddPoints(vBenchmarks.size() - ct + 1);
            pBench->AddScore(pRefBench->GetTime() / pBench->GetTime() );

            if (i == 0)
            {
               output(pRes, "%d: %5s %15s (%4.5f µs, %e, %e)\n",
                       ct,
                       (pBench->GetFails().size()>0) ? "DNQ " : "    ",
                       pBench->GetShortName().c_str(),
                       it->first,
                       pBench->GetRes(),
                       pBench->GetSum());
            }
            else
            {
               output(pRes, "   %5s %-15s (%4.5f µs, %e, %e)\n",
                       (pBench->GetFails().size()>0) ? "DNQ " : "    ",
                       pBench->GetShortName().c_str(),
                       it->first,
                       pBench->GetRes(),
                       pBench->GetSum());
            }
         }

         ct += vBench.size();
      }

      results.clear();
   }

    output(pRes, "\n\nBenchmark settings:\n");
    output(pRes, "  - Reference parser is %s\n", pRefBench->GetShortName().c_str());
    output(pRes, "  - Iterations per expression: %d\n", iCount);

#if defined(_DEBUG)
    output(pRes, "  - DEBUG build\n");
#else
    output(pRes, "  - RELEASE build\n");
#endif

#if defined (__GNUC__)
    output(pRes, "  - compiled with GCC Version %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ ");
#elif defined(_MSC_VER)
    output(pRes, "  - compiled with MSC Version %d\n", _MSC_VER);
#endif

    output(pRes, "  - IEEE 754 (IEC 559) is %s\n", (std::numeric_limits<double>::is_iec559) ? "available" : " NOT AVAILABLE");
    output(pRes, "  - %d bit build\n", sizeof(void*)*8);



   output(pRes, "\n\nScores:\n");

   // Dump scores
   bool bHasFailures = false;
   for (std::size_t i = 0;i<vBenchmarks.size(); ++i)
   {
      Benchmark *pBench = vBenchmarks[i];
      bHasFailures |= pBench->GetFails().size()>0;

      output(pRes,  "   %-15s: %4d %4.4lf\n", pBench->GetShortName().c_str(), pBench->GetPoints(), pBench->GetScore());
   }

   // Dump failures
   if (bHasFailures)
   {
     output(pRes, "\n\nFailures:\n");
     for (std::size_t i = 0;i<vBenchmarks.size(); ++i)
     {
        Benchmark *pBench = vBenchmarks[i];
        std::vector<std::string> vFail = pBench->GetFails();
        if (vFail.size()>0)
        {
          output(pRes, "   %-15s:\n", pBench->GetShortName().c_str());

          for (std::size_t i=0; i<vFail.size(); ++i)
          {
            output(pRes, "         \"%s\"\n", vFail[i].c_str());
          }
        }
     }
   }

   fclose(pRes);
}

void DoBenchmark(std::vector<Benchmark*> vBenchmarks, std::vector<string> vExpr, int iCount)
{
   for (std::size_t i = 0;i<vBenchmarks.size(); ++i)
      vBenchmarks[i]->DoAll(vExpr, iCount);
}

//-------------------------------------------------------------------------------------------------
int main(int argc, const char *argv[])
{
   SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

   //  std::vector<string> vExpr = LoadEqn("bench_slow.txt");
   //std::vector<string> vExpr = LoadEqn("bench_expr_all.txt");
   std::vector<string> vExpr = LoadEqn("bench1.txt");
   //std::vector<string> vExpr = LoadEqn("bench_dbg.txt");
   //std::vector<string> vExpr = LoadEqn("bench_expr_hparser.txt");

//   int iCount = 10000000;
   int iCount = 5000000;
#ifdef _DEBUG
   iCount   = 10000;
#endif

   std::vector<Benchmark*> vBenchmarks;

   // Important: The first parser in the list becomes the reference parser. Engines producing deviating results are
   //            disqualified so make sure the reference parser is computing properly.
   // 
   // Most reliable engines so far:   exprtk and muparser2
   //
   vBenchmarks.push_back(new BenchMuParser2());
   vBenchmarks.push_back(new BenchExprTk());

   
   //vBenchmarks.push_back(new BenchMTParser());
   vBenchmarks.push_back(new BenchFParser());
   //vBenchmarks.push_back(new BenchMuParserX());
   vBenchmarks.push_back(new BenchMuParserNT(true));
   vBenchmarks.push_back(new BenchMuParserSSE());
   vBenchmarks.push_back(new BenchATMSP());

   Shootout(vBenchmarks, vExpr, iCount);
//   DoBenchmark(vBenchmarks, vExpr, iCount);

   for (std::size_t i = 0; i<vBenchmarks.size(); ++i)
      delete vBenchmarks[i];

   return 0;
}
