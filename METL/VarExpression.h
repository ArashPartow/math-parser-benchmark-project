/*
@file VarExpression.h
Defines class VarExpression, which is a variant-type to contain std::functions returning different values.
This is used to contain the results of parsing. 

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

#include <functional>

#include "DeepCopy.h"

#include "TypeList.h"

namespace metl
{

	template<class T> using exprType = std::function<T()>;

	enum class TYPE : int;

	template<class T, class... Ts>
	constexpr TYPE classToType2()
	{
		return static_cast<TYPE>(findFirstIndex<T>(TypeList<Ts...>{}));
	}

	enum class CATEGORY
	{
		CONSTEXPR, //an expression that does not change after "build"-time, when the string is read. Constexpressions allow for some optimizations.
		DYNEXPR // an expression that DOES change after "build"-time. 
	};


	template<class... Ts, std::size_t... I>
	std::tuple<std::unique_ptr<Ts>...> deepCopy(const std::tuple<std::unique_ptr<Ts>...>& tuple, std::index_sequence<I...>)
	{
		return std::make_tuple<std::unique_ptr<Ts>...>(qengine::internal::deep_copy(std::get<I>(tuple))...);
	}

	template<class... Ts>
	class VarExpression
	{
	public:
		template<class T>
		VarExpression(const exprType<T>& t, CATEGORY category = CATEGORY::DYNEXPR) :
			type_(classToType2<T, Ts...>()),
			category_(category)
		{
			constexpr auto index = findFirstIndex<T>(TypeList<Ts...>{});
			std::get<index>(vals_) = std::make_unique<exprType<T>>(t);
		}

		VarExpression(const VarExpression& other) :
			type_(other.type_),
			category_(other.category_)
		{
			vals_ = deepCopy(other.vals_, std::make_index_sequence<sizeof...(Ts)>{});
		}

		VarExpression& operator=(const VarExpression& other)
		{
			if (&other != this)
			{
				type_ = other.type_;
				category_ = other.category_;
				vals_ = deepCopy(other.vals_, std::make_index_sequence<sizeof...(Ts)>{});
			}

			return *this;
		}

		template<class T> exprType<T> get() const
		{
			constexpr auto index = findFirstIndex<T>(TypeList<Ts...>{});
			static_assert(index < sizeof...(Ts), "Error: Requested Type is not a valid type!");

			if (std::get<index>(vals_)) return *std::get<index>(vals_);
			throw std::runtime_error("this is not the correct type");
		}

		template<class T> void set(exprType<T> expr)
		{
			constexpr auto index = findFirstIndex<T>(TypeList<Ts...>{});
			static_assert(index < sizeof...(Ts), "Error: Requested Type is not a valid type!");

			std::get<index>(vals_) = std::make_unique<exprType<T>>(expr);
		}

		TYPE type() const { return type_; }
		CATEGORY category() const { return category_; }

		template<class T>
		constexpr static TYPE toType() { return classToType2<T, Ts...>(); }
	private:
		TYPE type_;
		CATEGORY category_;

		std::tuple<std::unique_ptr<exprType<Ts>>...> vals_;
	};

	template<class... Ts>
	constexpr TypeList<Ts...> getTypeList(VarExpression<Ts...>) { return TypeList<Ts...>{}; }
}
