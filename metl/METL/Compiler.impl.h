/*
@file
Compiler.impl.h
Defines functions of template class Compiler

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
#include "Compiler.fwd.h"

#include "Compiler_Detail.impl.h"


namespace metl
{

	//template <class Grammar, class LiteralConverters, class... Ts>
	//Compiler<Grammar, LiteralConverters, Ts...>::Compiler() :
	//	stack_(operators_, functions_, castImplementations_, castDeclarations_),
	//	castDeclarations_({ std::make_pair(type<Ts>(), std::vector<TYPE>{type<Ts>()})... })
	//{
	//}

	template <class Grammar, class LiteralsConverters, class ... Ts>
	Compiler<Grammar, LiteralsConverters, Ts...>::Compiler(const LiteralsConverters& literalConverters) :
	impl_(literalConverters)
	{

	}

	namespace detail 
	{
		template<class Expr>
		void castToAll(Expr&, const std::map<std::string, CastImpl<Expr>>&)
		{
		}

		template<class T, class... Ts, class Expr>
		void castToAll(Expr& expr, const std::map<std::string, CastImpl<Expr>>& castImpls)
		{
			auto it = castImpls.find(mangleCast(expr.type(), expr.template toType<T>()));
			if(it != castImpls.end())
			{
				expr.template set<T>(it->second(expr).template get<T>());
			}
			castToAll<Ts...>(expr, castImpls);
		}
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	typename Compiler<Grammar, LiteralConverters, Ts...>::Expression Compiler<Grammar, LiteralConverters, Ts...>::build(const std::string& expression)
	{
		impl_.stack_.clear();
		tao::pegtl::memory_input<> input(expression, std::string{});
		tao::pegtl::parse<Grammar, action>(input, *this);

		auto expr =  impl_.stack_.finish();

		detail::castToAll<Ts...>(expr, impl_.getcastImplementations());

		return expr;
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	template <class T>
	exprType<T> Compiler<Grammar, LiteralConverters, Ts...>::build(const std::string& expression)
	{
		return build(expression).template get<T>();
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	void Compiler<Grammar, LiteralConverters, Ts...>::setOperatorPrecedence(const std::string op, const unsigned int precedence, const ASSOCIATIVITY associativity)
	{
		impl_.setOperatorPrecedence(op, precedence, associativity);
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	void Compiler<Grammar, LiteralConverters, Ts...>::setUnaryOperatorPrecedence(const std::string op, const unsigned precedence)
	{
		impl_.setUnaryOperatorPrecedence(op, precedence);
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	template <class Left, class Right, class F>
	void Compiler<Grammar, LiteralConverters, Ts...>::setOperator(const std::string& token, const F& f)
	{
		impl_.setOperator(token, { type<Left>(), type<Right>() }, metl::makeFunction<Expression, Left, Right>(f));
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	template <class T, class F>
	void Compiler<Grammar, LiteralConverters, Ts...>::setUnaryOperator(const std::string& token, const F& f)
	{
		impl_.setUnaryOperator(token, type<T>(), metl::makeFunction<Expression, T>(f));
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	template <class ... ParamTypes, class F>
	void Compiler<Grammar, LiteralConverters, Ts...>::setFunction(const std::string& token, const F& f)
	{
		impl_.setFunction(token, std::vector<TYPE>{type<ParamTypes>()...}, metl::makeFunction<Expression, ParamTypes...>(f));
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	template <class From, class F>
	void Compiler<Grammar, LiteralConverters, Ts...>::setCast(const F& f)
	{
		using To = std::result_of_t<F(From)>;
		static_assert(isInList<From, Ts...>(), "Type casted from is not one of the types of this compiler");
		static_assert(isInList<To, Ts...>(), "Type casted to is not one of the types of this compiler");

		auto impl = [f](const Expression& from)
		{
			auto f_from = from.template get<From>();
			return Expression(exprType<To>{
				[f, f_from]()
				{
					return f(f_from());
				}
			});
		};

		impl_.setCast(type<From>(), type<To>(), CastImpl<Expression>(impl));
	}

	template <class Grammar, class LiteralsConverters, class ... Ts>
	template <class From, class To, class F>
	void Compiler<Grammar, LiteralsConverters, Ts...>::setSuffix(const std::string& token, const F& f)
	{
		static_assert(isInList<From, Ts...>(), "Type the suffix converts from is not one of the types of this compiler!");
		static_assert(isInList<To, Ts...>(), "Type the suffix converts to is not one of the types of this compiler!");

		auto impl = [f](const Expression& from)
		{
			auto f_from = from.template get<From>();
			return Expression(exprType<To>{
				[f, f_from]()
				{
					return f(f_from());
				}
			});
		};

		impl_.setSuffix(token, type<From>(), CastImpl<Expression>(impl));
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	template <class T>
	void Compiler<Grammar, LiteralConverters, Ts...>::setConstant(const std::string& token, T&& val)
	{
		/*
					static_assert(isInList<T, Ts...>(), "T must be one of the types the compiler works with.");*/
		impl_.addConstantOrVariable(token, makeConstExpression<Expression>(std::forward<T>(val)));
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	template <class T>
	void Compiler<Grammar, LiteralConverters, Ts...>::setVariable(const std::string& token, T* val)
	{
		impl_.addConstantOrVariable(token, makeVariableExpression<Expression>(val));
	}

	template <class Grammar, class LiteralConverters, class... Ts>
	template <class T>
	constexpr TYPE Compiler<Grammar, LiteralConverters, Ts...>::type()
	{
		return classToType2<T, Ts...>();
	}
}
