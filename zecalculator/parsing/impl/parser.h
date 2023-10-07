#pragma once

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

#include <zecalculator/error.h>
#include <zecalculator/math_objects/aliases.h>
#include <zecalculator/math_objects/impl/expression.h>
#include <zecalculator/math_objects/impl/function.h>
#include <zecalculator/math_objects/impl/sequence.h>
#include <zecalculator/mathworld/impl/mathworld.h>
#include <zecalculator/parsing/data_structures/impl/node.h>
#include <zecalculator/parsing/decl/parser.h>

#include <cmath>
#include <numeric>
#include <optional>
#include <string_view>

namespace zc {
namespace parsing {

inline std::optional<std::pair<double, size_t>> to_double(std::string_view view)
{
  std::optional<std::pair<double, size_t>> result = std::make_pair(0.0, 0);
  char* charAfter = const_cast<char*>(view.data()); // char that comes right after the number
  result->first = std::strtod(view.data(), &charAfter);

  if (charAfter == view.data() or result->first == HUGE_VAL)
    result.reset();
  else result->second = size_t(charAfter - view.data());

  return result;
}

tl::expected<std::vector<Token>, Error> tokenize(std::string_view expression)
{
  const std::string_view orig_expr = expression;
  std::vector<Token> parsing;

  auto is_seperator = [](const char ch) {
    static constexpr std::array separators = {'+', '-', '*', '/', '^', ' ', '(', ')'};
    return std::ranges::any_of(separators, [&ch](const char op){ return op == ch; });
  };

  auto is_digit = [](const char ch)
  {
    return std::isdigit(static_cast<unsigned char>(ch));
  };

  auto is_argument_separator = [](const char ch)
  {
    return ch == ',' or ch == ';';
  };

  bool openingParenthesis = true, numberSign = true, value = true, canEnd = false,
       ope = false, closingParenthesis = false;

  enum : bool { FUNCTION_CALL_PTH, NORMAL_PTH};
  std::stack<bool> last_opened_pth;

  auto it = expression.cbegin();
  while (it != expression.cend())
  {
    const std::optional<char> next_char = it+1 != expression.cend() ? *(it+1) : std::optional<char>();

    // view on the single character pointed to by 'it'
    const std::string_view char_v = std::string_view(it, 1);

    if (is_digit(*it) or (numberSign and *it == '-' and next_char and is_digit(next_char.value())))
    {
      auto double_val = to_double(std::string_view(it, expression.cend()));

      if (double_val)
      {
        const auto& [double_opt_val, processed_char_num] = *double_val;
        const std::string_view val_str_v(it, processed_char_num);
        // parsing successful
        parsing.push_back(tokens::Number(double_opt_val, tokens::Text(val_str_v, orig_expr)));
        it += processed_char_num;

        openingParenthesis = value = numberSign = false;
        ope = canEnd = closingParenthesis = true;
      }
      else
        return tl::unexpected(Error::wrong_format(
          tokens::Number(std::nan(""), tokens::Text(char_v, orig_expr))));
    }
    else if (tokens::Operator::is_operator(*it))
    {
      if (ope)
      {
        parsing.push_back(tokens::Operator(char_v, orig_expr));

        openingParenthesis = value = true;
        ope = numberSign = closingParenthesis = canEnd = false;
        it++;
      }
      else return tl::unexpected(Error::unexpected(tokens::Operator(char_v, orig_expr)));
    }
    else if (*it == '(')
    {
      if (openingParenthesis)
      {
        if (not parsing.empty() and std::holds_alternative<tokens::Function>(parsing.back()))
        {
          parsing.emplace_back(tokens::FunctionCallStart(char_v, orig_expr));
          last_opened_pth.push(FUNCTION_CALL_PTH);
        }
        else
        {
          parsing.emplace_back(tokens::OpeningParenthesis(char_v, orig_expr));
          last_opened_pth.push(NORMAL_PTH);
        }

        numberSign = value = openingParenthesis = true;
        ope = closingParenthesis = canEnd = false;
        it++;
      }
      else return tl::unexpected(Error::unexpected(tokens::OpeningParenthesis(char_v, orig_expr)));
    }
    else if (*it == ')')
    {
      if (closingParenthesis and not last_opened_pth.empty())
      {
        if (last_opened_pth.top() == FUNCTION_CALL_PTH)
        {
          parsing.emplace_back(tokens::FunctionCallEnd(char_v, orig_expr));
        }
        else parsing.emplace_back(tokens::ClosingParenthesis(char_v, orig_expr));

        last_opened_pth.pop();

        ope = canEnd = closingParenthesis = true;
        value = numberSign = openingParenthesis = false;
        it++;
      }
      else return tl::unexpected(Error::unexpected(tokens::ClosingParenthesis(char_v, orig_expr)));
    }
    else if (*it == ' ')
      // spaces are skipped
      it++;
    else if (is_argument_separator(*it))
    {
      if (not last_opened_pth.empty() and last_opened_pth.top() == FUNCTION_CALL_PTH)
        parsing.emplace_back(tokens::FunctionArgumentSeparator(char_v, orig_expr));
      else return tl::unexpected(Error::unexpected(tokens::FunctionArgumentSeparator(char_v, orig_expr)));

      openingParenthesis = numberSign = value = true;
      canEnd = ope = closingParenthesis = false;
      it++;
    }
    else
    {
      if (value)
      {
        // the only possibilities left are variables and functions
        // to differentiate between them, functions always are followed by an opening parenthesis
        // e.g. "cos("

        const auto token_begin = it;
        while (it != expression.cend() and
               not is_seperator(*it) and
               not is_argument_separator(*it)) { it++; }

        const std::string_view token_v(token_begin, it);

        if (it == expression.cend() or *it != '(')
        {
          // can only be a variable when we reach the end of the expression
          parsing.emplace_back(tokens::Variable(token_v, orig_expr));

          openingParenthesis = numberSign = value = false;
          canEnd = ope = closingParenthesis = true;
        }
        else
        {
          parsing.emplace_back(tokens::Function(token_v, orig_expr));

          canEnd = closingParenthesis = ope = numberSign = value = false;
          openingParenthesis = true;
        }
      }
      else return tl::unexpected(Error::unexpected(tokens::Unkown(char_v, orig_expr)));
    }
  }

  if (not last_opened_pth.empty())
  {
    std::string_view expr_cend = std::string_view(it, 0);
    if (last_opened_pth.top() == FUNCTION_CALL_PTH)
      return tl::unexpected(Error::missing(tokens::FunctionCallEnd(expr_cend, orig_expr)));
    else return tl::unexpected(Error::missing(tokens::ClosingParenthesis(expr_cend, orig_expr)));
  }

  if (not canEnd)
  {
    std::string_view expr_cend = std::string_view(it, 0);
    return tl::unexpected(Error::unexpected(tokens::EndOfExpression(expr_cend, orig_expr)));
  }

  return parsing;
}


bool is_valid_name(std::string_view name)
{
  auto parsing = tokenize(name);
  return parsing and parsing->size() == 1
         and std::holds_alternative<tokens::Variable>(parsing->front());
}

tl::expected<
  std::vector<std::span<const Token>::iterator>,
  Error
> get_non_pth_enclosed_tokens(std::span<const Token> tokens)
{
  std::vector<std::span<const Token>::iterator> non_pth_enclosed_tokens;

  enum : bool { FUNCTION_CALL_PTH, NORMAL_PTH};
  std::stack<bool> last_opened_pth;

  // search for parentheses
  for (auto tokenIt = tokens.begin() ; tokenIt != tokens.end() ; tokenIt++)
  {
    if (std::holds_alternative<tokens::OpeningParenthesis>(*tokenIt))
    {
      last_opened_pth.push(NORMAL_PTH);
    }
    else if (std::holds_alternative<tokens::FunctionCallStart>(*tokenIt))
    {
      last_opened_pth.push(FUNCTION_CALL_PTH);
    }
    else if (std::holds_alternative<tokens::FunctionCallEnd>(*tokenIt))
    {
      if (not last_opened_pth.empty() and last_opened_pth.top() == FUNCTION_CALL_PTH)
        last_opened_pth.pop();
      else return tl::unexpected(Error::unexpected(text_token(*tokenIt)));
    }
    else if (std::holds_alternative<tokens::ClosingParenthesis>(*tokenIt))
    {
      if (not last_opened_pth.empty() and last_opened_pth.top() == NORMAL_PTH)
        last_opened_pth.pop();
      else return tl::unexpected(Error::unexpected(text_token(*tokenIt)));
    }
    // if not a parenthesis, and the token is not enclosed within parentheses, push it
    else if (last_opened_pth.empty())
      non_pth_enclosed_tokens.push_back(tokenIt);
  }

  return non_pth_enclosed_tokens;
}

/// @brief functor that maps a MathWorld::ConstDynMathObject to tl::expected<ast::Tree, Error>
template <parsing::Type world_type>
struct VariableVisiter
{
  using Ret = tl::expected<parsing::Tree<world_type>, Error>;

