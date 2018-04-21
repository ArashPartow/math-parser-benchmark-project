/*
@file
grammar.h
Defines the grammar to be used by PEGTL for parsing strings

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

#include "tao/pegtl.hpp"


namespace metl
{
	// Implementations of special rules are in bottom of file.

	namespace pegtl = tao::pegtl;
	using namespace pegtl;

	///////////////// ATOMICS ////////////////
	struct intLiteral
		: seq< plus<digit>> {};

	struct realLiteral
		: seq< plus<digit>, one<'.'>, plus<digit>> {};
	
	struct Variable; // constants and variables are equivalent wrt the grammar. 

	template<class... Literals> 
	struct Expr;

	template<class... Literals>
	struct bracket : seq< one< '(' >, Expr<Literals...>, one< ')' > > {};


	/////////////// FUNCTIONS ///////////

	struct FunctionName;

	struct FunctionStart: seq<FunctionName, at<one<'('>>>{};

	template<class... Literals>
	struct Function: if_must<FunctionStart, one<'('>, opt<list<Expr<Literals...>, one<','>, space>>, one<')'>>{};

	/////////////// RECURSIVE EXPRESSIONSTRUCTURE ///////////

	struct UnaryOperator;

	struct Suffix;

	template<class... Literals>
	struct Atomic:
		seq<opt<UnaryOperator>, star<space>, sor<bracket<Literals...>, Function<Literals...>, Variable, seq<Literals, opt<Suffix>>...>> {};
	
	struct Operator;

	template<class... Literals>
	struct Expr
		: list<Atomic<Literals...>, Operator, space> {};
	

	////////////////// GRAMMAR //////////////////////

	template<class... Literals>
	struct grammar
		: must<Expr<Literals...>, pegtl::opt<pegtl::space>, pegtl::eof> {};
}

namespace metl
{
	template<typename Input, class T>
	static auto match_any_recursive(Input& in, const std::map<std::string, T>& map, std::string t)
		-> typename std::map<std::string, T>::const_iterator
	{
		// t starts out empty, and slowly becomes the same as in.current, adding one char on each recursion-step. t is then searched in the keys of map.
		if (in.size() > t.size()) {
			t += in.peek_char(t.size()); // append another char to teststring t
			const auto i = map.lower_bound(t); // not sure why this works
			if (i != map.end()) {
				// recursion step. try the next one down the line with an additional char.
				// This happend before the termination, because we are expected to be greedy.
				auto i2 = match_any_recursive(in, map, t);
				if (i2 != map.end())
				{
					return i2;
				}
				if (i->first == t)  // recursion stop: if we found a match, return.
				{
					return i;
				}
			}
		}
		return map.end();
	}

	struct Variable // constants and variables are equivalent wrt the grammar
	{
		using analyze_t = analysis::generic< analysis::rule_type::ANY >;

		template< apply_mode A,
			rewind_mode M,
			template< typename... > class Action,
			template< typename... > class Control,
			typename Input, class Compiler, class... Others>
			static bool match(Input& in, Compiler& s, const Others&...)
		{
			const auto& map = s.impl_.getCandV();
			auto i = match_any_recursive(in, map, std::string());
			if (i != map.end())
			{
				constexpr_if(std::integral_constant<bool,A==pegtl::apply_mode::ACTION>(),
					[&](auto _)
				{
					s.impl_.stack_.push(i->second);
				});

				in.bump(i->first.size());
				return true;
			}

			return false;
		}
	};

	struct Operator
	{
		using analyze_t = analysis::generic< analysis::rule_type::ANY >;

		template< apply_mode A,
			rewind_mode M,
			template< typename... > class Action,
			template< typename... > class Control,
			typename Input, class Compiler>
			static bool match(Input& in, Compiler& s)
		{
			// In here, we first check if we can match the input to an operator of the current precedence N.
			// Then, we check if it exists for the desired left and right types. 

			const auto& operators = s.impl_.getCarriers(); // maps the name of each operator to its precedence.
			auto it = match_any_recursive(in, operators, std::string{});

			if (it == operators.end()) return false; // no operator was found

			s.impl_.stack_.push(it->second);
			in.bump(it->first.size()); // remove the operator from the input.
			return true;
		}
	};

	struct UnaryOperator
	{
		using analyze_t = analysis::generic< analysis::rule_type::ANY >;

		template< apply_mode A,
			rewind_mode M,
			template< typename... > class Action,
			template< typename... > class Control,
			typename Input, class Compiler>
			static bool match(Input& in, Compiler& s)
		{
			// In here, we first check if we can match the input to an operator of the current precedence N.
			// Then, we check if it exists for the desired left and right types. 

			const auto& operators = s.impl_.getUnaryCarriers(); // maps the name of each operator to its precedence.
			auto it = match_any_recursive(in, operators, std::string{});

			if (it == operators.end()) return false; // no operator was found

			s.impl_.stack_.push(it->second);
			in.bump(it->first.size()); // remove the operator from the input.
			return true;
		}
	};

	struct Suffix
	{
		using analyze_t = analysis::generic<analysis::rule_type::ANY>;

		template< apply_mode A,
			rewind_mode M,
			template< typename... > class Action,
			template< typename... > class Control,
			typename Input, class Compiler>
			static bool match(Input& in, Compiler& s)
		{
			// In here, we first check if we can match the input to an operator of the current precedence N.
			// Then, we check if it exists for the desired left and right types. 

			const auto& suffixes = s.impl_.getSuffixes(); // maps the name of each operator to its precedence.
			auto it = match_any_recursive(in, suffixes, std::string{});

			if (it == suffixes.end()) return false; // no operator was found

			s.impl_.stack_.push(it->second);
			in.bump(it->first.size()); // remove the operator from the input.
			return true;
		}
	};

	struct FunctionName
	{
		using analyze_t = analysis::generic< analysis::rule_type::ANY >;

		template< apply_mode A,
			rewind_mode M,
			template< typename... > class Action,
			template< typename... > class Control,
			typename Input, class Compiler>
			static bool match(Input& in, Compiler& s)
		{
			const auto& functionNames = s.impl_.getFunctionNames();
			auto it = match_any_recursive(in, functionNames, std::string{});
			if (it == functionNames.end()) return false;

			in.bump(it->first.size()); // remove the operator from the input.
			return true;
		}
	};
}
