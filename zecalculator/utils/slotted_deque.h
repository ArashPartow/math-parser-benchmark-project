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

#include <deque>
#include <cstddef>
#include <optional>
#include <stack>

namespace zc {

/// @brief a vector of T, where each element keeps its index
///        during its whole lifetime
template <class T>
class SlottedDeque: protected std::deque<std::optional<T>>
{
  using Parent = std::deque<std::optional<T>>;

public:
  SlottedDeque() = default;

  using Parent::size;

  /// @brief finds the a free slot, puts 'val' in it, then returns the slot index
  size_t push(T val)
  {
    if (free_slots.empty())
    {
      const size_t slot = size();
      Parent::push_back(std::move(val));
      return slot;
    }
    else
    {
      const size_t slot = free_slots.top();
      free_slots.pop();
      Parent::operator[](slot).emplace(std::move(val));
      return slot;
    }
  }

  ///@brief frees the slot 'slot'
  void pop(const size_t slot)
  {
    (*this)[slot].reset();
    free_slots.push(slot);
  }

  /// @brief returns the element T at 'slot', bounds checked
  const T& at(size_t slot) const
  {
    return Parent::at(slot).value();
  }

  /// @brief returns the element T at 'slot', bounds checked
  T& at(size_t slot)
  {
    return Parent::at(slot).value();
  }

  /// @brief returns the element T at 'slot'
  const T& operator [] (size_t slot) const
  {
    return *Parent::operator [] (slot);
  }

    /// @brief returns the element T at 'slot'
  T& operator [] (size_t slot)
  {
    return *Parent::operator [] (slot);
  }

protected:
  std::stack<size_t> free_slots;
};

}
