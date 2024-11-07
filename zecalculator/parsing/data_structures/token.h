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

#include <cmath>
#include <variant>
#include <string_view>
#include <string>
#include <cassert>
#include <algorithm>

#include <zecalculator/external/expected.h>
#include <zecalculator/utils/substr_info.h>

namespace zc {
namespace parsing {

namespace tokens {

struct Text
{
  Text() = default;

  Text(std::string_view substr, std::string_view original_expr)
    : name(std::string(substr)), substr_info(SubstrInfo::from_views(substr, original_expr))
  {}

  Text(std::string_view name, size_t begin, size_t size) : name(std::string(name)), substr_info{begin, size} {}

  Text(std::string_view name, SubstrInfo substr_info) : name(std::string(name)), substr_info(substr_info) {}

  /// @brief name of the token, can different from what appears in the expressions
  /// @example '+' is replaced with 'internal::plus' (a valid function name)
  std::string name = {};

  /// @brief information about the location of the original token with the original expression
  /// @example token '+' in '2+2*2' will have: begin=1, size=1
  SubstrInfo substr_info = {};

  bool operator == (const Text& other) const = default;
};

struct Unkown: Text
{
  explicit Unkown(const Text& txt) : Text(txt) {}
  using Text::Text;
};

struct Number: Text
{
  Number(double value, const tokens::Text& text_token): Text(text_token), value(value) {}
  double value = std::nan("");
};

struct Variable: Text
{
  explicit Variable(const Text& txtTok): Text(txtTok) {}
  using Text::Text;
};

struct Function: Text
{
  explicit Function(const Text& txtTok): Text(txtTok) {}
  using Text::Text;
};

struct Operator: Function
{
  using pair_type = std::pair<char, std::string_view>;
  // operators ordered in increasing order of priority
  static constexpr std::array<pair_type, 5> operators = {{{'+', "internal::plus"},
                                                          {'-', "internal::minus"},
                                                          {'*', "internal::multiply"},
                                                          {'/', "internal::divide"},
                                                          {'^', "internal::power"}}};

  constexpr static std::string_view name_of(char op)
  {
    assert(std::ranges::count(operators, op, &pair_type::first) == 1);
    return std::ranges::find(operators, op, &pair_type::first)->second;
  }

  constexpr static bool is_operator(const char ch)
  {
    return std::ranges::any_of(
      operators, [&ch](const char op) { return op == ch; }, &pair_type::first);
  }

  Operator(char op, size_t begin): Function(name_of(op), begin, 1) {}

  Operator(std::string_view op_v, std::string_view original_expr)
    : Function(name_of(op_v.front()), SubstrInfo::from_views(op_v, original_expr))
  {}
};

struct OpeningParenthesis: Text
{
  using Text::Text;
};

struct ClosingParenthesis: Text
{
  using Text::Text;
};

struct FunctionCallStart: Text
{
  using Text::Text;
};

struct FunctionCallEnd: Text
{
  using Text::Text;
};

struct FunctionArgumentSeparator: Text
{
  using Text::Text;
};

struct EndOfExpression: Text // will be used only to signal errors
{
  using Text::Text;
};

}

/// @brief represents a  in a parsed expression
/// @example an operatr '+', a function name 'cos', a variable 'x', a number '-3.14E+2'
using TokenType =
    std::variant<tokens::Unkown, tokens::Number, tokens::Variable,
                 tokens::Function, tokens::Operator, tokens::OpeningParenthesis,
                 tokens::ClosingParenthesis, tokens::FunctionCallStart,
                 tokens::FunctionCallEnd, tokens::FunctionArgumentSeparator,
                 tokens::EndOfExpression>;

struct Token: TokenType
{
  using TokenType::TokenType;
};

inline tokens::Text text_token(const Token& token)
{
  return std::visit([](const auto& tk) -> tokens::Text { return tk; }, token);
}

inline SubstrInfo substr_info(const Token& token)
{
  return text_token(token).substr_info;
}

}
}
