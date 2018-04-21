/*
@file
Compiler.fwd.h
Declares template class Compiler, which is the public relations class of metl: The only class a user interacts with directly. Except maybe for expressions.

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

#include <map>

#include "Compiler_Detail.fwd.h"

namespace metl
{
	template<class Grammar, class LiteralsConverters, class... Ts>
	class Compiler
	{
	public:
		using Expression = VarExpression<Ts...>;

	public:

		Compiler(const LiteralsConverters& literalConverters);

		Expression build(const std::string& expression);

		template<class T>
		exprType<T> build(const std::string& expression);

	public:
		void setOperatorPrecedence(std::string op, unsigned int precedence, ASSOCIATIVITY associativity = ASSOCIATIVITY::LEFT);
		void setUnaryOperatorPrecedence(std::string op, unsigned int precedence);

		template<class Left, class Right, /*inferred*/ class F>
		void setOperator(const std::string& token, const F& f);

		template<class T, /*inferred*/ class F>
		void setUnaryOperator(const std::string& token, const F& f);

		// Finds strings of the form token(ParamTypes...) and calls f on the params
		template<class... ParamTypes, /*inferred*/ class F>
		void setFunction(const std::string& token, const F& f);

		// tries to implicitly cast from type "From" to whatever type is returned by function f
		template<class From, /*inferred*/ class F>
		void setCast(const F& f);

		// adds 'token' as a possible suffix for literals of type From, converting them to type To.
		template<class From, class To, /*inferred*/class F>
		void setSuffix(const std::string& token, const F& f);

	public:
		template<class T>
		void setConstant(const std::string& token, T&& val);

		template<class T>
		void setVariable(const std::string& token, T* val);
	public:
		template<class T>
		constexpr static TYPE type();

		detail::Compiler_impl<LiteralsConverters, Ts...> impl_;
	};
}
