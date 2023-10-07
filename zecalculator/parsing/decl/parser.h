/****************************************************************************
**  Copyright (c) 2023, Adel Kara Slimane <adel.ks@zegrapher.com>
**
**  This file is part of ZeCalculator.
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

#pragma once

#include <zecalculator/parsing/data_structures/token.h>
#include <zecalculator/parsing/data_structures/decl/node.h>
#include <zecalculator/mathworld/decl/mathworld.h>
#include <zecalculator/error.h>

#include <span>

/* TODO: update approach as the following:
    - Parse: aka cut each atom in a formula
    - Evaluate type of atom: separator, number
    - Treat number in a special as to make 1.2E+33 as one atom
    - Check for validity
    - Enable setting custom names for functions and variables
    - Performance improvement: flatten trees
*/

namespace zc {
namespace parsing {

/// @brief interprets "view" as a floating number
/// @returns if successful, the interpreted double and the number of characters interpreted, otherwise empty
std::optional<std::pair<double, size_t>> to_double(std::string_view view);

/// @brief parses the expression into a list of tokens
/// @note the string that is void must remain valid for for the returned instance
///       to remain valid (for both a successful or unsuccessful  parsing)
///       as they contain sub-string views of the input view
tl::expected<std::vector<Token>, Error> tokenize(std::string_view expression);

/// @brief tells if the string_view contains a valid math object name
bool is_valid_name(std::string_view name);

/// @brief makes a syntax tree from from a sequence of tokens
/// @param input_vars: variable names that are considered as input (for functions)
///                    e.g."x" in the function "f" such as "f(x) = cos(x)"
template <Type type>
tl::expected<Tree<type>, Error> make_tree(std::span<const parsing::Token> tokens,
                                          const MathWorld<type>& math_world,
                                          const std::vector<std::string>& input_vars = {});

/// @brief transforms a syntax tree to a flat Reverse Polish / postfix notation representation
RPN make_RPN(const Tree<Type::RPN>& tree);

}
}
