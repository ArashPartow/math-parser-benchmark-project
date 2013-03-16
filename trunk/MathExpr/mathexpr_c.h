/*

mathexpr_c.h version 2.0

Copyright Yann OLLIVIER 1997-2000
  
This software may be freely distributed as is, including this whole notice.

It may be modified, but any modification should include this whole 
notice as is and a description of the changes made.

This software may not be sold.

This software or any modified version of it may be freely used in free
programs. The program should include a copy of this whole notice.
If you want to use it in a program you sell, contact me

This software comes with absolutely no warranty.

*/

#ifndef __MATHEXPR_C_H
#define __MATHEXPR_C_H

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<complex>
#include<float.h>

#ifndef __STD_COMPLEX_
#define double_complex std::complex<double>
double_complex tan(double_complex);
double_complex acos(double_complex);
double_complex asin(double_complex);
double_complex atan(double_complex);
#endif

// Compatibility with long double-typed functions
#define atanl atan
#define asinl asin
#define acosl acos
#define expl exp
#define logl log
#define powl pow
#define pow10l(x) pow(10,x)
#define fabsl fabs
#define cosl cos
#define sinl sin
#define tanl tan
#define fmodl fmod
#define sqrtl sqrt


// Warning : everything will fail with strings longer than 32767 chars

const double_complex ErrVal=double_complex(DBL_MAX,0);

//Class definitions for operations

class CVar{
 public:
  char*name;double_complex*pval;
  CVar(const CVar&);
  CVar(const char*,double_complex*);
  ~CVar();
  friend int operator==(const CVar&,const CVar&);
};

typedef CVar* PCVar;

enum COperator{ErrOp,Juxt,Num,Var,Add,Sub,Opp,Mult,Div,Pow,Sqrt,
	       NthRoot,Real,Imag,Conj,Abs,Arg,Sin,Cos,Tg,Ln,Exp,Acos,Asin,Atan,E10,Fun};

typedef void ((*pfoncld)(double_complex*&));

class COperation;
typedef COperation* PCOperation;
class CFunction;
typedef CFunction* PCFunction;

class COperation{
  pfoncld*pinstr;double_complex**pvals;double_complex*ppile;CFunction**pfuncpile;
  mutable signed char containfuncflag;
  void BuildCode();
	void Destroy();
 public:
  COperator op;
  PCOperation mmb1,mmb2;
  double_complex ValC;const CVar* pvar;double_complex*pvarval;
  CFunction* pfunc;
  COperation();
  COperation(const COperation&);
  COperation(double);COperation(double_complex);
  COperation(const CVar&);
  COperation(char*sp,int nvarp=0,PCVar*ppvarp=NULL,int nfuncp=0,PCFunction*ppfuncp=NULL);
  ~COperation();
  double_complex Val() const;
  signed char ContainVar(const CVar&) const;
  signed char ContainFunc(const CFunction&) const;
  signed char ContainFuncNoRec(const CFunction&) const; // No recursive test on subfunctions
  COperation NthMember(int) const;int NMembers() const;
  signed char HasError(const COperation* =NULL) const;
  COperation& operator=(const COperation&);
  friend int operator==(const COperation&,const double);
  friend int operator==(const COperation&,const double_complex);
  friend int operator==(const COperation&,const COperation&);
  friend int operator!=(const COperation&,const COperation&);
  COperation operator+() const;COperation operator-() const;
  friend COperation operator,(const COperation&,const COperation&);
  friend COperation operator+(const COperation&,const COperation&);
  friend COperation operator-(const COperation&,const COperation&);
  friend COperation operator*(const COperation&,const COperation&);
  friend COperation operator/(const COperation&,const COperation&);
  friend COperation operator^(const COperation&,const COperation&);  // Caution: wrong associativity and precedence
  friend COperation real(const COperation&);
  friend COperation imag(const COperation&);
  friend COperation conj(const COperation&);
  friend COperation arg(const COperation&);
  friend COperation sqrt(const COperation&);
  friend COperation abs(const COperation&);
  friend COperation sin(const COperation&);
  friend COperation cos(const COperation&);
  friend COperation tan(const COperation&);
  friend COperation log(const COperation&);
  friend COperation exp(const COperation&);
  friend COperation acos(const COperation&);
  friend COperation asin(const COperation&);
  friend COperation atan(const COperation&);
  friend COperation ApplyOperator(int,COperation**,COperation (*)(const COperation&,const COperation&));
  COperation Diff(const CVar&) const; //  Differentiate w.r.t a variable
  COperation DiffConj(const CVar&) const; // This one is d / d conj(z)
  char* Expr() const;
  COperation Substitute(const CVar&,const COperation&) const;
};

class CFunction{
  double_complex*buf;
public:
  signed char type;
  double_complex ((*pfuncval)(double_complex));
  COperation op;int nvars;CVar** ppvar;
  char*name;
  CFunction();
  CFunction(double_complex ((*pfuncvalp)(double_complex)));
  CFunction(const COperation& opp, CVar* pvarp);
  CFunction(const COperation& opp, int nvarsp, CVar**ppvarp);
  CFunction(const CFunction&);
  ~CFunction();
  CFunction& operator=(const CFunction&);
  void SetName(const char*s);
  double_complex Val(double_complex) const;
  double_complex Val(double_complex*) const;
  friend int operator==(const CFunction&,const CFunction&);
  COperation operator()(const COperation&);
};

char* PrettyPrint(double_complex);

char* MidStr(const char*s,int i1,int i2);
char* CopyStr(const char*s);
char* InsStr(const char*s,int n,const char c);
signed char EqStr(const char*s,const char*s2);
signed char CompStr(const char*s,int n,const char*s2);
char* DelStr(const char*s,int n);

#endif
