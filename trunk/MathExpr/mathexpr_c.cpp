/*

mathexpr_c.cpp version 2.0

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

#include"mathexpr_c.h"

#ifndef __STD_COMPLEX_
double_complex tan(double_complex z)
{return sin(z)/cos(z);}
double_complex acos(double_complex z)
{return -double_complex(0,1)*log(z+double_complex(0,1)*sqrt(double_complex(1,0)-z*z));}
double_complex asin(double_complex z)
{return -double_complex(0,1)*log(double_complex(0,1)*z+sqrt(double_complex(1,0)-z*z));}
double_complex atan(double_complex z)
{return -double_complex(0,1)*log((double_complex(1,0)+double_complex(0,1)*z)/sqrt(double_complex(1,0)+z*z));}
#endif

char* MidStr(const char*s,int i1,int i2)
{
 if(i1<0||i2>=(int)strlen(s)||i1>i2){
   char* cp = new char[1];
   cp[0] = '\0';
   return cp;
 }
 char*s1=new char[i2-i1+2];
 int i;
 for(i=i1;i<=i2;i++)s1[i-i1]=s[i];
 s1[i2-i1+1]=0;return s1;
}

char* CopyStr(const char*s)
{char*s1=new char[strlen(s)+1];char*s12=s1;const char*s2=s;
while((*s12++=*s2++));return s1;}

void InsStr(char*&s,int n,char c)// Warning : deletes the old string
{if(n<0||n>(int)strlen(s))return;
char*s1=new char[strlen(s)+2];
int i;
for(i=0;i<n;i++)s1[i]=s[i];
s1[n]=c;for(i=n+1;s[i-1];i++)s1[i]=s[i-1];
s1[i]=0;
delete[]s;s=s1;
}

signed char EqStr(const char*s,const char*s2)
{if(strlen(s)!=strlen(s2))return 0;
int i;
for(i=0;i<s[i];i++)if(s[i]!=s2[i])return 0;
return 1;
}

signed char CompStr(const char*s,int n,const char*s2)
{if(n<0||n>=(int)strlen(s)||n+(int)strlen(s2)>(int)strlen(s))return 0;
int i;
for(i=0;s2[i];i++)if(s[i+n]!=s2[i])return 0;
return 1;
}

void DelStr(char*&s,int n)//Deletes the old string
{char*s1=new char[strlen(s)];
int i;
for(i=0;i<n;i++)s1[i]=s[i];
for(i=n;s[i+1];i++)s1[i]=s[i+1];
s1[i]=0;
delete[]s;s=s1;
}

CVar::CVar(const CVar & rvarp)
{if(this==&rvarp)return;pval=rvarp.pval;name=CopyStr(rvarp.name);
}

CVar::CVar(const char*namep,double_complex*pvalp)
{pval=(double_complex*)pvalp;name=CopyStr(namep);}

CVar::~CVar()
{if(name!=NULL)delete[] name;}

CFunction::CFunction()
{
  type=-1;name=new char[1];name[0]=0;
  nvars=0;ppvar=NULL;pfuncval=NULL;op=ErrVal;buf=NULL;
}

CFunction::CFunction(double_complex ((*pfuncvalp)(double_complex)))
{
  type=0;pfuncval=pfuncvalp;name=new char[1];name[0]=0;
  nvars=1;ppvar=NULL;op=ErrVal;buf=NULL;
}

CFunction::CFunction(const CFunction& rfunc)
{
  if(this==&rfunc)return;
  type=rfunc.type;op=rfunc.op;
  pfuncval=rfunc.pfuncval;
  name=CopyStr(rfunc.name);
  nvars=rfunc.nvars;
  if(rfunc.ppvar!=NULL&&nvars){
    ppvar=new PCVar[nvars];
    int i;for(i=0;i<nvars;i++)ppvar[i]=rfunc.ppvar[i];
    buf=new double_complex[nvars];
  }else {ppvar=NULL;buf=NULL;}
}

CFunction::CFunction(const COperation& opp,CVar* pvarp):op(opp)
{
  type=1;name=new char[1];name[0]=0;
  nvars=1;ppvar=new PCVar[1];ppvar[0]=pvarp;buf=new double_complex[1];
}

CFunction::CFunction(const COperation& opp, int nvarsp,CVar**ppvarp):op(opp)
{
  type=1;name=new char[1];name[0]=0;
  nvars=nvarsp;
  if(nvars){
    ppvar=new PCVar[nvars];
    int i;for(i=0;i<nvars;i++)ppvar[i]=ppvarp[i];
    buf=new double_complex[nvars];
  }else {ppvar=NULL;buf=NULL;}
}

CFunction::~CFunction()
{
  if(name!=NULL)delete[]name;
  if(ppvar!=NULL)delete[]ppvar;
  if(buf!=NULL)delete[]buf;
}

CFunction& CFunction::operator=(const CFunction& rfunc)
{
  if(this==&rfunc)return *this;
  type=rfunc.type;op=rfunc.op;
  pfuncval=rfunc.pfuncval;
  delete[]name;
  name=CopyStr(rfunc.name);
  if(ppvar!=NULL)delete[]ppvar;
  ppvar=NULL;
  if(buf!=NULL)delete[]buf;
  buf=NULL;
  nvars=rfunc.nvars;
  if(type==1&&nvars){
    ppvar=new PCVar[nvars];buf=new double_complex[nvars];
    int i;for(i=0;i<nvars;i++)ppvar[i]=rfunc.ppvar[i];
  }
  return *this;
}

void CFunction::SetName(const char*s)
{if(name!=NULL)delete[]name;name=CopyStr(s);}

double_complex CFunction::Val(double_complex x) const
{
  if(type==-1||nvars>=2)return ErrVal;
  if(type==0)return (*pfuncval)(x);
  double_complex xb=*(*ppvar)->pval,y;
  *(*ppvar)->pval=x;  // Warning : could cause trouble if this value is used in a parallel process
  y=op.Val();
  *(*ppvar)->pval=xb;
  return y;
}

double_complex CFunction::Val(double_complex*pv) const
{
  if(type==-1)return ErrVal;
  if(type==0)return (*pfuncval)(*pv);
  double_complex y;
  int i;
  for(i=0;i<nvars;i++){
    buf[i]=*ppvar[i]->pval;
    // Warning : could cause trouble if this value is used in a parallel process
    *ppvar[i]->pval=pv[i];
  }
  y=op.Val();
  for(i=0;i<nvars;i++)*ppvar[i]->pval=buf[i];
  return y;
}

COperation::COperation()
{op=ErrOp;mmb1=NULL;mmb2=NULL;ValC=ErrVal;pvar=NULL;pvarval=NULL;pfunc=NULL;containfuncflag=0;pinstr=NULL;pvals=NULL;ppile=NULL;pfuncpile=NULL;BuildCode();}

COperation::~COperation()
{
  Destroy();
}

COperation::COperation(const COperation&COp)
{
  op=COp.op;pvar=COp.pvar;pvarval=COp.pvarval;ValC=COp.ValC;pfunc=COp.pfunc;containfuncflag=0;pinstr=NULL;pvals=NULL;ppile=NULL;pfuncpile=NULL;
  if(COp.mmb1!=NULL)mmb1=new COperation(*(COp.mmb1));else mmb1=NULL;
  if(COp.mmb2!=NULL)mmb2=new COperation(*(COp.mmb2));else mmb2=NULL;
  BuildCode();
}

COperation::COperation(double_complex x)
{
  if(x==ErrVal){op=ErrOp;mmb1=NULL;mmb2=NULL;ValC=ErrVal;}
  else {op=Num;mmb1=NULL;mmb2=NULL;ValC=x;}
  pvar=NULL;pvarval=NULL;pfunc=NULL;containfuncflag=0;pinstr=NULL;pvals=NULL;ppile=NULL;pfuncpile=NULL;
  BuildCode();
}

COperation::COperation(double x)
{
  if(x==ErrVal){op=ErrOp;mmb1=NULL;mmb2=NULL;ValC=ErrVal;}
  else if(x>=0){op=Num;mmb1=NULL;mmb2=NULL;ValC=x;}
  else{op=Opp;mmb1=NULL;mmb2=new COperation(-x);ValC=ErrVal;}
  pvar=NULL;pvarval=NULL;pfunc=NULL;containfuncflag=0;pinstr=NULL;pvals=NULL;ppile=NULL;pfuncpile=NULL;
  BuildCode();
}

COperation::COperation(const CVar& varp)
{op=Var;mmb1=NULL;mmb2=NULL;ValC=ErrVal;pvar=&varp;pvarval=varp.pval;containfuncflag=0;pfunc=NULL;pinstr=NULL;pvals=NULL;ppile=NULL;pfuncpile=NULL;BuildCode();}

COperation& COperation::operator=(const COperation& COp)
{
  if(this==&COp)return *this;
  Destroy();
  op=COp.op;pvar=COp.pvar;pvarval=COp.pvarval;ValC=COp.ValC;pfunc=COp.pfunc;containfuncflag=0;pinstr=NULL;pvals=NULL;ppile=NULL;pfuncpile=NULL;
  if(COp.mmb1!=NULL)mmb1=new COperation(*(COp.mmb1));else mmb1=NULL;
  if(COp.mmb2!=NULL)mmb2=new COperation(*(COp.mmb2));else mmb2=NULL;
  BuildCode();
  return *this;
}

int operator==(const COperation& op,const double v)
{return(op.op==Num&&op.ValC==v);}

int operator==(const COperation& op,const double_complex v)
{return(op.op==Num&&op.ValC==v);}

int operator==(const COperation& op1,const COperation& op2)
{if(op1.op!=op2.op)return 0;
if(op1.op==Var)return(*(op1.pvar)==*(op2.pvar));
if(op1.op==Fun)return(op1.pfunc==op2.pfunc); // *op1.pfunc==*op2.pfunc could imply infinite loops in cases of self-dependence
if(op1.op==Num)return(op1.ValC==op2.ValC);
if(op1.mmb1==NULL&&op2.mmb1!=NULL)return 0;
if(op1.mmb2==NULL&&op2.mmb2!=NULL)return 0;
if(op2.mmb1==NULL&&op1.mmb1!=NULL)return 0;
if(op2.mmb2==NULL&&op1.mmb2!=NULL)return 0;
return(((op1.mmb1==NULL&&op2.mmb1==NULL)||(*(op1.mmb1)==*(op2.mmb1)))&&
	((op1.mmb2==NULL&&op2.mmb2==NULL)||(*(op1.mmb2)==*(op2.mmb2))));
}

int operator!=(const COperation& op1,const COperation& op2)
{
  if(op1.op!=op2.op)return 1;
  if(op1.op==Var)return(op1.pvar!=op2.pvar);
  if(op1.op==Fun)return(!(op1.pfunc==op2.pfunc)); // *op1.pfunc==*op2.pfunc could imply infinite loops in cases of self-dependence
  if(op1.op==Num)return(op1.ValC!=op2.ValC);
  if(op1.mmb1==NULL&&op2.mmb1!=NULL)return 1;
  if(op1.mmb2==NULL&&op2.mmb2!=NULL)return 1;
  if(op2.mmb1==NULL&&op1.mmb1!=NULL)return 1;
  if(op2.mmb2==NULL&&op1.mmb2!=NULL)return 1;
  return(((op1.mmb1!=NULL||op2.mmb1!=NULL)&&(*(op1.mmb1)!=*(op2.mmb1)))||
	 ((op1.mmb2!=NULL||op2.mmb2!=NULL)&&(*(op1.mmb2)!=*(op2.mmb2))));
}

COperation COperation::operator+() const
{return *this;}

COperation COperation::operator-() const
{if(op==Num)return -ValC;
COperation resultat;
if(op==Opp)resultat=*mmb2;else{resultat.op=Opp;resultat.mmb2=new COperation(*this);};
return resultat;
}

COperation operator,(const COperation& op1,const COperation& op2)
{COperation resultat;
resultat.op=Juxt;resultat.mmb1=new COperation(op1);
resultat.mmb2=new COperation(op2);
return resultat;
}

COperation operator+(const COperation& op1,const COperation& op2)
{
if(op1.op==Num&&op2.op==Num)return op1.ValC+op2.ValC;
if(op1==0.)return op2;if(op2==0.)return op1;
if(op1.op==Opp)return op2-*(op1.mmb2);if(op2.op==Opp)return op1-*(op2.mmb2);
COperation resultat;
resultat.op=Add;resultat.mmb1=new COperation(op1);
resultat.mmb2=new COperation(op2);
return resultat;
}

COperation operator-(const COperation& op1,const COperation& op2)
{
if(op1.op==Num&&op2.op==Num)return op1.ValC-op2.ValC;
if(op1==0.)return -op2;if(op2==0.)return op1;
if(op1.op==Opp)return -(op2+*(op1.mmb2));if(op2.op==Opp)return op1+*(op2.mmb2);
COperation resultat;
resultat.op=Sub;resultat.mmb1=new COperation(op1);
resultat.mmb2=new COperation(op2);
return resultat;
}

COperation operator*(const COperation& op1,const COperation& op2)
{
if(op1.op==Num&&op2.op==Num)return op1.ValC*op2.ValC;
if(op1==0.||op2==0.)return 0.;
if(op1==1.)return op2;if(op2==1.)return op1;
if(op1.op==Opp)return -(*(op1.mmb2)*op2);if(op2.op==Opp)return -(op1**(op2.mmb2));
COperation resultat;
resultat.op=Mult;resultat.mmb1=new COperation(op1);
resultat.mmb2=new COperation(op2);
return resultat;
}

COperation operator/(const COperation& op1,const COperation& op2)
{if(op1.op==Num&&op2.op==Num)return (op2.ValC!=double_complex(0,0)?op1.ValC/op2.ValC:ErrVal);
if(op1==0.0)return 0.;if(op2==1.)return op1;if(op2==0.)return ErrVal;
if(op1.op==Opp)return -(*(op1.mmb2)/op2);if(op2.op==Opp)return -(op1/(*(op2.mmb2)));
COperation resultat;
resultat.op=Div;resultat.mmb1=new COperation(op1);
resultat.mmb2=new COperation(op2);
return resultat;
}

COperation operator^(const COperation& op1,const COperation& op2)
{if(op1==0.)return 0.;
if(op2==0.)return 1.;
if(op2==1.)return op1;
COperation resultat;
resultat.op=Pow;resultat.mmb1=new COperation(op1);
resultat.mmb2=new COperation(op2);
return resultat;
}               
                
COperation real(const COperation& op)
{
  if(op.op==Num)return real(op.ValC);
  COperation rop;rop.op=Real;rop.mmb2=new COperation(op);return rop;
}
COperation imag(const COperation& op)
{
  if(op.op==Num)return imag(op.ValC);
  COperation rop;rop.op=Imag;rop.mmb2=new COperation(op);return rop;
}
COperation conj(const COperation& op)
{
  if(op.op==Num)return conj(op.ValC);
  COperation rop;rop.op=Conj;rop.mmb2=new COperation(op);return rop;
}
COperation arg(const COperation& op)
{COperation rop;rop.op=Arg;rop.mmb2=new COperation(op);return rop;}
COperation sqrt(const COperation& op)
{COperation rop;rop.op=Sqrt;rop.mmb2=new COperation(op);return rop;}
COperation abs(const COperation& op)
{COperation rop;rop.op=Abs;rop.mmb2=new COperation(op);return rop;}
COperation sin(const COperation& op)
{COperation rop;rop.op=Sin;rop.mmb2=new COperation(op);return rop;}
COperation cos(const COperation& op)
{COperation rop;rop.op=Cos;rop.mmb2=new COperation(op);return rop;}
COperation tan(const COperation& op)
{COperation rop;rop.op=Tg;rop.mmb2=new COperation(op);return rop;}
COperation log(const COperation& op)
{COperation rop;rop.op=Ln;rop.mmb2=new COperation(op);return rop;}
COperation exp(const COperation& op)
{COperation rop;rop.op=Exp;rop.mmb2=new COperation(op);return rop;}
COperation acos(const COperation& op)
{COperation rop;rop.op=Acos;rop.mmb2=new COperation(op);return rop;}
COperation asin(const COperation& op)
{COperation rop;rop.op=Asin;rop.mmb2=new COperation(op);return rop;}
COperation atan(const COperation& op)
{COperation rop;rop.op=Atan;rop.mmb2=new COperation(op);return rop;}

COperation ApplyOperator(int n,COperation**pops,COperation (*func)(const COperation&,const COperation&))
{
  if(n<=0)return ErrVal;
  if(n==1)return *pops[0];
  if(n==2)return (*func)(*pops[0],*pops[1]);
  return (*func)(*pops[0],ApplyOperator(n-1,pops+1,func));
}

COperation CFunction::operator()(const COperation& op)
{
  /* Code to use to replace explcitly instead of using a pointer to
     if(nvars!=op.NMembers()||type==-1||type==0)return ErrVal;
     COperation op2=*pop;int i;
     CVar**ppvar2=new PCVar[nvars];char s[11]="";
     for(i=0;i<nvars;i++){
     sprintf(s,";var%i;",i);
     ppvar2[i]=new CVar(s,NULL);
     op2=op2.Substitute(*ppvar[i],(COperation)*ppvar2[i]);
     }
     for(i=0;i<nvars;i++){
     op2=op2.Substitute(*ppvar2[i],op.NthMember(i+1));
     delete ppvar2[i];
     }
     delete[]ppvar2;
     return op2;
  */
  COperation op2;op2.op=Fun;op2.pfunc=this;op2.mmb2=new COperation(op);
  return op2;
}

