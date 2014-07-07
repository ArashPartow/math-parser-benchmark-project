// This file is distributed under the BSD License.
// See "license.txt" for details.
// Copyright 2009-2012, Jonathan Turner (jonathan@emptycrate.com)
// Copyright 2009-2014, Jason Turner (jason@emptycrate.com)
// http://www.chaiscript.com

/// \file
/// This file contains utility functions for registration of STL container
/// classes. The methodology used is based on the SGI STL concepts.
/// http://www.sgi.com/tech/stl/table_of_contents.html


#ifndef CHAISCRIPT_BOOTSTRAP_STL_HPP_
#define CHAISCRIPT_BOOTSTRAP_STL_HPP_

#include "dispatchkit.hpp"
#include "register_function.hpp"

namespace chaiscript 
{
  namespace bootstrap
  {
    namespace standard_library
    {

      /// Bidir_Range, based on the D concept of ranges.
      /// \todo Update the Range code to base its capabilities on
      ///       the user_typetraits of the iterator passed in
      template<typename Container>
        struct Bidir_Range
        {
          typedef Container container_type;
          typedef typename std::iterator_traits<typename Container::iterator>::reference reference_type;

          Bidir_Range(Container &c)
            : m_begin(c.begin()), m_end(c.end())
          {
          }

          bool empty() const
          {
            return m_begin == m_end;
          }

          void pop_front()
          {
            if (empty())
            {
              throw std::range_error("Range empty");
            }
            ++m_begin;
          }

          void pop_back()
          {
            if (empty())
            {
              throw std::range_error("Range empty");
            }
            --m_end;
          }

          reference_type front() const
          {
            if (empty())
            {
              throw std::range_error("Range empty");
            }
            return *m_begin;
          }

          reference_type back() const
          {
            if (empty())
            {
              throw std::range_error("Range empty");
            }
            typename Container::iterator pos = m_end;
            --pos;
            return *(pos);
          }

          typename Container::iterator m_begin;
          typename Container::iterator m_end;
        };

      template<typename Container>
        struct Const_Bidir_Range
        {
          typedef const Container container_type;
          typedef typename std::iterator_traits<typename Container::const_iterator>::reference const_reference_type;

          Const_Bidir_Range(const Container &c)
            : m_begin(c.begin()), m_end(c.end())
          {
          }

          bool empty() const
          {
            return m_begin == m_end;
          }

          void pop_front()
          {
            if (empty())
            {
              throw std::range_error("Range empty");
            }
            ++m_begin;
          }

          void pop_back()
          {
            if (empty())
            {
              throw std::range_error("Range empty");
            }
            --m_end;
          }

          const_reference_type front() const
          {
            if (empty())
            {
              throw std::range_error("Range empty");
            }
            return *m_begin;
          }

          const_reference_type back() const
          {
            if (empty())
            {
              throw std::range_error("Range empty");
            }
            typename Container::const_iterator pos = m_end;
            --pos;
            return *(pos);
          }

          typename Container::const_iterator m_begin;
          typename Container::const_iterator m_end;
        };

      namespace detail {
        template<typename T>
          int return_int_impl(const boost::function<typename T::size_type (const T *)> &t_func, const T *t_obj)
          {
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4267)
#endif
            return t_func(t_obj);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
          }

        template<typename T>
        boost::function<int (const T *)> return_int(size_t (T::*t_func)() const)
          {
            return boost::bind(&return_int_impl<T>, boost::function<size_t (const T *)>(boost::mem_fn(t_func)), _1);
          }

        template<typename T, typename P1>
          int return_int_impl(const boost::function<typename T::size_type (const T *, P1)> &t_func, const T *t_obj, P1 p1)
          {
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4267)
#endif
            return t_func(t_obj, p1);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
          }

        template<typename T, typename P1>
          int return_int_impl_non_const(const boost::function<typename T::size_type (T *, P1)> &t_func, T *t_obj, P1 p1)
          {
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4267)
#endif
            return t_func(t_obj, p1);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
          }

