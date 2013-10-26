/*
 **************************************************************
 *         C++ Mathematical Expression Toolkit Library        *
 *                                                            *
 * Simple Example 10                                          *
 * Author: Arash Partow (1999-2013)                           *
 * URL: http://www.partow.net/programming/exprtk/index.html   *
 *                                                            *
 * Copyright notice:                                          *
 * Free use of the Mathematical Expression Toolkit Library is *
 * permitted under the guidelines and in accordance with the  *
 * most current version of the Common Public License.         *
 * http://www.opensource.org/licenses/cpl1.0.php              *
 *                                                            *
 **************************************************************
*/


#include <cmath>
#include <cstdio>
#include <string>
#include "exprtk.hpp"


template <typename T>
void newton_sqrt()
{
   typedef exprtk::symbol_table<T>      symbol_table_t;
   typedef exprtk::expression<T>          expression_t;
   typedef exprtk::parser<T>                  parser_t;
   typedef exprtk::function_compositor<T> compositor_t;

   T x = T(0);

   exprtk::symbol_table<T> symbol_table;

   symbol_table.add_constants();
   symbol_table.add_variable("x",x);

   compositor_t compositor(symbol_table);

   compositor
      .add("newton_sqrt_impl",
           "switch                                "
           "{                                     "
           "  case x < 0  : -inf;                 "
           "  case x == 0 : 0;                    "
           "  case x == 1 : 1;                    "
           "  default:                            "
           "  ~{                                  "
           "     z := 100;                        "
           "     y := x / 2;                      "
           "     repeat                           "
           "       if (equal(y * y,x), z := 0, 0);"
           "       y := (1 / 2) * (y + (x / y));  "
           "     until ((z := (z - 1)) <= 0)      "
           "   };                                 "
           "}                                     ",
           "x","y","z");

   compositor
      .add("newton_sqrt",
           "newton_sqrt_impl(x,0,0)","x");

   std::string expression_str = "newton_sqrt(x)";

   expression_t expression;

   expression.register_symbol_table(symbol_table);

   exprtk::parser<T> parser;

   parser.compile(expression_str,expression);

   for (std::size_t i = 0; i < 100; ++i)
   {
      x = i;
      T result = expression.value();
      printf("sqrt(%03d) - Result: %12.10f\tReal: %12.10f\n",
             static_cast<unsigned int>(i),
             result,
             std::sqrt(x));
   }
}

int main()
{
   newton_sqrt<double>();
   return 0;
}
