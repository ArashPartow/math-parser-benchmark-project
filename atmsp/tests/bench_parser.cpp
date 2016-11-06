// g++ -Wall -Wextra -pedantic -ansi -O3 -ffast-math -flto -fwhole-program bench_parser.cpp

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

/** No execution times here. Just measures time for parsing/evaluations     **/

#include <iostream>
#include "../atmsp.h"


/** Choose basic parser type to bench here !!! **/
typedef double PTYPE;


/** Benchmark **/
static void bench(const size_t loops) {

	// Parser/bytecode instances
	ATMSP<PTYPE> pa;
	ATMSB<PTYPE> bc;

	// Expression
	std::string exps("((3*x^4-7*x^3+2*x^2-4*x+10) - (4*y^3+2*y^2-10*y+2))*10");
	std::cout << "\"" << exps << "\"" << " parsed " << loops << " x times\n";

	// And parse
	size_t err;
	for (size_t i=0; i<loops; i++) {
		if ( (err = pa.parse(bc, exps, "x, y")) ) {
			std::cerr << "Error: " << pa.errMessage(err) << std::endl;
			exit(err);
		}
	}

	// Show result
	bc.var[0] = 1;
	bc.var[1] = 2;
	std::cout << "Evaluated result: " << bc.run() << std::endl;
}


/** USAGE: ./bench [num-of-loops]
 ** *********************************************************************** **/
int main(int argc, char *argv[]) {

	// Default/arbitrary benchmark loops
	argc==2 ? bench(atol(argv[1])) : bench(100000);

	return 0;
}
