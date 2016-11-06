// g++ -Wall -Wextra -pedantic -ansi -O3 -flto -fwhole-program main.cpp [-DCOMPLEX] [-DMPFR -lmpfr]

/** *********************************************************************** **
 **                                                                         **
 ** Copyright (C) 1989-2013 Heinz van Saanen                                **
 **                                                                         **
 ** This file may be used under the terms of the GNU General Public         **
 ** License version 3 or later as published by the Free Software Foundation **
 ** and appearing in the file LICENSE.GPL included in the packaging of      **
 ** this file.                                                              **
 **                                                                         **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE **
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR        **
 ** PURPOSE.                                                                **
 **                                                                         **
 ** *********************************************************************** **/

/// Includes
#include <iostream>    // Usual I/O
#include <iomanip>     // setprecision()
#include "atmsp.h"     // Our parser


/// Choose your basic parser type here
#if !defined(COMPLEX) && !defined(MPFR)

// Default could be any int8-int128 or any float
typedef double PTYPE;

// Use complex? Template type may be any float
#elif defined(COMPLEX)

#include <complex>
typedef std::complex<double> PTYPE;

// Use Gnu MPFR multiprecision? Here with 256 bit precision
#elif defined(MPFR)

#include <mpfr.h>
#include "./extra/real.hpp"
#define ATMSP_MPFR_BITS 256
typedef mpfr::real<ATMSP_MPFR_BITS> PTYPE;

#endif


/// Only needed for extra paranoia NaN/inf checks and float/complex-types
/// NOTE: do NOT compile with -ffast-math or similar switches then
#if !defined(MPFR)
#include <limits>
static bool hasNumErr(PTYPE a) {
   if ( a != a ||
       a ==  std::numeric_limits<PTYPE>::infinity() ||
       a == -std::numeric_limits<PTYPE>::infinity() ) return true;
   return false;
}
#endif


/// A simple test function. Defines variables x,y,z as x=1, y=2, z=3 always
static void test(const char *s, size_t rounds=0) {

   // Bytecode instance with SAME basic type as the parser
   ATMSB<PTYPE> byteCode;

   // Parsing/bytecode generation with error check. In a scope here JUST to
   // demonstrate that the parser-instance itself is NOT needed later on
   {
      ATMSP<PTYPE> parser;
      size_t err = parser.parse(byteCode, s, "x, y, z");
      if ( err ) {
         std::cerr << parser.errMessage(err) << std::endl;
         exit(err);
      }
   }

   // Set variable values for x,y,z. Here always 1,2,3
   byteCode.var[0] = 1.0;
   byteCode.var[1] = 2.0;
   byteCode.var[2] = 3.0;

   // Calculate/bench and show result
   PTYPE res = byteCode.run();
   if ( rounds ) for (size_t i=0; i<rounds; i++) res = byteCode.run();
   std::cout << std::setprecision(25) << ">>> Result = " <<  res << std::endl;

   // Need to be picky? Then check NaN/inf-errors with built-in flag. This is
   // fast and "catches" all common errors like x/0, sqrt(-3), asin(123) ...
   if ( byteCode.fltErr )
      std::cerr << "Float error fetched by ATMSP default-check" << std::endl;

   // Extra paranoia about NaN/inf float/complex errors? Due to the nature of
   // floats, the built-in check may not catch every case. Here how to fetch
   // these rare errors of more theoretical nature. But as they may happen:
   #if !defined(MPFR)
   if ( hasNumErr(res) )
      std::cerr << "Float error fetched by extra-check" << std::endl;
   #endif
}


/** Example usage:
 **
 ** ./atmsp '2*3+4'
 ** ./atmsp '2*3+4' 10000000
 ** ./atmsp '2^x+y+sqrt(z^-3)'
 ** ./atmsp 'sqrt((3+$i) * (4+2*$i)) ^ y'
 **
 ** Note: variables are always set to: x=1, y=2, z=3
 ** *********************************************************************** **/
int main (int argc, char *argv[]) {

   // Check parameter string from command line
   if ( argc<2 ) {
      #ifdef _MSC_VER
      std::cout << "Example usage: " << argv[0] << " \"2.5+x+y-z*$pi+3\" [benchmark-rounds]\n";
      #else
      std::cout << "Example usage: " << argv[0] << " \'2.5+x+y-z*$pi+3\' [benchmark-rounds]\n";
      #endif
      return 1;
   }

   // And call our test function w/wo benchmark-mode
   argc==2 ? test(argv[1]) : test(argv[1], atol(argv[2]));

   return 0;
}
