// g++ -Wall -Wextra -pedantic -ansi -O3 selftest.cpp [-DMPFR -lmpfr]

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

/// Includes and defines
#include <iostream>
#include "../atmsp.h"
#define MAXDIFF 0.00001


/// Choose your basic parser type here
#if defined(MPFR)
#include <mpfr.h>
#include "../extra/real.hpp"
#define ATMSP_MPFR_BITS 256
typedef mpfr::real<ATMSP_MPFR_BITS> PTYPE;
#define FEQUAL(a,b) ( (abs((a)-(b)) < MAXDIFF) ? 1 : 0 )
#else
typedef double PTYPE;
#define FEQUAL(a,b) ( (std::abs((a)-(b)) < MAXDIFF) ? 1 : 0 )
#endif


/// Structure for list entries. Just a helper here
template <typename T>
struct LISTENTRY {
	std::string name;
	T val;
	LISTENTRY() { name = "";  val = (T)0; }
	LISTENTRY(const std::string &Name)        { name = Name; val = (T)0; }
	LISTENTRY(const std::string &Name, T Val) { name = Name; val = Val;  }
	bool operator == (const LISTENTRY &Name) const { return name == Name.name; }
};


/// List for test-samples
static ATMSP_LIST<LISTENTRY<PTYPE>, 128> list;


