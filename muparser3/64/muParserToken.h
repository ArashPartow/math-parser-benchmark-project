/*
                 __________                                      
    _____   __ __\______   \_____  _______  ______  ____ _______ 
   /     \ |  |  \|     ___/\__  \ \_  __ \/  ___/_/ __ \\_  __ \
  |  Y Y  \|  |  /|    |     / __ \_|  | \/\___ \ \  ___/ |  | \/
  |__|_|  /|____/ |____|    (____  /|__|  /____  > \___  >|__|   
        \/                       \/            \/      \/        
  Copyright (C) 2004-2012 Ingo Berg

  Permission is hereby granted, free of charge, to any person obtaining a copy of this 
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify, 
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
  permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or 
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
*/
#ifndef MU_PARSER_TOKEN_H
#define MU_PARSER_TOKEN_H

#include "muParserDef.h"


MUP_NAMESPACE_START

  //-----------------------------------------------------------------------------------------------
  /** \brief A class representing a parser token.
  */
  template<typename TValue, typename TString>
  class Token
  {
  public:

    /** \brief Data for functions and operators. */
    struct SFunDef 
    {
      typename parser_types<TValue, TString>::fun_type ptr, ptr2, ptr3;          ///> function pointers for up to three successive functions
      int argc, argc2, argc3;        ///> number of arguments
      int prec;                      ///> precedence (only for operators)
      EOprtAssociativity asoc;       ///> associativity (only for operators)
    };

    /** \brief Data for value tokens. */
    struct SValDef 
    {
      // erster wert
      TValue *ptr;
      TValue  mul;
      TValue  fixed;

      // zweiter wert
      TValue *ptr2;
      TValue  mul2;
      TValue  fixed2;
    };

    /** \brief Data for built in operators. */
    struct SOprtDef 
    {
      TValue *ptr;
      int offset;
    };

    ECmdCode Cmd;
    TString Ident;
    mutable int StackPos;
    TValue *Stack;

    union
    {
      SValDef Val;
      SFunDef Fun;
      SOprtDef Oprt;
    };

    //---------------------------------------------------------------------------------------------
    void SetVal(TValue v, const TString &sIdent = TString())
    {
      Cmd = cmVAL;
      Ident = sIdent;
      Val.fixed = v;
      Val.mul = 0;
      Val.ptr = &ParserBase<TValue, TString>::g_NullValue;
    }

    //---------------------------------------------------------------------------------------------
    void SetFun(ECmdCode cmd, 
                typename parser_types<TValue, TString>::fun_type pFun, 
                int argc, 
                EOprtAssociativity asoc, 
                int prec, 
                const TString &sIdent = TString())
    {
      Token<TValue, TString> tok;
      Cmd = cmd;
      Ident = sIdent;
      Fun.asoc = asoc;
      Fun.prec = prec;
      Fun.argc  = argc;
      Fun.argc2 = 0;
      Fun.argc3 = 0;
      Fun.ptr  = pFun;
      Fun.ptr2 = nullptr;
      Fun.ptr3 = nullptr;
    }

    //---------------------------------------------------------------------------------------------
    void Set(ECmdCode eCmd, const TString &sIdent = TString())
    {
      Cmd = eCmd;
      Ident = sIdent;
      Fun.ptr = nullptr;
    }

    //---------------------------------------------------------------------------------------------
    void ResetVariablePart()
    {
      assert(Cmd==cmVAL_EX);
      Val.mul = 0;
      Val.ptr = &ParserBase<TValue, TString>::g_NullValue;
    }

    //---------------------------------------------------------------------------------------------
    void Finalize(TValue *pStack)
    {
      Stack = &pStack[StackPos];
      if (Val.mul==0 && Cmd==cmVAL_EX && Val.ptr2==nullptr)
        Cmd = cmVAL;
      else if (Val.fixed==0 && Val.mul==1 && Cmd==cmVAL_EX  && Val.ptr2==nullptr)
        Cmd = cmVAR;
    }
  };
} // namespace

#endif