  const tokens::Text& var_txt_token;

  Ret operator()(cref<GlobalConstant> global_constant)
  {
    return std::make_unique<node::ast::Node<world_type>>(
      node::GlobalConstant(var_txt_token, global_constant));
  }
  Ret operator()(cref<zc::GlobalVariable<world_type>> global_variable)
  {
    return std::make_unique<node::ast::Node<world_type>>(
      node::GlobalVariable<world_type>(var_txt_token, global_variable));
  }
  Ret operator()(MathWorld<world_type>::UnregisteredObject)
  {
    return tl::unexpected(Error::undefined_variable(var_txt_token));
  }
  Ret operator()(auto&&)
  {
    return tl::unexpected(Error::wrong_object_type(var_txt_token));
  }
};

template <parsing::Type world_type>
struct FunctionVisiter
{
  using Ret = tl::expected<Tree<world_type>, Error>;

  const tokens::Text& func_txt_token;
  std::vector<Tree<world_type>> subnodes;

  Ret operator()(cref<CppUnaryFunction> f)
  {
    if (subnodes.size() != 1) [[unlikely]]
      return tl::unexpected(Error::mismatched_fun_args(func_txt_token));

    return std::make_unique<node::ast::Node<world_type>>(
      node::ast::CppUnaryFunction<world_type>(func_txt_token, f.get(), std::move(subnodes.back())));
  }
  Ret operator()(cref<CppBinaryFunction> f)
  {
    if (subnodes.size() != 2) [[unlikely]]
      return tl::unexpected(Error::mismatched_fun_args(func_txt_token));

    return std::make_unique<node::ast::Node<world_type>>(
      node::ast::CppBinaryFunction<world_type>(func_txt_token,
                                               f.get(),
                                               std::move(subnodes.front()),
                                               std::move(subnodes.back())));
  }
  Ret operator()(cref<zc::Function<world_type>> f)
  {
    if (subnodes.size() != f.get().argument_size()) [[unlikely]]
      return tl::unexpected(Error::mismatched_fun_args(func_txt_token));

    return std::make_unique<node::ast::Node<world_type>>(
      node::ast::Function<world_type>(func_txt_token, f.get(), std::move(subnodes)));
  }
  Ret operator()(cref<zc::Sequence<world_type>> u)
  {
    if (subnodes.size() != 1) [[unlikely]]
      return tl::unexpected(Error::mismatched_fun_args(func_txt_token));

    return std::make_unique<node::ast::Node<world_type>>(
      node::ast::Sequence<world_type>(func_txt_token, u.get(), std::move(subnodes.front())));
  }
  Ret operator()(MathWorld<world_type>::UnregisteredObject)
  {
    return tl::unexpected(Error::undefined_function(func_txt_token));
  }
  Ret operator()(auto&&)
  {
    return tl::unexpected(Error::wrong_object_type(func_txt_token));
  }
};

template <Type type>
tl::expected<Tree<type>, Error> make_tree(std::span<const parsing::Token> tokens,
                                          const MathWorld<type>& world,
                                          const std::vector<std::string>& input_vars)
{
  using Ret = tl::expected<Tree<type>, Error>;

  // when there's only a single token, it can only be number or a variable
  if (tokens.size() == 1)
  {
    return std::visit(overloaded{[&](const tokens::Number& num) -> Ret { return Tree<type>(num); },
                                 [&](const tokens::Variable& var) -> Ret
                                 {
                                   // if variable is in 'input_vars' then treat it as such
                                   // this will avoid name lookup when we evaluate
                                   auto it = std::ranges::find(input_vars, var.name);
                                   if (it != input_vars.end())
                                     // the index is computed with the distance between begin() and 'it'
                                     return Tree<type>(
                                       node::InputVariable(var,
                                                           std::distance(input_vars.begin(), it)));
                                   else
                                     return std::visit(VariableVisiter<type>{var},
                                                       world.get(var.name));
                                 },
                                 [&](const auto& anything_else) -> Ret
                                 { return tl::unexpected(Error::unexpected(anything_else)); }},
                      tokens.back());
  }

  auto expected_non_pth_wrapped_tokens = get_non_pth_enclosed_tokens(tokens);
  if (not expected_non_pth_wrapped_tokens.has_value())
    return tl::unexpected(expected_non_pth_wrapped_tokens.error());

  const auto& non_pth_enclosed_tokens = expected_non_pth_wrapped_tokens.value();

  // expression of the type "(...)"
  if (non_pth_enclosed_tokens.empty() and tokens.size() > 2 and
      std::holds_alternative<tokens::OpeningParenthesis>(tokens.front()) and
      std::holds_alternative<tokens::ClosingParenthesis>(tokens.back()))
  {
    return make_tree(std::span(tokens.begin()+1, tokens.end()-1), world, input_vars);
  }

  // expression of the type "function(...)"
  else if (non_pth_enclosed_tokens.size() == 1 and tokens.size() > 3 and
           std::holds_alternative<tokens::Function>(tokens.front()) and
           std::holds_alternative<tokens::FunctionCallStart>(*(tokens.begin()+1)) and
           std::holds_alternative<tokens::FunctionCallEnd>(tokens.back()))
  {
    /// @todo needs changing to support multi-argument functions
    /// @note here we expect functions that receive that receive a single argument
    auto non_pth_wrapped_args = get_non_pth_enclosed_tokens(
      std::span(tokens.begin() + 2, tokens.end() - 1));

    if (not non_pth_wrapped_args.has_value())
      return tl::unexpected(non_pth_wrapped_args.error());

    // add the FunctionCallEnd token so we handle it in the loop
    non_pth_wrapped_args->push_back(tokens.end()-1);

    std::vector<Tree<type>> subnodes;
    auto last_non_coma_token_it = tokens.begin()+2;
    for (auto tokenIt: *non_pth_wrapped_args)
    {
      if (std::holds_alternative<tokens::FunctionArgumentSeparator>(*tokenIt) or
          std::holds_alternative<tokens::FunctionCallEnd>(*tokenIt))
      {
        auto expected_func_argument = make_tree(std::span(last_non_coma_token_it, tokenIt), world, input_vars);
        if (not expected_func_argument.has_value())
          return expected_func_argument;
        else subnodes.push_back(std::move(expected_func_argument.value()));
        last_non_coma_token_it = tokenIt+1;
      }
    }

    const auto func_txt_token = text_token(tokens.front());
    return std::visit(FunctionVisiter<type>{func_txt_token, std::move(subnodes)},
                      world.get(func_txt_token.name));

    // return ast::node::Function(text_token(tokens.front()), std::move(subnodes));
  }

  // there are tokens that are not within parentheses
  else if (not non_pth_enclosed_tokens.empty())
  {
    // we check for operations
    // loop through the expression by increasing operator priority
    // -> because the deepest parts of the syntax tree are to be calculated first
    for (const auto& [op, op_str]: tokens::Operator::operators)
    {
      for (auto tokenIt: non_pth_enclosed_tokens)
      {
        if (std::holds_alternative<tokens::Operator>(*tokenIt) and
            std::get<tokens::Operator>(*tokenIt).name == op_str)
        {
          // we are not within parentheses, and we are at the right operator priority
          if (tokenIt == tokens.begin() or tokenIt+1 == tokens.end())
            return tl::unexpected(Error::unexpected(text_token(*tokenIt)));

          auto left_hand_side = make_tree(std::span(tokens.begin(), tokenIt), world, input_vars);
          if (not left_hand_side.has_value())
            return left_hand_side;

          auto right_hand_side = make_tree(std::span(tokenIt+1, tokens.end()), world, input_vars);
          if (not right_hand_side.has_value())
            return right_hand_side;

          const zc::CppBinaryFunction* cpp_bin_f = world.template get<zc::CppBinaryFunction>(op_str);

          assert(cpp_bin_f);

          return node::ast::CppBinaryFunction<type>(text_token(*tokenIt),
                                                    *cpp_bin_f,
                                                    std::move(left_hand_side.value()),
                                                    std::move(right_hand_side.value()));
        }
      }
    }
  }

  // if we reach the end of this function, something is not right
  const SubstrInfo substrinfo
    = std::accumulate(tokens.begin(),
                      tokens.end(),
                      substr_info(tokens.front()),
                      [](const SubstrInfo& info, const Token& t1)
                      { return substr_info(t1) + info; });

  return tl::unexpected(Error::unexpected(tokens::Unkown("", substrinfo)));
}

struct RpnMaker
{
  RPN operator () (std::monostate)
  {
    return RPN{std::monostate()};
  }

