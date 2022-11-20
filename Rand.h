#pragma once
#include "Math.h"


namespace rnd
{

  void srand_time()
  {
    auto time_s = std::time(nullptr);
    // Don't lose least significant digits.
    auto shift_time_s = time_s % UINT_MAX;
    // Choose "smaller" representation.
    auto ui_shift_time_s = static_cast<unsigned int>(shift_time_s);
    // Scale up seconds to higher units of time, to get more radical changes in p-random sequences.
    auto scaled_shifted_time_s = ui_shift_time_s * 3163; // Use prime number I guess.
    // Set seed.
    std::srand(scaled_shifted_time_s);
  }
  
  // Uniform random value in range [0, 1].
  float rand()
  {
    auto r = static_cast<float>(std::rand());
    return r / static_cast<float>(RAND_MAX);
  }

  // Normal-distributed random value using the Box-Muller algorithm.
  float randn(float mu, float sigma)  /* normal random variate generator */
  {                       /* mean m, standard deviation s */
      float x1, x2, w, y1;
      static float y2;
      static bool use_last = false;
  
      if (use_last)               /* use value from previous call */
      {
          y1 = y2;
          use_last = false;
      }
      else
      {
          do {
              x1 = 2.0f * rand() - 1.0f;
              x2 = 2.0f * rand() - 1.0f;
              w = x1 * x1 + x2 * x2;
          } while ( w >= 1.0 );
  
          w = std::sqrt((-2.0f * std::log(w)) / w);
          y1 = x1 * w;
          y2 = x2 * w;
          use_last = true;
      }
  
      return mu + y1 * sigma;
  }

  int randn_int(float mu, float sigma)
  {
    return std::round(randn(mu, sigma));
  }

  float randn_clamp(float mu, float sigma, float min, float max)
  {
    float r = 0.f;
    do
    {
      r = randn(mu, sigma);
    } while (!math::in_range<float>(r, min, max, Range::Closed));
    return r;
  }

  int randn_clamp_int(float mu, float sigma, int min, int max)
  {
    return std::round(randn_clamp(mu, sigma, min, max));
  }
  
  template<typename EnumType>
  EnumType rand_enum()
  {
    float t = rand();
    auto scaling = static_cast<float>(EnumType::NUM_ITEMS) - 1.f;
    auto rnd = t * scaling;
    return static_cast<EnumType>(std::round(rnd));
  }

  template<typename EnumType>
  EnumType randn_enum(float mu, float sigma)
  {
    int idx = randn_clamp_int(mu, sigma,
                              0,
                              static_cast<int>(EnumType::NUM_ITEMS) - 1);
    return static_cast<EnumType>(idx);
  }
  
  bool rand_bool()
  {
    float t = rand();
    return static_cast<bool>(std::round(t));
  }
  
  float rand_float(float start, float end)
  {
    float t = rand();
    auto rnd = math::lerp(t, start, end);
    return rnd;
  }
  
  int rand_int(int start, int end)
  {
    float t = rand();
    auto rnd = math::lerp<float>(t, start, end);
    return std::round(rnd);
  }
  
  template<typename T>
  T rand_select(const std::vector<T>& values)
  {
    assert(!values.empty());
    int idx = rand_int(0, static_cast<int>(values.size()) - 1);
    return values[idx];
  }

  template<typename T>
  T randn_select(float mu, float sigma, const std::vector<T>& values)
  {
    assert(!values.empty());
    int idx = randn_clamp_int(mu, sigma,
                              0,
                              static_cast<int>(values.size()) - 1);
    return values[idx];
  }

}
