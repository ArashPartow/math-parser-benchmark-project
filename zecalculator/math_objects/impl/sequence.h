#pragma once

#include <zecalculator/math_objects/decl/sequence.h>

namespace zc {

template <parsing::Type type>
Sequence<type>::Sequence(const MathWorld<type>* mathworld) : Function<type>(mathworld)
{}

template <parsing::Type type>
void Sequence<type>::set(std::string var_name,
                         const std::string& expr,
                         std::vector<double> first_vals)
{
  values = std::move(first_vals);
  Function<type>::set(std::vector{var_name}, expr);
}

template <parsing::Type type>
void Sequence<type>::set_expression(const std::string& expr)
{
  Function<type>::set_expression(expr);
}

template <parsing::Type type>
void Sequence<type>::set_input_var(std::string var_name)
{
  this->set_input_vars(std::vector {var_name});
}

template <parsing::Type type>
void Sequence<type>::set_first_values(std::vector<double> first_vals)
{
  values = std::move(first_vals);
}

template <parsing::Type type>
void Sequence<type>::set_first_val_index(int index)
{
  first_val_index = index;
  values.clear();
}

template <parsing::Type type>
constexpr int Sequence<type>::get_first_val_index() const { return first_val_index; };

template <parsing::Type type>
tl::expected<double, Error> Sequence<type>::evaluate(double index,
                                                     size_t current_recursion_depth) const
{
  if (this->mathworld->max_recursion_depth < current_recursion_depth) [[unlikely]]
    return tl::unexpected(Error::recursion_depth_overflow());
  // round double to nearest integer
  int integer_index = std::lround(index);

  if (integer_index < first_val_index) [[unlikely]]
    return std::nan("");
  else if (size_t(integer_index - first_val_index) < values.size())
    return values[size_t(integer_index - first_val_index)];
  else return Function<type>::evaluate(std::vector{double(integer_index)}, current_recursion_depth);
}

template <parsing::Type type>
tl::expected<double, Error> Sequence<type>::evaluate(double index) const
{
  return evaluate(index, 0);
}

template <parsing::Type type>
tl::expected<double, Error> Sequence<type>::operator ()(double index) const
{
  return evaluate(index);
}

}
