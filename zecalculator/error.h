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

#include <cstdint>
#include <zecalculator/parsing/data_structures/token.h>

namespace zc {

struct Error
{
  // type of error
  enum Type : uint8_t
  {
    UNKNOWN = 0,
    WRONG_FORMAT,
    UNEXPECTED,
    MISSING,
    UNDEFINED_VARIABLE,
    UNDEFINED_FUNCTION,
    CALLING_FUN_ARG_COUNT_MISMATCH,
    CALLED_FUN_ARG_COUNT_MISMATCH,
    NOT_IMPLEMENTED,
    EMPTY_EXPRESSION,
    INVALID_FUNCTION,
    CALLING_INVALID_FUNCTION, // expression that contains a function who cannot return values
    RECURSION_DEPTH_OVERFLOW, // maximum recursion depth has been reached
    WRONG_OBJECT_TYPE, // object has been used as a different type as it actually is, example "2+cos" (where cos is a function used here as variable)
  };

  static Error unexpected(parsing::tokens::Text  token)
  {
    return Error {.error_type = UNEXPECTED, .token = token};
  }

  static Error wrong_format(parsing::tokens::Text  token)
  {
    return Error {.error_type = WRONG_FORMAT, .token = token};
  }

  static Error missing(parsing::tokens::Text  token)
  {
    return Error {.error_type = MISSING, .token = token};
  }

  static Error unkown()
  {
    return Error {UNKNOWN};
  }

  static Error undefined_variable(parsing::tokens::Text tokenTxt)
  {
    return Error {UNDEFINED_VARIABLE, tokenTxt};
  }

  static Error undefined_function(parsing::tokens::Text tokenTxt)
  {
    return Error {UNDEFINED_FUNCTION, tokenTxt};
  }

  static Error mismatched_fun_args(parsing::tokens::Text tokenTxt)
  {
    return Error {CALLING_FUN_ARG_COUNT_MISMATCH, tokenTxt};
  }

  static Error mismatched_fun_args()
  {
    return Error {CALLED_FUN_ARG_COUNT_MISMATCH};
  }

  static Error not_implemented(parsing::tokens::Text tokenTxt)
  {
    return Error {NOT_IMPLEMENTED, tokenTxt};
  }

  static Error empty_expression()
  {
    return Error {EMPTY_EXPRESSION};
  }

  static Error invalid_function()
  {
    return Error {INVALID_FUNCTION};
  }

  static Error calling_invalid_function(parsing::tokens::Text tokenTxt)
  {
    return Error {CALLING_INVALID_FUNCTION, tokenTxt};
  }

  static Error recursion_depth_overflow()
  {
    return Error{RECURSION_DEPTH_OVERFLOW};
  }

  static Error wrong_object_type(parsing::tokens::Text tokenTxt)
  {
    return Error {WRONG_OBJECT_TYPE, tokenTxt};
  }

  // kind of error
  Type error_type = UNKNOWN;

  // on what token
  parsing::tokens::Text token = {};

  bool operator == (const Error& other) const = default;
};

}
