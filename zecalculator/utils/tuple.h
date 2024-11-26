#pragma once

#include <tuple>
#include <variant>
#include <type_traits>

namespace zc {


// ================== to_variant

/// @brief transforms an std::tuple to an std::variant
template <class T>
struct to_variant;

template <class...T>
struct to_variant<std::tuple<T...>>
{
  using type = std::variant<T...>;
};

template <class T>
using to_variant_t = to_variant<T>::type;

// ================== to_variant

// ================== tuple_map

/// @brief transforms std::tuple<T, ...> to std::tuple<Mapper<T>::type, ...>
template <template <class> class Mapper, class T>
struct tuple_map;

template <template <class> class Mapper, class...T>
struct tuple_map<Mapper, std::tuple<T...>>
{
  using type = std::tuple<typename Mapper<T>::type...>;
};

template <template <class> class Mapper, class T>
using tuple_map_t = tuple_map<Mapper, T>::type;

// ================== tuple_map

// ================== tuple_transform

/// @brief transforms std::tuple<T, ...> to std::tuple<U<T>, ...>
template <template <class> class U, class T>
struct tuple_transform;

template <template <class> class U, class...T>
struct tuple_transform<U, std::tuple<T...>>
{
  using type = std::tuple<U<T>...>;
};

template <template <class> class U, class T>
using tuple_transform_t = tuple_transform<U, T>::type;

// ================== tuple_transform

// ================== tuple_contains

/// @brief says whether the tuple 'T' contains 'U' as one of its types
template <class T, class U>
struct tuple_contains;

template <class...T, class U>
struct tuple_contains<std::tuple<T...>, U>
{
  static constexpr bool value = (std::is_same_v<T, U> or ...);
};

template <class T, class U>
inline constexpr bool tuple_contains_v = tuple_contains<T, U>::value;

// ================== tuple_contains

// ================== tuple_type_cat

/// @brief out of the tuples 'Ti == std::tuple<Uij...>' makes the tuples who's the
///        concatenation of all of the types std::tuple<Uij...>'
template <class... T>
struct tuple_type_cat;

template <class...Ui, class... Uj>
struct tuple_type_cat<std::tuple<Ui...>, std::tuple<Uj...>>
{
  using type = std::tuple<Ui..., Uj...>;
};

template <class T1, class T2, class... T>
struct tuple_type_cat<T1, T2, T...>
{
  using type = tuple_type_cat<typename tuple_type_cat<T1, T2>::type, T...>;
};

template <class... T>
using tuple_type_cat_t = tuple_type_cat<T...>::type;

// ================== tuple_type_cat

}
