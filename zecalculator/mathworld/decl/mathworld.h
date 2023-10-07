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

#include <zecalculator/utils/name_map.h>
#include <zecalculator/utils/refs.h>
#include <zecalculator/utils/slotted_deque.h>
#include <zecalculator/utils/utils.h>
#include <zecalculator/math_objects/builtin_binary_functions.h>
#include <zecalculator/math_objects/builtin_unary_functions.h>
#include <zecalculator/math_objects/global_constant.h>
#include <zecalculator/utils/tuple.h>
#include <zecalculator/math_objects/object_list.h>

#include <string>
#include <variant>
#include <string_view>

namespace zc {

template <parsing::Type type>
class MathWorld;

namespace ast {
  using MathWorld = zc::MathWorld<parsing::Type::AST>;
}

namespace rpn {
  using MathWorld = zc::MathWorld<parsing::Type::RPN>;
}


struct NameError
{
  enum Type {ALREADY_TAKEN, INVALID_FORMAT};

  static NameError already_taken(std::string_view name)
  {
    return NameError{.type = ALREADY_TAKEN, .name = std::string(name)};
  }

  static NameError invalid_format(std::string_view name)
  {
    return NameError{.type = INVALID_FORMAT, .name = std::string(name)};
  }

  Type type;
  std::string name;
};

template <parsing::Type type>
class MathWorld
{
public:

  class UnregisteredObject {};

  /// @brief type used when looking up a match object with a name at runtime
  using DynMathObject = to_variant_t<tuple_type_cat_t<std::tuple<UnregisteredObject>, tuple_transform_t<ref, MathObjects<type>>>>;

  /// @brief const version of the one above
  using ConstDynMathObject = to_variant_t<tuple_type_cat_t<std::tuple<UnregisteredObject>, tuple_transform_t<cref, MathObjects<type>>>>;

  /// @brief default constructor that defines the usual functions and global constants
  MathWorld()
    : MathWorld(builtin_unary_functions, builtin_binary_functions, builtin_global_constants){};

  template <class ObjectType1, size_t size1, class... ObjectTypeN, size_t... sizeN>
  MathWorld(const std::array<std::pair<std::string_view, ObjectType1>, size1>& objects1,
             const std::array<std::pair<std::string_view, ObjectTypeN>, sizeN>&... objectsN)
    : MathWorld(objectsN...)
  {
    for(auto [name, obj]: objects1)
      add<ObjectType1>(name, obj);
  }

  template <class ObjectType, size_t size>
  MathWorld(const std::array<std::pair<std::string_view, ObjectType>, size>& objects)
  {
    for(auto [name, obj]: objects)
      add<ObjectType>(name, obj);
  }

  /// @brief get object from name, the underlying type is to be dynamically resolved at runtime
  /// @note const version
  ConstDynMathObject get(std::string_view name) const
  {
    auto it = inventory.find(name);
    return it != inventory.end() ? to_const(it->second) : ConstDynMathObject();
  }

  /// @brief get object from name, the underlying type is to be dynamically resolved at runtime
  DynMathObject get(std::string_view name)
  {
    auto it = inventory.find(name);
    return it != inventory.end() ? it->second : DynMathObject();
  }

  /// @brief get object 'ObjectType' from name, if it exists, nullptr otherwise
  template <class ObjectType>
    requires tuple_contains_v<MathObjects<type>, ObjectType>
  ObjectType* get(std::string_view name)
  {
    DynMathObject dyn_obj = get(name);
    if (std::holds_alternative<ref<ObjectType>>(dyn_obj))
      return &std::get<ref<ObjectType>>(dyn_obj).get();
    else return nullptr;
  }

  /// @brief get object 'ObjectType' from name, if it exists, nullptr otherwise
  /// @note const version
  template <class ObjectType>
    requires tuple_contains_v<MathObjects<type>, ObjectType>
  const ObjectType* get(std::string_view name) const
  {
    ConstDynMathObject dyn_obj = get(name);
    if (std::holds_alternative<cref<ObjectType>>(dyn_obj))
      return &std::get<cref<ObjectType>>(dyn_obj).get();
    else return nullptr;
  }

  /// @brief get object 'ObjectType' from id
  /// @note ids are not unique, they live in different sets between ObjectTypes
  template <class ObjectType>
    requires tuple_contains_v<MathObjects<type>, ObjectType>
  ObjectType& get(size_t id)
  {
    return std::get<SlottedDeque<ObjectType>>(math_objects).at(id);
  }

  /// @brief get object 'ObjectType' from id
  /// @note const version
  template <class ObjectType>
    requires tuple_contains_v<MathObjects<type>, ObjectType>
  const ObjectType& get(size_t id) const
  {
    return std::get<SlottedDeque<ObjectType>>(math_objects).at(id);
  }

  /// @brief default constructs an ObjectType in the world, under the name 'name'
  ///        then, if there are extra args, forwards them the member function .set() of the newly added object
  /// @param arg...: arguments passed to the set() member function of the object
  /// @note returns a NameError if the name is already taken or has the wrong format, leaves the world unchanged.
  template <class ObjectType, class... Arg>
    requires(tuple_contains_v<MathObjects<type>, ObjectType>
             and (sizeof...(Arg) == 0 or requires(ObjectType o) { o.set(std::declval<Arg>()...); }))
  tl::expected<ref<ObjectType>, NameError> add(std::string_view name, Arg&&... arg);

  /// @brief says if an object with the given name exists within the world
  bool contains(std::string_view name) const
  {
    return inventory.find(name) != inventory.end();
  }

  /// @brief maximum recursion depth to reach before returning an error
  size_t max_recursion_depth = 20;


protected:

  /// @brief converts a DynMathObject to a ConstDynMathObject
  ConstDynMathObject to_const(DynMathObject obj) const
  {
    return std::visit(
      overloaded{
        [](UnregisteredObject) -> ConstDynMathObject { return UnregisteredObject(); },
        [](auto&& val) -> ConstDynMathObject { return std::cref(val.get()); }
      },
      obj);
  }

  /// @brief maps an object name to its type and ID (index within the container that holds it)
  name_map<DynMathObject> inventory;

  tuple_transform_t<SlottedDeque, MathObjects<type>> math_objects;

};

}
