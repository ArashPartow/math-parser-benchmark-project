C++ Mathematical Expression Toolkit Library

[00 - INTRODUCTION]
The C++ Mathematical Expression  Toolkit Library (ExprTk) is  a simple
to  use,  easy  to  integrate  and  extremely  efficient  mathematical
expression parsing and evaluation engine. The parsing engine  supports
numerous forms  of functional  and logic  processing semantics  and is
easily extendible.



[01 - CAPABILITIES]
The ExprTk  evaluator  supports the following  fundamental  arithmetic
operations, functions and processes:

(0) Basic operators: +, -, *, /, %, ^

(1) Functions:       abs, avg, ceil, clamp, equal, erf, erfc, exp,
                     expm1, floor, frac, log, log10, log1p, log2,
                     logn, max, min, mul, nequal, root, round,
                     roundn, sgn, sqrt, sum, trunc

(2) Trigonometry:    acos, acosh, asin, asinh, atan, atanh, atan2,
                     cos, cosh, cot, csc, deg2grad, deg2rad, grad2deg,
                     hypot, rad2deg, sec, sin, sinh, tan, tanh

(3) Equalities &
    Inequalities:    =, ==, <>, !=, <, <=, >, >=

(4) Boolean logic:   and, mand, mor, nand, nor, not, or, shl, shr,
                     xnor, xor, true, false

(5) Conditional,
    Switch &
    Loop statements: if-then-else, switch-case, while, repeat-until

(6) Assignment:      :=

(7) String
    processing:      in, like, ilike

(8) Calculus:        numerical integration and differentiation



[02 - EXAMPLE EXPRESSIONS]
The  following  is  a  short listing  of  the types  of  mathematical
expressions that can be parsed and evaluated using the ExprTk library.

(01) sqrt(1 - (x^2))
(02) clamp(-1, sin(2 * pi * x) + cos(y / 2 * pi), +1)
(03) sin(2.34e-3 * x)
(04) if(((x + 2) == 3) and ((y + 5) <= 9),1 + w, 2 / z)
(05) inrange(-2,m,+2) == if(({-2 <= m} and [m <= +2]),1,0)
(06) ({1/1}*[1/2]+(1/3))-{1/4}^[1/5]+(1/6)-({1/7}+[1/8]*(1/9))
(07) a * exp(2.2 / 3.3 * t) + c
(08) z := x + sin(2.567 * pi / y)
(09) u := 2.123 * (pi * z) / (w := x + cos(y / pi))
(10) 2x + 3y + 4z + 5w == 2 * x + 3 * y + 4 * z + 5 * w
(11) 3(x + y) / 2.9 + 1.234e+12 == 3 * (x + y) / 2.9 + 1.234e+12
(12) (x + y)3.3 + 1 / 4.5 == (x + y) * 3.3 + 1 / 4.5
(13) (x + y)z + 1.1 / 2.7 == (x + y) * z + 1.1 / 2.7
(14) (sin(x / pi) cos(2y) + 1) == (sin(x / pi) * cos(2 * y) + 1)
(15) 75x^17 + 25.1x^5 - 35x^4 - 15.2x^3 + 40x^2 - 15.3x + 1
(16) if (avg(x,y) <= x + y, x - y, x * y) + 2.345 * pi / x
(17) fib_i := fib_i + (x := y + 0 * (fib_i := x + (y := fib_i)))
(18) while (x <= 100) { x := x + 1 }
(19) x <= 'abc123' and (y in 'AString') or ('1x2y3z' != z)
(20) (x like '*123*') or ('a123b' ilike y)



[03 - COPYRIGHT NOTICE]
Free  use  of  the  C++  Mathematical  Expression  Toolkit  Library is
permitted under the guidelines and in accordance with the most current
version of the Common Public License.

http://www.opensource.org/licenses/cpl1.0.php



[04 - DOWNLOADS & UPDATES]
The most  recent version  of the  C++ Mathematical  Expression Toolkit
Library including all updates and tests can be found at the  following
locations:

 (1) http://www.partow.net/programming/exprtk/index.html
 (2) svn checkout http://exprtk.googlecode.com/svn/ exprtk



