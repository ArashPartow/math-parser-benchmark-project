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

#include <variant>
#include <zecalculator/error.h>
#include <zecalculator/evaluation/rpn/decl/evaluation.h>
#include <zecalculator/math_objects/impl/function.h>

namespace zc {
namespace eval {
namespace rpn {

inline void Evaluator::operator () (std::monostate)
{
  expected_eval_stack = tl::unexpected(Error::empty_expression());
}

inline void Evaluator::operator () (const zc::parsing::node::Number& val)
{
  expected_eval_stack->push_back(val.value);
}

inline void Evaluator::operator()(const zc::parsing::node::rpn::Function& node)
{
  const size_t args_num = node.f.argument_size().value();
  if (max_recursion_depth < current_recursion_depth) [[unlikely]]
    expected_eval_stack = tl::unexpected(Error::recursion_depth_overflow());
  if (not bool(node.f)) [[unlikely]]
    expected_eval_stack = tl::unexpected(Error::calling_invalid_function(node));
  else
  {
    const auto evaluations = std::span<const double>(expected_eval_stack->end() - args_num,
                                                     expected_eval_stack->end());

    auto expected_res = node.f.evaluate(evaluations, current_recursion_depth + 1);

    // when done, remove args_num from the back of the evaluation stack
    // note: the resize needs to be done before pushing in the new result
    expected_eval_stack->resize(expected_eval_stack->size() - args_num);

    if (expected_res)
      // push the result to the evaluation stack if correct
      expected_eval_stack->push_back(*expected_res);

    // save error in the expected otherwise
    else expected_eval_stack = tl::unexpected(expected_res.error());
  }
}

inline void Evaluator::operator()(const zc::parsing::node::rpn::CppUnaryFunction& node)
{
  if (expected_eval_stack->empty())
    expected_eval_stack = tl::unexpected(Error::mismatched_fun_args(node));
  else
  {
    double& back_val = expected_eval_stack->back();

    // overwrite the last value with the function evaluation on it
    back_val = node.f(back_val);
  }
}

inline void Evaluator::operator()(const zc::parsing::node::rpn::CppBinaryFunction& node)
{
  if (expected_eval_stack->size() < 2) [[unlikely]]
    expected_eval_stack = tl::unexpected(Error::mismatched_fun_args(node));
  else
  {
    // points on the before last value on the stack
    const auto it = expected_eval_stack->end() - 2;

    // since the function pops two elements, then pushes back one
    // we can overwrite directly the value that will get replaced
    *it = node.f(*it, *(it+1));

    // remove the last value, i.e. at it+1, as it got consumed
    expected_eval_stack->pop_back();
  }
}

inline void Evaluator::operator()(const zc::parsing::node::rpn::Sequence& node)
{
  //              std::cout << "Evaluating zc function: " << node.name << std::endl;
  if (not bool(node.u))
    expected_eval_stack = tl::unexpected(Error::calling_invalid_function(node));
  else if (expected_eval_stack->empty())
    expected_eval_stack = tl::unexpected(Error::mismatched_fun_args(node));
  else
  {
    // sequence handles only one argument
    double& back_val = expected_eval_stack->back();

    auto expected_res = node.u.evaluate(back_val, current_recursion_depth + 1);

    if (expected_res)
      // overwrite the top of the stack on computation success
      back_val = *expected_res;

    // save error in the expected otherwise
    else expected_eval_stack = tl::unexpected(expected_res.error());
  }
}

inline void Evaluator::operator () (const zc::parsing::node::InputVariable& in_var)
{
  // node.index should never be bigger than input_vars.size()
  assert(in_var.index < input_vars.size());

  expected_eval_stack->push_back(input_vars[in_var.index]);
}

inline void Evaluator::operator()(const zc::parsing::node::GlobalConstant& node)
{
  expected_eval_stack->push_back(node.constant.value);
}

inline void Evaluator::operator()(const zc::parsing::node::GlobalVariable<parsing::Type::RPN>& node)
{
  auto expected_res = node.var.evaluate(current_recursion_depth + 1);
  if (expected_res)
    expected_eval_stack->push_back(*expected_res);
  else expected_eval_stack = tl::unexpected(expected_res.error());
}

}
}

/// @brief evaluates a syntax expr using a given math world
/// @param expr: expr to evaluate
/// @param input_vars: variables that are given as input to the expr, will shadow any variable in the math world
/// @param world: math world (contains functions, global constants... etc)
inline tl::expected<double, Error> evaluate(const parsing::RPN& expr,
                                            std::span<const double> input_vars,
                                            size_t current_recursion_depth)
{
  eval::rpn::Evaluator stateful_evaluator{.input_vars = input_vars,
                                          .current_recursion_depth = current_recursion_depth};

  for (const parsing::node::rpn::Node& tok: expr)
  {
    std::visit(stateful_evaluator, tok);
    if (not stateful_evaluator.expected_eval_stack)
      break;
  }

  if (stateful_evaluator.expected_eval_stack)
  {
    if (stateful_evaluator.expected_eval_stack->size() == 1)
      return stateful_evaluator.expected_eval_stack->front();
    else return tl::unexpected(Error::unkown());
  }
  else return tl::unexpected(stateful_evaluator.expected_eval_stack.error());
}

/// @brief evaluates a syntax expr using a given math world
inline tl::expected<double, Error> evaluate(const parsing::RPN& expr,
                                            std::span<const double> input_vars)
{
  return evaluate(expr, input_vars, 0);
}

/// @brief evaluates a syntax expr using a given math world
inline tl::expected<double, Error> evaluate(const parsing::RPN& expr)
{
  return evaluate(expr, std::span<const double>(), 0);
}


}
