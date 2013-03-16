#include "BenchLepton.h"

#include <string>
#include <map>

#include <windows.h>
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
double BenchLepton::DoBenchmark(const std::string &sExpr, long iCount)
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
   }
   catch (std::exception& e)
   {
      return std::numeric_limits<double>::max();
   }

   Lepton::ExpressionProgram program = Lepton::Parser::parse(sExpr).optimize().createProgram();

   // Calculate/bench and show result finally
   double fTime = 0;
   double fRes  = 0;
   double fSum  = 0;

   fRes = program.evaluate(var_list);
   StartTimer();
   for (int j = 0; j < iCount; j++)
   {
      std::swap(a,b);
      std::swap(x,y);
      fSum += program.evaluate(var_list);
   }

   StopTimer(fRes, fSum, iCount);
   return m_fTime1;
}