[05 - INSTALLATION]
The header  file exprtk.hpp  should be  placed in  a project or system
include path (e.g: /usr/include/).



[06 - COMPILATION]
(1) For a complete build: make clean all
(2) For a PGO build: make clean pgo
(3) To strip executables: make strip_bin



[07 - COMPILER COMPATIBILITY]
(*) GNU Compiler Collection (4.1+)
(*) Intel C++ Compiler (9.x+)
(*) Clang/LLVM (1.1+)
(*) PGI C++ (10.x+)
(*) Microsoft Visual Studio C++ Compiler (8.1+)
(*) Comeau C++ Compiler (4.3+)
(*) IBM XL C/C++ (10.x+)



[08 - BUILT-IN OPERATIONS & FUNCTIONS]

(0) Arithmetic Operators
+----------+---------------------------------------------------------+
| OPERATOR | DEFINITION                                              |
+----------+---------------------------------------------------------+
|  +       | Addition between x and y. (eg: x + y)                   |
+----------+---------------------------------------------------------+
|  -       | Subtraction between x and y. (eg: x - y)                |
+----------+---------------------------------------------------------+
|  *       | Multiplication between x and y. (eg: x * y)             |
+----------+---------------------------------------------------------+
|  /       | Division between x and y (eg: x / y)                    |
+----------+---------------------------------------------------------+
|  %       | Modulus of x with respect to y. (eg: x % y)             |
+----------+---------------------------------------------------------+
|  ^       | x to the power of y. (eg: x ^ y)                        |
+----------+---------------------------------------------------------+
|  :=      | Assign the value of x to y. (eg: y := x)                |
|          | Where y is a variable type.                             |
+----------+---------------------------------------------------------+

(1) Equalities & Inequalities
+----------+---------------------------------------------------------+
| OPERATOR | DEFINITION                                              |
+----------+---------------------------------------------------------+
| == or =  | True only if x is strictly equal to y. (eg: x == y)     |
+----------+---------------------------------------------------------+
| <> or != | True only if x does not equal y. (eg: x <> y or x != y) |
+----------+---------------------------------------------------------+
|  <       | True only if x is less than y. (eg: x < y)              |
+----------+---------------------------------------------------------+
|  <=      | True only if x is less than or equal to y. (eg: x <= y) |
+----------+---------------------------------------------------------+
|  >       | True only if x is greater than y. (eg: x > y)           |
+----------+---------------------------------------------------------+
|  >=      | True only if x greater than or equal to y. (eg: x >= y) |
+----------+---------------------------------------------------------+

(2) Boolean Operations
+----------+---------------------------------------------------------+
| OPERATOR | DEFINITION                                              |
+----------+---------------------------------------------------------+
| true     | True state or any value other than zero (typically 1).  |
+----------+---------------------------------------------------------+
| false    | False state, value of zero.                             |
+----------+---------------------------------------------------------+
| and      | Logical AND, True only if x and y are both true.        |
|          | (eg: x and y)                                           |
+----------+---------------------------------------------------------+
| mand     | Multi-input logical AND, True only if all inputs are    |
|          | true. Left to right short-circuiting of expressions.    |
|          | (eg: mand(x > y,z < w,u or v,w and x))                  |
+----------+---------------------------------------------------------+
| mor      | Multi-input logical OR, True if at least one of the     |
|          | inputs are true. Left to right short-circuiting of      |
|          | expressions. (eg: mor(x > y,z < w,u or v,w and x))      |
+----------+---------------------------------------------------------+
| nand     | Logical NAND, True only if either x or y is false.      |
|          | (eg: x nand y)                                          |
+----------+---------------------------------------------------------+
| nor      | Logical NOR, True only if the result of x or y is false |
|          | (eg: x nor y)                                           |
+----------+---------------------------------------------------------+
| not      | Logical NOT, Negate the logical sense of the input.     |
|          | (eg: not(x and y) == x nand y)                          |
+----------+---------------------------------------------------------+
| or       | Logical OR, True if either x or y is true. (eg: x or y) |
+----------+---------------------------------------------------------+
| xor      | Logical XOR, True only if the logical states of x and y |
|          | differ. (eg: x xor y)                                   |
+----------+---------------------------------------------------------+
| xnor     | Logical XNOR, True iff the biconditional of x and y is  |
|          | satisfied. (eg: x xnor y)                               |
+----------+---------------------------------------------------------+
| &        | Similar to AND but with left to right expression short  |
|          | circuiting optimisation. (eg: (x & y) == (y and x))     |
+----------+---------------------------------------------------------+
| |        | Similar to OR but with left to right expression short   |
|          | circuiting optimisation. (eg: (x | y) == (y or x))      |
+----------+---------------------------------------------------------+