        template<typename T, typename P1>
        boost::function<int (const T *, P1)> return_int(size_t (T::*t_func)(P1) const)
          {
            return boost::bind(&return_int_impl<T, P1>, boost::function<size_t (const T *, P1)>(boost::mem_fn(t_func)), _1, _2);
          }

        template<typename T, typename P1>
        boost::function<int (T *, P1)> return_int(size_t (T::*t_func)(P1) )
          {
            return boost::bind(&return_int_impl_non_const<T, P1>, boost::function<size_t (T*, P1)>(boost::mem_fn(t_func)), _1, _2);
          }


        template<typename T, typename P1, typename P2>
          int return_int_impl(const boost::function<typename T::size_type (const T *, P1, P2)> &t_func, const T *t_obj, P1 p1, P2 p2)
          {
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4267)
#endif
            return t_func(t_obj, p1, p2);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
          }

        template<typename StringType, StringType (StringType::*Func)(typename StringType::size_type, typename StringType::size_type) const >
        StringType substr_helper(const StringType &str, int begin, int end)
        {
          return (str.*Func)(begin, end);
        }

        template<typename T, typename P1, typename P2>
        boost::function<int (const T *, P1, P2)> return_int(size_t (T::*t_func)(P1, P2) const)
          {
            return boost::bind(&return_int_impl<T, P1, P2>, boost::function<size_t (const T *, P1, P2)>(boost::mem_fn(t_func)), _1, _2, _3);
          }

        template<typename T>
          void insert(T &t_target, const T &t_other)
          {
            t_target.insert(t_other.begin(), t_other.end());
          }

        template<typename T>
          void insert_ref(T &t_target, const typename T::value_type &t_val)
          {
            t_target.insert(t_val);
          }





        /// Add Bidir_Range support for the given ContainerType
        template<typename Bidir_Type>
          ModulePtr input_range_type_impl(const std::string &type, ModulePtr m = ModulePtr(new Module()))
          {
            m->add(user_type<Bidir_Type>(), type + "_Range");

            copy_constructor<Bidir_Type>(type + "_Range", m);

            m->add(constructor<Bidir_Type (typename Bidir_Type::container_type &)>(), "range");

            m->add(fun(&Bidir_Type::empty), "empty");
            m->add(fun(&Bidir_Type::pop_front), "pop_front");
            m->add(fun(&Bidir_Type::front), "front");
            m->add(fun(&Bidir_Type::pop_back), "pop_back");
            m->add(fun(&Bidir_Type::back), "back");

            return m;
          } 


        /// Algorithm for inserting at a specific position into a container
        template<typename Type>
          void insert_at(Type &container, int pos, const typename Type::value_type &v)
          {
            typename Type::iterator itr = container.begin();
            typename Type::iterator end = container.end();

            if (pos < 0 || std::distance(itr, end) < pos)
            {
              throw std::range_error("Cannot insert past end of range");
            }

            std::advance(itr, pos);
            container.insert(itr, v);
          }


        /// Algorithm for erasing a specific position from a container
        template<typename Type>
          void erase_at(Type &container, int pos)
          {
            typename Type::iterator itr = container.begin();
            typename Type::iterator end = container.end();

            if (pos < 0 || std::distance(itr, end) < (pos-1))
            {
              throw std::range_error("Cannot erase past end of range");
            }

            std::advance(itr, pos);
            container.erase(itr);
          }      
        
      }

      template<typename ContainerType>
        ModulePtr input_range_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          detail::input_range_type_impl<Bidir_Range<ContainerType> >(type,m);
          detail::input_range_type_impl<Const_Bidir_Range<ContainerType> >("Const_" + type, m);
          return m;
        }


      /// Add random_access_container concept to the given ContainerType
      /// http://www.sgi.com/tech/stl/RandomAccessContainer.html
      template<typename ContainerType>
        ModulePtr random_access_container_type(const std::string &/*type*/, ModulePtr m = ModulePtr(new Module()))
        {
          typedef typename ContainerType::reference(ContainerType::*indexoper)(size_t);
          typedef typename ContainerType::const_reference(ContainerType::*constindexoper)(size_t) const;

          //In the interest of runtime safety for the m, we prefer the at() method for [] access,
          //to throw an exception in an out of bounds condition.
          m->add(
              fun(boost::function<typename ContainerType::reference (ContainerType *, int)>
                (boost::mem_fn(static_cast<indexoper>(&ContainerType::at)))), "[]");
          m->add(
              fun(boost::function<typename ContainerType::const_reference (const ContainerType *, int)>
                (boost::mem_fn(static_cast<constindexoper>(&ContainerType::at)))), "[]");

          return m;
        }


      /// Add assignable concept to the given ContainerType
      /// http://www.sgi.com/tech/stl/Assignable.html
      template<typename ContainerType>
        ModulePtr assignable_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          basic_constructors<ContainerType>(type, m);
          operators::assign<ContainerType>(m);
          return m;
        }


      /// Add container concept to the given ContainerType
      /// http://www.sgi.com/tech/stl/Container.html
      template<typename ContainerType>
        ModulePtr container_type(const std::string &/*type*/, ModulePtr m = ModulePtr(new Module()))
        {
          boost::function<int (const ContainerType *)> f = detail::return_int(&ContainerType::size);
          m->add(fun(f), "size");
          m->add(fun<bool (ContainerType::*)() const>(&ContainerType::empty), "empty");
          m->add(fun<void (ContainerType::*)()>(&ContainerType::clear), "clear");
          return m;
        }


      /// Add default constructable concept to the given Type
      /// http://www.sgi.com/tech/stl/DefaultConstructible.html
      template<typename Type>
        ModulePtr default_constructible_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          m->add(constructor<Type ()>(), type);
          return m;
        }




      /// Add sequence concept to the given ContainerType
      /// http://www.sgi.com/tech/stl/Sequence.html
      template<typename ContainerType>
        ModulePtr sequence_type(const std::string &/*type*/, ModulePtr m = ModulePtr(new Module()))
        {
          std::string insert_name;
          if (typeid(typename ContainerType::value_type) == typeid(Boxed_Value))
          {
            insert_name = "insert_ref_at";
          } else {
            insert_name = "insert_at";
          }

          m->add(fun(&detail::insert_at<ContainerType>), insert_name);
          m->add(fun(&detail::erase_at<ContainerType>), "erase_at");

          return m;
        }


      /// Add back insertion sequence concept to the given ContainerType
      /// http://www.sgi.com/tech/stl/BackInsertionSequence.html
      template<typename ContainerType>
        ModulePtr back_insertion_sequence_type(const std::string &/*type*/, ModulePtr m = ModulePtr(new Module()))
        {
          typedef typename ContainerType::reference (ContainerType::*backptr)();

          m->add(fun(static_cast<backptr>(&ContainerType::back)), "back");

          std::string push_back_name;
          if (typeid(typename ContainerType::value_type) == typeid(Boxed_Value))
          {
            push_back_name = "push_back_ref";
          } else {
            push_back_name = "push_back";
          }

          typedef void (ContainerType::*pushback)(const typename ContainerType::value_type &);
          m->add(fun(static_cast<pushback>(&ContainerType::push_back)), push_back_name);
          m->add(fun(&ContainerType::pop_back), "pop_back");
          return m;
        }



      /// Front insertion sequence
      /// http://www.sgi.com/tech/stl/FrontInsertionSequence.html
      template<typename ContainerType>
        ModulePtr front_insertion_sequence_type(const std::string &, ModulePtr m = ModulePtr(new Module()))
        {
          typedef typename ContainerType::reference (ContainerType::*frontptr)();
          typedef void (ContainerType::*pushptr)(typename ContainerType::const_reference);
          typedef void (ContainerType::*popptr)();

          m->add(fun(static_cast<frontptr>(&ContainerType::front)), "front");

          std::string push_front_name;
          if (typeid(typename ContainerType::value_type) == typeid(Boxed_Value))
          {
            push_front_name = "push_front_ref";
          } else {
            push_front_name = "push_front";
          }

          m->add(fun(static_cast<pushptr>(&ContainerType::push_front)), push_front_name);
          m->add(fun(static_cast<popptr>(&ContainerType::pop_front)), "pop_front");
          return m;
        }


      /// bootstrap a given PairType
      /// http://www.sgi.com/tech/stl/pair.html
      template<typename PairType>
        ModulePtr pair_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          m->add(user_type<PairType>(), type);


          typename PairType::first_type PairType::* f = &PairType::first;
          typename PairType::second_type PairType::* s = &PairType::second;

          m->add(fun(f), "first");
          m->add(fun(s), "second");

          basic_constructors<PairType>(type, m);
          m->add(constructor<PairType (const typename PairType::first_type &, const typename PairType::second_type &)>(), type);

          return m;
        }



      /// Add pair associative container concept to the given ContainerType
      /// http://www.sgi.com/tech/stl/PairAssociativeContainer.html

      template<typename ContainerType>
        ModulePtr pair_associative_container_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          pair_type<typename ContainerType::value_type>(type + "_Pair", m);

          return m;
        }


      /// Add unique associative container concept to the given ContainerType
      /// http://www.sgi.com/tech/stl/UniqueAssociativeContainer.html
      template<typename ContainerType>
        ModulePtr unique_associative_container_type(const std::string &/*type*/, ModulePtr m = ModulePtr(new Module()))
        {
          m->add(fun(boost::function<int (const ContainerType *, const typename ContainerType::key_type &)>(detail::return_int(&ContainerType::count))), "count");


          typedef size_t (ContainerType::*erase)(const typename ContainerType::key_type &);
          erase eraseptr(&ContainerType::erase);

          m->add(fun(boost::function<int (ContainerType *, const typename ContainerType::key_type &)>(detail::return_int(eraseptr))), "erase");

          m->add(fun(&detail::insert<ContainerType>), "insert");

          std::string insert_name;
          if (typeid(typename ContainerType::mapped_type) == typeid(Boxed_Value))
          {
            insert_name = "insert_ref";
          } else {
            insert_name = "insert";
          }

          m->add(fun(&detail::insert_ref<ContainerType>), insert_name);
          return m;
        }


      /// Add a MapType container
      /// http://www.sgi.com/tech/stl/Map.html
      template<typename MapType>
        ModulePtr map_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          m->add(user_type<MapType>(), type);

          typedef typename MapType::mapped_type &(MapType::*elemaccess)(const typename MapType::key_type &);

          m->add(fun(static_cast<elemaccess>(&MapType::operator[])), "[]");

          container_type<MapType>(type, m);
          assignable_type<MapType>(type, m);
          unique_associative_container_type<MapType>(type, m);
          pair_associative_container_type<MapType>(type, m);
          input_range_type<MapType>(type, m);

          return m;
        }


      /// hopefully working List type
      /// http://www.sgi.com/tech/stl/List.html
      template<typename ListType>
        ModulePtr list_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          m->add(user_type<ListType>(), type);

          front_insertion_sequence_type<ListType>(type, m);
          back_insertion_sequence_type<ListType>(type, m);
          sequence_type<ListType>(type, m);
          container_type<ListType>(type, m);
          default_constructible_type<ListType>(type, m);
          assignable_type<ListType>(type, m);
          input_range_type<ListType>(type, m);

          return m;
        }


      /// Create a vector type with associated concepts
      /// http://www.sgi.com/tech/stl/Vector.html
      template<typename VectorType>
        ModulePtr vector_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          m->add(user_type<VectorType>(), type);

          typedef typename VectorType::reference (VectorType::*frontptr)();
          m->add(fun(static_cast<frontptr>(&VectorType::front)), "front");


          back_insertion_sequence_type<VectorType>(type, m);
          sequence_type<VectorType>(type, m);
          random_access_container_type<VectorType>(type, m);
          container_type<VectorType>(type, m);
          default_constructible_type<VectorType>(type, m);
          assignable_type<VectorType>(type, m);
          input_range_type<VectorType>(type, m);

          if (typeid(VectorType) == typeid(std::vector<Boxed_Value>))
          {
            m->eval("def Vector::`==`(rhs) : type_match(rhs, this) { \
                       if ( rhs.size() != this.size() ) {    \
                         return false;  \
                       } else {  \
                         var r1 = range(this); \
                         var r2 = range(rhs);  \
                         while (!r1.empty()) \
                         {  \
                           if (!eq(r1.front(), r2.front())) \
                           {  \
                             return false; \
                           } \
                           r1.pop_front(); \
                           r2.pop_front(); \
                         } \
                       return true; \
                     } \
                   }");
          } 

          return m;
        }

        namespace detail {
          template<typename String>
          struct apple_string_workarounds
          {
            /// The latest version of MacOS has a broken std::string implementation which will not allow
            /// us to take pointers to the members. Code compiles, but does not link
            /// \todo re-evaluate at some point

            static size_t find(const String *s, const String &w, int pos) { return s->find(w, pos); }
            static size_t rfind(const String *s, const String &w, size_t pos) { return s->rfind(w, pos); }
            static size_t find_first_of(const String *s, const String &w, size_t pos) { return s->find_first_of(w, pos); }
            static size_t find_last_of(const String *s, const String &w, size_t pos) { return s->find_last_of(w, pos); }
            static size_t find_first_not_of(const String *s, const String &w, size_t pos) { return s->find_first_not_of(w, pos); }
            static size_t find_last_not_of(const String *s, const String &w, size_t pos) { return s->find_last_not_of(w, pos); }

            static void clear(String *s) { s->clear(); }
            static bool empty(const String *s) { return s->empty(); }
            static size_t size(const String *s) { return s->size(); }
 
            static std::string substr(const String *s, size_t pos, size_t len) { return s->substr(pos,len); }
            static const char *c_str(const String *s) {  return s->c_str(); }
            static const char *data(const String *s) { return s->data(); }
          };
        }


      /// Add a String container
      /// http://www.sgi.com/tech/stl/basic_string.html
      template<typename String>
        ModulePtr string_type(const std::string &type, ModulePtr m = ModulePtr(new Module()))
        {
          m->add(user_type<String>(), type);
          operators::addition<String>(m);
          operators::assign_sum<String>(m);
          opers_comparison<String>(m);
          random_access_container_type<String>(type, m);
          sequence_type<String>(type, m);
          default_constructible_type<String>(type, m);
          // container_type<String>(type, m);
          assignable_type<String>(type, m);
          input_range_type<String>(type, m);

          //Special case: add push_back to string (which doesn't support other back_insertion operations
          std::string push_back_name;
          if (typeid(typename String::value_type) == typeid(Boxed_Value))
          {
            push_back_name = "push_back_ref";
          } else {
            push_back_name = "push_back";
          }
          m->add(fun(&String::push_back), push_back_name);

            
          m->add(fun(&detail::apple_string_workarounds<String>::find), "find");
          m->add(fun(&detail::apple_string_workarounds<String>::rfind), "rfind");
          m->add(fun(&detail::apple_string_workarounds<String>::find_first_of), "find_first_of");
          m->add(fun(&detail::apple_string_workarounds<String>::find_last_of), "find_last_of");
          m->add(fun(&detail::apple_string_workarounds<String>::find_first_not_of), "find_first_not_of");
          m->add(fun(&detail::apple_string_workarounds<String>::find_last_not_of), "find_last_not_of");
          m->add(fun(&detail::apple_string_workarounds<String>::clear), "clear");
          m->add(fun(&detail::apple_string_workarounds<String>::size), "size");
          m->add(fun(&detail::apple_string_workarounds<String>::empty), "empty");
          m->add(fun(&detail::apple_string_workarounds<String>::substr), "substr");
          m->add(fun(&detail::apple_string_workarounds<String>::c_str), "c_str");
          m->add(fun(&detail::apple_string_workarounds<String>::data), "data");


          return m;
        }
    }
  }
}


#endif
