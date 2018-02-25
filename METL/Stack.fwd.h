/*
@file
Stack.fwd.h
Declares class Stack, which implements the shunting-yard algorithm.

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
#include <vector>
#include <functional>
#include <string>

#include "VarExpression.h"

namespace metl
{
	template<class Expression, class T>
	Expression makeConstExpression(const T& v)
	{
		auto f = [v]()
		{
			return v;
		};

		return Expression(exprType<T>(f), CATEGORY::CONSTEXPR);
	}

	template<class ExprT>
	class FunctionImpl
	{
		using FunctionType = std::function<ExprT(const std::vector<ExprT>&)>;
	public:
		FunctionImpl(FunctionType f):f_(f){}

		ExprT operator()(const std::vector<ExprT>& v) const;

		template<class T>
		FunctionImpl& operator=(T&& t)
		{
			f_ = t;
			return *this;
		}

	private:

		 FunctionType f_;
	};
	template<class ExprT>
	class CastImpl
	{
		using FunctionType = std::function<ExprT(ExprT)>;
	public:
		CastImpl(FunctionType f):f_(f){}

		ExprT operator()(ExprT v) const;

		template<class T>
		CastImpl& operator=(T&& t)
		{
			f_ = t;
			return *this;
		}

	private:

		 FunctionType f_;
	};


	enum class ASSOCIATIVITY{LEFT,RIGHT};

	struct opCarrier
	{
		std::string name;
		unsigned int precedence;
		ASSOCIATIVITY associativity;
		bool isUnary;
	};

	struct suffixCarrier
	{
		std::string name;
	};
}

namespace metl
{
	template<class... Ts>
	class Stack
	{
		using Expression = VarExpression<Ts...>;

		class Substack
		{
		public:

			explicit Substack(const std::map<std::string, FunctionImpl<Expression>>& opMap, 
				const std::map<std::string, FunctionImpl<Expression>>& functionMap,
				const std::map<std::string, CastImpl<Expression>>& castImplementations,
				const std::map<std::string, CastImpl<Expression>>& suffixImplementations,
				const std::map<TYPE, std::vector<TYPE>>& castDeclarations);


			void push(const Expression l);
			void push(const opCarrier& b);
			void pushFunction(std::string FunctionName);
			void push(const suffixCarrier& suffix);

			Expression finish();

			void evaluateFunction();

			void reduce();
			void reduceBinary();
			void reduceUnary();

			bool empty() const { return expressions_.empty(); }
		private:
			bool plannedSignSwitch = false;

			std::vector< Expression > expressions_;
			std::vector< opCarrier > operators_;

			std::unique_ptr<std::string> function_;

			const std::map<std::string, FunctionImpl<Expression>>& opMap_;
			const std::map<std::string, FunctionImpl<Expression>>& functionMap_;
			const std::map<std::string, CastImpl<Expression>>& suffixMap_;

			const std::map<std::string, CastImpl<Expression>>& castImplementations_;
			const std::map<TYPE, std::vector<TYPE>>& castDeclarations_;


		private:
			//void tryCast()
			bool are_all_const(const std::vector<Expression>& expressions);
			void castTo(const std::vector<TYPE>& targetTypes);
		};

	public:
		Stack(const std::map<std::string, FunctionImpl<Expression>>& opMap, 
			const std::map<std::string, FunctionImpl<Expression>>& funcMap,
			const std::map<std::string, CastImpl<Expression>>& castImplementations,
			const std::map<std::string, CastImpl<Expression>>& suffixImplementations,
			const std::map<TYPE, std::vector<TYPE>>& castDeclarations);

		void push(const Expression& t);

		void pushFunction(std::string functionName);

		void push(const opCarrier& op);

		void push(const suffixCarrier& suffix);

		void open();

		void close();

		Expression finish();
		void clear();

	private:
		std::vector<Substack> subStacks_;

		const std::map<std::string, FunctionImpl<Expression>>& opMap_;
		const std::map<std::string, FunctionImpl<Expression>>& funcMap_;

		const std::map<std::string, CastImpl<Expression>>& castImplementations_;
		const std::map<std::string, CastImpl<Expression>>& suffixImplementations_;
		const std::map<TYPE, std::vector<TYPE>>& castDeclarations_;
	};
}