(3) General Purpose Functions
+----------+---------------------------------------------------------+
| FUNCTION | DEFINITION                                              |
+----------+---------------------------------------------------------+
| abs      | Absolute value of x.                                    |
+----------+---------------------------------------------------------+
| avg      | Average of all the inputs.                              |
|          | (eg: avg(x,y,z,w,u,v) == (x + y + z + w + u + v) / 6)   |
+----------+---------------------------------------------------------+
| ceil     | Smallest integer that is greater than or equal to x.    |
+----------+---------------------------------------------------------+
| clamp    | Clamp x in range between r0 and r1, where r0 < r1.      |
|          | (eg: clamp(r0,x,r1)                                     |
+----------+---------------------------------------------------------+
| equal    | Equality test between x and y using normalized epsilon  |
+----------+---------------------------------------------------------+
| erf      | Error function of x.                                    |
+----------+---------------------------------------------------------+
| erfc     | Complimentary error function of x.                      |
+----------+---------------------------------------------------------+
| exp      | e to the power of x.                                    |
+----------+---------------------------------------------------------+
| expm1    | e to the power of x minus 1, where x is very small.     |
|          | (eg: expm1(x))                                          |
+----------+---------------------------------------------------------+
| floor    | Largest integer that is less than or equal to x.        |
+----------+---------------------------------------------------------+
| frac     | Fractional portion of x.                                |
+----------+---------------------------------------------------------+
| hypot    | Hypotenuse of x and y (eg: hypot(x,y) = sqrt(x*x + y*y))|
+----------+---------------------------------------------------------+
| log      | Natural logarithm of x.                                 |
+----------+---------------------------------------------------------+
| log10    | Base 10 logarithm of x.                                 |
+----------+---------------------------------------------------------+
| log1p    | Natural logarithm of 1 + x, where x is very small.      |
|          | (eg: log1p(x))                                          |
+----------+---------------------------------------------------------+
| log2     | Base 2 logarithm of x.                                  |
+----------+---------------------------------------------------------+
| logn     | Base N logarithm of x (eg: logn(1235,8))                |
|          | where n > 0 and is an integer.                          |
+----------+---------------------------------------------------------+
| max      | Largest value of all the inputs. (eg: max(x,y,z,w,u,v)) |
+----------+---------------------------------------------------------+
| min      | Smallest value of all the inputs. (eg: min(x,y,z,w,u))  |
+----------+---------------------------------------------------------+
| mul      | Product of all the inputs.                              |
|          | (eg: mul(x,y,z,w,u,v,t) == (x * y * z * w * u * v * t)) |
+----------+---------------------------------------------------------+
| nequal   | Not-equal test between x and y using normalized epsilon |
+----------+---------------------------------------------------------+
| root     | Nth-Root of x (eg: root(x,3))                           |
|          | where n > 0 and is an integer.                          |
+----------+---------------------------------------------------------+
| round    | Round x to the nearest integer.                         |
+----------+---------------------------------------------------------+
| roundn   | Round x to n decimal places (eg: roundn(x,3))           |
|          | where n > 0 and is an integer.                          |
|          | (eg: roundn(1.2345678,4) == 1.2346)                     |
+----------+---------------------------------------------------------+
| sgn      | Sign of x, -1 where x < 0, +1 where x > 0, else zero.   |
+----------+---------------------------------------------------------+
| sqrt     | Square root of x, where x > 0                           |
+----------+---------------------------------------------------------+
| sum      | Sum of all the inputs.                                  |
|          | (eg: sum(x,y,z,w,u,v,t) == (x + y + z + w + u + v + t)) |
+----------+---------------------------------------------------------+
| trunc    | Integer portion of x.                                   |
+----------+---------------------------------------------------------+

(4) Trigonometry Functions
+----------+---------------------------------------------------------+
| FUNCTION | DEFINITION                                              |
+----------+---------------------------------------------------------+
| acos     | Arc cosine of x expressed in radians. Interval [-1,+1]  |
+----------+---------------------------------------------------------+
| acosh    | Inverse hyperbolic cosine of x expressed in radians.    |
+----------+---------------------------------------------------------+
| asin     | Arc sine of x expressed in radians. Interval [-1,+1]    |
+----------+---------------------------------------------------------+
| asinh    | Inverse hyperbolic sine of x expressed in radians.      |
+----------+---------------------------------------------------------+
| atan     | Arc tangent of x expressed in radians. Interval [-1,+1] |
+----------+---------------------------------------------------------+
| atan2    | Arc tangent of (x/y) expressed in radians. [-pi,+pi]    |
|          | eg: atan2(x,y)                                          |
+----------+---------------------------------------------------------+
| atanh    | Inverse hyperbolic tangent of x expressed in radians.   |
+----------+---------------------------------------------------------+
| cos      | Cosine of x.                                            |
+----------+---------------------------------------------------------+
| cosh     | Hyperbolic cosine of x.                                 |
+----------+---------------------------------------------------------+
| cot      | Cotangent of x.                                         |
+----------+---------------------------------------------------------+
| csc      | Cosecant of x.                                          |
+----------+---------------------------------------------------------+
| sec      | Secant of x.                                            |
+----------+---------------------------------------------------------+
| sin      | Sine of x.                                              |
+----------+---------------------------------------------------------+
| sinh     | Hyperbolic sine of x.                                   |
+----------+---------------------------------------------------------+
| tan      | Tangent of x.                                           |
+----------+---------------------------------------------------------+
| tanh     | Hyperbolic tangent of x.                                |
+----------+---------------------------------------------------------+
| deg2rad  | Convert x from degrees to radians.                      |
+----------+---------------------------------------------------------+
| deg2grad | Convert x from degrees to gradians.                     |
+----------+---------------------------------------------------------+
| rad2deg  | Convert x from radians to degrees.                      |
+----------+---------------------------------------------------------+
| grad2deg | Convert x from gradians to degrees.                     |
+----------+---------------------------------------------------------+

(5) String Processing
+----------+---------------------------------------------------------+
| FUNCTION | DEFINITION                                              |
+----------+---------------------------------------------------------+
| in       | True only if x is a substring of y.                     |
|          | (eg: x in y or 'abc' in 'abcdefgh')                     |
+----------+---------------------------------------------------------+
| like     | True only if the string x matches the pattern y.        |
|          | Available wildcard characters are '*' and '?' denoting  |
|          | zero or more and zero or one matches respectively.      |
|          | (eg: x like y or 'abcdefgh' like 'a?d*h')               |
+----------+---------------------------------------------------------+
| ilike    | True only if the string x matches the pattern y in a    |
|          | case insensitive manner. Available wildcard characters  |
|          | are '*' and '?' denoting zero or more and zero or one   |
|          | matches respectively.                                   |
|          | (eg: x ilike y or 'a1B2c3D4e5F6g7H' ilike 'a?d*h')      |
+----------+---------------------------------------------------------+
| [r0:r1]  | The closed interval [r0,r1] of the specified string.    |
|          | eg: Given a string x with a value of 'abcdefgh' then:   |
|          | 0. x[1:4] == 'bcde'                                     |
|          | 1. x[ :5] == x[:5] == 'abcdef'                          |
|          | 2. x[3: ] == x[3:] =='cdefgh'                           |
|          | 3. x[ : ] == x[:] == 'abcdefgh'                         |
|          | 4. x[4/2:3+2] == x[2:5] == 'cdef'                       |
|          |                                                         |
|          | Note: Both r0 and r1 are assumed to be integers, where  |
|          | r0 <= r1. They may also be the result of an expression, |
|          | in the event they have fractional components truncation |
|          | will be performed. (eg: 1.67 -> 1)                      |
+----------+---------------------------------------------------------+

(6) Control Structures
+----------+---------------------------------------------------------+
|STRUCTURE | DEFINITION                                              |
+----------+---------------------------------------------------------+
| if       | If x is true then return y else return z.               |
|          | (eg: if(x, y, z) or if((x + 1) > 2y, z + 1, w / v))     |
+----------+---------------------------------------------------------+
| switch   | The first true case condition that is encountered will  |
|          | determine the result of the switch. If none of the case |
|          | conditions hold true, the default action is assumed as  |
|          | the final return value. This is sometimes also known as |
|          | a multi-way branch mechanism.                           |
|          | eg:                                                     |
|          | switch                                                  |
|          | {                                                       |
|          |   case x > (y + z) : 2 * x / abs(y - z);                |
|          |   case x < 3       : sin(x + y);                        |
|          |   default          : 1 + x;                             |
|          | }                                                       |
+----------+---------------------------------------------------------+
| while    | The structure will repeatedly evaluate the internal     |
|          | statement(s) 'while' the condition is true. The final   |
|          | statement in the final iteration will be used as the    |
|          | return value of the loop.                               |
|          | eg:                                                     |
|          | while ((x := (x - 1)) > 0)                              |
|          | {                                                       |
|          |   y := x + z;                                           |
|          |   w := z + y;                                           |
|          | }                                                       |
+----------+---------------------------------------------------------+
| repeat/  | The structure will repeatedly evaluate the internal     |
| until    | statement(s) 'until' the condition is true. The final   |
|          | statement in the final iteration will be used as the    |
|          | return value of the loop.                               |
|          | eg:                                                     |
|          | repeat                                                  |
|          |   y := x + z;                                           |
|          |   w := z + y;                                           |
|          | until ((x := (x - 1)) <= 0)                             |
+----------+---------------------------------------------------------+
| ~        | Evaluate each sub-expression, then return as the result |
|          | the value of the last sub-expression. This is sometimes |
|          | known as multiple sequence point evaluation.            |
|          | eg:                                                     |
|          | ~(i := x + 1, j := y / z, k := sin(w/u)) == (sin(w/u))) |
|          | ~{i := x + 1; j := y / z; k := sin(w/u)} == (sin(w/u))) |
+----------+---------------------------------------------------------+



