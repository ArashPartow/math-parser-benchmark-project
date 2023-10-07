#pragma once

/****************************************************************************
**  Copyright (c) 2023, Adel Kara Slimane <adel.ks@zegrapher.com>
**
**  This file is part of ZeCalculator's source code.
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

#include <zecalculator/error.h>
#include <zecalculator/parsing/data_structures/decl/node.h>
#include <zecalculator/math_objects/builtin_binary_functions.h>
#include <zecalculator/math_objects/builtin_unary_functions.h>
#include <zecalculator/math_objects/decl/function.h>
#include <zecalculator/math_objects/global_constant.h>
#include <zecalculator/mathworld/decl/mathworld.h>
#include <zecalculator/utils/name_map.h>

namespace zc {
namespace eval {
namespace ast {

struct Evaluator
{
  const std::span<const double> input_vars;
  const size_t current_recursion_depth = 0;

  using ReturnType = tl::expected<double, Error>;

  // using T = std::remove_cvref_t<decltype(node)>;

  ReturnType operator () (std::monostate);

  ReturnType operator () (const zc::parsing::node::ast::Function<zc::parsing::Type::AST>&);

  ReturnType operator () (const zc::parsing::node::ast::Sequence<zc::parsing::Type::AST>&);

  ReturnType operator () (const zc::parsing::node::InputVariable&);

  ReturnType operator () (const zc::parsing::node::Number&);

  ReturnType operator () (const zc::parsing::node::ast::CppUnaryFunction<zc::parsing::Type::AST>&);

  ReturnType operator () (const zc::parsing::node::ast::CppBinaryFunction<zc::parsing::Type::AST>&);

  ReturnType operator () (const zc::parsing::node::GlobalConstant&);

  ReturnType operator () (const zc::parsing::node::GlobalVariable<parsing::Type::AST>&);

};

}
}

/// @brief evaluates a syntax tree using a given math world
/// @param tree: tree to evaluate
/// @param input_vars: variables that are given as input to the tree, will shadow any variable in the math world
/// @param world: math world (contains functions, global constants... etc)
inline tl::expected<double, Error> evaluate(const parsing::Tree<parsing::Type::AST>& tree,
                                            std::span<const double> input_vars,
                                            size_t current_recursion_depth);

/// @brief evaluates a syntax tree using a given math world
inline tl::expected<double, Error> evaluate(const parsing::Tree<parsing::Type::AST>& tree,
                                            std::span<const double> input_vars);

/// @brief evaluates a syntax tree using a given math world
inline tl::expected<double, Error> evaluate(const parsing::Tree<parsing::Type::AST>& tree);

} // namespace zc
