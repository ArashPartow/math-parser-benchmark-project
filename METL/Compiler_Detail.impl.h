/*
@file
Compiler_Detail.impl.h
Implements functions for class Compiler_Detail

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
#include "Compiler_Detail.fwd.h"

#include "tao/pegtl.hpp"

#include "grammar.h"
#include "actions.h"

#include "nameMangling.h"
#include "Stack.impl.h"

#include "CompilerHelpers.h"

namespace metl
{
	namespace detail
	{
		template<class T>
		void insert_or_emplace(std::map<std::string, T>& map, const std::string& key, const T& val)
		{
			auto it = map.find(key);
			if (it == map.end())
			{
				map.emplace(key, val);
				return;
			}
			it->second = val;
		}
	}
}

namespace metl
{
	namespace detail
	{
		template <class LiteralConverters, class ... Ts>
		Compiler_impl<LiteralConverters, Ts...>::Compiler_impl(const LiteralConverters& literalConverters) :
			stack_(operators_, functions_, castImplementations_, suffixImplementations_ ,castDeclarations_),
			literalConverters_(literalConverters),
			castDeclarations_({ std::make_pair(type<Ts>(), std::vector<TYPE>{type<Ts>()})... })
		{}

		template <class LiteralConverters, class ... Ts>
		void Compiler_impl<LiteralConverters, Ts...>::setOperatorPrecedence(const std::string& op, unsigned precedence,
			ASSOCIATIVITY associativity)
		{

		// if operator already exists, replace precedence. Else, insert new operator with new precedence

		insert_or_emplace(opCarriers_, op, opCarrier{ op, precedence, associativity, false });
		}

		template <class LiteralConverters, class ... Ts>
		void Compiler_impl<LiteralConverters, Ts...>::setUnaryOperatorPrecedence(const std::string& op, unsigned precedence)
		{
			insert_or_emplace(unaryCarriers_, op, opCarrier{ op, precedence, ASSOCIATIVITY::RIGHT, true });
		}

		template <class LiteralConverters, class ... Ts>
		void Compiler_impl<LiteralConverters, Ts...>::setOperator(const std::string& token,
			const std::vector<TYPE>& paramTypes, const FunctionImpl<Expression>& op)
		{
			// check, if operator is in the list of precedences. 
			auto it = opCarriers_.find(token);
			if (it == opCarriers_.end())
			{
				throw std::runtime_error("The operator \" " + token + "\" has no precedence set!");
			}

			auto mangledName = mangleName(token, paramTypes);
			insert_or_emplace(operators_, mangledName, op);
		}

		template <class LiteralConverters, class ... Ts>
		void Compiler_impl<LiteralConverters, Ts...>::setUnaryOperator(const std::string& token, TYPE paramType,
			const FunctionImpl<Expression>& op)
		{
			auto it = unaryCarriers_.find(token);
			if (it == unaryCarriers_.end())
			{
				throw std::runtime_error("The unary operator \" " + token + "\" has no precedence set!");
			}

			auto mangledName = mangleName(token, { paramType });
			insert_or_emplace(operators_, mangledName, op);
		}

		template <class LiteralConverters, class ... Ts>
		void Compiler_impl<LiteralConverters, Ts...>::setFunction(const std::string& token,
			const std::vector<TYPE>& paramTypes, const FunctionImpl<Expression>& function)
		{
			insert_or_emplace(functionNames_, token, token);
			insert_or_emplace(functions_, mangleName(token, paramTypes), function);
		}

		template <class LiteralConverters, class ... Ts>
		void Compiler_impl<LiteralConverters, Ts...>::setCast(const TYPE from, const TYPE to, const CastImpl<Expression>& fs)
		{
			auto it = castDeclarations_.find(from);
			if (it == castDeclarations_.end())
			{
				castDeclarations_.emplace(from, std::vector<TYPE>{ to });
			}
			else
			{
				it->second.push_back(to);
			}

			insert_or_emplace(castImplementations_, mangleCast(from, to), fs);
		}

		template <class LiteralConverters, class ... Ts>
		void Compiler_impl<LiteralConverters, Ts...>::setSuffix(const std::string& token, const TYPE from, const CastImpl<Expression>& conversion)
		{
			insert_or_emplace(suffixes_, token, suffixCarrier{ token });
			insert_or_emplace(suffixImplementations_, mangleSuffix(token, from), conversion);
		}

		template <class LiteralConverters, class ... Ts>
		void Compiler_impl<LiteralConverters, Ts...>::addConstantOrVariable(const std::string& token, const Expression& val)
		{
			if (token.empty()) throw std::runtime_error("token must not be empty!");
			if (isdigit(token.front())) throw std::runtime_error("token must not start with a number!");

			insert_or_emplace(constantsAndVariables_, token, val);
		}

		template <class LiteralConverters, class... Ts>
		template <class T>
		constexpr TYPE Compiler_impl<LiteralConverters, Ts...>::type()
		{
			return classToType2<T, Ts...>();
		}
	}
}