[09 - COMPONENTS]
There are three primary components, that are specialized upon a  given
numeric type, which make up the core of ExprTk. The components are  as
follows:

  1. Symbol Table  exprtk::symbol_table<T>
  2. Expression    exprtk::expression<T>
  3. Parser        exprtk::parser<T>


(1) Symbol Table
A structure that is used  to store references to variables,  constants
and functions that are to be used within expressions.

(2) Expression
A structure that holds an AST  for a specified expression and is  used
to evaluate said expression.  If a compiled Expression  uses variables
or user defined functions, it will then also have an associated Symbol
Table, which will contain  references to said variables,  functions et
al. An example AST structure for the denoted expression is as follows:

Expression:  z := (x + y^-2.345) * sin(pi / min(w - 7.3,v))

                  [Root]
                    |
               [Assignment]
        ________/        \_____
       /                       \
 Variable(z)               [Multiply]
                ____________/      \___________
               /                               \
              /                          [Unary-Func(sin)]
         [Addition]                            |
      ____/      \____                    [Division]
     /                \                 ___/      \___
 Variable(x)       [Power]             /              \
              ______/   \______  Constant(pi)  [Binary-Func(min)]
             /                 \                 ___/    \___
        Variable(y)         [Negate]            /            \
                               |           [Subtract]    Variable(v)
                        Constant(2.345) ____/      \___
                                       /               \
                                  Variable(w)     Constant(7.3)

