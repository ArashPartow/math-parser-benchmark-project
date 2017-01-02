#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <algorithm>
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

   const std::size_t priming_rounds = 1000;

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
   void   IgnoreLastRate();

   void   copy(Benchmark* n);

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

inline std::vector<std::pair<std::string,double> > test_expressions()
{
   static const std::vector<std::pair<std::string,double> > test_expressions_
                {
                   std::make_pair("a + 0.0" ,     1.1),
                   std::make_pair("b + 0.0" ,     2.2),
                   std::make_pair("c + 0.0" ,     3.3),
                   std::make_pair("x + 0.0" ,2.123456),
                   std::make_pair("y + 0.0" ,3.123456),
                   std::make_pair("z + 0.0" ,4.123456),
                   std::make_pair("w + 0.0" ,5.123456)
                };

   return test_expressions_;
}

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

#endif
