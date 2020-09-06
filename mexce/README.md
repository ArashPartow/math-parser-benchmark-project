# mexce 

Mini Expression Compiler/Evaluator

## Overview

mexce is a small runtime compiler of mathematical expressions, written in C++. It generates machine code that primarily uses the x87 FPU.
It is a single header with no dependencies.

I wrote this back in 2003 as part of a larger application and then its existence was almost forgotten. The code was now updated with added support for x64 and Data Execution Prevention, which probably did not exist back then.

It currently supports Windows and Linux.

## Usage

Here is an example:

```cpp
float   x  = 0.0f;
double  y  = 0.1;
int     z  = 200;

mexce::evaluator eval;

eval.bind(x, "x");
eval.bind(y, "y");
eval.bind(z, "z");

eval.assign_expression("0.3+(-sin(2.33+x-logb((.3*pi+(88/y)/e),3.2+z)))/98");

cout << endl << "Evaluation results:" << endl;
for (int i = 0; i < 10; i++, x-=0.1f, y+=0.212, z+=2) {
    cout << "  " << eval.evaluate() << endl;
}
```

Output:
```
Evaluation results:
  0.289926
  0.290975
  0.292393
  0.294023
  0.295788
  0.297623
  0.299475
  0.301293
  0.303031
  0.304649
```

## Performance

Apparently, mexce is quite fast.
Here is how it compares in the [math-parser-benchmark-project](https://github.com/ArashPartow/math-parser-benchmark-project) on an AMD Zen2:


| #       |Parser               |  Type      |     Points | Score   |Failures
  --------|---------------------|------------|------------|---------|--------
  ***00***|***mexce***          |***double***|  ***2630***|***217***|***0***
  01      | ExprTk              |   double   |        2577|    100  |   0
  02      | METL                |   double   |        1857|     51  |   0
  03      | FParser 4.5         |   double   |        1832|     53  |   2
  04      | muparser 2.2.4      |   double   |        1655|     45  |   0
  05      | muparserSSE         |   float    |        1640|     89  |  58
  06      | ExprTkFloat         |   float    |        1635|     61  |  62
  07      | atmsp 1.0.4         |   double   |        1616|     45  |   4
  08      | muparser 2.2.4 (omp)|   double   |        1442|     43  |   0
  09      | TinyExpr            |   double   |        1183|     37  |   3
  10      | MathExpr            |   double   |         930|     27  |  12
  11      | MTParser            |   double   |         836|     29  |   9
  12      | Lepton              |   double   |         438|      9  |   4
  13      | muparserx           |   double   |         239|      5  |   0

Full results [here](https://github.com/imakris/mexce/blob/master/bench_expr_all_results.txt)

## License

The source code of the library is licensed under the Simplified BSD License.
