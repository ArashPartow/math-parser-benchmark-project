#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>

#include "FormelGenerator.h"
#include "cpuid.h"
#include "Benchmark.h"
#include "BenchMuParserX.h"
#include "BenchMuParser2.h"
#include "BenchATMSP.h"
//#include "BenchFParser.h"
#include "BenchExprTk.h"
#include "BenchExprTkFloat.h"
#include "BenchLepton.h"
#include "BenchMathExpr.h"

#ifdef _MSC_VER
#include "BenchMTParser.h"
#include "BenchMuParserSSE.h"
#endif


template <typename T>
inline bool is_equal(const T v0, const T v1)
{
   static const T epsilon = T(0.000001);
   //static const T epsilon = T(std::numeric_limits<double>::epsilon());
   //static const T epsilon = T(std::numeric_limits<float>::epsilon());
   //Is either a NaN?
   if (v0 != v0) return false;
   if (v1 != v1) return false;
   return (std::abs(v0 - v1) <= (std::max(T(1),std::max(std::abs(v0),std::abs(v1))) * epsilon)) ? true : false;
}

std::vector<std::string> load_expressions(const std::string& file_name)
{
   std::ifstream stream(file_name.c_str());
   std::vector<std::string> result;
   if (stream)
   {
      std::string buffer;
      while (std::getline(stream,buffer))
      {
         if (buffer.empty())
            continue;
         else if ('#' == buffer[0])
            continue;
         else
            result.push_back(buffer);
      }
   }
   return result;
}

void output(FILE *pFile, const char *fmt, ...)
{
  va_list args;

  va_start (args, fmt);
  if (pFile)
  {
     vfprintf(pFile, fmt, args);
     fflush(pFile);
  }
  va_end (args);

  va_start (args, fmt);
  vprintf(fmt, args);
  va_end (args);

  fflush(nullptr);
}

