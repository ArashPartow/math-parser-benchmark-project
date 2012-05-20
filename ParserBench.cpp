#include <cstdio>
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
    :Benchmark()
  {
    m_sName = "muparserSSE";
  }
  
  double DoBenchmark(const std::string &sExpr, long iCount)
  {
    mecFloat_t fRes(0), a(1), b(2), c(3), buf(0);
    double fSum(0);
  
    mecParserHandle_t hParser = mecCreate();

    mecSetExpr(hParser, sExpr.c_str());
    mecDefineVar(hParser, "a", &a);
    mecDefineVar(hParser, "b", &b);
    mecDefineVar(hParser, "c", &c);
    mecDefineConst(hParser, "pi", (mecFloat_t)M_PI);
    mecDefineConst(hParser, "e", (mecFloat_t)M_E);

    mecEvalFun_t ptfun = mecCompile(hParser);

    fRes = ptfun();

    StartTimer();
    for (int j=0; j<iCount; j++) 
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
    :Benchmark()
  {
    m_sName = "MTParser";
  }
  
  double DoBenchmark(const std::string &sExpr, long iCount)
  {
    double a(1), b(2), c(3);

    MTParser p;
    p.defineVar("a", &a);
    p.defineVar("b", &b);
    p.defineVar("c", &b);
    p.defineConst("e", M_E);
    p.defineConst("pi", M_PI);
    p.compile(sExpr.c_str());

    double fTime(0);
    double fRes(0), fSum(0);

    fRes = p.evaluate();	

    StartTimer();
    for (int j=0; j<iCount; j++) 
    {
      std::swap(a,b);
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
  FormelGenerator	fg;

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
  for (std::size_t i=0; i<vExpr.size(); ++i)
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
void Shootout(std::vector<Benchmark*> vBenchmarks, std::vector<string> vExpr, int iCount)
{
  printf("\nBenchmark (Shootout Mode)\n");

  char outstr[400], file[400];
  time_t t = time(NULL);

  sprintf(outstr, "Shootout_%%Y%%m%%d_%%H%%M%%S.txt");
  strftime(file, sizeof(file), outstr, localtime(&t));

  FILE *pRes = fopen(file, "w");
  assert(pRes);

  std::map<double, std::vector<Benchmark*>> results;
  for (std::size_t i=0; i<vExpr.size(); ++i)
  {
    fprintf(pRes, "\nExpression: \"%s\"\n", vExpr[i].c_str());
    printf("\nExpression: \"%s\"\n", vExpr[i].c_str());

    for (std::size_t j=0; j<vBenchmarks.size(); ++j)
    {
      Benchmark *pBench = vBenchmarks[j];
     
      std::string sExpr = vExpr[i];   // get the original expression anew for each parser
      pBench->PreprocessExpr(sExpr);  // some parsers use fancy characters to signal variables
      double time = 1000 * pBench->DoBenchmark(sExpr + " ", iCount);
      
      results[time].push_back(pBench);
    }

    int ct = 1;
    for (auto it = results.begin(); it!=results.end(); ++it)
    {
      const std::vector<Benchmark*> &vBench = it->second;

      for (std::size_t i=0; i<vBench.size(); ++i)
      {
        Benchmark *pBench = vBench[i];

        pBench->AddPoints(vBenchmarks.size() - ct + 1);

        if (i==0)
        {
          fprintf(pRes, "%d: %s (%4.5f 탎, %e, %e)\n", ct, pBench->GetShortName().c_str(), it->first, pBench->GetRes(), pBench->GetSum());
          printf("%d: %s (%4.5f 탎, %e, %e)\n", ct, pBench->GetShortName().c_str(), it->first, pBench->GetRes(), pBench->GetSum());
        }
        else
        {
          fprintf(pRes, "   %s (%4.5f 탎, %e, %e)\n", pBench->GetShortName().c_str(), it->first, pBench->GetRes(), pBench->GetSum());
          printf("   %s (%4.5f 탎, %e, %e)\n", pBench->GetShortName().c_str(), it->first, pBench->GetRes(), pBench->GetSum());
        }
      }
      ct += vBench.size();
    }

    results.clear();
  }


  fprintf(pRes, "\n\nScores:\n");
  printf("\n\nScores:\n");

  for (std::size_t i=0; i<vBenchmarks.size(); ++i)
  {
    Benchmark *pBench = vBenchmarks[i];
    fprintf(pRes, "   %s: %d\n", pBench->GetShortName().c_str(), pBench->GetPoints());
    printf("   %s: %d\n", pBench->GetShortName().c_str(), pBench->GetPoints());
  }

  fclose(pRes);
}

void DoBenchmark(std::vector<Benchmark*> vBenchmarks, std::vector<string> vExpr, int iCount)
{
  for (std::size_t i=0; i<vBenchmarks.size(); ++i)
    vBenchmarks[i]->DoAll(vExpr, iCount);
}

//-------------------------------------------------------------------------------------------------
int main(int argc, const char *argv[])
{
  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

//  std::vector<string> vExpr = LoadEqn("bench_slow.txt");
  std::vector<string> vExpr = LoadEqn("bench_expr_all.txt");
//std::vector<string> vExpr = LoadEqn("bench_expr_hparser.txt");

	int iCount   = 10000000; 

#ifdef _DEBUG
	iCount   = 1000000; 
#endif

  std::vector<Benchmark*> vBenchmarks;
  vBenchmarks.push_back(new BenchMTParser());
  vBenchmarks.push_back(new BenchFParser());
  vBenchmarks.push_back(new BenchMuParserX());
  vBenchmarks.push_back(new BenchMuParserNT(false));
  vBenchmarks.push_back(new BenchMuParser2());
//  vBenchmarks.push_back(new BenchMuParserSSE());
  vBenchmarks.push_back(new BenchATMSP());
  vBenchmarks.push_back(new BenchExprTk());

  Shootout(vBenchmarks, vExpr, iCount);
  DoBenchmark(vBenchmarks, vExpr, iCount);

  for (std::size_t i=0; i<vBenchmarks.size(); ++i)
    delete vBenchmarks[i];

  return 0;
}
