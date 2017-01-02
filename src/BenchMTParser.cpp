#include "BenchMTParser.h"

#include <cmath>
// MTParser
#include "MTParser/MTParserLib/MTParser.h"
#include "MTParser/MTParserLib/MTParserExcepStrEng.h"

#include "BenchMTParser.h"

using namespace std;

class ExpFct : public MTFunctionI
{
   virtual const MTCHAR* getSymbol()
   {
      return _T("exp");
   }

   virtual const MTCHAR* getHelpString()
   {
      return _T("exp(x)");
   }

   virtual const MTCHAR* getDescription()
   {
      return _T("Calculate the value of e to the power of x, where e is the base of the natural logarithm");
   }

   virtual int getNbArgs()
   {
      return 1;
   }

   virtual MTDOUBLE evaluate(unsigned int nbArgs, const MTDOUBLE *pArg)
   {
      return exp(pArg[0]);
   }

   virtual MTFunctionI* spawn()
   {
      return new ExpFct();
   }
};

//-------------------------------------------------------------------------------------------------
BenchMTParser::BenchMTParser()
: Benchmark()
{
   m_sName = "MTParser";
}

//-------------------------------------------------------------------------------------------------
double BenchMTParser::DoBenchmark(const std::string& sExpr, long iCount)
{
   double a = 1.1;
   double b = 2.2;
   double c = 3.3;
   double x = 2.123456;
   double y = 3.123456;
   double z = 4.123456;
   double w = 5.123456;

   MTParser p;
   p.defineVar("a", &a);
   p.defineVar("b", &b);
   p.defineVar("c", &c);

   p.defineVar("x", &x);
   p.defineVar("y", &y);
   p.defineVar("z", &z);
   p.defineVar("w", &w);

   p.defineConst("e",   M_E);
   p.defineConst("pi", M_PI);

   p.defineFunc(new ExpFct());

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
         MTParser test_p;
         test_p.defineVar("a", &a);
         test_p.defineVar("b", &b);
         test_p.defineVar("c", &c);

         test_p.defineVar("x", &x);
         test_p.defineVar("y", &y);
         test_p.defineVar("z", &z);
         test_p.defineVar("w", &w);

         test_p.defineFunc(new ExpFct());

         try
         {
            test_p.compile(test.first.c_str());

            if (!is_equal(test.second,test_p.evaluate()))
            {
               test_result = false;
               break;
            }
         }
         catch(MTParserException&)
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

   double fTime = 0;
   double fRes  = 0;
   double fSum  = 0;

   try
   {
      p.compile(sExpr.c_str());
   }
   catch(MTParserException& e)
   {
      StopTimerAndReport(e.getDesc(0).c_str());
      return std::numeric_limits<double>::quiet_NaN();
   }

   //Prime the I and D caches for the expression
   {
      double d0 = 0.0;
      double d1 = 0.0;

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
         if (i & 1)
            d0 += p.evaluate();
         else
            d1 += p.evaluate();
      }

      if (
            (d0 == std::numeric_limits<double>::infinity()) &&
            (d1 == std::numeric_limits<double>::infinity())
         )
      {
         printf("\n");
      }
   }

   fRes = p.evaluate();

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      fSum += p.evaluate();
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes, fSum, iCount);

   return m_fTime1;
}