/// Add test samples to list
static void addSamples() {

	list.push(LISTENTRY<PTYPE>("x", 1.0));
	list.push(LISTENTRY<PTYPE>("y", 2.0));
	list.push(LISTENTRY<PTYPE>("z", 3.0));
	list.push(LISTENTRY<PTYPE>("u", 4.0));
	list.push(LISTENTRY<PTYPE>("v", 5.0));

	list.push(LISTENTRY<PTYPE>("1", 1.0));
	list.push(LISTENTRY<PTYPE>("1.23", 1.23));
	list.push(LISTENTRY<PTYPE>("--1.23-(-2)-2", 1.23));
	list.push(LISTENTRY<PTYPE>("-1.23-(-2)-2", -1.23));
	list.push(LISTENTRY<PTYPE>("-((1.23-((-2))-2))", -1.23));
	list.push(LISTENTRY<PTYPE>("--1.23--2-2", 1.23));
	list.push(LISTENTRY<PTYPE>("123.45e-2", 123.45e-2));
	list.push(LISTENTRY<PTYPE>("123.45e-2+20", 123.45e-2+20.0));
	list.push(LISTENTRY<PTYPE>("-123.45e-2+20", 18.7655));

	list.push(LISTENTRY<PTYPE>("--x--y", 3.0));
	list.push(LISTENTRY<PTYPE>("---y+z", 1.0));
	list.push(LISTENTRY<PTYPE>("---y-(-z*x)", 1.0));
	list.push(LISTENTRY<PTYPE>("---y--z", 1.0));
	list.push(LISTENTRY<PTYPE>("---y--z*x", 1.0));
	list.push(LISTENTRY<PTYPE>("--x--y*--2", 5.0));
	list.push(LISTENTRY<PTYPE>("x+y+z+u+v", 15.0));
	list.push(LISTENTRY<PTYPE>("-2*x+y+z+u+v", 12.0));
	list.push(LISTENTRY<PTYPE>("-2*x+y-z-2*u+4/v", -10.2));
	list.push(LISTENTRY<PTYPE>("x/y+z/u+v*x", 6.25));
	list.push(LISTENTRY<PTYPE>("x/y+z/-u+v*-x", -5.25));
	list.push(LISTENTRY<PTYPE>("x/y+z/-(u*(y-x))+v*-x", -5.25));
	list.push(LISTENTRY<PTYPE>("x/y+z/-(u*(-x+y))+v*-x", -5.25));
	list.push(LISTENTRY<PTYPE>("x/-2*y+3*z/-u+v*-x", -8.25));

	list.push(LISTENTRY<PTYPE>("(---y+z)*sin($pi/2)", 1.0));
	list.push(LISTENTRY<PTYPE>("(---y+z)*(2*$e/($e*y))", 1.0));
	list.push(LISTENTRY<PTYPE>("($pi*2)", 3.1415926535897932384*2.0));
	list.push(LISTENTRY<PTYPE>("(1+$e)", 3.7182818284590452354));
	list.push(LISTENTRY<PTYPE>("sqrt(y-x)*($con1+$con2^(y-x))", 33.0));
	list.push(LISTENTRY<PTYPE>("  s qr t (($ co n 1+ x) ^  y )  ", 12.0));
	list.push(LISTENTRY<PTYPE>("  - -s qr t (($ co n1  + x) ^  --y )  ", 12.0));

	list.push(LISTENTRY<PTYPE>("y^2", 4.0));
	list.push(LISTENTRY<PTYPE>("y^3", 8.0));
	list.push(LISTENTRY<PTYPE>("y^2^3", 256.0));
	list.push(LISTENTRY<PTYPE>("2^2^3", 256.0));
	list.push(LISTENTRY<PTYPE>("y^2^3*2", 512.0));
	list.push(LISTENTRY<PTYPE>("y^2^3/2", 128.0));
	list.push(LISTENTRY<PTYPE>("-y^2", -4.0));
	list.push(LISTENTRY<PTYPE>("-y^3", -8.0));
	list.push(LISTENTRY<PTYPE>("y^-2", 0.25));
	list.push(LISTENTRY<PTYPE>("y^(-2)", 0.25));
	list.push(LISTENTRY<PTYPE>("y^(-2)+x", 1.25));
	list.push(LISTENTRY<PTYPE>("y^-2+1", 1.25));
	list.push(LISTENTRY<PTYPE>("y^-2*2", 0.5));
	list.push(LISTENTRY<PTYPE>("y^-3", 0.125));
	list.push(LISTENTRY<PTYPE>("-y^-2", -0.25));
	list.push(LISTENTRY<PTYPE>("-y^-3", -0.125));
	list.push(LISTENTRY<PTYPE>("x/-2^y+3^z/-u+v*-x", -12.0));
	list.push(LISTENTRY<PTYPE>("x/-2^y+(3^z)/-u+v*-x", -12.0));
	list.push(LISTENTRY<PTYPE>("-x/(-2^y+3)^z/-u+v*-x", -5.25));
	list.push(LISTENTRY<PTYPE>("x/(2^y+3)^(z/u+v)*-x", -1.3825672650832439555e-05));
	list.push(LISTENTRY<PTYPE>("-(x/(2^y+3)^(z/u+v)*-x)", 1.3825672650832439555e-05));

	list.push(LISTENTRY<PTYPE>("y*log($e)", 2.0));
	list.push(LISTENTRY<PTYPE>("y*log2(2)", 2.0));
	list.push(LISTENTRY<PTYPE>("-y*log($e)", -2.0));
	list.push(LISTENTRY<PTYPE>("-y*log2(2)", -2.0));
	list.push(LISTENTRY<PTYPE>("y*log10(z+7)", 2.0));
	list.push(LISTENTRY<PTYPE>("-y*log10(z+7)", -2.0));
	list.push(LISTENTRY<PTYPE>("(y*log($e))^-2+1", 1.25));
	list.push(LISTENTRY<PTYPE>("(y*log2(2))^-2+1", 1.25));
	list.push(LISTENTRY<PTYPE>("(y*log10(z+7))^-2+1", 1.25));
	list.push(LISTENTRY<PTYPE>("-(y*log($e))^-2+1", 0.75));
	list.push(LISTENTRY<PTYPE>("-(y*log2(2))^-2+1", 0.75));
	list.push(LISTENTRY<PTYPE>("-(y*log10(z+7))^-2+1", 0.75));

	list.push(LISTENTRY<PTYPE>("-2*(x+y)+z+u+v", 6.0));
	list.push(LISTENTRY<PTYPE>("-2*(x/y)+z+u+v", 11.0));
	list.push(LISTENTRY<PTYPE>("-(-2*(x/y)+z)*u+v", -3.0));
	list.push(LISTENTRY<PTYPE>("-(-2*(x/y)+z)*(u+u/v)", -9.6));
	list.push(LISTENTRY<PTYPE>("-(-2^(x/y)+z)*(u^u/v)", -81.19226560649752855));
	list.push(LISTENTRY<PTYPE>("-(-2^(x/y)^z)*(u^u/v)", 55.833995912461197975));
	list.push(LISTENTRY<PTYPE>("-(-2^(x/y)^z)*(u^(u/v))", 3.3058012726168470863));
	list.push(LISTENTRY<PTYPE>("x+(-2^(x/y)^z)/(u^(u/v))", 0.64026660499729493026));
	list.push(LISTENTRY<PTYPE>("x*-(z-y)+(-2^(x/y)^z)/(u^(u/v))", -1.3597333950027050697));
	list.push(LISTENTRY<PTYPE>("-x*-(-z-y)+(-2^(x/y)^z)/(u^(u/-v))", -8.3058012726168470863));
	list.push(LISTENTRY<PTYPE>("-x*-(-z-y+(-2^(x/y)^z)/(u^(u/-v)))", -8.3058012726168470863));
	list.push(LISTENTRY<PTYPE>("-(x*-(-z*(y+((-2^(x/y)^z)/(u^(u/-v))))))", 3.9174038178505412588));
	list.push(LISTENTRY<PTYPE>("-(x*(y+z/-z^(2+x))-(-z*(y+((-2^(x/y)^z)/(u^(u/-v))))))", 2.0285149289616524193));

	list.push(LISTENTRY<PTYPE>("sin(x)+1", 1.8414709848078965049));
	list.push(LISTENTRY<PTYPE>("sin(((((y))-x)))+1+(0)", 1.8414709848078965049));
	list.push(LISTENTRY<PTYPE>("sin(cos(x))/tan(x)", 0.33028939716960203921));
	list.push(LISTENTRY<PTYPE>("sin(cos(x))^tan(cos(x+sin(x)))", 1.199741439038031432));
	list.push(LISTENTRY<PTYPE>("sin(cos(tan(cos(x+sin(x))))^sin(x))^tan(cos(x+sin(x)))", 1.054443437377038828));

	list.push(LISTENTRY<PTYPE>("sig(x+y-z)", 0.0));
	list.push(LISTENTRY<PTYPE>("-sig(x-z)", 1.0));
	list.push(LISTENTRY<PTYPE>("-sig(x-z)^5", 1.0));
	list.push(LISTENTRY<PTYPE>("sig(x+z)", 1.0));
	list.push(LISTENTRY<PTYPE>("sig((sin(x)+1)/z)", 1.0));
	list.push(LISTENTRY<PTYPE>("min(sig(x+y-z),sin(x)+1)", 0.0));
	list.push(LISTENTRY<PTYPE>("max(-sig(x+z),-2*(x+y)+z+u+v)", 6.0));
	list.push(LISTENTRY<PTYPE>("min(-x/(-2^y+3)^z/-u+v*-x,x/-2^y+3^z/-u+v*-x)", -12.0));
	list.push(LISTENTRY<PTYPE>("min(min(-x/(-2^y+3)^z/-u+v*-x,x/-2^y+3^z/-u+v*-x),-sin(cos(x))/tan(x))", -12.0));
	list.push(LISTENTRY<PTYPE>("min(min(-x/(-2^y+3)^z/-u+v*-x,x/-(2^y)+3^z/-u+v*-x),-sin(cos(x))/tan(x))", -12.0));

	list.push(LISTENTRY<PTYPE>("exp(log($pi))", 3.1415926535897932384));
	list.push(LISTENTRY<PTYPE>("-exp(log($pi))", -3.1415926535897932384));
	list.push(LISTENTRY<PTYPE>("abs(exp(log($pi)))", 3.1415926535897932384));
	list.push(LISTENTRY<PTYPE>("abs(-exp(log($pi)))", 3.1415926535897932384));
	list.push(LISTENTRY<PTYPE>("--abs(--log2(2))*y", 2.0));
	list.push(LISTENTRY<PTYPE>("--abs(--log10(--10))*y", 2.0));
	list.push(LISTENTRY<PTYPE>("floor(sin(x)+1)", 1.0));

	list.push(LISTENTRY<PTYPE>("+x+y", 3.0));
	list.push(LISTENTRY<PTYPE>("+1*y", 2.0));
	list.push(LISTENTRY<PTYPE>("-1*y", -2.0));
	list.push(LISTENTRY<PTYPE>("+x*+y", 2.0));
	list.push(LISTENTRY<PTYPE>("3.3-((+x)*(-y))", 5.3));
	list.push(LISTENTRY<PTYPE>("3.3+((((+x/2))+((+y/2))))", 4.8));
	list.push(LISTENTRY<PTYPE>("+x^+y", 1.0));
	list.push(LISTENTRY<PTYPE>("-y^+y", -4.0));
	list.push(LISTENTRY<PTYPE>("-x^+y/2.0", -0.5));
	list.push(LISTENTRY<PTYPE>("-2.0*z^+y", -18.0));
	list.push(LISTENTRY<PTYPE>("-x*+y", -2.0));
}


