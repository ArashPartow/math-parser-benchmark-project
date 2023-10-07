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
#include <numbers>
#include <string>

namespace zc {

struct GlobalConstant
{
  constexpr GlobalConstant() = default;

  constexpr GlobalConstant(double val): value(val) {}

  constexpr void set(GlobalConstant cst) {value = cst.value;}

  void set_name(std::string name) { this->name = std::move(name); }

  const std::string& get_name() const { return name; }

  double value = 0;
  std::string name;
};

inline std::array<std::pair<std::string_view, GlobalConstant>, 5> builtin_global_constants =
{{
  {"math::pi", std::numbers::pi},
  {"math::π",  std::numbers::pi},
  {"physics::kB", 1.380649e-23},   // Blotzmann constant, SI units
  {"physics::h",  6.62607015e-34}, // Plank constant, SI units
  {"physics::c",  299792458},      // Speed of light in vacuum, SI units
}};

}
