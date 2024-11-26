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

namespace zc {

using CppUnaryFunctionPtr = double (*) (double);

class CppUnaryFunction
{
public:
  constexpr CppUnaryFunction() = default;

  constexpr CppUnaryFunction(CppUnaryFunctionPtr f_ptr) : f_ptr(f_ptr) {};

  constexpr void set(CppUnaryFunction f) {f_ptr = f.f_ptr; }

  void set_name(std::string name) { this->name = std::move(name); }

  const std::string& get_name() const { return name; }

  double operator()(double a) const
  {
    return f_ptr(a);
  }

protected:
  CppUnaryFunctionPtr f_ptr = nullptr;
  std::string name;
};

// we save the names along with the function pointers for convenience
// we could save only the function pointers, and the names only in the inventory
inline std::array<std::pair<std::string_view, CppUnaryFunction>, 30> builtin_unary_functions = {{
  {"cos",   CppUnaryFunction(std::cos)},
  {"sin",   CppUnaryFunction(std::sin)},
  {"tan",   CppUnaryFunction(std::tan)},

  {"acos",  CppUnaryFunction(std::acos)},
  {"asin",  CppUnaryFunction(std::asin)},
  {"atan",  CppUnaryFunction(std::atan)},

  {"cosh",  CppUnaryFunction(std::cosh)},
  {"sinh",  CppUnaryFunction(std::sinh)},
  {"tanh",  CppUnaryFunction(std::tanh)},

  {"ch",    CppUnaryFunction(std::cosh)},
  {"sh",    CppUnaryFunction(std::sinh)},
  {"th",    CppUnaryFunction(std::tanh)},

  {"acosh", CppUnaryFunction(std::acosh)},
  {"asinh", CppUnaryFunction(std::asinh)},
  {"atanh", CppUnaryFunction(std::atanh)},

  {"ach",   CppUnaryFunction(std::acosh)},
  {"ash",   CppUnaryFunction(std::asinh)},
  {"ath",   CppUnaryFunction(std::atanh)},

  {"sqrt",  CppUnaryFunction(std::sqrt)},
  {"log",   CppUnaryFunction(std::log10)},
  {"lg",    CppUnaryFunction(std::log2)},
  {"ln",    CppUnaryFunction(std::log)},
  {"abs",   CppUnaryFunction(std::abs)},
  {"exp",   CppUnaryFunction(std::exp)},
  {"floor", CppUnaryFunction(std::floor)},
  {"ceil",  CppUnaryFunction(std::ceil)},
  {"erf",   CppUnaryFunction(std::erf)},
  {"erfc",  CppUnaryFunction(std::erfc)},
  {"gamma", CppUnaryFunction(std::tgamma)},
  {"Γ",     CppUnaryFunction(std::tgamma)},
}};

inline CppUnaryFunction unary_func_from_name(std::string_view name)
{
  for(auto&& [f_name, f]: builtin_unary_functions)
  {
    if (f_name == name)
      return f;
  };
  return nullptr;
}

}
