#include "BenchLepton.h"

#include <string>
#include <map>

#include <cmath>

#define LEPTON_BUILDING_STATIC_LIBRARY
#include "lepton/Lepton.h"

using namespace std;


//-------------------------------------------------------------------------------------------------
BenchLepton::BenchLepton()
: Benchmark()
{
  m_sName = "Lepton";
}

//-------------------------------------------------------------------------------------------------
double BenchLepton::DoBenchmark(const std::string& sExpr, long iCount)
{
   std::map<std::string,double> var_list;
   var_list["a" ] = 1.1;
   var_list["b" ] = 2.2;
   var_list["c" ] = 3.3;
   var_list["x" ] = 2.123456;
   var_list["y" ] = 3.123456;
   var_list["z" ] = 4.123456;
   var_list["w" ] = 5.123456;

   var_list["e" ] = 2.718281828459045235360;
   var_list["pi"] = 3.141592653589793238462;

   double& a = var_list["a"];
   double& b = var_list["b"];
   double& c = var_list["c"];

   double& x = var_list["x"];
   double& y = var_list["y"];
   double& z = var_list["z"];
   double& w = var_list["w"];

   try
   {
      Lepton::ExpressionProgram program = Lepton::Parser::parse(sExpr).optimize().createProgram();
      program.evaluate(var_list);
   }
   catch (std::exception& e)
   {
      StopTimerAndReport(e.what());
      return std::numeric_limits<double>::quiet_NaN();
   }

   Lepton::ExpressionProgram program = Lepton::Parser::parse(sExpr).optimize().createProgram();

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      try
      {
         for (auto test : tests_list)
         {
            Lepton::ExpressionProgram test_program = Lepton::Parser::parse(test.first).optimize().createProgram();

            if (!is_equal(test.second,test_program.evaluate(var_list)))
            {
               StopTimerAndReport("Failed variable test");
               return m_fTime1;
            }
         }
      }
      catch (std::exception& e)
      {
         StopTimerAndReport(e.what());
         return std::numeric_limits<double>::quiet_NaN();
      }
   }

   //Prime the I and D caches for the expression
   {
      double d0 = 0.0;
      double d1 = 0.0;

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
         if (i & 1)
            d0 += program.evaluate(var_list);
         else
            d1 += program.evaluate(var_list);
      }

      if (
            (d0 == std::numeric_limits<double>::infinity()) &&
            (d1 == std::numeric_limits<double>::infinity())
         )
      {
         printf("\n");
      }
   }

   // Perform benchmark then return results
   double fRes  = 0;
   double fSum  = 0;

   fRes = program.evaluate(var_list);

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      fSum += program.evaluate(var_list);
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes, fSum, iCount);

   return m_fTime1;
}
