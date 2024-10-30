//
//  Vec2.h
//  Termin8or
//
//  Created by Rasmus Anthin on 2024-10-25.
//

#pragma once
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