//Auxiliary string functions

void SupprSpaces(char*&s)//Deletes the old string
{
 int i;
 for(i=0;s[i];i++)if(s[i]==' '||s[i]=='\t'||s[i]=='\n')DelStr(s,i--);
}

signed char IsNumeric(char c)
{if(c!='0'&&c!='1'&&c!='2'&&c!='3'&&c!='4'
	&&c!='5'&&c!='6'&&c!='7'&&c!='8'&&c!='9'&&c!='.')return 0;
return 1;
}

signed char IsTNumeric(char *s)
{int i;for(i=0;i<(int)strlen(s);i++)if(!IsNumeric(s[i]))return 0;return 1;
}

int SearchCorOpenbracket(char*s,int n)  //Searchs the corresponding bracket of an opening bracket
{if(n>=(int)strlen(s)-1)return -1;
int i,c=1;
for(i=n+1;s[i];i++){
	if(s[i]=='(')c++;else if(s[i]==')')c--;
	if(!c)return i;
  };
return -1;
}

int SearchCorClosebracket(char*s,int n)  //Searchs the corresponding bracket of a closing bracket
{if(n<1)return -1;
int i,c=1;
for(i=n-1;i>=0;i--){
	if(s[i]==')')c++;else if(s[i]=='(')c--;
	if(!c)return i;
  };
return -1;
}

