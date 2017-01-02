#include "BenchMathExpr.h"

#include <cmath>

#include "MathExpr/mathexpr.h"

using namespace std;


//-------------------------------------------------------------------------------------------------
BenchMathExpr::BenchMathExpr()
: Benchmark()
{
   m_sName = "MathExpr";
}

//-------------------------------------------------------------------------------------------------
double BenchMathExpr::DoBenchmark(const std::string& sExpr, long iCount)
{
   double a = 1.1;
   double b = 2.2;
   double c = 3.3;
   double x = 2.123456;
   double y = 3.123456;
   double z = 4.123456;
   double w = 5.123456;

   double e  = 2.718281828459045235360;
   double pi = 3.141592653589793238462;

   RVar var_a ( "a"  , &a );
   RVar var_b ( "b"  , &b );
   RVar var_c ( "c"  , &c );
   RVar var_x ( "x"  , &x );
   RVar var_y ( "y"  , &y );
   RVar var_z ( "z"  , &z );
   RVar var_w ( "w"  , &w );
   RVar var_e ( "e"  , &e );
   RVar var_pi( "pi" , &pi);

   RVar* var_array[9];

   var_array[0] = &var_a;
   var_array[1] = &var_b;
   var_array[2] = &var_c;
   var_array[3] = &var_x;
   var_array[4] = &var_y;
   var_array[5] = &var_z;
   var_array[6] = &var_w;

   var_array[7] = &var_e;
   var_array[8] = &var_pi;

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
         ROperation test_op (const_cast<char*>(test.first.c_str()), 9, var_array);

         if (
              test_op.HasError(&test_op) ||
              (!is_equal(test.second,test_op.Val()))
            )
         {
            test_result = false;
            break;
         }
      }

      if (!test_result)
      {
         StopTimerAndReport("Failed variable test");
         return m_fTime1;
      }
   }

   ROperation op (const_cast<char*>(sExpr.c_str()), 9, var_array);

   if (op.HasError(&op))
   {
      // I did not find functions for reporting an error, taking generic message instead
      StopTimerAndReport("parsing error");
      return m_fTime1;
   }

   // Perform benchmark then return results
   double fRes  = 0;
   double fSum  = 0;

   //Prime the I and D caches for the expression
   {
      double d0 = 0.0;
      double d1 = 0.0;

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
         if (i & 1)
            d0 += op.Val();
         else
            d1 += op.Val();
      }

      if (
            (d0 == std::numeric_limits<double>::infinity()) &&
            (d1 == std::numeric_limits<double>::infinity())
         )
      {
         printf("\n");
      }
   }

   fRes = op.Val();

   StartTimer();

   for (int j = 0; j < iCount; j++)
   {
      fSum += op.Val();
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes, fSum, iCount);

   return m_fTime1;
}
