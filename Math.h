#pragma once
#include <cstdlib>
#include <vector>
#include <math.h>
#include <cmath>

enum class Range { Closed, Open, ClosedOpen, OpenClosed };

namespace math
{

  template<typename T>
  int sgn(T val)
  {
    if (val < 0)
      return -1;
    if (val > 0)
      return +1;
    return 0;
  }
  
  template<typename T>
  int sign(T val)
  {
    if (val < 0)
      return -1;
    return +1;
  }
  
  template<typename T>
  T sq(T val)
  {
    return val * val;
  }
  
  template<typename T>
  T length_squared(T x, T y)
  {
    return sq(x) + sq(y);
  }
  
  template<typename T>
  T length(T x, T y)
  {
    return std::sqrt(length_squared(x, y));
  }

  template<typename T>
  T distance_squared(T x0, T y0, T x1, T y1)
  {
    auto diff_x = x1 - x0;
    auto diff_y = y1 - y0;
    return length_squared(diff_x, diff_y);
  }

  template<typename T>
  T distance(T x0, T y0, T x1, T y1)
  {
    return std::sqrt(distance_squared(x0, y0, x1, y1));
  }
  
  template<typename T>
  bool normalize(T& x, T& y)
  {
    auto len = length(x, y);
    if (len < 1e-10f)
      return false;
    x /= len;
    y /= len;
    return true;
  }
  
  template<typename T>
  T clamp(T val, T lo, T hi)
  {
    if (val < lo)
      return lo;
    if (hi < val)
      return hi;
    return val;
  }
  
  template<typename T>
  T lerp(float t, T a, T b)
  {
    return a*(1.f-t) + b*t;
  }
  
  template<typename T>
  float value_to_param(T val, T start, T end)
  {
    if (start == end)
    {
      if (val < start)
        return 0.f;
      else
        return 1.f;
    }
    return static_cast<float>(val - start) / static_cast<float>(end - start);
  }

  template<typename T>
  float value_to_param_clamped(T val, T start, T end)
  {
    //val = clamp(val, start, end);
    auto t = value_to_param(val, start, end);
    t = clamp(t, 0.f, 1.f);
    return t;
  }
  
  template<typename T>
  std::vector<T> linspace(T start, T step, T end)
  {
    std::vector<T> res;
    if (step > 0)
      for (T v = start; v <= end; v += step)
        res.emplace_back(v);
    else if (step < 0)
      for (T v = start; v >= end; v += step)
        res.emplace_back(v);
    return res;
  }
  
  template<typename T0, typename T1>
  T1 linmap(T0 val_0, T0 start_0, T0 end_0, T1 start_1, T1 end_1)
  {
    auto t = value_to_param<T0>(val_0, start_0, end_0);
    return lerp<T1>(t, start_1, end_1);
  }

  template<typename T>
  bool in_range(T val, T start, T end, Range type)
  {
    switch (type)
    {
      case Range::Closed:
        return start <= val && val <= end;
      case Range::Open:
        return start < val && val < end;
      case Range::ClosedOpen:
        return start <= val && val < end;
      case Range::OpenClosed:
        return start < val && val <= end;
    }
    return false;
  }

  template<typename T>
  bool in_unit_range(T val, Range type)
  {
    return in_range(val, static_cast<T>(0), static_cast<T>(1), type);
  }
  
}