int SearchOperator(char*s,COperator op)
{
  char opc;
  switch(op){
  case ErrOp:case Num:case Var:return -1;
  case Juxt:opc=',';break;
  case Add:opc='+';break;
  case Sub:opc='-';break;
  case Mult:opc='*';break;
  case Div:opc='/';break;
  case Pow:opc='^';break;
  case NthRoot:opc='#';break;
  case E10:opc='E';break;        
  default:return -1;
  };
  int i;
  for(i=(int)strlen(s)-1;i>=0;i--){
    if(s[i]==opc&&(op!=Sub||i&&s[i-1]==')'))return i;
    if(s[i]==')'){i=SearchCorClosebracket(s,i);if(i==-1)return -1;};
  };
  return -1;
}

void SimplifyStr(char*&s) //Warning : deletes the old string
{if(!strlen(s))return;
char*s1=s,*s2=s+strlen(s);signed char ind=0;
if(s1[0]=='('&&SearchCorOpenbracket(s1,0)==s2-s1-1){
  s1++;s2--;ind=1;}
if(s1==s2)
{
	delete[]s;
	s=new char[1]; // ISO C++ forbids initialization in array new
	s[0]=0;
	return;
}
if(s1[0]==' '){ind=1;while(s1[0]==' '&&s1<s2)s1++;}
if(s1==s2)
{
	delete[]s;
	s=new char[1]; // ISO C++ forbids initialization in array new
	s[0]=0;
	return;
}
if(*(s2-1)==' '){ind=1;while(s2>s1&&*(s2-1)==' ')s2--;}
*s2=0;
s1=CopyStr(s1);delete[]s;s=s1;
if(ind)SimplifyStr(s);
}

int max(int a, int b){return (a>b?a:b);}

int IsVar(const char*s,int n,int nvar,PCVar*ppvar)
{
  if(n<0||n>(int)strlen(s))return 0;
  int i;int l=0;
  for(i=0;i<nvar;i++)if(CompStr(s,n,(*(ppvar+i))->name))l=max(l,strlen((*(ppvar+i))->name));
  return l;
}

int IsFunction(const char*s,int n)
{
  if(CompStr(s,n,"sin")||CompStr(s,n,"cos")||CompStr(s,n,"exp")
     ||CompStr(s,n,"tan")||CompStr(s,n,"log")||CompStr(s,n,"atg")
     ||CompStr(s,n,"arg")||CompStr(s,n,"abs"))return 3;
  if(CompStr(s,n,"tg")||CompStr(s,n,"ln"))return 2;
  if(CompStr(s,n,"sqrt")||CompStr(s,n,"asin")||CompStr(s,n,"atan")
     ||CompStr(s,n,"real")||CompStr(s,n,"conj")
     ||CompStr(s,n,"imag")||CompStr(s,n,"acos"))return 4;
  if(CompStr(s,n,"arcsin")||CompStr(s,n,"arccos")||CompStr(s,n,"arctan"))return 6;
  if(CompStr(s,n,"arctg"))return 5;
  return 0;
}

int IsFunction(const char*s,int n,int nfunc,PCFunction*ppfunc)
  //Not recognized if a user-defined function is eg "sine" ie begins like
  //a standard function
  //IF PATCHED TO DO OTHERWISE, SHOULD BE PATCHED TOGETHER WITH THE
  //PARSER BELOW which treats standard functions before user-defined ones
{
  int l=IsFunction(s,n);
  if(l)return l;
  int i;l=0;
  for(i=0;i<nfunc;i++)if(CompStr(s,n,ppfunc[i]->name))l=max(l,strlen(ppfunc[i]->name));
  return l;
}

signed char IsFunction(COperator op)
{return (op==Exp||op==Abs||op==Sin||op==Cos||op==Tg||op==Ln
	||op==Atan||op==Asin||op==Acos||op==Atan||op==Sqrt||op==Opp
	||op==Real||op==Imag||op==Conj||op==Arg);
}

void IsolateVars(char*&s,int nvar,PCVar*ppvar,int nfunc,PCFunction*ppfunc)//Deletes the old string
{
  int i,j;
  i=0;
  for(i=0;s[i];i++){
    if(s[i]=='('){i=SearchCorOpenbracket(s,i);if(i==-1)return;continue;};
    if(((j=IsVar(s,i,nvar,ppvar))>IsFunction(s,i,nfunc,ppfunc))||((CompStr(s,i,"pi")||CompStr(s,i,"PI")||CompStr(s,i,"Pi"))&&(j=2)
       ||(CompStr(s,i,"i")&&(j=1)))){
      InsStr(s,i,'(');InsStr(s,i+j+1,')');i+=j+1;continue;};
    if(IsFunction(s,i,nfunc,ppfunc)){i+=IsFunction(s,i,nfunc,ppfunc)-1;if(!s[i])return;continue;};
  };
}

void IsolateNumbers(char*&s,int nvar,CVar**ppvar,int nfunc,CFunction**ppfunc)//Deletes the old string
{
  int i,i2,ind=0,t1,t2;
  for(i=0;s[i];i++){
    if(ind&&!IsNumeric(s[i])){ind=0;InsStr(s,i2,'(');i++;InsStr(s,i,')');continue;};
		t1=IsVar(s,i,nvar,ppvar);t2=IsFunction(s,i,nfunc,ppfunc);
		if(t1||t2){i+=max(t1,t2)-1;continue;}
    if(s[i]=='('){i=SearchCorOpenbracket(s,i);if(i==-1)return;continue;};
    if(!ind&&IsNumeric(s[i])){i2=i;ind=1;};
  };
if(ind)InsStr(s,i2,'(');i++;InsStr(s,i,')');
}

