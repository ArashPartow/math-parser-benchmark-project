/*
@file
CompilersHelpers.h
Bunch of helpers for the compiler. Named so because included by Compiler-files

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

#include "nameMangling.h"
#include "VarExpression.h"

namespace metl
{
	template<class... Ts, std::size_t... Ind, class Expression>
	auto getTypedExpr(const std::vector<Expression>& v, std::index_sequence<Ind...>)
	{
		return std::make_tuple(v.at(Ind).template get<Ts>()...);
	}

	template <class F, class Tuple, std::size_t... I>
	constexpr decltype(auto) apply(F&& f, Tuple&& t, std::index_sequence<I...>)
	{
		return f(std::get<I>(std::forward<Tuple>(t))...);
	}

	template<class Tuple, std::size_t... I>
	auto evaluate(Tuple&& funcs, std::index_sequence<I...>)
	{
		return std::make_tuple(std::get<I>(funcs)()...);
	}

	template<class Expression, class... Ts, class F>
	FunctionImpl<Expression> makeFunction(const F& f)
	{
		return FunctionImpl<Expression>
		(
			[f](const std::vector<Expression>& v)
			{
				auto vv = getTypedExpr<Ts...>(v, std::make_index_sequence<sizeof...(Ts)>{});

				using retType = std::result_of_t<F(Ts...)>;
				return Expression(exprType<retType>([f, vv]()
				{
					auto vals = evaluate(vv, std::make_index_sequence<sizeof...(Ts)>{});
					return apply(f, vals, std::make_index_sequence<sizeof...(Ts)>{});
				}));
			}
		);
	}

	template<class Expression, class T>
	Expression makeVariableExpression(T* v)
	{
		auto f = [v]()
		{
			return *v;
		};

		return Expression(exprType<T>(f), CATEGORY::DYNEXPR);
	}
}

