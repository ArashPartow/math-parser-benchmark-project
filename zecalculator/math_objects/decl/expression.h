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

#include <zecalculator/math_objects/decl/function.h>
#include <zecalculator/parsing/data_structures/decl/node.h>
#include <zecalculator/parsing/decl/parser.h>
#include <zecalculator/parsing/shared.h>

/* TODO: update approach as the following:
   - Check for validity
   - Enable setting custom names for functions and variables
   - Performance improvement: flatten trees
*/

namespace zc {

template <parsing::Type type>
class MathWorld;

/// @brief a class that represents a general expression
/// @note  an expression is a function that does not have any input
template <parsing::Type type>
class Expression: public Function<type>
{
public:

  void set(std::string expression);

  tl::expected<double, Error> evaluate() const;

  tl::expected<double, Error> operator ()() const;

protected:

  // constructor reserved for MathWorld when using add() function
  Expression(const MathWorld<type>* mathworld);

  tl::expected<double, Error> evaluate(size_t current_recursion_depth) const;

  friend struct eval::rpn::Evaluator;
  friend struct eval::ast::Evaluator;

  // hide functions that are not needed from Function
  using Function<type>::evaluate;
  using Function<type>::set_input_vars;

  template <parsing::Type>
  friend class MathWorld;

};

}
