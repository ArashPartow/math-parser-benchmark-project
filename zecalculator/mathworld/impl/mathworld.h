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

#include <zecalculator/mathworld/decl/mathworld.h>
#include <zecalculator/parsing/parser.h>

namespace zc {

template <parsing::Type type>
template <class ObjectType, class... Arg>
  requires(tuple_contains_v<MathObjects<type>, ObjectType>
           and (sizeof...(Arg) == 0 or requires(ObjectType o) { o.set(std::declval<Arg>()...); }))
tl::expected<ref<ObjectType>, NameError> MathWorld<type>::add(std::string_view name, Arg &&...arg)
{
  if (not parsing::is_valid_name(name))
    return tl::unexpected(NameError::invalid_format(name));
  else if (contains(name))
    return tl::unexpected(NameError::already_taken(name));

  SlottedDeque<ObjectType> &object_container = std::get<SlottedDeque<ObjectType>>(math_objects);

  size_t id;
  // compile time check if objects needs MathWorld pointer
  if constexpr (requires { ObjectType(this); })
    id = object_container.push(ObjectType(this));
  else id = object_container.push(ObjectType());

  ObjectType& world_object = object_container[id];
  world_object.set_name(std::string(name));

  inventory[std::string(name)] = std::ref(world_object);

  if constexpr (sizeof...(Arg) > 0)
    world_object.set(std::forward<Arg>(arg)...);

  return world_object;
}

}
