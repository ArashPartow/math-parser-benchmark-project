/*
@file
addDefaults.h
Helper-functions to add default operators, functions, etc. to a compiler

Copyright 2017 Till Heinzel

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once
#include "Compiler.h"

namespace metl
{
	template<class... Ts>
	void setDefaultOperatorPrecedences(Compiler<Ts...>& c)
	{

		c.setOperatorPrecedence("!=", 10);
		c.setOperatorPrecedence("==", 10);

		c.setOperatorPrecedence("<", 9);
		c.setOperatorPrecedence(">", 9);
		c.setOperatorPrecedence("<=", 9);
		c.setOperatorPrecedence(">=", 9);

		c.setOperatorPrecedence("+", 6);
		c.setOperatorPrecedence("-", 6);
		c.setOperatorPrecedence("*", 5);
		c.setOperatorPrecedence("/", 5);
		c.setUnaryOperatorPrecedence("-", 3);
		c.setUnaryOperatorPrecedence("+", 3);
		c.setOperatorPrecedence("^", 2, ASSOCIATIVITY::RIGHT);
	}

	// sets default binary operators {+,-,*,/} with the corresponding call in C++ 
	template<class T1, class T2, class... Ts>
	void addDefaultOperators(Compiler<Ts...>& c)
	{
		setDefaultOperatorPrecedences(c);

		auto plus = [](auto left, auto right) { return left + right; };
		auto minus = [](auto left, auto right) { return left - right; };
		auto mul = [](auto left, auto right) { return left * right; };
		auto div = [](auto left, auto right) { return left / right; };

		c.template setOperator<T1, T2>(std::string("+"), plus);
		c.template setOperator<T1, T2>("-", minus);
		c.template setOperator<T1, T2>("*", mul);
		c.template setOperator<T1, T2>("/", div);
	}

	// sets default unary operator {+,-} and binary operator {+,-,*,/} with the corresponding call in C++ 
	template<class T, class... Ts>
	void addDefaultOperators(Compiler<Ts...>& c)
	{
		setDefaultOperatorPrecedences(c);

		auto unaryPlus = [](auto a) { return a; };
		auto unaryMinus = [](auto a) { return -a; };

		c.template setUnaryOperator<T>(std::string("+"), unaryPlus);
		c.template setUnaryOperator<T>("-", unaryMinus);

		addDefaultOperators<T, T>(c);
	}


	template<class T, class... Ts>
	void addBasicFunctions(Compiler<Ts...>& c)
	{
		c.template setFunction<T>("exp", [](auto a) {return exp(a); });
		c.template setFunction<T>("sqrt", [](auto a) {return sqrt(a); });
		c.template setFunction<T>("exp2", [](auto a) {return exp2(a); });
		c.template setFunction<T>("log", [](auto a) {return log(a); });
		c.template setFunction<T>("log2", [](auto a) {return log2(a); });
		c.template setFunction<T>("log10", [](auto a) {return log10(a); });

	}

	template<class T, class... Ts>
	void addTrigFunctions(Compiler<Ts...>& c)
	{
		c.template setFunction<T>("sin", [](auto a) {return sin(a); });
		c.template setFunction<T>("cos", [](auto a) {return cos(a); });
		c.template setFunction<T>("tan", [](auto a) {return tan(a); });
		c.template setFunction<T>("asin", [](auto a) {return asin(a); });
		c.template setFunction<T>("acos", [](auto a) {return acos(a); });
		c.template setFunction<T>("atan", [](auto a) {return atan(a); });
		c.template setFunction<T>("sinh", [](auto a) {return sinh(a); });
		c.template setFunction<T>("cosh", [](auto a) {return cosh(a); });
		c.template setFunction<T>("tanh", [](auto a) {return tanh(a); });
		c.template setFunction<T>("asinh", [](auto a) {return asinh(a); });
		c.template setFunction<T>("acosh", [](auto a) {return acosh(a); });
		c.template setFunction<T>("atanh", [](auto a) {return atanh(a); });
	}

	namespace detail
	{
		template<class T>
		constexpr T recursive_pow(const T t, const int exponent)
		{
			if (exponent == 0) return T(1);
			if (exponent == 1) return t;

			const auto intermediate = recursive_pow(t, exponent / 2);

			if (exponent % 2) return intermediate * intermediate*t; // odd
			return intermediate * intermediate; // even


		}
	}

	// sets defaults for basic types (currently int, 
	template<class Grammar, class Converter, class... Ts>
	void setDefaults(Compiler<Grammar, Converter, Ts...>& c)
	{
		using intType = decltype(c.impl_.literalConverters_.toInt.f(std::declval<std::string>()));
		using realType = decltype(c.impl_.literalConverters_.toReal.f(std::declval<std::string>()));

		// defaults with intType
		constexpr_if(IsInList<intType, Ts...>(), [&c](auto _)
		{
			addDefaultOperators<intType>(c);
			constexpr_if(std::is_integral<intType>{}, [&c](auto _)
			{
				c.template setFunction<intType>("abs", [](const auto& a) {return std::abs(a); });
			});
		});

		// defaults with realType
		constexpr_if(IsInList<realType, Ts...>(), [&c](auto _)
		{
			addDefaultOperators<realType>(c);
			addBasicFunctions<realType>(c);
			addTrigFunctions<realType>(c);
			constexpr_if(std::is_floating_point<realType>{}, [&c](auto _)
			{
				c.template setFunction<realType>("abs", [](const auto& a) {return std::abs(a); });

				c.template setOperator<realType, realType>("^", [](const auto& left, const auto& right)
				{
					return std::pow(left, right);
				});
			});
		});

		// if both integer and real-types exist, add cast from int to real
		constexpr_if(std::integral_constant<bool, isInList<intType, Ts...>() && isInList<realType, Ts...>()>{},
			[&c](auto _)
		{
			c.template setCast<intType>(_([](const intType& in)
			{
				return static_cast<realType>(in);
			}));
			addDefaultOperators<intType, realType>(c);
			addDefaultOperators<realType, intType>(c);
		}
		);
	}
}