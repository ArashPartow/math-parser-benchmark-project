
#ifndef FORMEL_GENERATOR_H
#define FORMEL_GENERATOR_H

#include "stdlib.h"

class FormelGenerator
{
public:

   int Make(char *Buffer, int Length, int Items, int NumberOfVars);

private:

   char   *buf;
   int len, pos, items, vars;

   void Make();
   void MakeVar();

   int    RandInt(int number);
   void   RandFunction();
   char   RandOp();
   bool   RandBool();
   double RandDouble();
};

#endif
