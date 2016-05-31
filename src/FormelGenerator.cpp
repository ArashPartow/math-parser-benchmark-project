#include <cstdio>

#include "FormelGenerator.h"

int FormelGenerator::Make(char *Buffer, int Length, int Items, int NumberOfVars)
{
  pos = 0;

  items = Items;
  len = Length;
  buf = Buffer;

  if (NumberOfVars > 20) vars = 20;
  else vars = NumberOfVars;

  Make();

  Buffer[pos] = 0;

  return Items - items;
}

bool FormelGenerator::RandBool()
{
  return rand() & 1;
}

int FormelGenerator::RandInt(int number)
{
  return (int)((double)rand() * (double)number / ((double)(RAND_MAX) + 1));
}

double FormelGenerator::RandDouble()
{
  return (double)rand() / ((double)(RAND_MAX) + 1.0);
}

char FormelGenerator::RandOp()
{
  switch (RandInt(5))
  {
  case 1: return '-';
  case 2: return '*';
  case 3: return '/';
  default: return '+';
  }
}

void FormelGenerator::Make()
{
  if (items-- > 0)
  {
    if (pos >= len - 10) return;

    switch (RandInt(8))
    {
    case 1:
      buf[pos++] = '(';
      Make();
      buf[pos++] = RandOp();
      MakeVar();
      buf[pos++] = ')';

      break;

    case 2:
      buf[pos++] = '(';
      MakeVar();
      buf[pos++] = RandOp();
      Make();
      buf[pos++] = ')';

      break;

    case 3:
    case 4:
      RandFunction();
      buf[pos++] = '(';
      Make();
      buf[pos++] = ')';
      break;

    default:
      buf[pos++] = '(';
      Make();
      buf[pos++] = RandOp();
      Make();
      buf[pos++] = ')';

      break;

    }
  }
  else
  {
    MakeVar();
  }
}

void FormelGenerator::RandFunction()
{
  switch (RandInt(3))
  {
  case 1:
    buf[pos++] = 'c';
    buf[pos++] = 'o';
    buf[pos++] = 's';
    break;

  case 2:
//    buf[pos++] = 'a';
    buf[pos++] = 't';
    buf[pos++] = 'a';
    buf[pos++] = 'n';
    break;

  default:
    buf[pos++] = 's';
    buf[pos++] = 'i';
    buf[pos++] = 'n';
  }
}

void FormelGenerator::MakeVar()
{
  char      str[16];
  double d;
  int    i;

  switch (RandInt(4))
  {
//  case 1:
    default:
    if (vars > 0)
    {
      buf[pos++] = RandInt(vars) + 'a';
      break;
    }
    break;

  case 2:
    if (RandBool())
    {
      buf[pos++] = 'e';
    }
    else
    {
      buf[pos++] = 'p';
      buf[pos++] = 'i';
    }

    break;

//  default:
    case 1:
// <ibg> ich will keine negativen werte weil der fparser die nicht nimmt
//    d = RandDouble() * 4.0 - 2.0;
    d = RandDouble() * 4.0;

    if (d < 0) sprintf(str,"(%.2f)",d);
    else sprintf(str,"%.2f",d);

    for (i = 0; str[i]; i++) buf[pos++] = str[i];
  }
}
