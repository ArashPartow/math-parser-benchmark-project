#include "BenchNative.h"

#include <cmath>


namespace
{
   /*
      Note: In order to add new expressions they must be added
      in similar priority to both the native_expression_list
      struct and define_expr section, and a new case statement
      needs to be made in the switch found in BenchNative::DoBenchmark
   */

   const std::string native_expression_list[] =
                      {
                        "a+b/c",
                        "a*b+c",
                        "a/b-c",
                        "(2*a+1)*3",
                        "a^2+1",
                        "a/((a+b)*(a-b))/b",
                        "1.1*a^2+2.2*b^3+3.3*c^4",
                        "1/(a*sqrt(2*pi))*exp(-0.5*((b-a)/a)^2)",
                        "(((((((7*a+6)*a+5)*a+4)*a+3)*a+2)*a+1)*a+0.1)",
                        "7*a^7+6*a^6+5*a^5+4*a^4+3*a^3+2*a^2+1*a^1+0.1",
                        "sqrt(a^2+b^2)",
                        "a+(cos(b-sin(2/a*pi))-sin(a-cos(2*b/pi)))-b",
                        "abs(sin(sqrt(a^2+b^2))*255)",
                        "(0.1*a+1)*a+1.1-sin(a)-log(a)/a*3/4",
                        "sin(2*a)+cos(pi/b)",
                        "1-sin(2*a)+cos(pi/b)",
                        "sqrt(1-sin(2*a)+cos(pi/b)/3)",
                        "(a/((((b+(((e*(((((pi*((((3.45*((pi+a)+pi))+b)+b)*a))+0.68)+e)+a)/a))+a)+b))+b)*a)-pi))",
                        "((((((((((((4.4*a+3.3)*a+2.2)*a+1.1)*a+9.9)*a+8.8)*a+7.7)*a+6.6)*a+5.5)*a+4.4)*a+3.3)*a+2.2)*a+1.1)",
                        "(1.1+(b+1)*(b+2))*(2.2+(b+3)*(b+4))*(3.3+(b+5)*(b+6))*(4.4+(b+7)*(b+8))*(5.5+(b+9)*(b+10))*(6.6+(b+11)*(b+12))",
                        "cos(((((a+(((a-((sin(e)+3.14)+a))*b)-pi))/b)-b)/e))",
                        "(c+sin(a+cos(b+(c+(5.5+(6.6+tan((b+3.96))-b)+pi)/a)+2.2)+3.3)+4.4/e)"
                        //Add new expression here...
                      };

   static std::map<std::string,unsigned int> function_map;

   enum var_idx
   {
      a = 0,
      b = 1,
      c = 2,
      x = 3,
      y = 4,
      z = 5,
      w = 6
   };

   static const double e  = 2.71828182845904523536028747135266249775724709369996;
   static const double pi = 3.14159265358979323846264338327950288419716939937510;

   #define define_expr(NN,EXPR)                                      \
   struct expr##NN##_impl : public Benchmark                         \
   {                                                                 \
      std::vector<double> v;                                         \
      expr##NN##_impl() : Benchmark() { m_sName = "Native"; }        \
      inline double f()                                              \
      {                                                              \
         return (EXPR);                                              \
      }                                                              \
      double DoBenchmark(const std::string&, long iCount)            \
      {                                                              \
         v.push_back(1.1);                                           \
         v.push_back(2.2);                                           \
         v.push_back(3.3);                                           \
         v.push_back(2.123456);                                      \
         v.push_back(3.123456);                                      \
         v.push_back(4.123456);                                      \
         v.push_back(5.123456);                                      \
                                                                     \
         {                                                           \
            double d0 = 0.0;                                         \
            double d1 = 0.0;                                         \
                                                                     \
            for (std::size_t i = 0; i < priming_rounds; ++i)         \
            {                                                        \
               if (i & 1)                                            \
                  d0 += f();                                         \
               else                                                  \
                  d1 += f();                                         \
            }                                                        \
                                                                     \
            if (                                                     \
                  (d0 == std::numeric_limits<double>::infinity()) && \
                  (d1 == std::numeric_limits<double>::infinity())    \
               )                                                     \
            {                                                        \
               printf("\n");                                         \
            }                                                        \
         }                                                           \
                                                                     \
         double fRes = 0;                                            \
         double fSum = 0;                                            \
                                                                     \
         fRes = f();                                                 \
                                                                     \
         StartTimer();                                               \
                                                                     \
         for (int j = 0; j < iCount; ++j)                            \
         {                                                           \
            fSum += f();                                             \
            std::swap(v[0], v[1]);                                   \
            std::swap(v[3], v[4]);                                   \
         }                                                           \
                                                                     \
         StopTimer(fRes, fSum, iCount);                              \
         return m_fTime1;                                            \
      }                                                              \
   };                                                                \