(3) Parser
A  structure  which  takes  as input  a  string  representation  of an
expression and attempts to compile said input with the result being an
instance  of  Expression.  If  an  error  is  encountered  during  the
compilation  process, the  parser will  stop compiling  and return  an
error status code,  with a more  detailed description of  the error(s)
and  its  location  within  the  input  provided  by  the  'get_error'
interface.



[10 - SPECIAL FUNCTIONS]
The purpose  of special  functions in  ExprTk is  to provide  compiler
generated equivalents of common mathematical expressions which can  be
invoked by  using the  'special function'  syntax (eg:  $f12(x,y,z) or
$f82(x,y,z,w)).

Special functions dramatically decrease  the total evaluation time  of
expressions which would otherwise  have been written using  the common
form by reducing the total number  of nodes in the evaluation tree  of
an  expression  and  by  also  leveraging  the  compiler's  ability to
correctly optimize such expressions for a given architecture.

          3-Parameter                       4-Parameter
 +-------------+-------------+    +--------------+------------------+
 |  Prototype  |  Operation  |    |  Prototype   |    Operation     |
 +-------------+-------------+    +--------------+------------------+
   $f00(x,y,z) | (x + y) / z       $f47(x,y,z,w) | x + ((y + z) / w)
   $f01(x,y,z) | (x + y) * z       $f48(x,y,z,w) | x + ((y + z) * w)
   $f02(x,y,z) | (x + y) - z       $f49(x,y,z,w) | x + ((y - z) / w)
   $f03(x,y,z) | (x + y) + z       $f50(x,y,z,w) | x + ((y - z) * w)
   $f04(x,y,z) | (x - y) / z       $f51(x,y,z,w) | x + ((y * z) / w)
   $f05(x,y,z) | (x - y) * z       $f52(x,y,z,w) | x + ((y * z) * w)
   $f06(x,y,z) | (x * y) + z       $f53(x,y,z,w) | x + ((y / z) + w)
   $f07(x,y,z) | (x * y) - z       $f54(x,y,z,w) | x + ((y / z) / w)
   $f08(x,y,z) | (x * y) / z       $f55(x,y,z,w) | x + ((y / z) * w)
   $f09(x,y,z) | (x * y) * z       $f56(x,y,z,w) | x - ((y + z) / w)
   $f10(x,y,z) | (x / y) + z       $f57(x,y,z,w) | x - ((y + z) * w)
   $f11(x,y,z) | (x / y) - z       $f58(x,y,z,w) | x - ((y - z) / w)
   $f12(x,y,z) | (x / y) / z       $f59(x,y,z,w) | x - ((y - z) * w)
   $f13(x,y,z) | (x / y) * z       $f60(x,y,z,w) | x - ((y * z) / w)
   $f14(x,y,z) | x / (y + z)       $f61(x,y,z,w) | x - ((y * z) * w)
   $f15(x,y,z) | x / (y - z)       $f62(x,y,z,w) | x - ((y / z) / w)
   $f16(x,y,z) | x / (y * z)       $f63(x,y,z,w) | x - ((y / z) * w)
   $f17(x,y,z) | x / (y / z)       $f64(x,y,z,w) | ((x + y) * z) - w
   $f18(x,y,z) | x * (y + z)       $f65(x,y,z,w) | ((x - y) * z) - w
   $f19(x,y,z) | x * (y - z)       $f66(x,y,z,w) | ((x * y) * z) - w
   $f20(x,y,z) | x * (y * z)       $f67(x,y,z,w) | ((x / y) * z) - w
   $f21(x,y,z) | x * (y / z)       $f68(x,y,z,w) | ((x + y) / z) - w
   $f22(x,y,z) | x - (y + z)       $f69(x,y,z,w) | ((x - y) / z) - w
   $f23(x,y,z) | x - (y - z)       $f70(x,y,z,w) | ((x * y) / z) - w
   $f24(x,y,z) | x - (y / z)       $f71(x,y,z,w) | ((x / y) / z) - w
   $f25(x,y,z) | x - (y * z)       $f72(x,y,z,w) | (x * y) + (z * w)
   $f26(x,y,z) | x + (y * z)       $f73(x,y,z,w) | (x * y) - (z * w)
   $f27(x,y,z) | x + (y / z)       $f74(x,y,z,w) | (x * y) + (z / w)
   $f28(x,y,z) | x + (y + z)       $f75(x,y,z,w) | (x * y) - (z / w)
   $f29(x,y,z) | x + (y - z)       $f76(x,y,z,w) | (x / y) + (z / w)
   $f30(x,y,z) | x * y^2 + z       $f77(x,y,z,w) | (x / y) - (z / w)
   $f31(x,y,z) | x * y^3 + z       $f78(x,y,z,w) | (x / y) - (z * w)
   $f32(x,y,z) | x * y^4 + z       $f79(x,y,z,w) | x / (y + (z * w))
   $f33(x,y,z) | x * y^5 + z       $f80(x,y,z,w) | x / (y - (z * w))
   $f34(x,y,z) | x * y^6 + z       $f81(x,y,z,w) | x * (y + (z * w))
   $f35(x,y,z) | x * y^7 + z       $f82(x,y,z,w) | x * (y - (z * w))
   $f36(x,y,z) | x * y^8 + z       $f83(x,y,z,w) | x*y^2 + z*w^2
   $f37(x,y,z) | x * y^9 + z       $f84(x,y,z,w) | x*y^3 + z*w^3
   $f38(x,y,z) | x * log(y)+z      $f85(x,y,z,w) | x*y^4 + z*w^4
   $f39(x,y,z) | x * log(y)-z      $f86(x,y,z,w) | x*y^5 + z*w^5
   $f40(x,y,z) | x * log10(y)+z    $f87(x,y,z,w) | x*y^6 + z*w^6
   $f41(x,y,z) | x * log10(y)-z    $f88(x,y,z,w) | x*y^7 + z*w^7
   $f42(x,y,z) | x * sin(y)+z      $f89(x,y,z,w) | x*y^8 + z*w^8
   $f43(x,y,z) | x * sin(y)-z      $f90(x,y,z,w) | x*y^9 + z*w^9
   $f44(x,y,z) | x * cos(y)+z      $f91(x,y,z,w) | (x and y) ? z : w
   $f45(x,y,z) | x * cos(y)-z      $f92(x,y,z,w) | (x or  y) ? z : w
   $f46(x,y,z) | x ? y : z         $f93(x,y,z,w) | (x <   y) ? z : w
                                   $f94(x,y,z,w) | (x <=  y) ? z : w
                                   $f95(x,y,z,w) | (x >   y) ? z : w
                                   $f96(x,y,z,w) | (x >=  y) ? z : w
                                   $f97(x,y,z,w) | (x ==  y) ? z : w
                                   $f98(x,y,z,w) | x * sin(y) + z * cos(w)



