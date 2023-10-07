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

#include <zecalculator/math_objects/decl/expression.h>
#include <zecalculator/math_objects/impl/function.h>

/* TODO: update approach as the following:
   - Check for validity
   - Enable setting custom names for functions and variables
   - Performance improvement: flatten trees
*/

namespace zc {

namespace eval {
  struct Variable;
}

template <parsing::Type type>
Expression<type>::Expression(const MathWorld<type>* mathworld) : Function<type>(mathworld)
{}

template <parsing::Type type>
void Expression<type>::set(std::string expression)
{
  Function<type>::set_expression(std::move(expression));
}

template <parsing::Type type>
tl::expected<double, Error> Expression<type>::evaluate() const
{
  return Function<type>::evaluate(std::span<double>());
}

template <parsing::Type type>
tl::expected<double, Error> Expression<type>::operator ()() const
{
  return Function<type>::evaluate(std::span<double>());
}

template <parsing::Type type>
tl::expected<double, Error> Expression<type>::evaluate(size_t current_recursion_depth) const
{
  return Function<type>::evaluate(std::span<double>(), current_recursion_depth);
}

}
