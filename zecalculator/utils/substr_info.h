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
#include <cassert>

namespace zc {


/// @brief This class is some kind of meta std::string_view
///        it contains the beginning index and the size of a substring
///        without saving a reference/pointer/copy to the original string
///        a substring can be retrieved by giving it the original expression
struct SubstrInfo
{
  constexpr static SubstrInfo from_views(std::string_view substr, std::string_view full_str)
  {
    assert(full_str.data() <= substr.data()
           and substr.data() + substr.size() <= full_str.data() + full_str.size());

    return SubstrInfo{.begin = size_t(substr.data() - full_str.data()), .size = substr.size()};
  };

  /// @brief returns the substring this class is refering to within the full string 'full_str'
  /// @example *this == {2, 3}, full_str = "2+cos(2)" returns "cos"
  /// @note if the full_str isn't long enough (wrong string given by the end-user), returns empty string_view
  std::string_view substr(std::string_view full_str) const
  {
    if (begin + size > full_str.size())
      return std::string_view();
    return full_str.substr(begin, size);
  }

  /// @brief returns the substring that is before substr(full_str)
  /// @example *this == {2, 3}, full_str = "2+cos(3)" returns "2+"
  std::string_view substr_before(std::string_view full_str) const
  {
    return full_str.substr(0, begin);
  }

  /// @brief returns the substring that is after substr(full_str)
  /// @example *this == {2, 3}, full_str = "2+cos(3)" returns "(3)"
  std::string_view substr_after(std::string_view full_str) const
  {
    if (begin + size > full_str.size())
      return std::string_view();
    else return full_str.substr(begin + size);
  }

  ///@brief begin position in the original string
  size_t begin = 0;

  ///@brief substring size
  size_t size = 0;

  bool operator == (const SubstrInfo& other) const = default;
};

inline SubstrInfo operator + (const SubstrInfo& a, const SubstrInfo& b)
{
  const size_t begin = std::min(a.begin, b.begin);
  return SubstrInfo
  {
    .begin = begin, .size = std::max(a.begin + a.size, b.begin + b.size) - begin
  };
}

}
