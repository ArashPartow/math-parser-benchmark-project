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

#include <memory>
#include <variant>
#include <vector>
#include <zecalculator/parsing/shared.h>
#include <zecalculator/utils/utils.h>

namespace zc {

struct SubstrInfo;

namespace parsing {
  namespace tokens {

    struct Variable;
    struct Number;
    struct Text;

  } // namespace tokens

  namespace node {

    struct InputVariable;
    struct GlobalConstant;

    template <zc::parsing::Type>
    struct GlobalVariable;

    using Number = zc::parsing::tokens::Number;

    namespace rpn {

      struct Function;
      struct Sequence;
      struct CppBinaryFunction;
      struct CppUnaryFunction;

      using GlobalVariable = node::GlobalVariable<parsing::Type::RPN>;

      using Node = std::variant<std::monostate,
                                InputVariable,
                                Number,
                                CppUnaryFunction,
                                CppBinaryFunction,
                                GlobalConstant,
                                Function,
                                GlobalVariable,
                                Sequence>;

    } // namespace rpn

    namespace ast {

      template <parsing::Type world_type>
      struct Function;

      template <parsing::Type world_type>
      struct Sequence;

      template <parsing::Type world_type>
      struct CppBinaryFunction;

      template <parsing::Type world_type>
      struct CppUnaryFunction;

      template <parsing::Type world_type>
      using Node = std::variant<std::monostate,
                                InputVariable,
                                Number,
                                CppUnaryFunction<world_type>,
                                CppBinaryFunction<world_type>,
                                GlobalConstant,
                                Function<world_type>,
                                GlobalVariable<world_type>,
                                Sequence<world_type>>;

      template <parsing::Type world_type>
      struct NodePtr;

    } // namespace ast

  } // namespace node

  /// @brief A tree representation in an AST or RPN world
  /// @note when the math world is RPN based, this Tree is simply an intermediate form
  ///       before being transformed into an RPN representation
  template <parsing::Type world_type>
  using Tree = node::ast::NodePtr<world_type>;

  using RPN = std::vector<node::rpn::Node>;

  template <parsing::Type type>
  using Parsing = std::conditional_t<type == parsing::Type::AST, Tree<parsing::Type::AST>, RPN>;

  template <class NodeType>
    requires(is_any_of<NodeType,
                       node::ast::Node<parsing::Type::AST>,
                       node::ast::Node<parsing::Type::RPN>,
                       node::rpn::Node>)
  parsing::tokens::Text text_token(const NodeType& token);

  template <class NodeType>
    requires(is_any_of<NodeType,
                       node::ast::Node<parsing::Type::AST>,
                       node::ast::Node<parsing::Type::RPN>,
                       node::rpn::Node>)
  SubstrInfo substr_info(const NodeType& token);

  } // namespace parsing
} // namespace zc
