#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <vector>
#include <string>
#include "Stopwatch.h"


//-------------------------------------------------------------------------------------------------
class Benchmark
{
public:

   typedef std::vector<std::string> expr_vec;

   Benchmark();
   void DoAll(std::vector<std::string> vExpr, long num);

   virtual double DoBenchmark(const std::string &sExpr, long iCount) = 0;
   virtual void PreprocessExpr(std::vector<std::string> &vExpr);
   virtual void PreprocessExpr(std::string &vExpr) {};
   virtual std::string GetShortName() const;
   std::string GetName() const;
   void Reset();

   void StartTimer();
   void StopTimer(double fRes, double fSum, int iCount);

   void AddPoints(int pt);
   int GetPoints() const;

   void AddScore(double sc);
   double GetScore() const;

   double GetTime() const;
   double GetRes() const;
   double GetSum() const;

   const std::vector<std::string> GetFails() const;
   void AddFail(const std::string &sExpr);

protected:

   std::string m_sName;
   std::string m_sInfo;
   int m_nTotalBytecodeSize;
   int m_nPoints;
   int m_nFail;
   long m_nNum;
   double m_fScore;
   double m_fTime1;
   double m_fResult;
   double m_fSum;
   Stopwatch m_timer;

   std::vector<std::string> m_vFails;
};

#endif