COperation::COperation(char*sp,int nvar,PCVar*ppvarp,int nfuncp,PCFunction*ppfuncp)
{
  ValC=ErrVal;mmb1=NULL;mmb2=NULL;pvar=NULL;op=ErrOp;pvarval=NULL;containfuncflag=0;pfunc=NULL;pinstr=NULL;pvals=NULL;ppile=NULL;pfuncpile=NULL;
  int i,j,k,l;signed char flag=1;
  char*s=CopyStr(sp),*s1=NULL,*s2=NULL;
  SimplifyStr(s);if(!s[0]||!strcmp(s,"Error")){goto fin;}
  while(s[0]==':'||s[0]==';'){
		s1=CopyStr(s+1);delete[]s;s=s1;s1=NULL;
    SimplifyStr(s);if(!s[0]||!strcmp(s,"Error")){goto fin;}
  }
  if(IsTNumeric(s)){op=Num;ValC=atof(s);mmb1=NULL;mmb2=NULL;goto fin;};
  if(EqStr(s,"pi")||EqStr(s,"PI")||EqStr(s,"Pi"))
    {op=Num;ValC=3.141592653589793238462643383279L;mmb1=NULL;mmb2=NULL;goto fin;};
  if(EqStr(s,"i")||EqStr(s,"I"))
    {op=Num;ValC=double_complex(0,1);mmb1=NULL;mmb2=NULL;goto fin;};
  if(IsFunction(s,0,nfuncp,ppfuncp)<IsVar(s,0,nvar,ppvarp))
    for(i=0;i<nvar;i++)if(EqStr(s,(*(ppvarp+i))->name))
      {pvar=ppvarp[i];pvarval=pvar->pval;op=Var;mmb1=NULL;mmb2=NULL;goto fin;};
  for(k=0;s[k];k++){
    if(s[k]=='('){k=SearchCorOpenbracket(s,k);if(k==-1)break;continue;};
    if((l=IsFunction(s,k,nfuncp,ppfuncp))&&l>=IsVar(s,k,nvar,ppvarp)){
      i=k+l;while(s[i]==' ')i++;
      if(s[i]=='('){
				j=SearchCorOpenbracket(s,i);
				if(j!=-1){InsStr(s,i,';');k=j+1;}
			}else if(s[i]!=':'&&s[i]!=';'){InsStr(s,i,':');k=i;}
    }
  }
  IsolateNumbers(s,nvar,ppvarp,nfuncp,ppfuncp);
	if(nvar)IsolateVars(s,nvar,ppvarp,nfuncp,ppfuncp);
  SupprSpaces(s);
  i=SearchOperator(s,Juxt);
  if(i!=-1){char*s1="",*s2="";s1=MidStr(s,0,i-1);s2=MidStr(s,i+1,strlen(s)-1);
  op=Juxt;mmb1=new COperation(s1,nvar,ppvarp,nfuncp,ppfuncp);
  mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  i=SearchOperator(s,Add);
  if(i!=-1){s1=MidStr(s,0,i-1);s2=MidStr(s,i+1,strlen(s)-1);
  op=Add;mmb1=new COperation(s1,nvar,ppvarp,nfuncp,ppfuncp);
  mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  i=SearchOperator(s,Sub);
  if(i!=-1){
    s1=MidStr(s,0,i-1);s2=MidStr(s,i+1,strlen(s)-1);
    op=Sub;mmb1=new COperation(s1,nvar,ppvarp,nfuncp,ppfuncp);
    mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  if(s[0]=='-'){s2=MidStr(s,1,strlen(s)-1);
  op=Opp;mmb1=NULL;
  mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  for(i=0;s[i];i++){
		if(s[i]=='('){i=SearchCorOpenbracket(s,i);if(i==-1)break;continue;};
		if(IsFunction(s,i,nfuncp,ppfuncp)){
			k=i+IsFunction(s,i,nfuncp,ppfuncp);while(s[k]==' ')k++;
			if(s[k]==';'){
				//	s=DelStr(s,k);
				j=k;while(s[j]!='(')j++;
				j=SearchCorOpenbracket(s,j);
				if(j!=-1){InsStr(s,j,')');InsStr(s,i,'(');i=j+2;}
			}else if(s[k]==':'){
				//	s=DelStr(s,k);
				for(j=k;s[j];j++)
					if(s[j]=='('){j=SearchCorOpenbracket(s,j);break;}
				if(j==-1)break;
				for(j++;s[j];j++){
					if(s[j]=='('){j=SearchCorOpenbracket(s,j);if(j==-1){flag=0;break;};continue;};
					if(IsFunction(s,j,nfuncp,ppfuncp))break;
				}
				if(flag==0){flag=1;break;}
				while(j>i&&s[j-1]!=')')j--;if(j<=i+1)break;
				InsStr(s,i,'(');InsStr(s,j+1,')');
				i=j+1;
			}
		}
  }
  for(i=0;s[i]&&s[i+1];i++)if(s[i]==')'&&s[i+1]=='(')
    InsStr(s,++i,'*');
  if(s[0]=='('&&SearchCorOpenbracket(s,0)==(int)strlen(s)-1){
    if(CompStr(s,1,"exp")){op=Exp;s2=MidStr(s,4,strlen(s)-2);}
    else if(CompStr(s,1,"real")){op=Real;s2=MidStr(s,5,strlen(s)-2);}
    else if(CompStr(s,1,"imag")){op=Imag;s2=MidStr(s,5,strlen(s)-2);}
    else if(CompStr(s,1,"conj")){op=Conj;s2=MidStr(s,5,strlen(s)-2);}
    else if(CompStr(s,1,"arg")){op=Arg;s2=MidStr(s,4,strlen(s)-2);}
    else if(CompStr(s,1,"abs")){op=Abs;s2=MidStr(s,4,strlen(s)-2);}
    else if(CompStr(s,1,"sin")){op=Sin;s2=MidStr(s,4,strlen(s)-2);}
    else if(CompStr(s,1,"cos")){op=Cos;s2=MidStr(s,4,strlen(s)-2);}
    else if(CompStr(s,1,"tan")){op=Tg;s2=MidStr(s,4,strlen(s)-2);}
    else if(CompStr(s,1,"log")){op=Ln;s2=MidStr(s,4,strlen(s)-2);}
    else if(CompStr(s,1,"atg")){op=Atan;s2=MidStr(s,4,strlen(s)-2);}
    else if(CompStr(s,1,"tg")){op=Tg;s2=MidStr(s,3,strlen(s)-2);}
    else if(CompStr(s,1,"ln")){op=Ln;s2=MidStr(s,3,strlen(s)-2);}
    else if(CompStr(s,1,"asin")){op=Asin;s2=MidStr(s,5,strlen(s)-2);}
    else if(CompStr(s,1,"acos")){op=Acos;s2=MidStr(s,5,strlen(s)-2);}
    else if(CompStr(s,1,"atan")){op=Atan;s2=MidStr(s,5,strlen(s)-2);}
    else if(CompStr(s,1,"sqrt")){op=Sqrt;s2=MidStr(s,5,strlen(s)-2);}
    else if(CompStr(s,1,"arcsin")){op=Asin;s2=MidStr(s,7,strlen(s)-2);}
    else if(CompStr(s,1,"arccos")){op=Acos;s2=MidStr(s,7,strlen(s)-2);}
    else if(CompStr(s,1,"arctan")){op=Atan;s2=MidStr(s,7,strlen(s)-2);}
    else if(CompStr(s,1,"arctg")){op=Atan;s2=MidStr(s,6,strlen(s)-2);}
    else {
      for(i=-1,k=0,j=0;j<nfuncp;j++)if(CompStr(s,1,ppfuncp[j]->name)&&k<(int)strlen(ppfuncp[j]->name)){k=strlen(ppfuncp[j]->name);i=j;}
      if(i>-1){
				op=Fun;s2=MidStr(s,strlen(ppfuncp[i]->name)+1,strlen(s)-2);
				pfunc=ppfuncp[i];
      }
    }
    mmb1=NULL;mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);
    if(op==Fun)if(mmb2->NMembers()!=pfunc->nvars){op=ErrOp;mmb1=NULL;mmb2=NULL;goto fin;}
    goto fin;
  };
  i=SearchOperator(s,Mult);
  if(i!=-1){s1=MidStr(s,0,i-1);s2=MidStr(s,i+1,strlen(s)-1);
  op=Mult;mmb1=new COperation(s1,nvar,ppvarp,nfuncp,ppfuncp);
  mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  i=SearchOperator(s,Div);
  if(i!=-1){s1=MidStr(s,0,i-1);s2=MidStr(s,i+1,strlen(s)-1);
  op=Div;mmb1=new COperation(s1,nvar,ppvarp,nfuncp,ppfuncp);
  mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  i=SearchOperator(s,Pow);
  if(i!=-1){s1=MidStr(s,0,i-1);s2=MidStr(s,i+1,strlen(s)-1);
  op=Pow;mmb1=new COperation(s1,nvar,ppvarp,nfuncp,ppfuncp);
  mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  i=SearchOperator(s,NthRoot);
  if(i!=-1){s1=MidStr(s,0,i-1);s2=MidStr(s,i+1,strlen(s)-1);
  if(i==0||s[i-1]!=')')
    {op=Sqrt;mmb1=NULL;}else
      {op=NthRoot;mmb1=new COperation(s1,nvar,ppvarp,nfuncp,ppfuncp);};
  mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  i=SearchOperator(s,E10);
  if(i!=-1){s1=MidStr(s,0,i-1);s2=MidStr(s,i+1,strlen(s)-1);
  op=E10;mmb1=new COperation(s1,nvar,ppvarp,nfuncp,ppfuncp);
  mmb2=new COperation(s2,nvar,ppvarp,nfuncp,ppfuncp);goto fin;
  };
  op=ErrOp;mmb1=NULL;mmb2=NULL;
fin:
	BuildCode();
	delete[]s;if(s1!=NULL)delete[] s1;if(s2!=NULL)delete[]s2;
}

void COperation::Destroy()
{
  if(mmb1!=NULL&&mmb2!=NULL&&mmb1!=mmb2){delete mmb1;delete mmb2;mmb1=NULL;mmb2=NULL;}
  else if(mmb1!=NULL){delete mmb1;mmb1=NULL;}else if(mmb2!=NULL){delete mmb2;mmb2=NULL;}
  if(pinstr!=NULL){delete[]pinstr;pinstr=NULL;}
	if(pvals!=NULL){
		if(op==ErrOp||op==Num)delete pvals[0];
		delete[]pvals;pvals=NULL;
	}
  if(ppile!=NULL){delete[]ppile;ppile=NULL;}
  if(pfuncpile!=NULL){delete[]pfuncpile;pfuncpile=NULL;}
}

int operator==(const CVar& var1,const CVar& var2)
{return(var1.pval==var2.pval&&EqStr(var1.name,var2.name));
}

int operator==(const CFunction& f1,const CFunction& f2)
{
  if(f1.type!=f2.type)return 0;
  if(f1.type==-1)return 1; // Nonfunction==nonfunction
  if(f1.type==0)return (f1.pfuncval==f2.pfuncval&&EqStr(f1.name,f2.name));
  if(f1.op!=f2.op)return 0;
  if(!EqStr(f1.name,f2.name))return 0;
  if(f1.nvars!=f2.nvars)return 0;
  int i;
  for(i=0;i<f1.nvars;i++)if(!(*f1.ppvar[i]==*f2.ppvar[i]))return 0;
  return 1;
}

/*
double_complex COperation::Val() const // Won't work if multi-variable functions are included
{
  double_complex v1=ErrVal,v2=ErrVal;
  if(mmb1!=NULL){v1=mmb1->Val();if(norm(v1)<sqrtminfloat)v1=0;else if(v1==double_complex(ErrVal)||norm(v1)>sqrtmaxfloat)return ErrVal;};
  if(mmb2!=NULL){v2=mmb2->Val();if(norm(v2)<sqrtminfloat)v2=0;else if(v2==double_complex(ErrVal)||norm(v2)>sqrtmaxfloat)return ErrVal;};
  switch(op){
  case Num:return ValC;
  case Var:return *pvarval;
  case Add:return v1+v2;
  case Sub:return v1-v2;
  case Opp:return -v2;
  case Mult:return v1*v2;
  case Div:if(v2!=double_complex(0))return v1/v2;else return ErrVal;
  case Pow:if(v1==double_complex(0))return 0;else
    if(norm(v2)*log(norm(v1))<DBL_MAX_EXP)return pow(v1,v2);else return ErrVal;
  case Sqrt:return sqrt(v2);
  case NthRoot:if(v1==double_complex(0)||norm(v2)*log(fabs(norm(v1)))<DBL_MIN_EXP)return ErrVal;
  else return pow(v2,1/v1);
  case E10:if(norm(v2)<300)return v1*pow(double_complex(10.),v2);else return ErrVal;
  case Ln:if(v2!=double_complex(0))return log(v2);else return ErrVal;
  case Exp:if(real(v2)<DBL_MAX_EXP)return exp(v2);else return ErrVal;
  case Sin:if(norm(v2)<DBL_MAX_EXP)
	    return sin(v2);else return ErrVal;
  case Cos:if(norm(v2)<DBL_MAX_EXP)return cos(v2);else return ErrVal;
  case Tg:if(norm(v2)<DBL_MAX_EXP)
	   return tan(v2);else return ErrVal;
  case Atan:if(v2==double_complex(0,1)||v2==double_complex(0,-1))return ErrVal;
  else return atan(v2);
  case Asin:return asin(v2);
  case Acos:return acos(v2);
  case Abs:return norm(v2);
  case Real:return real(v2);
  case Imag:return imag(v2);
  case Conj:return conj(v2);
  case Arg:if(v2!=double_complex(0))return arg(v2);else return ErrVal; 
  case Fun:return pfunc->Val(v2);
  default:return ErrVal;
  };
}
*/

signed char COperation::ContainVar(const CVar& varp) const
{if(op==Var){if(EqStr(pvar->name,varp.name)&&pvar->pval==varp.pval)
	return 1;else return 0;};
if(mmb1!=NULL&&mmb1->ContainVar(varp))return 1;
if(mmb2!=NULL&&mmb2->ContainVar(varp))return 1;
return 0;
}

signed char COperation::ContainFuncNoRec(const CFunction& func) const // No recursive test on subfunctions
{if(op==Fun){if(*pfunc==func)
  return 1;else return 0;}
 if(mmb1!=NULL&&mmb1->ContainFuncNoRec(func))return 1;
 if(mmb2!=NULL&&mmb2->ContainFuncNoRec(func))return 1;
 return 0;
}

signed char COperation::ContainFunc(const CFunction& func) const // Recursive test on subfunctions
{
  if(containfuncflag)return 0;
  if(op==Fun&&*pfunc==func)return 1;
  containfuncflag=1;
  if(op==Fun)if(pfunc->op.ContainFunc(func)){containfuncflag=0;return 1;}
  if(mmb1!=NULL&&mmb1->ContainFunc(func)){containfuncflag=0;return 1;}
  if(mmb2!=NULL&&mmb2->ContainFunc(func)){containfuncflag=0;return 1;}
  containfuncflag=0;return 0;
}

signed char COperation::HasError(const COperation*pop) const
{
  if(op==ErrOp)return 1;
  if(op==Fun&&pfunc->type==1&&pfunc->op==*(pop==NULL?this:pop))return 1;
  if(op==Fun&&pfunc->type==1&&pfunc->op.HasError((pop==NULL?this:pop)))return 1;
  if(mmb1!=NULL&&mmb1->HasError((pop==NULL?this:pop)))return 1;
  if(mmb2!=NULL&&mmb2->HasError((pop==NULL?this:pop)))return 1;
  if(op==Fun&&pfunc->type==-1)return 1;
  return 0;
}

int COperation::NMembers() const //Number of members for an operation like a,b,c...
{
  if(op==Fun)return(pfunc->type==1?pfunc->op.NMembers():pfunc->type==0?1:0);
  if(op!=Juxt)return 1;else if(mmb2==NULL)return 0;else return 1+mmb2->NMembers();
}

COperation COperation::NthMember(int n) const
{
  PCFunction prf;
  if(op==Fun&&pfunc->type==1&&pfunc->op.NMembers()>1){
    prf=new CFunction(pfunc->op.NthMember(n),pfunc->nvars,pfunc->ppvar);
    char*s=new char[strlen(pfunc->name)+10];
    sprintf(s,"(%s_%i)",pfunc->name,n);prf->SetName(s);delete[]s;
    return(*prf)(*mmb2);
  }
  if(n==1){
    if(op!=Juxt)return *this; else if(mmb1!=NULL)return *mmb1;else return ErrVal;
  };
  if(op!=Juxt)return ErrVal;
  if(n>1&&mmb2!=NULL)return mmb2->NthMember(n-1);
  return ErrVal;
}

COperation COperation::Substitute(const CVar& var,const COperation& rop) const // Replaces variable var with expression rop
{
  if(!ContainVar(var))return *this;
  if(op==Var)return rop;
  COperation r;
  r.op=op;r.pvar=pvar;r.pvarval=pvarval;r.ValC=ValC;r.pfunc=pfunc;
  if(mmb1!=NULL)r.mmb1=new COperation(mmb1->Substitute(var,rop));else r.mmb1=NULL;
  if(mmb2!=NULL)r.mmb2=new COperation(mmb2->Substitute(var,rop));else r.mmb2=NULL;
  return r;
}

COperation COperation::Diff(const CVar& var) const //This is d / dz
{
  if(!ContainVar(var))return 0.0;
  if(op==Var)return 1.0;
  COperation **ppop1,op2;int i,j;
  switch(op){
  case Juxt:return(mmb1->Diff(var),mmb2->Diff(var));
  case Add:return(mmb1->Diff(var)+mmb2->Diff(var));
  case Sub:return(mmb1->Diff(var)-mmb2->Diff(var));
  case Opp:return(-mmb2->Diff(var));
  case Mult:return((*mmb1)*(mmb2->Diff(var))+(*mmb2)*(mmb1->Diff(var)));
  case Div:if(mmb2->ContainVar(var))return(((*mmb2)*(mmb1->Diff(var))-(*mmb1)*(mmb2->Diff(var)))/((*mmb2)^2));
  else return(mmb1->Diff(var)/(*mmb2));
  case Pow:if(mmb2->ContainVar(var))return((*this)*(log(*mmb1)*mmb2->Diff(var)+
						    (*mmb2)*mmb1->Diff(var)/(*mmb1)));else
						      return (*mmb2)*mmb1->Diff(var)*((*mmb1)^(*mmb2-1));
  case Sqrt:return(mmb2->Diff(var)/(2*sqrt(*mmb2)));
  case NthRoot:{COperation interm=(*mmb2)^(1/(*mmb1));return interm.Diff(var);};
  case E10:{COperation interm=(*mmb1)*(10^(*mmb2));return interm.Diff(var);};;
  case Ln:return (mmb2->Diff(var)/(*mmb2));
  case Exp:return (mmb2->Diff(var)*(*this));
  case Sin:return (mmb2->Diff(var)*cos(*mmb2));
  case Cos:return (-mmb2->Diff(var)*sin(*mmb2));
  case Tg:return (mmb2->Diff(var)*(1+((*this)^2)));
  case Atan:return(mmb2->Diff(var)/(1+((*mmb2)^2)));
  case Asin:return(mmb2->Diff(var)/sqrt(1-((*mmb2)^2)));
  case Acos:return(-mmb2->Diff(var)/sqrt(1-((*mmb2)^2)));
  case Abs:return ((conj(*mmb2)*mmb2->Diff(var)+(*mmb2)*conj(mmb2->DiffConj(var)))/(2*abs(*mmb2)));
  case Conj:return(conj(mmb2->DiffConj(var)));
  case Real:return ((mmb2->Diff(var)+conj(mmb2->DiffConj(var)))/2);
  case Imag:return ((mmb2->Diff(var)-conj(mmb2->DiffConj(var)))/double_complex(0,2));
  case Arg:return (double_complex(0,-.5)*(mmb2->Diff(var)/(*mmb2)-conj(mmb2->DiffConj(var)/(*mmb2))));
  case Fun:if(pfunc->type==-1||pfunc->type==0)return ErrVal;
    if(pfunc->nvars==0)return 0.;
    else if(pfunc->op.NMembers()>1){
      j=pfunc->op.NMembers();
      ppop1=new COperation*[j];
      for(i=0;i<j;i++)ppop1[i]=new COperation(NthMember(i+1).Diff(var));
      op2=ApplyOperator(pfunc->nvars,ppop1,&operator,);
      for(i=0;i<pfunc->nvars;i++)delete ppop1[i];
      delete[]ppop1;
      return op2;  
    }else{
      ppop1=new COperation*[2*pfunc->nvars];
      for(i=0;i<pfunc->nvars;i++){
	ppop1[i]=new COperation(pfunc->op.Diff(*pfunc->ppvar[i]));
	for(j=0;j<pfunc->nvars;j++)
	  *ppop1[i]=ppop1[i]->Substitute(*pfunc->ppvar[j],mmb2->NthMember(j+1));
	*ppop1[i]=(mmb2->NthMember(i+1).Diff(var))*(*ppop1[i]);
      }
      for(i=pfunc->nvars;i<2*pfunc->nvars;i++){
	  ppop1[i]=new COperation(pfunc->op.DiffConj(*pfunc->ppvar[i-pfunc->nvars]));
	  for(j=0;j<pfunc->nvars;j++)
	    *ppop1[i]=ppop1[i]->Substitute(*pfunc->ppvar[j],mmb2->NthMember(j+1));
	  *ppop1[i]=((conj(mmb2->NthMember(i+1-pfunc->nvars))).Diff(var))*(*ppop1[i]);
      }
      op2=ApplyOperator(2*pfunc->nvars,ppop1,&::operator+);
      for(i=0;i<2*pfunc->nvars;i++)delete ppop1[i];
      delete[]ppop1;
      return op2;
      // In the obtained expression, f' will have been replaced with its expression but f will remain pointing to itself ; this could cause some trouble if changing f afterwards
    }
  default:return ErrVal;
  };
}

COperation COperation::DiffConj(const CVar& var) const // This one is d / d conj(z)
{
  if(!ContainVar(var))return 0.0;
  if(op==Var)return 0.0;
  COperation **ppop1,op2;int i,j;
  switch(op){
  case Juxt:return(mmb1->DiffConj(var),mmb2->DiffConj(var));
  case Add:return(mmb1->DiffConj(var)+mmb2->DiffConj(var));
  case Sub:return(mmb1->DiffConj(var)-mmb2->DiffConj(var));
  case Opp:return(-mmb2->DiffConj(var));
  case Mult:return((*mmb1)*(mmb2->DiffConj(var))+(*mmb2)*(mmb1->DiffConj(var)));
  case Div:if(mmb2->ContainVar(var))return(((*mmb2)*(mmb1->DiffConj(var))-(*mmb1)*(mmb2->DiffConj(var)))/((*mmb2)^2));
  else return(mmb1->DiffConj(var)/(*mmb2));
  case Pow:if(mmb2->ContainVar(var))return((*this)*(log(*mmb1)*mmb2->DiffConj(var)+
						    (*mmb2)*mmb1->DiffConj(var)/(*mmb1)));else
						      return (*mmb2)*mmb1->DiffConj(var)*((*mmb1)^(*mmb2-1));
  case Sqrt:return(mmb2->DiffConj(var)/(2*sqrt(*mmb2)));
  case NthRoot:{COperation interm=(*mmb2)^(1/(*mmb1));return interm.DiffConj(var);};
  case E10:{COperation interm=(*mmb1)*(10^(*mmb2));return interm.DiffConj(var);};;
  case Ln:return (mmb2->DiffConj(var)/(*mmb2));
  case Exp:return (mmb2->DiffConj(var)*(*this));
  case Sin:return (mmb2->DiffConj(var)*cos(*mmb2));
  case Cos:return (-mmb2->DiffConj(var)*sin(*mmb2));
  case Tg:return (mmb2->DiffConj(var)*(1+((*this)^2)));
  case Atan:return(mmb2->DiffConj(var)/(1+((*mmb2)^2)));
  case Asin:return(mmb2->DiffConj(var)/sqrt(1-((*mmb2)^2)));
  case Acos:return(-mmb2->DiffConj(var)/sqrt(1-((*mmb2)^2)));
  case Abs:return ((conj(*mmb2)*mmb2->DiffConj(var)+(*mmb2)*conj(mmb2->Diff(var)))/(2*abs(*mmb2)));
  case Conj:return(conj(mmb2->Diff(var)));
  case Real:return ((mmb2->DiffConj(var)+conj(mmb2->Diff(var)))/2);
  case Imag:return ((mmb2->DiffConj(var)-conj(mmb2->Diff(var)))/double_complex(0,2));
  case Arg:return (double_complex(0,-.5)*(mmb2->DiffConj(var)/(*mmb2)-conj(mmb2->Diff(var)/(*mmb2))));
  case Fun:if(pfunc->type==-1||pfunc->type==0)return ErrVal;
    if(pfunc->nvars==0)return 0.;
    else if(pfunc->op.NMembers()>1){
      j=pfunc->op.NMembers();
      ppop1=new COperation*[j];
      for(i=0;i<j;i++)ppop1[i]=new COperation(NthMember(i+1).DiffConj(var));
      op2=ApplyOperator(pfunc->nvars,ppop1,&operator,);
      for(i=0;i<pfunc->nvars;i++)delete ppop1[i];
      delete[]ppop1;
      return op2;  
    }else{
      ppop1=new COperation*[2*pfunc->nvars];
      for(i=0;i<pfunc->nvars;i++){
	ppop1[i]=new COperation(pfunc->op.DiffConj(*pfunc->ppvar[i]));
	for(j=0;j<pfunc->nvars;j++)
	  *ppop1[i]=ppop1[i]->Substitute(*pfunc->ppvar[j],mmb2->NthMember(j+1));
	*ppop1[i]=(conj(mmb2->NthMember(i+1).Diff(var)))*(*ppop1[i]);
      }
      for(i=pfunc->nvars;i<2*pfunc->nvars;i++){
	ppop1[i]=new COperation(pfunc->op.Diff(*pfunc->ppvar[i-pfunc->nvars]));
	for(j=0;j<pfunc->nvars;j++)
	  *ppop1[i]=ppop1[i]->Substitute(*pfunc->ppvar[j],mmb2->NthMember(j+1));
	*ppop1[i]=(mmb2->NthMember(i+1-pfunc->nvars).DiffConj(var))*(*ppop1[i]);
      }
      op2=ApplyOperator(2*pfunc->nvars,ppop1,&::operator+);
      for(i=0;i<2*pfunc->nvars;i++)delete ppop1[i];
      delete[]ppop1;
      return op2;
      // In the obtained expression, f' will have been replaced with its expression but f will remain pointing to itself ; this could cause some trouble if changing f afterwards
    }
  default:return ErrVal;
  };
}

char* formatreal(double x)
{
  char*s=new char[20];
  if(x==0)s[0]=0;
  else if(x==(double)3.141592653589793238462643383279L)sprintf(s,"pi");
  else sprintf(s,"%.8g",x);
  return s;
}

char* formatimag(double x)
{
  char*s=new char[20];
  if(x==0)s[0]=0;
  else if(x==1)sprintf(s,"i");
  else if(x==-1)sprintf(s,"-i");
  else if(x==(double)3.141592653589793238462643383279L)sprintf(s,"i pi");
  else if(x==(double)(-3.141592653589793238462643383279L))sprintf(s,"-i pi");
  else sprintf(s,"%.8g i",x);
  return s;
}

char* PrettyPrint(double_complex x)
{
  char*s=new char[30],*s1=formatreal(real(x)),*s2=formatimag(imag(x));
  if(!strlen(s1)&&!strlen(s2))sprintf(s,"0");
  else if(x==double_complex(0,1))sprintf(s,"i");
  else if(!strlen(s1))sprintf(s,"(%s)",s2);
  else if(!strlen(s2))sprintf(s,"%s",s1);
  else if(imag(x)>0)sprintf(s,"(%s+%s)",s1,s2);
  else sprintf(s,"(%s%s)",s1,s2);
  delete s1, delete s2;
  return s;
}

char* COperation::Expr() const
{
  char*s=NULL,*s1=NULL,*s2=NULL;int n=10;signed char f=0,g=0;
  if(op==Fun)if(strlen(pfunc->name)>4)n+=strlen(pfunc->name)-4;
  if(mmb1!=NULL){s1=mmb1->Expr();n+=strlen(s1);f=IsFunction(mmb1->op);}
  if(mmb2!=NULL){s2=mmb2->Expr();n+=strlen(s2);g=IsFunction(mmb2->op);}
  s=new char[n];
  switch(op){
  case Num:return PrettyPrint(ValC);
  case Var:return CopyStr(pvar->name);
  case Juxt:sprintf(s,"%s , %s",s1,s2);break;
  case Add:
    f=f||(mmb1->op==Juxt);
    g=g||(mmb2->op==Juxt);
    if(f&&g)sprintf(s,"(%s)+(%s)",s1,s2);else
      if(f)sprintf(s,"(%s)+%s",s1,s2);else
	if(g)sprintf(s,"%s+(%s)",s1,s2);else
	  sprintf(s,"%s+%s",s1,s2);
    break;
  case Sub:
    f=f||(mmb1->op==Juxt);
    g=g||(mmb2->op==Juxt||mmb2->op==Add||mmb2->op==Sub);
    if(f&&g)sprintf(s,"(%s)-(%s)",s1,s2);else
      if(f)sprintf(s,"(%s)-%s",s1,s2);else
	if(g)sprintf(s,"%s-(%s)",s1,s2);else
	  sprintf(s,"%s-%s",s1,s2);
    break;
  case Opp:
    if(mmb2->op==Add||mmb2->op==Sub||mmb2->op==Juxt)sprintf(s,"-(%s)",s2);else
      sprintf(s,"-%s",s2);
    break;
  case Mult:
    f=f||(mmb1->op==Juxt||mmb1->op==Add||mmb1->op==Sub||mmb1->op==Opp);
    g=g||(mmb2->op==Juxt||mmb2->op==Add||mmb2->op==Sub||mmb2->op==Opp);
    if(f&&g)sprintf(s,"(%s)*(%s)",s1,s2);else
      if(f)sprintf(s,"(%s)*%s",s1,s2);else
	if(g)sprintf(s,"%s*(%s)",s1,s2);else
	  sprintf(s,"%s*%s",s1,s2);
    break;
  case Div:
    f=f||(mmb1->op==Juxt||mmb1->op==Add||mmb1->op==Sub||mmb1->op==Opp||mmb1->op==Div);
    g=g||(mmb2->op==Juxt||mmb2->op==Add||mmb2->op==Sub||mmb2->op==Opp||mmb2->op==Mult||mmb2->op==Div);
    if(f&&g)sprintf(s,"(%s)/(%s)",s1,s2);else
      if(f)sprintf(s,"(%s)/%s",s1,s2);else
	if(g)sprintf(s,"%s/(%s)",s1,s2);else
	  sprintf(s,"%s/%s",s1,s2);
    break;
  case Pow:
    f=(mmb1->op!=Num&&mmb1->op!=Var);
    g=(mmb2->op!=Num&&mmb2->op!=Var);
    if(f&&g)sprintf(s,"(%s)^(%s)",s1,s2);else
      if(f)sprintf(s,"(%s)^%s",s1,s2);else
	if(g)sprintf(s,"%s^(%s)",s1,s2);else
	  sprintf(s,"%s^%s",s1,s2);
    break;
  case Sqrt:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"sqrt(%s)",s2);
    else sprintf(s,"sqrt %s",s2);
    break;
  case NthRoot:
    f=(mmb1->op!=Num&&mmb1->op!=Var);
    g=(mmb2->op!=Num&&mmb2->op!=Var);
    if(f&&g)sprintf(s,"(%s)#(%s)",s1,s2);else
      if(f)sprintf(s,"(%s)#%s",s1,s2);else
	if(g)sprintf(s,"%s#(%s)",s1,s2);else
	  sprintf(s,"%s#%s",s1,s2);
    break;
  case E10:
    f=(mmb1->op!=Num&&mmb1->op!=Var);
    g=(mmb2->op!=Num&&mmb2->op!=Var);
    if(f&&g)sprintf(s,"(%s)E(%s)",s1,s2);else
      if(f)sprintf(s,"(%s)E%s",s1,s2);else
	if(g)sprintf(s,"%sE(%s)",s1,s2);else
	  sprintf(s,"%sE%s",s1,s2);
    break;
  case Ln:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"log(%s)",s2);
    else sprintf(s,"log %s",s2);
    break;
  case Exp:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"exp(%s)",s2);
    else sprintf(s,"exp %s",s2);
    break;
  case Sin:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"sin(%s)",s2);
    else sprintf(s,"sin %s",s2);
    break;
  case Cos:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"cos(%s)",s2);
    else sprintf(s,"cos %s",s2);
    break;
  case Tg:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"tan(%s)",s2);
    else sprintf(s,"tan %s",s2);
    break;
  case Atan:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"atan(%s)",s2);
    else sprintf(s,"atan %s",s2);
    break;
  case Asin:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"asin(%s)",s2);
    else sprintf(s,"asin %s",s2);
    break;
  case Acos:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"acos(%s)",s2);
    else sprintf(s,"acos %s",s2);
    break;
  case Abs:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"abs(%s)",s2);
    else sprintf(s,"abs %s",s2);
    break;
  case Real:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"real(%s)",s2);
    else sprintf(s,"real %s",s2);
    break;
  case Imag:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"imag(%s)",s2);
    else sprintf(s,"imag %s",s2);
    break;
  case Conj:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"conj(%s)",s2);
    else sprintf(s,"conj %s",s2);
    break;
  case Arg:
    g=(mmb2->op!=Num&&mmb2->op!=Var&&!g);
    if(g)sprintf(s,"arg(%s)",s2);
    else sprintf(s,"arg %s",s2);
    break;
  case Fun:
    sprintf(s,"%s(%s)",pfunc->name,s2);
    break;
  default:return CopyStr("Error");
  };
  if(s1!=NULL)delete[] s1;if(s2!=NULL)delete[] s2;
  return s;
}

