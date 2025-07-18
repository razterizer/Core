//
//  Vec2.h
//  Termin8or
//
//  Created by Rasmus Anthin on 2024-10-25.
//

#pragma once
#include "Math.h"
#include <string>


struct Vec2
{
  float r = 0.f;
  float c = 0.f;
  
  Vec2() = default;
  
  Vec2(float rr, float cc)
    : r(rr)
    , c(cc)
  {}
  
  Vec2(const Vec2& v)
  {
    r = v.r;
    c = v.c;
  }
  
  const Vec2& operator+() const
  {
    return *this;
  }
  
  Vec2 operator-() const
  {
    return { -r, -c };
  }
  
  Vec2 operator+(const Vec2& v) const
  {
    return { r + v.r, c + v.c };
  }
  Vec2 operator-(const Vec2& v) const
  {
    return { r - v.r, c - v.c };
  }
  Vec2& operator+=(const Vec2& v)
  {
    this->r += v.r;
    this->c += v.c;
    return *this;
  }
  Vec2& operator-=(const Vec2& v)
  {
    this->r -= v.r;
    this->c -= v.c;
    return *this;
  }
  Vec2 operator*(float v) const
  {
    return { r * v, c * v };
  }
  Vec2 operator/(float v) const
  {
    return { r / v, c / v };
  }
  Vec2& operator/=(float v)
  {
    this->r /= v;
    this->c /= v;
    return *this;
  }
  
  std::string str() const
  {
    return "(" + std::to_string(r) + ", " + std::to_string(c) + ")";
  }
};

Vec2 operator*(float v, const Vec2& p)
{
  return { p.r * v, p.c * v };
}

namespace math
{
  
  float length_squared(const Vec2& pt)
  {
    return length_squared(pt.r, pt.c);
  }
  
  float length(const Vec2& pt)
  {
    return length(pt.r, pt.c);
  }
  
  float distance_squared(const Vec2& ptA, const Vec2& ptB)
  {
    return distance_squared(ptA.r, ptA.c, ptB.r, ptB.c);
  }
  
  float distance(const Vec2& ptA, const Vec2& ptB)
  {
    return distance(ptA.r, ptA.c, ptB.r, ptB.c);
  }
  
  float distance_squared_ar(const Vec2& ptA, const Vec2& ptB, float ar)
  {
    auto dr = (ptB.r - ptA.r)/ar;
    auto dc = ptB.c - ptA.c;
    return math::sq(dr) + math::sq(dc);
  }
  
  float distance_ar(const Vec2& ptA, const Vec2& ptB, float ar)
  {
    return std::sqrt(distance_squared_ar(ptA, ptB, ar));
  }
  
  Vec2 normalize(const Vec2& v)
  {
    auto ret = v;
    if (!normalize(ret.r, ret.c))
      return {};
    return ret;
  }
  
  float dot(const Vec2& vA, const Vec2& vB)
  {
    return dot(vA.r, vA.c, vB.r, vB.c);
  }
  
}
