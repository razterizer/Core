#pragma once
#include "Math.h"


namespace rnd
{

  void srand_time()
  {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
  }
  
  float calc_t_rnd()
  {
    auto r = static_cast<float>(std::rand());
    return r / static_cast<float>(RAND_MAX);
  }
  
  template<typename EnumType>
  EnumType randomize_enum()
  {
    float t = calc_t_rnd();
    auto scaling = static_cast<float>(EnumType::NUM_ITEMS) - 1.f;
    auto rnd = t * scaling;
    return static_cast<EnumType>(std::round(rnd));
  }
  
  bool randomize_bool()
  {
    float t = calc_t_rnd();
    return static_cast<bool>(std::round(t));
  }
  
  float randomize_float(float start, float end)
  {
    float t = calc_t_rnd();
    auto rnd = math::lerp(t, start, end);
    return rnd;
  }
  
  int randomize_int(int start, int end)
  {
    float t = calc_t_rnd();
    auto rnd = math::lerp<float>(t, start, end);
    return std::round(rnd);
  }
  
  template<typename T>
  T rand_select(const std::vector<T>& values)
  {
    assert(!values.empty());
    int idx = randomize_int(0, static_cast<int>(values.size()) - 1);
    return values[idx];
  }

}
