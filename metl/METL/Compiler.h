/*
@file
Compiler.h
Public access-file for template class Compiler, containing the make-functions and helpers to construct a metl::Compiler

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

#include "Compiler.impl.h"

namespace metl
{
	struct BadLiteralException: public std::runtime_error{explicit BadLiteralException(const std::string& s):runtime_error(s){} };

	namespace detail
	{
		// Type to carry functors f that convert strings representing literals. 
		// From_t is basically the index for the metl-compiler, so when From_t =int this converter will be invoked to deal with literals "1" or "42", 
		// while From_t = doube is invoked for "1.0" and "8.008"
		template<class From_t, class To_t, class F>
		struct Converter
		{
			using From = From_t;
			using To = To_t;
			F f;
		};

		template<class From_t, class F>
		auto makeConverter(F f)
		{
			using To_t = decltype(f(std::string()));
			return Converter<From_t, To_t, F>{f};
		}

		template<class IntConverter, class RealConverter>
		struct LiteralConverters
		{
			IntConverter toInt;
			RealConverter toReal;
		};

		template<class... Ts>
		auto makeLiteralConverters(Ts&&...ts) { return LiteralConverters<Ts...>{ts...}; }
	
		template<class T> struct DefaultConverterMaker{};
		template<> struct DefaultConverterMaker<int> { static auto make() { return makeConverter<int>([](const std::string& s) {return std::stoi(s); }); } };
		template<> struct DefaultConverterMaker<double> { static auto make() { return makeConverter<double>([](const std::string& s) {return std::stod(s); }); } };
		
		// recursion-end for when no converter for type T has been passed in, so we define a default.
		// The default will convert to the default type (currently int and double), it these are part of the compiler, otherwise it will throw a BadLiteralException
		template<class T, class... Ts>
		auto getConverter()
		{
			return constexpr_ternary(std::integral_constant<bool, isInList<T, Ts...>()>(), [](auto _)
			{
				//return _([](const std::string& s) {return std::stoi(s); });
				return _(DefaultConverterMaker<T>::make());
			},
				[](auto _)
			{
				return _( makeConverter<T>([](const auto& s) -> T
				{
					throw BadLiteralException("");
				}));
			});
		}
		
		// recursion-end for when a converter for type T has actually been passed in.
		template<class T, class... Ts, class TT, class F, class... Converters>
		auto getConverter(Converter<T, TT, F> converter1, Converters...)
		{
			static_assert(isInList<TT, Ts...>(), "type converted to must be part of compiler!");
			return converter1;
		}

		// recursion-step
		template<class... Ts, class NotLookingForThisConverter, class... Converters>
		auto getConverter(NotLookingForThisConverter, Converters... converters)
		{
			return getConverter<Ts...>(converters...);
		}

		template<class... Ts, class... Converters>
		auto constructFullLiteralsConverter(Converters... converters)
		{
			auto toInt = getConverter<int, Ts...>(converters...); // picks out the converter from the list that is labelled to interpret int-literals
			auto toReal = getConverter<double, Ts...>(converters...); // picks out the converter from the list that is labelled to interpret real-literals

			return detail::makeLiteralConverters(toInt, toReal);
		}
	}

	template<class F, class T = decltype(std::declval<F>()(std::declval<std::string>())) >
	detail::Converter<int, T, F> intConverter(F f) {return detail::Converter<int, T, F>{f};	} 

	template<class F, class T = decltype(std::declval<F>()(std::declval<std::string>()))>
	detail::Converter<double, T, F> realConverter(F f) { return detail::Converter<double, T, F>{f}; }


	template<class... Ts, class... Converters>
	auto makeCompiler(Converters... converters) -> Compiler<grammar<realLiteral, intLiteral>, decltype(detail::constructFullLiteralsConverter<Ts...>(converters...)), Ts...>
	{
		auto literalsConverter = detail::constructFullLiteralsConverter<Ts...>(converters...);
		return Compiler<grammar<realLiteral, intLiteral>, decltype(literalsConverter), Ts...>(literalsConverter);
	}
}