/// main()
int main() {

	addSamples();

	std::cout << "Read in " << list.size() << " test samples" << std::endl;
	std::cout << "Start testing now ..." << std::endl;

	for (size_t i=0; i<list.size(); i++) {

		// Parser/bytecode instances
		ATMSP<PTYPE> pa;
		ATMSB<PTYPE> bc;
		size_t err;

		if ( (err = pa.addConstant("$con1", 11)) ) {
			std::cerr << list[i].name << "\t" << list[i].val << std::endl;
			std::cerr << "ADDING CONSTANT FAILED!\n ";
			exit(err);
		}

		if ( (err = pa.addConstant("$con2", 22))  ) {
			std::cerr << list[i].name << "\t" << list[i].val << std::endl;
			std::cerr << "ADDING CONSTANT FAILED!\n ";
			exit(err);
		}

		if ( (err = pa.parse(bc, list[i].name, "x,y,z,u,v")) ) {
			std::cerr << list[i].name << "\t" << list[i].val << std::endl;
			std::cerr << "PARSING FAILED! " << pa.errMessage(err) << std::endl;
			exit(err);
		}

		bc.var[0] = 1.0;   // x value
		bc.var[1] = 2.0;   // y value
		bc.var[2] = 3.0;   // z value
		bc.var[3] = 4.0;   // u value
		bc.var[4] = 5.0;   // v value

		PTYPE tmp;
		if ( !FEQUAL(tmp=bc.run(), list[i].val) ) {
			std::cerr << "\n" << list[i].name << "\t Result is : " << tmp << std::endl;
			std::cerr << "BAD RESULT! Expected was : " << list[i].val << std::endl << std::endl;
			exit(err);
		}
	
	}

	std::cout << "SUCCESS! All " << list.size() << " tests passed" << std::endl;
	#if defined(_MSC_VER)
	char dummy;
	std::cout << "Enter Ctrl-C to exit" << std::endl;
	std::cin >> dummy;
	#endif

	return 0;
}
