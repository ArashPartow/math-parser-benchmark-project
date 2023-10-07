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

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <span>

#include <zecalculator/error.h>
#include <zecalculator/external/expected.h>
#include <zecalculator/parsing/data_structures/decl/node.h>
#include <zecalculator/parsing/shared.h>
#include <zecalculator/utils/name_map.h>

/* TODO: update approach as the following:
   - Check for validity
   - Enable setting custom names for functions and variables
   - Performance improvement: flatten trees
*/

namespace zc {

template <parsing::Type type>
class MathWorld;

namespace eval {
namespace rpn {
  struct Evaluator;
}

namespace ast {
  struct Evaluator;
}
}

namespace parsing {
  struct RpnMaker;
}

struct Ok {};
struct Empty {};

struct InvalidInputVar
{
  std::string var_name;
};

using Vars = std::vector<std::string>;

template <parsing::Type type>
class Function
{
public:

  Function(Function&& f) = default;
  Function& operator = (Function&& f) = default;

  const std::string& get_name() const;

  /// @brief sets the names of the input variables
  /// @note the order of the input variables is important when calling the function
  ///       with positional arguments
  void set_input_vars(std::vector<std::string> input_vars);

  /// \brief set the expression
  void set_expression(std::string expr);

  /// @brief sets both the input_vars and the expression
  void set(std::vector<std::string> input_vars, std::string expr);

  /// @brief returns the number of input variables, if they are valid
  std::optional<size_t> argument_size() const;

  /// @brief gives the math objects that are present in this function's expression
  auto direct_dependencies() const;

  /// @brief tests if the function is valid, i.e. has a valid expression and input vars
  operator bool () const;

  std::variant<Ok, Empty, Error> parsing_status() const;

  const tl::expected<parsing::Parsing<type>, Error>& get_parsing() const;

  /// @brief evaluation on a given math world with the given input
  tl::expected<double, Error> evaluate(const std::vector<double>& args) const;

  // span version
  tl::expected<double, Error> evaluate(std::span<const double> args) const;

  /// @brief evaluation on a given math world with the given input
  /// @note operator style
  tl::expected<double, Error> operator()(const std::vector<double>& args) const;

  // span version
  tl::expected<double, Error> operator()(std::span<const double> args) const;

protected:

  // constructor reserved for MathWorld when using add() function
  Function(const MathWorld<type>* mathworld)
    requires(type == parsing::Type::AST);

  // constructor reserved for MathWorld when using add() function
  Function(const MathWorld<type>* mathworld)
    requires (type == parsing::Type::RPN);

  /// @note version that tracks the current recursion depth
  tl::expected<double, Error> evaluate(std::span<const double> args,
                                       size_t current_recursion_depth) const;

  void set_name(std::string name);

  std::string name;
  std::string expression;

  friend struct eval::rpn::Evaluator;
  friend struct eval::ast::Evaluator;
  friend struct parsing::RpnMaker;

  tl::expected<parsing::Parsing<type>, Error> parsed_expr;
  tl::expected<std::vector<std::string>, InvalidInputVar> vars;

  // non-owning pointer to the mathworld that contains this object
  const MathWorld<type>* mathworld;

  template <parsing::Type>
  friend class MathWorld;
};

}