const double sqrtmaxfloat=sqrt(DBL_MAX);
const double sqrtminfloat=sqrt(DBL_MIN);

void Addition(double_complex*&p)
{if(*p==ErrVal||norm(*p)>sqrtmaxfloat){*(--p)=ErrVal;return;};
if(*(--p)==ErrVal||norm(*p)>sqrtmaxfloat){*p=ErrVal;return;};
*p+=(*(p+1));}
void Soustraction(double_complex*&p)
{if(*p==ErrVal||norm(*p)>sqrtmaxfloat){*(--p)=ErrVal;return;};
if(*(--p)==ErrVal||norm(*p)>sqrtmaxfloat){*p=ErrVal;return;};
*p-=(*(p+1));}
void Multiplication(double_complex*&p)
{if(norm(*p)<sqrtminfloat){*--p=0;return;};
if(*p==ErrVal||norm(*p)>sqrtmaxfloat){*(--p)=ErrVal;return;};
if(norm(*(--p))<sqrtminfloat){*p=0;return;};
if(*p==ErrVal||norm(*p)>sqrtmaxfloat){*p=ErrVal;return;};
*p*=(*(p+1));}
void Division(double_complex*&p)
{if(norm(*p)<sqrtminfloat||*p==ErrVal||norm(*p)>sqrtmaxfloat)
  {*(--p)=ErrVal;return;};
if(norm(*(--p))<sqrtminfloat)*p=0;else if(*p==ErrVal||norm(*p)>sqrtmaxfloat)
  {*p=ErrVal;return;};
 *p/=(*(p+1));}
