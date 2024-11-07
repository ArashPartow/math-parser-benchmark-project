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

#include <zecalculator/evaluation/ast/decl/evaluation.h>
#include <zecalculator/parsing/data_structures/impl/node.h>

namespace zc {
namespace eval {
namespace ast {

inline Evaluator::ReturnType Evaluator::operator () (std::monostate)
{
  return tl::unexpected(Error::empty_expression());
}

inline Evaluator::ReturnType
  Evaluator::operator()(const zc::parsing::node::ast::Function<zc::parsing::Type::AST>& node)
{
  if (node.f.mathworld->max_recursion_depth < current_recursion_depth)
    return tl::unexpected(Error::recursion_depth_overflow());

  std::vector<double> evaluations;
  for (const auto& operand : node.operands)
  {
    auto eval = evaluate(operand, input_vars, current_recursion_depth + 1);
    if (eval) [[likely]]
      evaluations.push_back(*eval);
    else [[unlikely]]
      return eval;
  }

  return node.f.evaluate(evaluations, current_recursion_depth + 1);
}

inline Evaluator::ReturnType
  Evaluator::operator()(const zc::parsing::node::ast::Sequence<zc::parsing::Type::AST>& node)
{
  if (node.u.mathworld->max_recursion_depth < current_recursion_depth)
    return tl::unexpected(Error::recursion_depth_overflow());

  auto eval = evaluate(node.operand, input_vars, current_recursion_depth + 1);
  if (eval) [[likely]]
    return node.u.evaluate(*eval, current_recursion_depth + 1);
  else [[unlikely]]
    return eval;
}

inline Evaluator::ReturnType Evaluator::operator()(
  const zc::parsing::node::ast::CppUnaryFunction<zc::parsing::Type::AST>& node)
{
  auto operand = evaluate(node.operand, input_vars, current_recursion_depth + 1);
  if (operand) [[likely]]
    return node.f(*operand);
  else [[unlikely]]
    return operand;
}

inline Evaluator::ReturnType Evaluator::operator()(
  const zc::parsing::node::ast::CppBinaryFunction<zc::parsing::Type::AST>& node)
{
  auto operand1 = evaluate(node.operand1, input_vars, current_recursion_depth + 1);
  auto operand2 = evaluate(node.operand2, input_vars, current_recursion_depth + 1);
  if (operand1 and operand2) [[likely]]
    return node.f(*operand1, *operand2);
  else [[unlikely]]
    return operand1 ? operand2 : operand1;
}

inline Evaluator::ReturnType
  Evaluator::operator()(const zc::parsing::node::GlobalVariable<parsing::Type::AST>& node)
{
  if (node.var.mathworld->max_recursion_depth < current_recursion_depth)
    return tl::unexpected(Error::recursion_depth_overflow());

  return node.var.evaluate(current_recursion_depth + 1);
}

inline Evaluator::ReturnType Evaluator::operator () (const zc::parsing::node::GlobalConstant& node)
{
  return node.constant.value;
}

inline Evaluator::ReturnType Evaluator::operator () (const zc::parsing::node::InputVariable& node)
{
  // node.index should never be bigger than input_vars.size()
  assert(node.index < input_vars.size());

  return input_vars[node.index];
}

inline Evaluator::ReturnType Evaluator::operator () (const zc::parsing::node::Number& node)
{
  return node.value;
}

}
}

/// @brief evaluates a syntax tree using a given math world
/// @param tree: tree to evaluate
/// @param input_vars: variables that are given as input to the tree, will shadow any variable in the math world
/// @param world: math world (contains functions, global constants... etc)
inline tl::expected<double, Error> evaluate(const parsing::Tree<parsing::Type::AST>& tree,
                                            std::span<const double> input_vars,
                                            size_t current_recursion_depth)
{
  return std::visit(eval::ast::Evaluator{.input_vars = input_vars,
                                         .current_recursion_depth = current_recursion_depth},
                    *tree);
}

/// @brief evaluates a syntax tree using a given math world
inline tl::expected<double, Error> evaluate(const parsing::Tree<parsing::Type::AST>& tree,
                                            std::span<const double> input_vars)
{
  return evaluate(tree, input_vars, 0);
}

/// @brief evaluates a syntax tree using a given math world
inline tl::expected<double, Error> evaluate(const parsing::Tree<parsing::Type::AST>& tree)
{
  return evaluate(tree, std::span<const double>(), 0);
}


}