  static bool check_for_monostate(const RPN& rpn)
  {
    return std::ranges::any_of(rpn,
                               [](const node::rpn::Node& node)
                               { return std::holds_alternative<std::monostate>(node); });
  }

  RPN operator()(const node::ast::CppUnaryFunction<Type::RPN>& func)
  {
    RPN res = std::visit(*this, *func.operand);

    if (check_for_monostate(res)) [[unlikely]]
      return RPN{std::monostate()};

    res.push_back(func);
    return res;
  }

  RPN operator()(const node::ast::Sequence<Type::RPN>& seq)
  {
    RPN res = std::visit(*this, *seq.operand);

    if (check_for_monostate(res)) [[unlikely]]
      return RPN{std::monostate()};

    res.push_back(node::rpn::Sequence(seq, seq.u));
    return res;
  }

  RPN operator()(const node::ast::CppBinaryFunction<Type::RPN>& func)
  {
    RPN res = std::visit(*this, *func.operand1);
    RPN tmp = std::visit(*this, *func.operand2);

    std::ranges::move(tmp, std::back_inserter(res));

    if (check_for_monostate(res)) [[unlikely]]
      return RPN{std::monostate()};

    res.push_back(func);
    return res;
  }

  RPN operator () (const node::ast::Function<Type::RPN>& func)
  {
    RPN res;
    for (const Tree<Type::RPN>& sub_node : func.operands)
    {
      RPN tmp = std::visit(*this, *sub_node);
      if (check_for_monostate(tmp)) [[unlikely]]
        return RPN{std::monostate()};
      else [[likely]]
        std::ranges::move(tmp, std::back_inserter(res));
    }

    res.push_back(node::rpn::Function(func, func.f));
    return res;
  }

  RPN operator () (const node::InputVariable& in_var)
  {
    return RPN(1, in_var);
  }

  RPN operator () (const node::GlobalConstant& var)
  {
    return RPN(1, var);
  }

  RPN operator () (const node::GlobalVariable<Type::RPN>& var)
  {
    return RPN(1, node::rpn::GlobalVariable(var, var.var));
  }

  RPN operator () (const node::Number& number)
  {
    return RPN(1, number);
  }

};

RPN make_RPN(const Tree<Type::RPN>& tree)
{
  return std::visit(RpnMaker{}, *tree);
}

} // namespace parsing
} // namespace zc