void Shootout(const std::string &sCaption,
              std::vector<Benchmark*> vBenchmarks,
              std::vector<std::string> vExpr,
              int iCount)
{
   char outstr[400], file[400];
   time_t t = time(NULL);

   sprintf(outstr, "Shootout_%%Y%%m%%d_%%H%%M%%S.txt");
   strftime(file, sizeof(file), outstr, localtime(&t));

   FILE *pRes = fopen(file, "w");
   assert(pRes);

   output(pRes, "Benchmark (Shootout for file \"%s\")\n", sCaption.c_str());

   Benchmark* pRefBench = vBenchmarks[0];

   std::map<double, std::vector<Benchmark*>> results;

   for (std::size_t i = 0; i < vExpr.size(); ++i)
   {
      std::size_t failure_count = 0;
      const std::string current_expr = vExpr[i];

      output(pRes, "\nExpression %d of %d: \"%s\"; Progress: ",
             (int)(i + 1),
             vExpr.size(),
             current_expr.c_str());

      double fRefResult = 0.0;
      double fRefSum    = 0.0;

      // Setup Reference parser result and total sum.
      {
         Benchmark *pBench = vBenchmarks[0];

         pBench->DoBenchmark(current_expr + " ", iCount);

         fRefResult = pBench->GetRes();
         fRefSum    = pBench->GetSum();

         if (
             (fRefResult ==  std::numeric_limits<double>::infinity()) ||
             (fRefResult == -std::numeric_limits<double>::infinity()) ||
             (fRefResult != fRefResult)
            )
         {
            output(pRes, "\nWARNING: Expression rejected due to non-numeric result.");
            continue;
         }
      }

      for (std::size_t j = 0; j < vBenchmarks.size(); ++j)
      {
         output(pRes, "#");  // <- "Progress" indicator for debugging, if a parser is crashing i'd like to know which one
         Benchmark* pBench = vBenchmarks[j];

         std::string sExpr = current_expr;  // get the original expression anew for each parser
         pBench->PreprocessExpr(sExpr);     // some parsers use fancy characters to signal variables
         double time = 1000000.0 * pBench->DoBenchmark(sExpr + " ", iCount);

         // The first parser is used for obtaining reference results.
         // If the reference result is nan the reference parser is
         // disqualified too.
         if (pBench->DidNotEvaluate())
         {
            pBench->AddFail(vExpr[i]);
            ++failure_count;
         }
         else if (
                  !is_equal(pBench->GetRes(),fRefResult)
                  ||
                  //Instead of 5, perhaps something proportional to iCount, but no less than 1?
                  (std::abs(static_cast<long long>(pBench->GetSum()) - static_cast<long long>(fRefSum)) > 5)
                 )
         {
            // Check the sum of all results and if the sum is ok, check the last result of
            // the benchmark run.
            pBench->AddFail(vExpr[i]);
            ++failure_count;
         }

         results[time].push_back(pBench);
      }

      output(pRes, "\n");

      int ct = 1;

      for (auto it = results.begin(); it != results.end(); ++it)
      {
         const std::vector<Benchmark*>& vBench = it->second;

         for (std::size_t k = 0; k < vBench.size(); ++k)
         {
            Benchmark* pBench = vBench[k];

            if (pBench->ExpressionFailed(current_expr))
            {
               continue;
            }

            pBench->AddPoints(vBenchmarks.size() - ct + 1);
            pBench->AddScore(pRefBench->GetTime() / pBench->GetTime() );

            output(pRes, "    %-20s (%9.3f ns, %26.18f, %26.18f)\n",
                   pBench->GetShortName().c_str(),
                   it->first,
                   pBench->GetRes(),
                   pBench->GetSum());
         }

         ct += vBench.size();
      }

      if (failure_count)
      {
         output(pRes, "DNQ List\n");
         for (auto it = results.begin(); it != results.end(); ++it)
         {
            const std::vector<Benchmark*>& vBench = it->second;

            for (std::size_t k = 0; k < vBench.size(); ++k)
            {
               Benchmark* pBench = vBench[k];

               if (!pBench->ExpressionFailed(current_expr))
                  continue;

               pBench->AddPoints(0);
               pBench->AddScore(0);

               if (pBench->DidNotEvaluate())
               {
                 output(pRes, "    %-20s (%s)\n",
                        pBench->GetShortName().c_str(),
                        pBench->GetFailReason().c_str());
               }
               else
               {
                 output(pRes, "    %-20s (%9.3f ns, %26.18f, %26.18f)\n",
                        pBench->GetShortName().c_str(),
                        it->first,
                        (pBench->GetRes() == pBench->GetRes()) ? pBench->GetRes() : 0.0,
                        (pBench->GetSum() == pBench->GetSum()) ? pBench->GetSum() : 0.0);
               }
            }
         }
      }

      if (failure_count > 2)
      {
         output(pRes, "**** ERROR ****   Excessive number of evaluation failures!  [%d]\n\n",
                failure_count);
      }

      results.clear();
   }

   output(pRes, "\n\nBenchmark settings:\n");
   output(pRes, "  - Expressions File is \"%s\"\n"   , sCaption.c_str());
   output(pRes, "  - Reference parser is %s\n"       , pRefBench->GetShortName().c_str());
   output(pRes, "  - Iterations per expression: %d\n", iCount);
   output(pRes, "  - Number of expressions: %d\n"    , vExpr.size());

   #if defined(_DEBUG)
   output(pRes, "  - Debug build\n");
   #else
   output(pRes, "  - Release build\n");
   #endif

   #if defined (__GNUC__)
   output(pRes, "  - Compiled with GCC Version %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
   #elif defined(_MSC_VER)
   output(pRes, "  - Compiled with MSVC Version %d\n", _MSC_VER);
   #endif

   output(pRes, "  - IEEE 754 (IEC 559) is %s\n", (std::numeric_limits<double>::is_iec559) ? "Available" : " NOT AVAILABLE");
   output(pRes, "  - %d-bit build\n", sizeof(void*)*8);

   dump_cpuid(pRes);

   output(pRes, "\n\nScores:\n");

   // Dump scores

   std::deque<std::pair<int,Benchmark*> > order_list;
   for (std::size_t i = 0; i < vBenchmarks.size(); ++i)
   {
      order_list.push_back(std::make_pair(vBenchmarks[i]->GetPoints(),vBenchmarks[i]));
   }

   std::sort(order_list.begin(),order_list.end());
   std::reverse(order_list.begin(),order_list.end());

   bool bHasFailures = false;
   for (std::size_t i = 0; i < order_list.size(); ++i)
   {
      Benchmark* pBench = order_list[i].second;
      bHasFailures |= (pBench->GetFails().size() > 0);

      output(pRes,  "  %02d  %-20s (%-10s): %5d %5.0lf %3d\n",
             i,
             pBench->GetShortName().c_str(),
             pBench->GetBaseType().c_str(),
             pBench->GetPoints(),
             (pBench->GetScore() / (double)vExpr.size()) * 100.0,
             pBench->GetFails().size());
   }

   // Dump failures
   if (bHasFailures)
   {
      output(pRes, "\n\nFailures:\n");
      for (std::size_t i = 0; i < vBenchmarks.size(); ++i)
      {
         Benchmark *pBench = vBenchmarks[i];
         const std::map<std::string, std::string> &allFailures = pBench->GetFails();
         if (!allFailures.empty())
         {
            output(pRes, "  %-15s (%3d):\n",
                   pBench->GetShortName().c_str(),
                   allFailures.size());

            for (auto it = allFailures.begin(); it != allFailures.end(); ++it)
            {
               output(pRes, "         \"%s\" - \"%s\"\n",
                      it->first.c_str(),
                      it->second.c_str());
            }
         }
      }
   }

   fclose(pRes);
}

void DoBenchmark(std::vector<Benchmark*> vBenchmarks, std::vector<std::string> vExpr, int iCount)
{
   for (std::size_t i = 0; i < vBenchmarks.size(); ++i)
   {
      vBenchmarks[i]->DoAll(vExpr, iCount);
   }
}

int main(int argc, const char *argv[])
{
#ifdef _MSC_VER
   SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
#endif

   int iCount = 10000000;

   //std::string benchmark_file = "bench_expr.txt";
//   std::string benchmark_file = "bench_expr_all.txt";
   std::string benchmark_file = "bench_expr_all.txt";
   //std::string benchmark_file = "bench_expr_weird.txt";
   //std::string benchmark_file = "bench_expr_extensive.txt";
   //std::string benchmark_file = "bench_expr_random_with_functions.txt";
   //std::string benchmark_file = "bench_precedence.txt";
   //std::string benchmark_file = "bench_expr_complete.txt";
   //std::string benchmark_file = "debug.txt";

   // Usage:
   // 1. ParserBench
   // 2. ParserBench <num iterations>
   // 3. ParserBench <num iterations> <benchmark expression file>

   if (argc >= 2)
   {
      iCount = atoi(argv[1]);
   }

   if (argc == 3)
   {
      benchmark_file = argv[2];
   }

   std::vector<std::string> vExpr = load_expressions(benchmark_file);

   if (vExpr.empty())
   {
      std::cout << "ERROR - Failed to load any expressions!\n";
      return 1;
   }

   std::vector<Benchmark*> vBenchmarks;

   // Important: The first parser in the list becomes the reference parser.
   //            Engines producing deviating results are disqualified so make
   //            sure the reference parser is computing properly.
   vBenchmarks.push_back(new BenchExprTk());            // <- Note: first parser becomes the reference!
   vBenchmarks.push_back(new BenchMuParser2(false));
   vBenchmarks.push_back(new BenchMuParser2(true));
#ifdef _MSC_VER
//   vBenchmarks.push_back(new BenchMTParser());      // <- Crash in debug mode
#endif

   vBenchmarks.push_back(new BenchMuParserX());
   vBenchmarks.push_back(new BenchATMSP());
//   vBenchmarks.push_back(new BenchLepton());
   vBenchmarks.push_back(new BenchMathExpr());
   //   vBenchmarks.push_back(new BenchFParser());

#ifdef _MSC_VER
   vBenchmarks.push_back(new BenchMuParserSSE());
#endif
   vBenchmarks.push_back(new BenchExprTkFloat());

   Shootout(benchmark_file, vBenchmarks, vExpr, iCount);
   //DoBenchmark(vBenchmarks, vExpr, iCount);

   for (std::size_t i = 0; i < vBenchmarks.size(); ++i)
   {
      delete vBenchmarks[i];
   }

   return 0;
}
