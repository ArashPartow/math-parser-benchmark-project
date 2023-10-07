/****************************************************************************
**  Copyright (c) 2023, Adel Kara Slimane <adel.ks@zegrapher.com>
**
**  This file is part of ZeCalculator.
**
**  ZeCalculators is free software: you may copy, redistribute and/or modify it
**  under the terms of the GNU Affero General Public License as published by the
**  Free Software Foundation, either version 3 of the License, or (at your
**  option) any later version.
**
**  This file is distributed in the hope that it will be useful, but
**  WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#pragma once

#include <zecalculator/math_objects/decl/expression.h>
#include <zecalculator/math_objects/decl/function.h>
#include <zecalculator/math_objects/decl/sequence.h>
#include <zecalculator/math_objects/global_constant.h>
#include <zecalculator/math_objects/global_variable.h>
#include <zecalculator/parsing/data_structures/decl/node.h>
#include <zecalculator/parsing/data_structures/token.h>

namespace zc {
  namespace parsing {
    namespace node {

      using zc::parsing::tokens::Text;

      struct InputVariable: Text
      {
        InputVariable(const Text& txt, size_t index)
          : Text(txt), index(index) {}

        size_t index;
      };

      struct GlobalConstant: Text
      {
        GlobalConstant(const Text& txt, const zc::GlobalConstant& constant)
          : Text(txt), constant(constant) {}

        const zc::GlobalConstant& constant;
      };

      template <parsing::Type world_type>
      struct GlobalVariable: Text
      {
        GlobalVariable(const Text& txt, const zc::GlobalVariable<world_type>& var)
          : Text(txt), var(var) {}

        const zc::GlobalVariable<world_type>& var;
      };

      namespace rpn {

        using parsing::Type::RPN;

        struct Function: Text
        {
          Function(const Text& txt, const zc::Function<RPN>& f)
            : Text(txt),  f(f) {}

          const zc::Function<RPN>& f;
        };

        struct Sequence: Text
        {
          Sequence(const Text& txt, const zc::Sequence<RPN>& u)
            : Text(txt),  u(u) {}

          const zc::Sequence<RPN>& u;
        };

        struct CppBinaryFunction: Text
        {
          CppBinaryFunction(const Text& txt, const zc::CppBinaryFunction& f)
            : Text(txt),  f(f) {}

          const zc::CppBinaryFunction& f;
        };

        struct CppUnaryFunction: Text
        {
          CppUnaryFunction(const Text& txt, const zc::CppUnaryFunction& f)
            : Text(txt),  f(f) {}

          const zc::CppUnaryFunction& f;
        };

      } // namespace rpn

      namespace ast {

        using parsing::Type::AST;

        template <parsing::Type world_type>
        struct NodePtr: std::unique_ptr<Node<world_type>>
        {
          using Parent = std::unique_ptr<Node<world_type>>;

          NodePtr() : Parent(std::make_unique<Node<world_type>>()) {}

          template <class T>
            requires(not std::is_same_v<std::remove_cvref_t<T>, NodePtr>
                     and std::is_convertible_v<T, Node<world_type>>)
          NodePtr(T&& val) : Parent(std::make_unique<Node<world_type>>(std::forward<T>(val)))
          {}

          NodePtr(Parent&& parent_rval)
            : Parent(std::move(parent_rval))
          {}

          NodePtr(NodePtr&&) = default;
          NodePtr& operator = (NodePtr&&) = default;

          bool operator == (const NodePtr& other) const
          {
            assert(*this and other); // cannot be nullptrs, invariant of this class
            return **this == *other;
          }
        };

        template <parsing::Type world_type>
        struct Function: Text
        {
          Function(const Text& txt, const zc::Function<world_type>& f, std::vector<NodePtr<world_type>> operands)
            : Text(txt), f(f), operands(std::move(operands)) {}

          const zc::Function<world_type>& f;
          std::vector<NodePtr<world_type>> operands;
        };

        template <parsing::Type world_type>
        struct Sequence: Text
        {
          Sequence(const Text& txt, const zc::Sequence<world_type>& u, NodePtr<world_type> operand)
            : Text(txt), u(u), operand(std::move(operand)) {}

          const zc::Sequence<world_type>& u;
          NodePtr<world_type> operand;
        };

        template <parsing::Type world_type>
        struct CppBinaryFunction: rpn::CppBinaryFunction
        {
          CppBinaryFunction(const Text& txt,
                            const zc::CppBinaryFunction& f,
                            NodePtr<world_type> operand1,
                            NodePtr<world_type> operand2)
            : rpn::CppBinaryFunction(txt, f), operand1(std::move(operand1)),
              operand2(std::move(operand2))
          {}

          NodePtr<world_type> operand1, operand2;
        };

        template <parsing::Type world_type>
        struct CppUnaryFunction: rpn::CppUnaryFunction
        {
          CppUnaryFunction(const Text& txt,
                           const zc::CppUnaryFunction& f,
                           NodePtr<world_type> operand)
            : rpn::CppUnaryFunction(txt, f), operand(std::move(operand))
          {}

          NodePtr<world_type> operand;
        };

      } // namespace rpn
    } // namespace node

    template <class NodeType>
      requires(is_any_of<NodeType,
                        node::ast::Node<parsing::Type::AST>,
                        node::ast::Node<parsing::Type::RPN>,
                        node::rpn::Node>)
    inline parsing::tokens::Text text_token(const NodeType& token)
    {
      return std::visit(overloaded{[](const std::monostate&) -> parsing::tokens::Text
                                  { return parsing::tokens::Text(); },
                                  [](const auto& tk) -> parsing::tokens::Text { return tk; }},
                        token);
    }

    template <class NodeType>
      requires(is_any_of<NodeType,
                        node::ast::Node<parsing::Type::AST>,
                        node::ast::Node<parsing::Type::RPN>,
                        node::rpn::Node>)
    inline SubstrInfo substr_info(const NodeType& token)
    {
      return text_token(token).substr_info;

    }

  } // namespace parsing
} // namespace zc
