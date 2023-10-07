#pragma once

#include <functional>

namespace zc {

template <class T>
using cref = std::reference_wrapper<const T>;

template <class T>
using ref = std::reference_wrapper<T>;

}
