# The Great C++ Mathematical Expression Parser Benchmark

This is a benchmark suite for different implementations of open source
math expression parsers and evaluators written in C++. Currently the
following expression parsers are part of this benchmark:

|#    |  Library       |  Author                       |  License   |  Numeric Type   |
| --- | :------------- | :---------------------------- | :----------| :----------:|
| 00  | [ATMSP]    (http://sourceforge.net/projects/atmsp/)    | Heinz van Saanen              | [GPL v3](http://www.opensource.org/licenses/gpl-3.0.html) | double |
| 01  | [ExprTk]   (http://www.partow.net/programming/exprtk/) | Arash Partow                  | [CPL v1.0](http://www.opensource.org/licenses/cpl1.0.php) | double, float, MPFR |
| 02  | [FParser]  (http://warp.povusers.org/FunctionParser/)  | Juha Nieminen & Joel Yliluoma | [LGPL](http://www.gnu.org/copyleft/lesser.html)           | double |
| 03  | [Lepton]   (https://simtk.org/home/lepton)             | Peter Eastman                 | [MIT](http://www.opensource.org/licenses/mit-license.php) | double |
| 04  | [MathExpr] (http://www.yann-ollivier.org/mathlib/mathexpr)| Yann Ollivier              | [Copyright Notice 1997-2000](http://www.yann-ollivier.org/mathlib/mathexpr#C)| double |
| 05  | [MTParser] (http://www.codeproject.com/Articles/7335/An-extensible-math-expression-parser-with-plug-ins)| Mathieu Jacques | [CPOL](http://www.codeproject.com/info/cpol10.aspx)| double |
| 06  | [muParser] (http://muparser.beltoforion.de)            | Ingo Berg                     | [MIT](http://www.opensource.org/licenses/mit-license.php) | double, float |
| 07  | [muParserX](http://muparserx.beltoforion.de)           | Ingo Berg                     | [MIT](http://www.opensource.org/licenses/mit-license.php) | double, float |
| 08  | [TinyExpr] (https://github.com/codeplea/tinyexpr)      | Lewis Van Winkle              | [zlib](https://opensource.org/licenses/Zlib)              | double        |


**Note:** This archive is not meant as a primary source for any of the
libraries listed above as it may contain outdated versions of said
libraries.


## The Setup

The benchmark takes two parameters:

1.  Number of iterations (N)
1.  Benchmark Test File

The mathematical expression benchmark files are as follows:

1.  [bench_expr.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr.txt)
1.  [bench_expr_all.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_all.txt)
1.  [bench_expr_all_permutations.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_all_permutations.txt)
1.  [bench_expr_complete.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_complete.txt)
1.  [bench_expr_extensive.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_extensive.txt)
1.  [bench_expr_precedence.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_precedence.txt)
1.  [bench_expr_random_with_functions.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_random_with_functions.txt)
1.  [bench_expr_random_without_functions.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_random_without_functions.txt)
1.  [bench_expr_weird.txt](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_weird.txt)


As an example, the following execution will use the[*"bench_expr_all.txt"*]
(https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_all.txt) set of expressions, executing each expression 100000 times:

    ParserBench.exe 100000 bench_expr_all.txt

## The Rounds
For every expression in the benchmark file, every parser evaluates the
given expression N times, this is known as a round. The total time
each parser takes to evaluate the expression N times is recorded.
Ranking of the parsers for the round is done from the fastest to the
slowest. The following is an example summary for the expression
'(a^2/sin(2*pi/b))-a/2':

    Expression 61 of 67: "(a^2/sin(2*pi/b))-a/2"; Progress: ###########
    [01] ExprTk              ( 34.373 ns, 3.744853294789905362, -3153742.968144028913229704)
    [02] ExprTkFloat         ( 35.141 ns, 3.744853734970092773, -3153743.237257003784179688)
    [03] muparserSSE         ( 43.155 ns, 3.744852304458618164, -3153743.147850036621093750)
    [04] muparser 2.2.4 (omp)( 48.223 ns, 3.744853294789905362, -3153742.968144028913229704)
    [05] muparser 2.2.4      ( 52.411 ns, 3.744853294789905362, -3153742.968144028913229704)
    [06] MTParser            ( 56.825 ns, 3.744853294789905362, -3153742.968144028913229704)
    [07] FParser 4.5         ( 62.949 ns, 3.744853294789905362, -3153742.968144028913229704)
    [08] atmsp 1.0.4         ( 77.320 ns, 3.744853294789905362, -3153742.968144028913229704)
    [09] MathExpr            (124.067 ns, 3.744853294789905362, -3153742.968144028913229704)
    [10] Lepton              (376.444 ns, 3.744853294789905362, -3153742.968144028913229704)
    [11] muparserx           (545.148 ns, 3.744853294789905362, -3153742.968144028913229704)


Parsers that can't parse the expression or produce a result *different*
to the expected result (based on a normalized epsilon approach) are
disqualified for the round and do not participate in point
accumulation. The following is an example where a few of the parsers
failed to either parse or evaluate the given expression of '+1.1+a^b' correctly:

    Expression 69 of 96: "+1.1+a^b"; Progress: ###########
    [01] ExprTk              ( 40.885 ns, 2.333286300554663129, 2906884.279087092727422714)
    [02] muparserSSE         ( 41.089 ns, 2.333286285400390625, 2906884.431838989257812500)
    [03] ExprTkFloat         ( 41.434 ns, 2.333286285400390625, 2906884.431838989257812500)
    [04] atmsp 1.0.4         ( 48.107 ns, 2.333286300554663129, 2906884.279087092727422714)
    [05] MTParser            ( 49.801 ns, 2.333286300554663129, 2906884.279087092727422714)
    [06] muparser 2.2.4      ( 52.583 ns, 2.333286300554663129, 2906884.279087092727422714)
    [07] muparser 2.2.4 (omp)( 53.922 ns, 2.333286300554663129, 2906884.279087092727422714)
    [08] muparserx           (199.955 ns, 2.333286300554663129, 2906884.279087092727422714)
    DNQ List
    [01] FParser 4.5          (Syntax error)
    [02] MathExpr             (parsing error)
    [03] Lepton               (Parse error in expression "+1.1+a^b": unexpected token: +)
    **** ERROR ****   Excessive number of evaluation failures!  [3]

The meanings of each of the columns are as follows:

1.  Rank
2.  Parser
3.  Average time *(in nano-seconds)* to evaluate the expression once, taken over N-times
4.  Result of evaluating the expression
5.  Sum of N-evaluations of the given expression


## The Final Summary
Once all the expressions have been completed, a summary is provided,
that includes information relating to the build parameters of the
benchmark binary, the architecture which the benchmark was run upon, a
final ranking of the parsers, and a listing of expressions per parser
that were deemed as disqualified during the benchmark.

The following is an example summary generated at the completion of the benchmark:


    Benchmark settings:
      - Expressions File is "bench_expr.txt"
      - Reference parser is ExprTk
      - Iterations per expression: 1000000
      - Number of expressions: 67
      - Number of excessive failures: 4
      - Release build
      - Compiled with MSVC Version 1900
      - IEEE 754 (IEC 559) is Available
      - 32-bit build
      - CPU Name      : Intel(R) Xeon(R) CPU E5-2687W 0 @ 3.10GHz
      - Num. cores    : 16
      - Num. logical  : 32
      - Total logical : 16
      - L1 D cache    : 32 KB
      - L1 I cache    : 32 KB
      - L2 cache      : 256 KB
      - L3 cache      : 20480 KB
      - L1D assoc.    : 8-way
      - L2 assoc.     : 8-way
      - L3 assoc.     : 20-way
      - L1D line size : 64 bytes
      - L2 line size  : 64 bytes
      - L3 line size  : 64 bytes
      - CPU clock     : 3092 MHz
      - Features      : acpi aes apic avx clflush cmov cx16 cx8 dca de ds_cpl
                        dts dts64 est fpu fxsr ht lahf_lm lm mca mce mmx monitor
                        msr mtrr osxsave pae pat pbe pclmul pdcm pge pni popcnt
                        pse pse36 sep smx ss sse sse2 sse4_1 sse4_2 ssse3 tm tm2
                        tsc vme vmx xd xsave xtpr
      Scores:
      #  Parser               Type       Points   Score    Failures
      --------------------------------------------------------------
      00 ExprTk               double     671      100      0
      01 ExprTkFloat          float      600       91      5
      02 muparserSSE          float      591      104      5
      03 FParser 4.5          double     457       47      0
      04 atmsp 1.0.4          double     411       42      2
      05 muparser 2.2.4       double     386       39      0
      06 MTParser             double     355       41      7
      07 muparser 2.2.4 (omp) double     300       36      0
      08 MathExpr             double     280       31      2
      09 Lepton               double     104        7      2
      10 muparserx            double      94        6      0

## The Results
The summaries of runs of the benchmark suite upon various architectures can be found here: [Results](https://github.com/ArashPartow/math-parser-benchmark-project/tree/master/logs)

## Example Results
The following is a chart depicting the results as executions per
second obtained by running the
['bench_expr_random_without_functions.txt'](https://github.com/ArashPartow/math-parser-benchmark-project/blob/master/bench_expr_random_without_functions.txt)
benchmark, using the double type, 5000000 iterations per expression on
an Intel Xeon E5-2687W 3GHz. The horizontal measure on the chart is
the length of the expression in bytes.

![ScreenShot](http://www.partow.net/experimental/images/benchmark_result.png?raw=true "C++ Mathematical Expression Parser Benchmark Results")

**Note:** The parsers *muParserSSE* and *ExprTKFloat* were excluded
due to their use of the float type, and the *Lepton* and *muParserX*
parsers were excluded due to the fact that their results were
consistently 2-3 orders of magnitude slower than all the others.

**Note:** The command executed to generate the above results is as follows:

    ParserBenchmark.exe 5000000 bench_expr_random_without_functions.txt write_table

## Native Mode
The benchmark has a special mode called **"Native"**. In this mode a
predefined set of expressions are employed, and benchmarked against
both native equivalent implementations and the standard
parsers/evaluators.

The command to execute the benchmark in native mode is as follows:

    ParserBenchmark.exe 1000000 native

## Customised Tests
Creating a customised test is very simple. All that is required is to
create a utf-8 encoded text file, and pass it as the 2nd parameter to
the benchmark executable.

Each line can only have one expression, comprised of the following:

* **Operators:** +, -, *, /, ^
* **Variables:** a, b, c, x, y, z, w
* **Constants:** e and pi
* **Functions:** sin, cos, tan, abs, exp, sqrt, log, pow
* **Parentheses:** Round '(' and ')'

Furthermore blank lines or lines beginning with a **#**-symbol will be ignored (aka comments or white-space).

The following is a simple example of a custom test:

    ---- snip ----

    # My first expression:
    (x + 1) / 2 * b

    # Pythagoras
    a^2 + b^2

    # A constant expression
    1 + (2 * 3) / 7

    # Definition of tan in terms of sine and cosine
    sin(x) / cos(x)

    ---- snip ----


## New Parsers
The addition of new or unlisted C++ mathematical expression parsers is
always welcome. If you know of a parser and would like it included in
the suite feel free to make a request. Additionally if the associated
benchmark implementation *(eg: src/BenchXYZW.cpp)* could be made
available as part of the request that would very helpful.
