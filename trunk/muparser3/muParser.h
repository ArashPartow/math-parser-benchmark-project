#ifndef MU_PARSER_H
#define MU_PARSER_H

//--- Standard includes ---------------------------------------------------------------------------
#include <vector>
#include <algorithm>
#include <numeric>

//--- Parser includes -----------------------------------------------------------------------------
#include "muParserBase.h"
#include "muParserMath.h"

MUP_NAMESPACE_START

  //-----------------------------------------------------------------------------------------------
  /** \brief Basic implementation of the parser.
  */
  template<typename TValue, typename TString = std::string>
  class Parser : public ParserBase<TValue, TString>
  {
  public:

    //---------------------------------------------------------------------------------------------
    /** \brief Default constructor of the parser object.

      Preconfigures the parser according to its underlying valuetype.
    */
    Parser()
      :ParserBase()
    {
      if (!details::value_traits<typename TValue>::IsInteger())
      {
        AddValIdent(IsFloatVal);
      }
      else
      {
        AddValIdent(IsIntVal); // lowest priority
        AddValIdent(IsBinVal);
        AddValIdent(IsHexVal); // highest priority
      }

      InitFun();
      InitConst();
      InitOprt();
    }

  private:

    //---------------------------------------------------------------------------------------------
    void InitFun() 
    {
      if (!details::value_traits<TValue>::IsInteger())
      {
        // trigonometric functions
        DefineFun( _SL("sin"),   MathImpl<TValue, TString>::Sin, 1);
        DefineFun( _SL("cos"),   MathImpl<TValue, TString>::Cos, 1);
        DefineFun( _SL("tan"),   MathImpl<TValue, TString>::Tan, 1);
      
        // arcus functions
        DefineFun( _SL("asin"),  MathImpl<TValue, TString>::ASin,  1);
        DefineFun( _SL("acos"),  MathImpl<TValue, TString>::ACos,  1);
        DefineFun( _SL("atan"),  MathImpl<TValue, TString>::ATan,  1);
        DefineFun( _SL("atan2"), MathImpl<TValue, TString>::ATan2, 2);
      
        // hyperbolic functions
        DefineFun( _SL("sinh"),  MathImpl<TValue, TString>::Sinh, 1);
        DefineFun( _SL("cosh"),  MathImpl<TValue, TString>::Cosh, 1);
        DefineFun( _SL("tanh"),  MathImpl<TValue, TString>::Tanh, 1);
      
        // arcus hyperbolic functions
        DefineFun( _SL("asinh"), MathImpl<TValue, TString>::ASinh, 1);
        DefineFun( _SL("acosh"), MathImpl<TValue, TString>::ACosh, 1);
        DefineFun( _SL("atanh"), MathImpl<TValue, TString>::ATanh, 1);
      
        // Logarithm functions
        DefineFun( _SL("log2"),  MathImpl<TValue, TString>::Log2,  1);
        DefineFun( _SL("log10"), MathImpl<TValue, TString>::Log10, 1);
        DefineFun( _SL("log"),   MathImpl<TValue, TString>::Log,   1);
        DefineFun( _SL("ln"),    MathImpl<TValue, TString>::Log,   1);

        // misc
        DefineFun( _SL("exp"),   MathImpl<TValue, TString>::Exp,  1);
        DefineFun( _SL("sqrt"),  MathImpl<TValue, TString>::Sqrt, 1);
        DefineFun( _SL("sign"),  MathImpl<TValue, TString>::Sign, 1);
        DefineFun( _SL("rint"),  MathImpl<TValue, TString>::Rint, 1);
        DefineFun( _SL("avg"),   MathImpl<TValue, TString>::Avg, -1);
      }

      DefineFun( _SL("abs"),   MathImpl<TValue, TString>::Abs,  1);
      
      // Functions with variable number of arguments
      DefineFun( _SL("sum"),   MathImpl<TValue, TString>::Sum, -1);
      DefineFun( _SL("min"),   MathImpl<TValue, TString>::Min, -1);
      DefineFun( _SL("max"),   MathImpl<TValue, TString>::Max, -1);
    }

    //---------------------------------------------------------------------------------------------
    void InitConst() 
    {
      if (!details::value_traits<TValue>::IsInteger())
      {
        DefineConst( _SL("_pi"), MathImpl<TValue, TString>::c_pi);
        DefineConst( _SL("_e"),  MathImpl<TValue, TString>::c_e);
      }
    }

    //---------------------------------------------------------------------------------------------
    void InitOprt() 
    {
      DefineInfixOprt( _SL("-"), MathImpl<TValue, TString>::UnaryMinus);
//      DefineInfixOprt( _SL("+"), MathImpl<TValue, TString>::UnaryPlus);

      DefineOprt( _SL("&&"), MathImpl<TValue, TString>::And,       prLOGIC);
      DefineOprt( _SL("||"), MathImpl<TValue, TString>::Or,        prLOGIC);

      DefineOprt( _SL("<"),  MathImpl<TValue, TString>::Less,      prCMP);
      DefineOprt( _SL(">"),  MathImpl<TValue, TString>::Greater,   prCMP);
      DefineOprt( _SL("<="), MathImpl<TValue, TString>::LessEq,    prCMP);
      DefineOprt( _SL(">="), MathImpl<TValue, TString>::GreaterEq, prCMP);
      DefineOprt( _SL("=="), MathImpl<TValue, TString>::Equal,     prCMP);
      DefineOprt( _SL("!="), MathImpl<TValue, TString>::NotEqual,  prCMP);

      DefineOprt( _SL("+"), MathImpl<TValue, TString>::Add, prADD_SUB);
      DefineOprt( _SL("-"), MathImpl<TValue, TString>::Sub, prADD_SUB);
      DefineOprt( _SL("*"), MathImpl<TValue, TString>::Mul, prMUL_DIV, oaRIGHT);

      if (!details::value_traits<TValue>::IsInteger())
      {
        DefineOprt( _SL("/"), MathImpl<TValue, TString>::Div, prMUL_DIV);
        DefineOprt( _SL("^"), MathImpl<TValue, TString>::Pow, prPOW, oaRIGHT);
      }
    }

  protected:

    //---------------------------------------------------------------------------
    static int IsFloatVal(typename const TString::value_type* a_szExpr, int *a_iPos, TValue *a_fVal)
    {
      TValue fVal(0);

      stringstream_type stream(a_szExpr);
      stream.seekg(0);
      stream >> fVal;
      stringstream_type::pos_type iEnd = stream.tellg(); // Position after reading

      if (iEnd==(stringstream_type::pos_type)-1)
        return 0;

      *a_iPos += (int)iEnd;
      *a_fVal = fVal;
      return 1;
    }

    //---------------------------------------------------------------------------------------------
    /** \brief Check a given position in the expression for the presence of 
               an integer value. 
        \param a_szExpr Pointer to the expression string
        \param [in/out] a_iPos Pointer to an interger value holding the current parsing 
               position in the expression.
        \param [out] a_fVal Pointer to the position where the detected value shall be stored.
    */
    static int IsIntVal(typename const TString::value_type* a_szExpr, int *a_iPos, TValue *a_fVal)
    {
      TString buf(a_szExpr);
      std::size_t pos = buf.find_first_not_of(_SL("0123456789"));

      if (pos==std::string::npos)
        return 0;

      stringstream_type stream( buf.substr(0, pos ) );
      int iVal(0);

      stream >> iVal;
      if (stream.fail())
        return 0;
      
      stringstream_type::pos_type iEnd = stream.tellg();   // Position after reading
      if (stream.fail())
        iEnd = stream.str().length();  

      if (iEnd==(stringstream_type::pos_type)-1)
        return 0;

      *a_iPos += (int)iEnd;
      *a_fVal = (TValue)iVal;
      return 1;
    }

    //---------------------------------------------------------------------------------------------
    /** \brief Check a given position in the expression for the presence of 
               a hex value. 
        \param a_szExpr Pointer to the expression string
        \param [in/out] a_iPos Pointer to an interger value holding the current parsing 
               position in the expression.
        \param [out] a_fVal Pointer to the position where the detected value shall be stored.

      Hey values must be prefixed with "0x" in order to be detected properly.
    */
    static int IsHexVal(typename const TString::value_type* a_szExpr, int *a_iPos, TValue *a_fVal)
    {
      if (a_szExpr[1]==0 || (a_szExpr[0]!='0' || a_szExpr[1]!='x') ) 
        return 0;

      unsigned iVal(0);

      // New code based on streams for UNICODE compliance:
      stringstream_type::pos_type nPos(0);
      stringstream_type ss(a_szExpr + 2);
      ss >> std::hex >> iVal;
      nPos = ss.tellg();

      if (nPos==(stringstream_type::pos_type)0)
        return 1;

      *a_iPos += (int)(2 + nPos);
      *a_fVal = (TValue)iVal;
      return 1;
    }

    //---------------------------------------------------------------------------------------------
    static int IsBinVal(typename const TString::value_type* a_szExpr, int *a_iPos, TValue *a_fVal)
    {
      if (a_szExpr[0]!='#') 
        return 0;

      unsigned iVal(0), 
               iBits(sizeof(iVal)*8),
               i(0);

      for (i=0; (a_szExpr[i+1]=='0' || a_szExpr[i+1]=='1') && i<iBits; ++i)
        iVal |= (int)(a_szExpr[i+1]=='1') << ((iBits-1)-i);

      if (i==0) 
        return 0;

      if (i==iBits)
        throw ParserError<TString>(_SL("Binary to integer conversion error (overflow)."));

      *a_fVal = (unsigned)(iVal >> (iBits-i) );
      *a_iPos += i+1;

      return 1;
    }

  };
} // namespace mu

#endif

