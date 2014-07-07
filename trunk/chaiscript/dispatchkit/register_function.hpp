// This file is distributed under the BSD License.
// See "license.txt" for details.
// Copyright 2009-2012, Jonathan Turner (jonathan@emptycrate.com)
// Copyright 2009-2014, Jason Turner (jason@emptycrate.com)
// http://www.chaiscript.com

#ifndef CHAISCRIPT_REGISTER_FUNCTION_HPP_
#define CHAISCRIPT_REGISTER_FUNCTION_HPP_

#include "dispatchkit.hpp"
#include "bind_first.hpp"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/function_types/components.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/is_member_object_pointer.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>

namespace chaiscript
{
  namespace dispatch
  {
    namespace detail
    {
      template<bool Object, bool MemFn>
        struct Fun_Helper
        {
          template<typename T>
            static Proxy_Function go(T t)
            {
              return Proxy_Function(
                  new Proxy_Function_Impl<
                  typename boost::function_types::function_type<boost::function_types::components<T> >::type> (
                    boost::function< 
                    typename boost::function_types::function_type<boost::function_types::components<T> >::type 
                    >(t)));
            }      
        };

      template<>
        struct Fun_Helper<false, true>
        {
          template<typename T>
            static Proxy_Function go(T t)
            {
              return Proxy_Function(
                  new Proxy_Function_Impl<
                  typename boost::function_types::function_type<boost::function_types::components<T> >::type> (
                    boost::function< 
                    typename boost::function_types::function_type<boost::function_types::components<T> >::type 
                    >(boost::mem_fn(t))));
            }      
        };


      template<>
        struct Fun_Helper<true, false>
        {
          template<typename T, typename Class>
            static Proxy_Function go(T Class::* m)
            {
              return Proxy_Function(new Attribute_Access<T, Class>(m));
            }
        };
    }
  }

  /// \brief Creates a new Proxy_Function object from a boost::function object
  /// \param[in] f boost::function to expose to ChaiScript
  ///
  /// \b Example:
  /// \code
  /// boost::function<int (char, float, std::string)> f = get_some_function();
  /// chaiscript::ChaiScript chai;
  /// chai.add(fun(f), "some_function");
  /// \endcode
  /// 
  /// \sa \ref addingfunctions
  template<typename T>
    Proxy_Function fun(const boost::function<T> &f)
    {
      return Proxy_Function(new dispatch::Proxy_Function_Impl<T>(f));
    }

  /// \brief Creates a new Proxy_Function object from a free function, member function or data member
  /// \param[in] t Function / member to expose
  ///
  /// \b Example:
  /// \code
  /// int myfunction(const std::string &);
  /// class MyClass
  /// {
  ///   public:
  ///     void memberfunction();
  ///     int memberdata;
  /// };
  /// 
  /// chaiscript::ChaiScript chai;
  /// chai.add(fun(&myfunction), "myfunction");
  /// chai.add(fun(&MyClass::memberfunction), "memberfunction");
  /// chai.add(fun(&MyClass::memberdata), "memberdata");
  /// \endcode
  /// 
  /// \sa \ref addingfunctions
  template<typename T>
    Proxy_Function fun(T t)
    {
      return dispatch::detail::Fun_Helper<boost::function_types::is_member_object_pointer<T>::value, boost::function_types::is_member_function_pointer<T>::value>::go(t);
    }

  /// \brief Creates a new Proxy_Function object from a free function, member function or data member and binds the first parameter of it
  /// \param[in] t Function / member to expose
  /// \param[in] q Value to bind to first parameter
  ///
  /// \b Example:
  /// \code
  /// struct MyClass
  /// {
  ///   void memberfunction(int);
  /// };
  /// 
  /// MyClass obj;
  /// chaiscript::ChaiScript chai;
  /// // Add function taking only one argument, an int, and permanently bound to "obj"
  /// chai.add(fun(&MyClass::memberfunction, boost::ref(obj)), "memberfunction"); 
  /// \endcode
  /// 
  /// \sa \ref addingfunctions
  template<typename T, typename Q>
    Proxy_Function fun(T t, const Q &q)
    {
      return fun(detail::bind_first(t, q));
    }

  /// \brief Creates a new Proxy_Function object from a free function or member function and binds the first and second parameters of it
  /// \param[in] t Function / member to expose
  /// \param[in] q Value to bind to first parameter
  /// \param[in] r Value to bind to second parameter
  ///
  /// \b Example:
  /// \code
  /// struct MyClass
  /// {
  ///   void memberfunction(int);
  /// };
  /// 
  /// MyClass obj;
  /// chaiscript::ChaiScript chai;
  /// // Add function taking only no arguments, and permanently bound to "obj" and "1"
  /// // memberfunction() will be equivalent to obj.memberfunction(1)
  /// chai.add(fun(&MyClass::memberfunction, boost::ref(obj), 1), "memberfunction"); 
  /// \endcode
  /// 
  /// \sa \ref addingfunctions
  template<typename T, typename Q, typename R>
    Proxy_Function fun(T t, const Q &q, const R &r)
    {
      return fun(detail::bind_first(detail::bind_first(t, q), r));
    }
   
}


#endif