void Puissance(double_complex*&p)
{double_complex v2=*p--,v1=*p;
if(v2==ErrVal||v1==ErrVal||norm(v2)*log(norm(v1))>DBL_MAX_EXP){*p=ErrVal;return;};
*p=(v1==0.?0:pow(v1,v2));}
void RacineN(double_complex*&p)
{double_complex v2=*p--,v1=*p;
if(v1==ErrVal||v2==ErrVal||v1==0.||norm(v2)*log(norm(v1))<DBL_MIN_EXP){*p=ErrVal;return;};
*p=pow(v2,double_complex(1,0)/v1);return;}
void Puiss10(double_complex*&p)
{if(norm(*p)<sqrtminfloat){*(--p)=0;return;};
if(*p==ErrVal||norm(*p)>DBL_MAX_10_EXP){*(--p)=ErrVal;return;};
if(norm(*(--p))<sqrtminfloat)*p=0;else if(*p==ErrVal||norm(*p)>sqrtmaxfloat)
	{*p=ErrVal;return;};
*p*=pow(double_complex(10.),*(p+1));}
void NextVal(double_complex*&){}
void  RFunc(double_complex*&){}
void  JuxtF(double_complex*&){}
void Absolu(double_complex*&p){*p=((*p==ErrVal)?ErrVal:norm(*p));}
void Oppose(double_complex*&p){*p=((*p==ErrVal)?ErrVal:-*p);}
void Reelle(double_complex*&p){*p=((*p==ErrVal)?ErrVal:real(*p));}
void Imaginaire(double_complex*&p){*p=((*p==ErrVal)?ErrVal:imag(*p));}
void Conjugue(double_complex*&p){*p=((*p==ErrVal)?ErrVal:conj(*p));}
void ArcSinus(double_complex*&p)
{*p=((*p==ErrVal)?ErrVal:asin(*p));}
void ArcCosinus(double_complex*&p)
{*p=((*p==ErrVal||*p==double_complex(0,1)||*p==double_complex(0,-1))?ErrVal:acos(*p));}
void ArcTangente(double_complex*&p)
{*p=((*p==ErrVal)?ErrVal:atan(*p));}
void Logarithme(double_complex*&p)
{*p=((*p==ErrVal||*p==0.)?ErrVal:log(*p));}
void Argument(double_complex*&p)
{*p=((*p==ErrVal||*p==0.)?ErrVal:arg(*p));}
void Exponentielle(double_complex*&p)
{*p=((*p==ErrVal||norm(*p)>DBL_MAX_EXP)?ErrVal:exp(*p));}
void Sinus(double_complex*&p)
{*p=((*p==ErrVal||norm(*p)>DBL_MAX_EXP)?ErrVal:sin(*p));}
void Tangente(double_complex*&p)
{*p=((*p==ErrVal||norm(*p)>DBL_MAX_EXP)?ErrVal:tan(*p));}
void Cosinus(double_complex*&p)
{*p=((*p==ErrVal||norm(*p)>DBL_MAX_EXP)?ErrVal:cos(*p));}
void Racine(double_complex*&p)
{*p=((*p==ErrVal||norm(*p)>sqrtmaxfloat)?ErrVal:sqrt(*p));}
void FonctionError(double_complex*&p){*p=ErrVal;}
inline void ApplyRFunc(PCFunction rf,double_complex*&p)
{p-=rf->nvars-1;*p=rf->Val(p);}

