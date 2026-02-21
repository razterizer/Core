//
//  Utils.h
//  Core Lib
//
//  Created by Rasmus Anthin on 2024-05-20.
//


#pragma once

#define UNUSED(x) 

namespace utils
{
  
  namespace literals
  {
    inline constexpr int operator"" _i(long double x)
    {
      return static_cast<int>(x);
    }
  }

  template<typename T>
  bool try_set(T* dst, const T& src)
  {
    if (dst != nullptr)
    {
      *dst = src;
      return true;
    }
    return false;
  }
  
  template<typename T>
  T try_get(T* ptr, const T def_val = static_cast<T>(0))
  {
    if (ptr == nullptr)
      return def_val;
    return *ptr;
  }
  
  // e.g.
  //   Obj o1;
  //   Obj* raw_ptr1 = get_raw_ptr(o1);
  //   Obj* o2 = new Obj();
  //   Obj* raw_ptr2 = get_raw_ptr(o2);
  //   auto o3 = std::make_unique<Obj>();
  //   Obj* raw_ptr3 = get_raw_ptr(o3);
  template<typename T>
  T* get_raw_ptr(T& o) { return &o; }
  template<typename T>
  const T* get_raw_ptr(const T& o) { return &o; }
  template<typename T>
  T* get_raw_ptr(T* o) { return o; }
  template<typename T>
  const T* get_raw_ptr(const T* o) { return o; }
  template<typename T>
  T* get_raw_ptr(std::unique_ptr<T>& o) { return o.get(); }
  template<typename T>
  const T* get_raw_ptr(const std::unique_ptr<T>& o) { return o.get(); }

}
