// g++ -Wall -Wextra -pedantic -ansi -O3 -ffast-math -flto -fwhole-program bench_bytecode.cpp [-DMPFR -lmpfr]

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

/** General test-suite to test OSS-parsers against different expressions    **/

#include <iostream>
#include "../atmsp.h"
#include "timers.h"


/// Choose your basic parser type here
#if defined(MPFR)
#include <mpfr.h>
#include "../extra/real.hpp"
#define ATMSP_MPFR_BITS 256
typedef mpfr::real<ATMSP_MPFR_BITS> PTYPE;
#else
typedef double PTYPE;
#endif


/** Build up expression list to benchmark **/
ATMSP_LIST<std::string, 100> list;

// Here expressions for comparison with fparser
static void addSamples() {
	list.push("3+6");
	list.push("5-3");
	list.push("3^2");
	list.push("1-2-3-4");
	list.push("abs(-3)");
	list.push("sin(3)");

	list.push("x+6");
	list.push("x-3");
	list.push("x^2");
	list.push("x-2-3-4");
	list.push("x-y-z-4");
	list.push("abs(-x)");
	list.push("sin(x)");

	list.push("x^3");
	list.push("x^4");
	list.push("x^2+1");
	list.push("x^4+y^3+z^2");

	list.push("sqrt(x)");
	list.push("-sqrt(x)");
	list.push("sin(2*x)");
	list.push("sin($pi*x)");
	list.push("sin($pi*x^2)");
	list.push("sin($pi^2*x^2)");

	list.push("abs(-sqrt(x))");
	list.push("abs(-sqrt(x))^2");
	list.push("sqrt(abs(-sqrt(x))+2)");
	list.push("sqrt(abs(-sqrt(x))^4)");

	list.push("2*(x-y-z-1)");
	list.push("$pi*(x-y-z-1)");
	list.push("x+2*y+3*z+1");
	list.push("x-2*y-3*z-1");
	list.push("x^2+y^2");

	list.push("max(2,x)");
	list.push("max(2,x)^2");
	list.push("(max(2,x)^2-min(2,y))^2");
}


/** Benchmark **/
static void bench(const size_t loops) {

	double sec, minSec;
	PTYPE res;

	// Parser/bytecode instances
	ATMSP<PTYPE> pa;
	ATMSB<PTYPE> bc;

	// Sweep over all expressions
	std::cout << "Each expression is evaluated " << loops << " x times:\n";
	for (size_t i=0; i<list.size(); i++) {

		// Error check for parsing/bytecode generation
		size_t err;
		if ( (err=pa.parse(bc, list[i], "x, y, z")) ) {
			std::cerr << list[i] << " failed: " << pa.errMessage(err) << std::endl;
			exit(err);
		}

		// Some settings out of inner loops
		bc.var[0] = 1.0; bc.var[1] = 2.0; bc.var[2] = 3.0;
		minSec = 10.0e10;

		// Get fastest run out of a few
		for (size_t j=0; j<10; j++) {
			TIMERS t;
			for (size_t k=0; k<loops; k++) res = bc.run();
			sec = t.stop();
			if ( sec < minSec ) minSec = sec;
		}

		// Set locale for better import in OO spredsheet
		std::locale locale("");
		std::cout.imbue(locale);

		// Use ";" as delimiter for OO import
		std::cout << minSec << "\t;\'" << list[i] << std::endl;
	}
}


/** USAGE: ./bench [num-of-loops]
 ** *********************************************************************** **/
int main(int argc, char *argv[]) {

	// Build benchmark list
	addSamples();

	// Default/arbitrary benchmark loops
	argc==2 ? bench(atol(argv[1])) : bench(1000000);

	return 0;
}
