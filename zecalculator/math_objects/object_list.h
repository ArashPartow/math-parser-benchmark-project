#pragma once

#include <zecalculator/math_objects/aliases.h>
#include <zecalculator/parsing/shared.h>

#include <tuple>

namespace zc {

template <parsing::Type type>
using MathObjects = std::tuple<CppUnaryFunction,
                               CppBinaryFunction,
                               GlobalConstant,
                               Function<type>,
                               GlobalVariable<type>,
                               Sequence<type>>;
}
