/*
 @file 
actions.h
defines actions to be taken when finding specific patterns in the parsed string. Used by PEGTL
 
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
#include "grammar.h"
#include "VarExpression.h"

namespace metl
{
	struct BadLiteralException;

	template< typename Rule >
	struct action
		: nothing<Rule>
	{};

	template<class TargetType, class... Ts, class Compiler, class Converter>
	void convertLiteral(Compiler& compiler, const std::string& input, Converter& converter,TypeList<Ts...>)
	{
		constexpr_ternary(nostd::bool_constant<isInList<TargetType, Ts...>()>(),
			[&](auto _)
		{
			compiler.impl_.stack_.push(metl::makeConstExpression<typename Compiler::Expression>(converter.f(input)));
		},
			[&](auto _)
		{
			try
			{
				converter.f(input);
			}
			catch (const BadLiteralException& e)
			{
				throw e;
			}
		}
		);
	}

	template<>
	struct action<intLiteral>
	{
		template< typename Input, class Compiler >
		static void apply(const Input& in, Compiler& compiler)
		{
			auto& converter = compiler.impl_.literalConverters_.toInt;
			using intType = decltype(converter.f(in.string()));
			convertLiteral<intType>(compiler, in.string(), converter, compiler.impl_.getTypeList());
		}
	};

	template<>
	struct action<realLiteral>
	{
		template< typename Input, class Compiler >
		static void apply(const Input& in, Compiler& compiler)
		{
			auto& converter = compiler.impl_.literalConverters_.toReal;
			using realType = decltype(converter.f(in.string()));
			convertLiteral<realType>(compiler, in.string(), converter, compiler.impl_.getTypeList());
		}
	};

	template<>
	struct action<FunctionStart>
	{
		template< typename Input, class Compiler >
		static void apply(const Input& in, Compiler& compiler)
		{
			compiler.impl_.stack_.pushFunction(in.string());
		}
	};	
	
	template<>
	struct action<one<'('>>
	{
		template< typename Input, class Compiler >
		static void apply(const Input&, Compiler& compiler)
		{
			compiler.impl_.stack_.open();
		}
	};	

	template<>
	struct action<one<')'>>
	{
		template< typename Input, class Compiler >
		static void apply(const Input&, Compiler& compiler)
		{
			compiler.impl_.stack_.close();
		}
	};
	template<>
	struct action<one<','>>
	{
		template< typename Input, class Compiler >
		static void apply(const Input&, Compiler& compiler)
		{
			compiler.impl_.stack_.close();
			compiler.impl_.stack_.open();
		}
	};

	template<class... Literals>
	struct action<Function<Literals...>>
	{
		template< typename Input, class Compiler >
		static void apply(const Input&, Compiler& compiler)
		{
			compiler.impl_.stack_.close();
		}
	};
}
