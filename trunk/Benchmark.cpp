#include "Benchmark.h"

#include <cassert>
#include <cstdio>
#include <ctime>
#include <Windows.h>

using namespace std;


//-------------------------------------------------------------------------------------------------
Benchmark::Benchmark()
  :m_sName()
  ,m_fTime1(0)
  ,m_fResult(0)
  ,m_fSum(0)
  ,m_nTotalBytecodeSize(0)
  ,m_nPoints(0)
  ,m_vFails()
{}

//-------------------------------------------------------------------------------------------------
void Benchmark::AddPoints(int pt)
{
  m_nPoints+=pt;
}

//-------------------------------------------------------------------------------------------------
int Benchmark::GetPoints() const
{
  return m_nPoints;
}

//-------------------------------------------------------------------------------------------------
void Benchmark::PreprocessExpr(std::vector<std::string> &vExpr)
{}

//-------------------------------------------------------------------------------------------------
void Benchmark::DoAll(std::vector<string> vExpr, long num)
{
  printf("\n\n\n");

  PreprocessExpr(vExpr);

  char outstr[400], file[400];
  time_t t = time(NULL);

#ifdef _DEBUG
  sprintf(outstr, "Bench_%s_%%Y%%m%%d_%%H%%M%%S_dbg.txt", GetShortName().c_str());
#else
  sprintf(outstr, "Bench_%s_%%Y%%m%%d_%%H%%M%%S_rel.txt", GetShortName().c_str());
#endif

  strftime(file, sizeof(file), outstr, localtime(&t));

  FILE *pRes = fopen(file, "w");
  assert(pRes);

  fprintf(pRes,  "# Benchmark results\n");
  fprintf(pRes,  "#   Parser:  %s\n", GetName().c_str());
  fprintf(pRes,  "#   Evals per expr:  %d\n", num);
  fprintf(pRes,  "#\"ms per eval [ms]\", \"evals per sec\", \"Result\", \"expr_len\", \"Expression\"\n", GetName());

  std::string sExpr;

  Stopwatch timer;
  timer.Start();
  for (std::size_t i=0; i<vExpr.size(); ++i)
  {
    try
    {
      DoBenchmark(vExpr[i], num);
      fprintf(pRes, "%4.6lf, %4.6lf, %4.6lf, %d, %s, %s\n", m_fTime1, 1000.0/m_fTime1, m_fResult, vExpr[i].length(), vExpr[i].c_str(), m_sInfo.c_str());
      printf(       "%4.6lf, %4.6lf, %4.6lf, %d, %s, %s\n", m_fTime1, 1000.0/m_fTime1, m_fResult, vExpr[i].length(), vExpr[i].c_str(), m_sInfo.c_str());
    }
    catch(...)
    {
      fprintf(pRes, "fail: %s\n", vExpr[i].c_str());
      printf(       "fail: %s\n", vExpr[i].c_str());
    }

    fflush(pRes);
  }
  double dt = timer.Stop() / ((double)vExpr.size()*num);
  double fnum_per_sec = 1000.0/dt;

  fprintf(pRes,  "# avg. time per expr.: %lf ms;  avg. eval per sec: %lf; total bytecode size: %d", dt, 1000.0/dt, m_nTotalBytecodeSize);
  printf("\n#\n# avg. time per expr.: %lf ms;  avg. eval per sec: %lf; total bytecode size: %d", dt, 1000.0/dt, m_nTotalBytecodeSize);
  fclose(pRes);
}

//-------------------------------------------------------------------------------------------------
std::string Benchmark::GetName() const
{
  return m_sName;
}

//-------------------------------------------------------------------------------------------------
std::string Benchmark::GetShortName() const
{
  return m_sName;
}

//-------------------------------------------------------------------------------------------------
void Benchmark::Reset()
{
  m_fTime1 = 0;
  m_fResult = 0;
  m_vFails.clear();
}

//-------------------------------------------------------------------------------------------------
void Benchmark::StartTimer()
{
  m_timer.Start();
}

//-------------------------------------------------------------------------------------------------
void Benchmark::StopTimer(double fRes, double fSum, int iCount)
{
  m_fTime1 = m_timer.Stop() / (double)iCount;
  m_fResult = fRes;
  m_fSum = fSum;
}

//-------------------------------------------------------------------------------------------------
double Benchmark::GetSum() const
{
  return m_fSum;
}

//-------------------------------------------------------------------------------------------------
double Benchmark::GetRes() const
{
  return m_fResult;
}

//-------------------------------------------------------------------------------------------------
const std::vector<std::string> Benchmark::GetFails() const
{
  return m_vFails;
}

//-------------------------------------------------------------------------------------------------
void Benchmark::AddFail(const std::string &sExpr)
{
  m_vFails.push_back(sExpr);
}
