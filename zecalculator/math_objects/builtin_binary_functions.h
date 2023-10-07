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

#include <string_view>
#include <array>
#include <cmath>
#include <string>

#include <zecalculator/parsing/data_structures/token.h>

namespace zc {

using CppBinaryFunctionPtr = double (*) (double, double);

class CppBinaryFunction
{
public:
  constexpr CppBinaryFunction() = default;

  constexpr CppBinaryFunction(CppBinaryFunctionPtr f_ptr) : f_ptr(f_ptr) {};

  void set_name(std::string name) { this->name = std::move(name); }

  const std::string& get_name() const { return name; }

  constexpr void set(CppBinaryFunction f) {f_ptr = f.f_ptr; }

  double operator()(double a, double b) const
  {
    return f_ptr(a ,b);
  }

  bool operator == (const CppBinaryFunction&) const = default;

protected:
  CppBinaryFunctionPtr f_ptr = nullptr;
  std::string name;
};

inline double plus(const double a, const double b)
{
  return a + b;
}

inline double minus(const double a, const double b)
{
  return a - b;
}

inline double multiply(const double a, const double b)
{
  return a * b;
}

inline double divide(const double a, const double b)
{
  return a / b;
}


// we save the names along with the function pointers for convenience
// we could save only the function pointers, and the names only in the inventory
inline std::array<std::pair<std::string_view, CppBinaryFunction>, 5> builtin_binary_functions = {{
  {parsing::tokens::Operator::name_of('+'), plus},
  {parsing::tokens::Operator::name_of('-'), minus},
  {parsing::tokens::Operator::name_of('*'), multiply},
  {parsing::tokens::Operator::name_of('/'), divide},
  {parsing::tokens::Operator::name_of('^'), CppBinaryFunction(std::pow)},
}};

inline CppBinaryFunction binary_func_from_op(char op)
{
  switch (op)
  {
    case '+':
      return plus;
    case '-':
      return minus;
    case '*':
      return multiply;
    case '/':
      return divide;
    case '^':
      return CppBinaryFunction(std::pow);
    default:
      return nullptr;
  }
}

}