double_complex COperation::Val() const
{
  pfoncld*p1=pinstr;double_complex**p2=pvals,*p3=ppile-1;PCFunction*p4=pfuncpile;
  for(;*p1!=NULL;p1++)
    if(*p1==&NextVal)*(++p3)=**(p2++);else 
      if(*p1==&RFunc) ApplyRFunc(*(p4++),p3);
      else (**p1)(p3);
  return *p3;
}

void BCDouble(pfoncld*&pf,pfoncld*pf1,pfoncld*pf2,
	      double_complex**&pv,double_complex**pv1,double_complex**pv2,
	      double_complex*&pp,double_complex*pp1,double_complex*pp2,
	      CFunction**&prf,CFunction**prf1,CFunction**prf2,
	      pfoncld f)
{
  pfoncld*pf3,*pf4=pf1;long n1,n2;
  for(n1=0;*pf4!=NULL;pf4++,n1++);for(n2=0,pf4=pf2;*pf4!=NULL;pf4++,n2++);
  pf=new pfoncld[n1+n2+2];
  for(pf3=pf,pf4=pf1;*pf4!=NULL;pf3++,pf4++)*pf3=*pf4;
  for(pf4=pf2;*pf4!=NULL;pf3++,pf4++)*pf3=*pf4;
  *pf3++=f;*pf3=NULL;//delete[]pf1,pf2;
  double_complex**pv3,**pv4=pv1;
  for(n1=0;*pv4!=NULL;pv4++,n1++);for(n2=0,pv4=pv2;*pv4!=NULL;pv4++,n2++);
  pv=new double_complex*[n1+n2+1];
  for(pv3=pv,pv4=pv1;*pv4!=NULL;pv3++,pv4++)*pv3=*pv4;
  for(pv4=pv2;*pv4!=NULL;pv3++,pv4++)*pv3=*pv4;
  *pv3=NULL;//delete[]pv1,pv2;
  double_complex*pp3,*pp4=pp1;
  for(n1=0;*pp4!=ErrVal;pp4++,n1++);for(n2=0,pp4=pp2;*pp4!=ErrVal;pp4++,n2++);
  pp=new double_complex[n1+n2+1];  // Really need to add and not to take max(n1,n2) in case of Juxt operator
  for(pp3=pp,pp4=pp1;*pp4!=ErrVal;pp3++,pp4++)*pp3=0;
  for(pp4=pp2;*pp4!=ErrVal;pp3++,pp4++)*pp3=0;
  *pp3=ErrVal;//delete[]pp1,pp2;
  PCFunction*prf3,*prf4=prf1;
  for(n1=0;*prf4!=NULL;prf4++,n1++);for(n2=0,prf4=prf2;*prf4!=NULL;prf4++,n2++);
  prf=new PCFunction[n1+n2+1];
  for(prf3=prf,prf4=prf1;*prf4!=NULL;prf3++,prf4++)*prf3=*prf4;
  for(prf4=prf2;*prf4!=NULL;prf3++,prf4++)*prf3=*prf4;
  *prf3=NULL;//delete[]prf1,prf2;
}

