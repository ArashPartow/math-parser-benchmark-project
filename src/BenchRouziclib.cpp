#include "BenchRouziclib.h"

#include <cmath>
#include <cstring>

#include "rouziclib/rl.h"

//-------------------------------------------------------------------------------------------------
BenchRouziclib::BenchRouziclib()
: Benchmark()
{
   m_sName = "rouziclib";
}

//-------------------------------------------------------------------------------------------------

double BenchRouziclib::DoBenchmark(const std::string& sExpr, long iCount)
{
   double a = 1.1;
   double b = 2.2;
   double c = 3.3;
   double x = 2.123456;
   double y = 3.123456;
   double z = 4.123456;
   double w = 5.123456;

   rlip_inputs_t inputs[] = { RLIP_FUNC,
                 {"a", &a, "pd"},
                 {"b", &b, "pd"},
                 {"c", &c, "pd"},
                 {"x", &x, "pd"},
                 {"y", &y, "pd"},
                 {"z", &z, "pd"},
                 {"w", &w, "pd"}
               };

   // Perform basic tests for the variables used
   // in the expressions
   {
      bool test_result = true;

      auto tests_list = test_expressions();

      for (auto test : tests_list)
      {
	 rlip_t prog = rlip_expression_compile(test.first.c_str(), inputs, sizeof(inputs)/sizeof(*inputs), 0, NULL);
	 volatile int exec_on = 1;
	 prog.exec_on = &exec_on;

	 // Execution
	 rlip_execute_opcode(&prog);

	 // If compilation failed
	 if (prog.valid_prog == 0 || !is_equal(test.second, prog.return_value[0]))
	 {
		 free_rlip(&prog);
		 test_result = false;
		 break;
	 }

	 free_rlip(&prog);
      }

      if (!test_result)
      {
         StopTimerAndReport("Failed variable test");
         return m_fTime1;
      }
   }

   // Compile expression with log
   buffer_t comp_log={0};
   rlip_t prog = rlip_expression_compile(sExpr.c_str(), inputs, sizeof(inputs)/sizeof(*inputs), 0, &comp_log);
   volatile int exec_on = 1;
   prog.exec_on = &exec_on;

   if (prog.valid_prog == 0)
   {
      StopTimerAndReport(comp_log.buf ? (char *) comp_log.buf : "Compilation log is empty");
      return m_fTime1;
   }

   free_buf(&comp_log);

   // Prime the I and D caches for the expression
   {
      double d0 = 0.0;
      double d1 = 0.0;

      for (std::size_t i = 0; i < priming_rounds; ++i)
      {
	 rlip_execute_opcode(&prog);
         if (i & 1)
            d0 += prog.return_value[0];
         else
            d1 += prog.return_value[0];
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
   double fRes = 0;
   double fSum = 0;

   rlip_execute_opcode(&prog);
   fRes = prog.return_value[0];

   StartTimer();

   for (int j = 0; j < iCount; ++j)
   {
      rlip_execute_opcode(&prog);
      fSum += prog.return_value[0];
      std::swap(a,b);
      std::swap(x,y);
   }

   StopTimer(fRes, fSum, iCount);

   free_rlip(&prog);

   return m_fTime1;
}