[11 - EXPRTK NOTES]
 (00) Precision and performance of expression evaluations are the
      dominant principles of the ExprTk library.

 (01) Supported types are float, double and long double.

 (02) Standard mathematical operator precedence is applied (BEDMAS).

 (03) Results of expressions that are deemed as being 'valid' are to
      exist within the set of Real numbers. All other results will be
      of the value: Not-A-Number (NaN).

 (04) Supported user defined types are numeric and string variables
      and functions.

 (05) All variable and function names are case-insensitive.

 (06) Variable and function names must begin with a letter
      (A-Z or a-z), then can be comprised of any combination of
      letters, digits and underscores. (eg: x, var1 or power_func99)

 (07) Expression lengths and sub-expression lists are limited only by
      storage capacity.

 (08) The life-time of objects registered with or created from a
      specific symbol-table must span at least the life-time of the
      compiled expressions which utilize objects, such as variables,
      of that symbol-table, otherwise the result will be undefined
      behavior.

 (09) Equal/Nequal are normalized equality routines, which use
      epsilons of 0.0000000001 and 0.000001 for double and float
      types respectively.

 (10) All trigonometric functions assume radian input unless
      stated otherwise.

 (11) Expressions may contain white-space characters such as
      space,  tabs, new-lines, control-feed et al.
      ('\n', '\r', '\t', '\b', '\v', '\f')

 (12) Strings may be constructed from any letters, digits or special
      characters such as (~!@#$%^&*()[]|=+ ,./?<>;:"`~_), and must
      be enclosed with single-quotes.
      eg: 'Frankly, my dear, I do not give a damn!'

 (13) User defined normal functions can have up to 20 parameters,
      where as user defined vararg-functions can have an unlimited
      number of parameters.

 (14) The inbuilt polynomial functions can be at most of degree 12.

 (15) Where appropriate constant folding optimisations will be
      applied. (eg: The expression '2+(3-(x/y))' becomes '5-(x/y)')

 (16) String processing capabilities are available by default.
      To turn them off, the following needs to be defined at
      compile time: exprtk_disable_string_capabilities

 (17) Composited functions can call themselves or any other functions
      that have been defined prior to their own definition.

 (18) Recursive calls made from within composited functions will have
      a stack size bound by the stack of the executing architecture.

 (19) The following are examples of compliant floating point value
      representations:
      (a) 12345        (b) -123.456
      (c) +123.456e+12 (d) 123.456E-12
      (e) +012.045e+07 (f) .1234
      (g) 123.456f     (h) -321.654E+3L

 (20) Expressions may contain any of the following comment styles:
      1. // .... \n
      2. #  .... \n
      3. /* .... */



[12 - SIMPLE EXPRTK EXAMPLE]
--- snip ---
#include <cstdio>
#include <string>

#include "exprtk.hpp"

template <typename T>
struct myfunc : public exprtk::ifunction<T>
{
   myfunc() : exprtk::ifunction<T>(2) {}

   T operator()(const T& v1, const T& v2)
   {
      return T(1) + (v1 * v2) / T(3);
   }
};

int main()
{
   typedef exprtk::symbol_table<double> symbol_table_t;
   typedef exprtk::expression<double>     expression_t;
   typedef exprtk::parser<double>             parser_t;
   typedef exprtk::parser_error::type          error_t;

   std::string expression_str = "z := 2 myfunc([4+sin(x/pi)^3],y^2)";

   double x = 1.1;
   double y = 2.2;
   double z = 3.3;

   myfunc<double> mf;

   symbol_table_t symbol_table;
   symbol_table.add_constants();
   symbol_table.add_variable("x",x);
   symbol_table.add_variable("y",y);
   symbol_table.add_variable("z",z);
   symbol_table.add_function("myfunc",mf);

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   parser_t parser;

   if (!parser.compile(expression_str,expression))
   {
      printf("Error: %s\tExpression: %s\n",
             parser.error().c_str(),
             expression_str.c_str());

      for (std::size_t i = 0; i < parser.error_count(); ++i)
      {
         error_t error = parser.get_error(i);
         printf("Error: %02d Position: %02d "
                "Type: [%s] "
                "Message: %s "
                "Expression: %s\n",
                static_cast<int>(i),
                static_cast<int>(error.token.position),
                exprtk::parser_error::to_str(error.mode).c_str(),
                error.diagnostic.c_str(),
                expression_str.c_str());
      }

      return 1;
   }

   double result = expression.value();

   printf("Result: %10.5f\n",result);

   return 0;
}
--- snip ---



[13 - FILES]
(00) Makefile
(01) readme.txt
(02) exprtk.hpp
(03) exprtk_test.cpp
(04) exprtk_benchmark.cpp
(05) exprtk_simple_example_01.cpp
(06) exprtk_simple_example_02.cpp
(07) exprtk_simple_example_03.cpp
(08) exprtk_simple_example_04.cpp
(09) exprtk_simple_example_05.cpp
(10) exprtk_simple_example_06.cpp
(11) exprtk_simple_example_07.cpp
(12) exprtk_simple_example_08.cpp
(13) exprtk_simple_example_09.cpp
(14) exprtk_simple_example_10.cpp
