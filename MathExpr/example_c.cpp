/*

example.cpp , example file for mathexpr.cpp 2.0

Copyright Yann OLLIVIER 1997-2000

This software may be freely distributed as is, including this whole notice.

It may be modified, but any modification should include this whole notice as 
is and a description of the changes made.

This software may not be sold.

This software or any modified version of it may be freely used in free
programs. The program should include a copy of this whole notice.
If you want to use it in a program you sell, contact me

This software comes with absolutely no warranty.

*/

#include <stdio.h>
#include "mathexpr_c.h"

// Compilation :
// g++ mathexpr_c.cpp example_c.cpp

int main()
{

 // The number that the variable "x" will point to
 double_complex x;
 // Creates a variable named "x" and which value will be x
 CVar xvar ( "x" , &x );

 // Asks for a fomula depending on the variable x, e.g. "sin 2x"
 char s[500]="";
 printf("Enter a formula depending on the variable x:\n");
 gets(s);

 // Creates an operation with this formula. The operation depends on one
 // variable, which is xvar ; the third argument is an array of pointers
 // to variables; the previous argument is its size
 CVar* vararray[1]; vararray[0]=&xvar;
 COperation op ( s, 1, vararray );

 // Affects (indirectly) a value to xvar
 x=3;
 // Printfs the value of the formula for x=3;
 printf("%s = %s for x=3\n\n", op.Expr(), PrettyPrint(op.Val()) );

 // Creates a function name which can be used in later functions to refer to the operation op(x)
 CFunction f (op, &xvar); f.SetName("f");

 // Creates a second variable named y, and a formula depending on both x and y
 double_complex y;
 CVar yvar ( "y" , &y );
 CVar* vararray2[2]; // table of variables containing the adresses of xvar and yvar
 vararray2[0]=&xvar; vararray2[1]=&yvar;

 // Asks for a formula using x, y and the already-defined function f, e.g. x+f(3y)
 printf("Enter a formula using x, y and the function f(x): x -> %s that you just entered, e.g. x+f(3y) :\n", op.Expr());
 gets(s);
 CFunction* funcarray[1]; funcarray[0]=&f;
 COperation op2 ( (char*)s , 2 , vararray2 , 1, funcarray );
 // vararray2 is a CVar* array with two elements
 // funcarray is a CFunction* array with one element
 y=5;
 printf("Value for x=3, y=5 : %s\n", PrettyPrint(op2.Val()) );

 // Turns the last expression into a function of x and y
 CFunction g(op2, 2, vararray2); g.SetName("g");

 // Here is another way to do it
 double_complex z,t;
 CVar zvar("z", &z), tvar("t", &t);
 COperation op3,zop,top;
 zop=zvar; top=tvar; // constructs, from a variable, the operation returning its value

 op3=g( (zop+top, top^2) ); // Ready-to-use ; needs two pairs of ( )
 // Now op3 contains the operation op2 with x replaced with z+t, and y replaced with t^2

 z=5;t=7;
 printf("\nLet g be the function g : x,y -> %s\n", op2.Expr());
 printf("Value of %s for z=5,t=7:\n %s\n", op3.Expr(), PrettyPrint(op3.Val()) );

 COperation dopdt=op3.Diff(tvar); // Computes the derivative of op3 w.r.t t
 printf("Value of d/dt (g(z+t,t^2)) = %s for z=5,t=7:\n %s\n", dopdt.Expr(), PrettyPrint(dopdt.Val()) );
 COperation dopdtbar=op3.DiffConj(tvar); // Computes the derivative of op3 w.r.t the conjugate of t
 printf("Value of d/dtbar (g(z+t,t^2)) = %s for z=5,t=7:\n %s\n", dopdtbar.Expr(), PrettyPrint(dopdtbar.Val()) );

 return 0;
}