void BCSimple(pfoncld*&pf,pfoncld*pf1,double_complex**&pv,double_complex**pv1,
	double_complex*&pp,double_complex*pp1,CFunction**&prf,CFunction**prf1,pfoncld f)
{
  pfoncld*pf3,*pf4=pf1;long n;
  for(n=0;*pf4!=NULL;pf4++,n++);
  pf=new pfoncld[n+2];
  for(pf4=pf1,pf3=pf;*pf4!=NULL;pf3++,pf4++)*pf3=*pf4;
  *pf3++=f;*pf3=NULL;//delete[]pf1;
  double_complex**pv3,**pv4=pv1;
  for(n=0;*pv4!=NULL;pv4++,n++);
  pv=new double_complex*[n+1];
  for(pv3=pv,pv4=pv1;*pv4!=NULL;pv3++,pv4++)*pv3=*pv4;
  *pv3=NULL;//delete[]pv1;
  double_complex*pp3,*pp4=pp1;
  for(n=0;*pp4!=ErrVal;pp4++,n++);
  pp=new double_complex[n+1];
  for(pp3=pp,pp4=pp1;*pp4!=ErrVal;pp3++,pp4++)*pp3=0;
  *pp3=ErrVal;//delete[]pp1;
  CFunction**prf3,**prf4=prf1;
  for(n=0;*prf4!=NULL;prf4++,n++);
  prf=new CFunction*[n+1];
  for(prf3=prf,prf4=prf1;*prf4!=NULL;prf3++,prf4++)*prf3=*prf4;
  *prf3=NULL;//delete[]prf1;
}

void BCFun(pfoncld*&pf,pfoncld*pf1,double_complex**&pv,double_complex**pv1,
	double_complex*&pp,double_complex*pp1,CFunction**&prf,CFunction**prf1,PCFunction rf)
{
  pfoncld*pf3,*pf4=pf1;long n;
  for(n=0;*pf4!=NULL;pf4++,n++);
  pf=new pfoncld[n+2];
  for(pf4=pf1,pf3=pf;*pf4!=NULL;pf3++,pf4++)*pf3=*pf4;
  *pf3++=&RFunc;*pf3=NULL;//delete[]pf1;
  double_complex**pv3,**pv4=pv1;
  for(n=0;*pv4!=NULL;pv4++,n++);
  pv=new double_complex*[n+1];
  for(pv3=pv,pv4=pv1;*pv4!=NULL;pv3++,pv4++)*pv3=*pv4;
  *pv3=NULL;//delete[]pv1;
  double_complex*pp3,*pp4=pp1;
  for(n=0;*pp4!=ErrVal;pp4++,n++);
  pp=new double_complex[n+1];
  for(pp3=pp,pp4=pp1;*pp4!=ErrVal;pp3++,pp4++)*pp3=0;
  *pp3=ErrVal;//delete[]pp1;
  PCFunction*prf3,*prf4=prf1;
  for(n=0;*prf4!=NULL;prf4++,n++);
  prf=new PCFunction[n+2];
  for(prf4=prf1,prf3=prf;*prf4!=NULL;prf3++,prf4++)*prf3=*prf4;
  *prf3++=rf;*prf3=NULL;//delete[]pf1;
}

void COperation::BuildCode()
{
  //  if(mmb1!=NULL)mmb1->BuildCode();if(mmb2!=NULL)mmb2->BuildCode();
  if(pinstr!=NULL){delete[]pinstr;pinstr=NULL;}
  if(pvals!=NULL){delete[]pvals;pvals=NULL;}
  if(ppile!=NULL){delete[]ppile;ppile=NULL;}
  if(pfuncpile!=NULL){delete[]pfuncpile;pfuncpile=NULL;}
  switch(op){
  case ErrOp:pinstr=new pfoncld[2];pinstr[0]=&NextVal;pinstr[1]=NULL;
    pvals=new double_complex*[2];pvals[0]=new double_complex(ErrVal);pvals[1]=NULL;
    ppile=new double_complex[2];ppile[0]=0;ppile[1]=ErrVal;
    pfuncpile=new CFunction*[1];pfuncpile[0]=NULL;
    break;
  case Num:pinstr=new pfoncld[2];pinstr[0]=&NextVal;pinstr[1]=NULL;
    pvals=new double_complex*[2];pvals[0]=new double_complex(ValC);pvals[1]=NULL;
    ppile=new double_complex[2];ppile[0]=0;ppile[1]=ErrVal;
    pfuncpile=new CFunction*[1];pfuncpile[0]=NULL;break;
  case Var:pinstr=new pfoncld[2];pinstr[0]=&NextVal;pinstr[1]=NULL;
    pvals=new double_complex*[2];pvals[0]=pvarval;pvals[1]=NULL;
    ppile=new double_complex[2];ppile[0]=0;ppile[1]=ErrVal;
    pfuncpile=new CFunction*[1];pfuncpile[0]=NULL;break;
  case Juxt:BCDouble(pinstr,mmb1->pinstr,mmb2->pinstr,
		     pvals,mmb1->pvals,mmb2->pvals,ppile,mmb1->ppile,mmb2->ppile,pfuncpile,mmb1->pfuncpile,mmb2->pfuncpile,&JuxtF);
  break;case Add:BCDouble(pinstr,mmb1->pinstr,mmb2->pinstr,
		     pvals,mmb1->pvals,mmb2->pvals,ppile,mmb1->ppile,mmb2->ppile,pfuncpile,mmb1->pfuncpile,mmb2->pfuncpile,&Addition);
  break;case Sub:BCDouble(pinstr,mmb1->pinstr,mmb2->pinstr,
			  pvals,mmb1->pvals,mmb2->pvals,ppile,mmb1->ppile,mmb2->ppile,pfuncpile,mmb1->pfuncpile,mmb2->pfuncpile,&Soustraction);
  break;case Mult:BCDouble(pinstr,mmb1->pinstr,mmb2->pinstr,
			   pvals,mmb1->pvals,mmb2->pvals,ppile,mmb1->ppile,mmb2->ppile,pfuncpile,mmb1->pfuncpile,mmb2->pfuncpile,&Multiplication);
  break;case Div:BCDouble(pinstr,mmb1->pinstr,mmb2->pinstr,
			  pvals,mmb1->pvals,mmb2->pvals,ppile,mmb1->ppile,mmb2->ppile,pfuncpile,mmb1->pfuncpile,mmb2->pfuncpile,&Division);
  break;case Pow:BCDouble(pinstr,mmb1->pinstr,mmb2->pinstr,
			  pvals,mmb1->pvals,mmb2->pvals,ppile,mmb1->ppile,mmb2->ppile,pfuncpile,mmb1->pfuncpile,mmb2->pfuncpile,&Puissance);
  break;case NthRoot:BCDouble(pinstr,mmb1->pinstr,mmb2->pinstr,
			      pvals,mmb1->pvals,mmb2->pvals,ppile,mmb1->ppile,mmb2->ppile,pfuncpile,mmb1->pfuncpile,mmb2->pfuncpile,&RacineN);
  break;case E10:BCDouble(pinstr,mmb1->pinstr,mmb2->pinstr,
			  pvals,mmb1->pvals,mmb2->pvals,ppile,mmb1->ppile,mmb2->ppile,pfuncpile,mmb1->pfuncpile,mmb2->pfuncpile,&Puiss10);
  break;case Opp:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			  ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Oppose);
  break;case Sin:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			  ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Sinus);
  break;case Sqrt:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			   ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Racine);
  break;case Ln:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			 ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Logarithme);
  break;case Exp:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			  ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Exponentielle);
  break;case Cos:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			  ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Cosinus);
  break;case Tg:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			 ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Tangente);
  break;case Atan:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			   ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&ArcTangente);
  break;case Asin:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			   ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&ArcSinus);
  break;case Acos:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			   ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&ArcCosinus);
  break;case Abs:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			  ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Absolu);
  break;case Real:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			   ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Reelle);
  break;case Imag:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			   ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Imaginaire);
  break;case Conj:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			   ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Conjugue);
  break;case Arg:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			  ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&Argument);
  break;case Fun:BCFun(pinstr,mmb2->pinstr,pvals,mmb2->pvals,ppile,
		       mmb2->ppile,pfuncpile,mmb2->pfuncpile,pfunc);
  break;default:BCSimple(pinstr,mmb2->pinstr,pvals,mmb2->pvals,
			 ppile,mmb2->ppile,pfuncpile,mmb2->pfuncpile,&FonctionError);
  }
}
