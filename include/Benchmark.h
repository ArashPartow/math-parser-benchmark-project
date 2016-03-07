#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <map>
#include <vector>
#include <string>
#include "Stopwatch.h"


//-------------------------------------------------------------------------------------------------
class Benchmark
{
public:

   enum EBaseType
   {
     FLOAT,
     DOUBLE,
     LONG_DOUBLE,
     MPFR
   };

   typedef std::vector<std::string> expr_vec;

   Benchmark(EBaseType eBaseType = DOUBLE);
   virtual ~Benchmark();

   void DoAll(std::vector<std::string> vExpr, long num);

   virtual double DoBenchmark(const std::string& sExpr, long iCount) = 0;
   virtual void PreprocessExpr(std::vector<std::string>& vExpr);
   virtual void PreprocessExpr(std::string& /*vExpr*/) {};
   virtual std::string GetShortName() const;
   std::string GetName() const;
   std::string GetBaseType() const;
   void Reset();

   void StartTimer();
   void StopTimer(double fRes, double fSum, int iCount);
   void StopTimerAndReport(const std::string& msg);

   const std::string& GetFailReason() const;
   bool DidNotEvaluate() const;

   void AddPoints(int pt);
   int GetPoints() const;

   void AddScore(double sc);
   double GetScore() const;

   double GetTime() const;
   double GetRes() const;
   double GetSum() const;

   const std::map<std::string, std::string> GetFails() const;
   bool ExpressionFailed(const std::string& expr) const;
   void AddFail(const std::string& sExpr);

   double GetRate(const std::size_t& index) const;
   void IgnoreLastRate();

protected:

   std::string m_sName;
   std::string m_sInfo;
   int m_nTotalBytecodeSize;
   int m_nPoints;
   long m_nNum;
   double m_fScore;
   double m_fTime1;
   double m_fResult;
   double m_fSum;
   bool m_bFail;
   std::string m_sFailReason;
   Stopwatch m_timer;
   EBaseType m_eBaseType;
   std::map<std::string, std::string> m_allFails;
   std::vector<double> rate_list;
};

#endif
