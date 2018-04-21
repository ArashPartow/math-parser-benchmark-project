// Copyright (c) 2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAOCPP_PEGTL_INCLUDE_INTERNAL_APPLY0_HPP
#define TAOCPP_PEGTL_INCLUDE_INTERNAL_APPLY0_HPP

#include "../config.hpp"

#include "skip_control.hpp"
#include "trivial.hpp"

#include "../analysis/counted.hpp"

namespace tao
{
   namespace TAOCPP_PEGTL_NAMESPACE
   {
      namespace internal
      {
         template< typename Action, typename >
         struct apply0_single;

         template< typename Action >
         struct apply0_single< Action, void >
         {
            template< typename... States >
            static bool match( States&&... st )
            {
               Action::apply0( st... );
               return true;
            }
         };

         template< typename Action >
         struct apply0_single< Action, bool >
         {
            template< typename... States >
            static bool match( States&&... st )
            {
               return Action::apply0( st... );
            }
         };

         template< apply_mode A, typename... Actions >
         struct apply0_impl;

         template<>
         struct apply0_impl< apply_mode::ACTION >
         {
            template< typename... States >
            static bool match( States&&... )
            {
               return true;
            }
         };

         template< typename... Actions >
         struct apply0_impl< apply_mode::ACTION, Actions... >
         {
            template< typename... States >
            static bool match( States&&... st )
            {
#ifdef __cpp_fold_expressions
               return ( apply0_single< Actions, decltype( Actions::apply0( st... ) ) >::match( st... ) && ... );
#else
               bool result = true;
               using swallow = bool[];
               (void)swallow{ result = result && apply0_single< Actions, decltype( Actions::apply0( st... ) ) >::match( st... )... };
               return result;
#endif
            }
         };

         template< typename... Actions >
         struct apply0_impl< apply_mode::NOTHING, Actions... >
         {
            template< typename... States >
            static bool match( States&&... )
            {
               return true;
            }
         };

         template< typename... Actions >
         struct apply0
         {
            using analyze_t = analysis::counted< analysis::rule_type::ANY, 0 >;

            template< apply_mode A,
                      rewind_mode M,
                      template< typename... > class Action,
                      template< typename... > class Control,
                      typename Input,
                      typename... States >
            static bool match( Input&, States&&... st )
            {
               return apply0_impl< A, Actions... >::match( st... );
            }
         };

         template< typename... Actions >
         struct skip_control< apply0< Actions... > > : std::true_type
         {
         };

      }  // namespace internal

   }  // namespace TAOCPP_PEGTL_NAMESPACE

}  // namespace tao

#endif