   define_expr(00,v[a]+v[b]/v[c])
   define_expr(01,v[a]*v[b]+v[c])
   define_expr(02,v[a]/v[b]-v[c])
   define_expr(03,(2*v[a]+1)*3)
   define_expr(04,v[a]*v[a]+1)
   define_expr(05,v[a]/((v[a]+v[b])*(v[a]-v[b]))/v[b])
   define_expr(06,1.1*v[a]*v[a]+2.2*v[b]*v[b]*v[b]+3.3*v[c]*v[c]*v[c]*v[c])
   define_expr(07,1.0/(v[a]*std::sqrt(2*pi))*std::exp(-0.5*(((v[b]-v[a])/v[a])*((v[b]-v[a])/v[a]))))
   define_expr(08,(((((((7*v[a]+6)*v[a]+5)*v[a]+4)*v[a]+3)*v[a]+2)*v[a]+1)*v[a]+0.1))
   define_expr(09,7*v[a]*v[a]*v[a]*v[a]*v[a]*v[a]*v[a]+6*v[a]*v[a]*v[a]*v[a]*v[a]*v[a]+5*v[a]*v[a]*v[a]*v[a]*v[a]+4*v[a]*v[a]*v[a]*v[a]+3*v[a]*v[a]*v[a]+2*v[a]*v[a]+1*v[a]+0.1)
   define_expr(10,std::sqrt(v[a]*v[a]+v[b]*v[b]))
   define_expr(11,v[a]+(std::cos(v[b]-std::sin(2/v[a]*pi))-std::sin(v[a]-std::cos(2*v[b]/pi)))-v[b])
   define_expr(12,abs(std::sin(std::sqrt(v[a]*v[a]+v[b]*v[b]))*255.0))
   define_expr(13,(0.1*v[a]+1)*v[a]+1.1-std::sin(v[a])-log(v[a])/v[a]*3.0/4.0)
   define_expr(14,std::sin(2*v[a])+std::cos(pi/v[b]))
   define_expr(15,1-std::sin(2*v[a])+std::cos(pi/v[b]))
   define_expr(16,std::sqrt(1-std::sin(2*v[a])+std::cos(pi/v[b])/3.0))
   define_expr(17,(v[a]/((((v[b]+(((e*(((((pi*((((3.45*((pi+v[a])+pi))+v[b])+v[b])*v[a]))+0.68)+e)+v[a])/v[a]))+v[a])+v[b]))+v[b])*v[a])-pi)))
   define_expr(18,((((((((((((4.4*v[a]+3.3)*v[a]+2.2)*v[a]+1.1)*v[a]+9.9)*v[a]+8.8)*v[a]+7.7)*v[a]+6.6)*v[a]+5.5)*v[a]+4.4)*v[a]+3.3)*v[a]+2.2)*v[a]+1.1))
   define_expr(19,(1.1+(v[b]+1)*(v[b]+2))*(2.2+(v[b]+3)*(v[b]+4))*(3.3+(v[b]+5)*(v[b]+6))*(4.4+(v[b]+7)*(v[b]+8))*(5.5+(v[b]+9)*(v[b]+10))*(6.6+(v[b]+11)*(v[b]+12)))
   define_expr(20,std::cos(((((v[a]+(((v[a]-((std::sin(e)+3.14)+v[a]))*v[b])-pi))/v[b])-v[b])/e)))
   define_expr(21,(v[c]+std::sin(v[a]+std::cos(v[b]+(v[c]+(5.5+(6.6+std::tan((v[b]+3.96))-b)+pi)/v[a])+2.2)+3.3)+4.4/e))
   //Add new expression definition here...
   #undef define_expr
}

//-------------------------------------------------------------------------------------------------
BenchNative::BenchNative()
: Benchmark()
{
   m_sName = "Native";

   for (std::size_t i = 0; i < sizeof(native_expression_list) / sizeof(std::string); ++i)
   {
      function_map[native_expression_list[i] + " "] = i;
   }
}

//-------------------------------------------------------------------------------------------------
double BenchNative::DoBenchmark(const std::string& sExpr, long iCount)
{
   if (function_map.end() == function_map.find(sExpr))
   {
      StopTimerAndReport("Invalid expression: " + sExpr);
      return std::numeric_limits<double>::quiet_NaN();
   }

   Benchmark* b = reinterpret_cast<Benchmark*>(0);

   double fRes = 0;
   double fSum = 0;

   switch(function_map.find(sExpr)->second)
   {
      #define case_stmt(N,NN)                    \
      case N : b = new expr##NN##_impl(); break; \

      case_stmt( 0,00)
      case_stmt( 1,01)
      case_stmt( 2,02)
      case_stmt( 3,03)
      case_stmt( 4,04)
      case_stmt( 5,05)
      case_stmt( 6,06)
      case_stmt( 7,07)
      case_stmt( 8,08)
      case_stmt( 9,09)
      case_stmt(10,10)
      case_stmt(11,11)
      case_stmt(12,12)
      case_stmt(13,13)
      case_stmt(14,14)
      case_stmt(15,15)
      case_stmt(16,16)
      case_stmt(17,17)
      case_stmt(18,18)
      case_stmt(19,19)
      case_stmt(20,20)
      case_stmt(21,21)
      //Add new case statement here...
      #undef case_stmt
      default: {
                  StopTimerAndReport("Invalid expression: " + sExpr);
                  return std::numeric_limits<double>::quiet_NaN();
               }
   }

   b->DoBenchmark(sExpr,iCount);

   copy(b);

   delete b;

   return m_fTime1;
}

std::vector<std::string> BenchNative::load_native_expressions()
{
   std::vector<std::string> result;

   result.assign(native_expression_list,
                 native_expression_list + (sizeof(native_expression_list) / sizeof(std::string)));

   return result;
}
