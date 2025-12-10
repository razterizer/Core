//
//  MathUtils.h
//  Core
//
//  Important Note: Naming a header Math.h is a very bad idea,
//    even if first letter is capitalized. Why? Because XCode confuses its own
//    math.h with Math.h. Therefore I had to change the name of the header
//    from Math.h to MathUtils.h.
//
//  Created by Rasmus Anthin.
//

#pragma once
//#include <cstdlib>
#include <vector>
#include <cmath>
#include <optional>
#include <limits>
//#include <type_traits>

enum class Range { Free, Closed, Open, ClosedOpen, OpenClosed, ClosedFree, FreeClosed, OpenFree, FreeOpen };

template<typename T>
struct RangeData
{
  std::optional<T> start = {};
  std::optional<T> end = {};
  Range range = Range::Free;
  
  RangeData(std::optional<T> start_val = {}, std::optional<T> end_val = {}, Range range_type = Range::Free)
   : start(start_val), end(end_val), range(range_type)
  {}
};

namespace math
{

  static constexpr long double cld_pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640628;
  static constexpr long double cld_2pi = 6.28318530717958647692528676655900576839433879875021164194988918461563281257;
  static constexpr long double cld_pi_2 = 1.57079632679489661923132169163975144209858469968755291048747229615390820314;
  static constexpr long double cld_pi_3 = 1.04719755119659774615421446109316762806572313312503527365831486410260546876;
  static constexpr long double cld_pi_4 = 0.78539816339744830961566084581987572104929234984377645524373614807695410157;
  static constexpr long double cld_pi_6 = 0.52359877559829887307710723054658381403286156656251763682915743205130273438;
  static constexpr long double cld_3pi_2 = 4.71238898038468985769396507491925432629575409906265873146241688846172460942;
  static constexpr long double cld_3pi_4 = 2.35619449019234492884698253745962716314787704953132936573120844423086230471;
  static constexpr long double cld_5pi_4 = 3.92699081698724154807830422909937860524646174921888227621868074038477050785;
  static constexpr long double cld_7pi_4 = 5.49778714378213816730962592073913004734504644890643518670615303653867871100;
  static constexpr long double cld_1_pi = 0.31830988618379067153776752674502872406891929148091289749533468811779359526;
  static constexpr long double cld_2_pi = 0.63661977236758134307553505349005744813783858296182579499066937623558719053;
  static constexpr long double cld_sqrt2 = 1.41421356237309504880168872420969807856967187537694807317667973799073247846;
  static constexpr long double cld_2_sqrt_pi = 1.12837916709551257389615890312154517168810125865799771368817144342128493688; // 2/sqrt(pi)
  static constexpr long double cld_sqrt1_2 = 0.70710678118654752440084436210484903928483593768847403658833986899536623923; // 1/sqrt(2)
  static constexpr long double cld_ln2 = 0.69314718055994530941723212145817656807550013436025525412068000949339362196;
  static constexpr long double cld_ln10 = 2.30258509299404568401799145468436420760110148862877297603332790096757260967;
  static constexpr long double cld_e = 2.71828182845904523536028747135266249775724709369995957496696762772407663035;
  static constexpr long double cld_1_e = 0.36787944117144232159552377016146086744581113103176783450783680169746149574;
  static constexpr long double cld_log2e = 1.44269504088896340735992468100189213742664595415298593413544940693110921918;
  static constexpr long double cld_log10e = 0.43429448190325182765112891891660508229439700580366656611445378316586464920;

  static constexpr double cd_pi = static_cast<double>(cld_pi);
  static constexpr double cd_2pi = static_cast<double>(cld_2pi);
  static constexpr double cd_pi_2 = static_cast<double>(cld_pi_2);
  static constexpr double cd_pi_3 = static_cast<double>(cld_pi_3);
  static constexpr double cd_pi_4 = static_cast<double>(cld_pi_4);
  static constexpr double cd_pi_6 = static_cast<double>(cld_pi_6);
  static constexpr double cd_3pi_2 = static_cast<double>(cld_3pi_2);
  static constexpr double cd_3pi_4 = static_cast<double>(cld_3pi_4);
  static constexpr double cd_5pi_4 = static_cast<double>(cld_5pi_4);
  static constexpr double cd_7pi_4 = static_cast<double>(cld_7pi_4);
  static constexpr double cd_1_pi = static_cast<double>(cld_1_pi);
  static constexpr double cd_2_pi = static_cast<double>(cld_2_pi);
  static constexpr double cd_sqrt2 = static_cast<double>(cld_sqrt2);
  static constexpr double cd_2_sqrt_pi = static_cast<double>(cld_2_sqrt_pi); // 2/sqrt(pi)
  static constexpr double cd_sqrt1_2 = static_cast<double>(cld_sqrt1_2); // 1/sqrt(2)
  static constexpr double cd_ln2 = static_cast<double>(cld_ln2);
  static constexpr double cd_ln10 = static_cast<double>(cld_ln10);
  static constexpr double cd_e = static_cast<double>(cld_e);
  static constexpr double cd_1_e = static_cast<double>(cld_1_e);
  static constexpr double cd_log2e = static_cast<double>(cld_log2e);
  static constexpr double cd_log10e = static_cast<double>(cld_log10e);

  static constexpr float c_pi = static_cast<float>(cld_pi);
  static constexpr float c_2pi = static_cast<float>(cld_2pi);
  static constexpr float c_pi_2 = static_cast<float>(cld_pi_2);
  static constexpr float c_pi_3 = static_cast<float>(cld_pi_3);
  static constexpr float c_pi_4 = static_cast<float>(cld_pi_4);
  static constexpr float c_pi_6 = static_cast<float>(cld_pi_6);
  static constexpr float c_3pi_2 = static_cast<float>(cld_3pi_2);
  static constexpr float c_3pi_4 = static_cast<float>(cld_3pi_4);
  static constexpr float c_5pi_4 = static_cast<float>(cld_5pi_4);
  static constexpr float c_7pi_4 = static_cast<float>(cld_7pi_4);
  static constexpr float c_1_pi = static_cast<float>(cld_1_pi);
  static constexpr float c_2_pi = static_cast<float>(cld_2_pi);
  static constexpr float c_sqrt2 = static_cast<float>(cld_sqrt2);
  static constexpr float c_2_sqrt_pi = static_cast<float>(cld_2_sqrt_pi); // 2/sqrt(pi)
  static constexpr float c_sqrt1_2 = static_cast<float>(cld_sqrt1_2); // 1/sqrt(2)
  static constexpr float c_ln2 = static_cast<float>(cld_ln2);
  static constexpr float c_ln10 = static_cast<float>(cld_ln10);
  static constexpr float c_e = static_cast<float>(cld_e);
  static constexpr float c_1_e = static_cast<float>(cld_1_e);
  static constexpr float c_log2e = static_cast<float>(cld_log2e);
  static constexpr float c_log10e = static_cast<float>(cld_log10e);

  // ////////////////

  template<typename T>
  int roundI(T val)
  {
    return static_cast<int>(std::round(val));
  }
  
  template<typename T>
  int floorI(T val)
  {
    return static_cast<int>(std::floor(val));
  }
  
  template<typename T>
  int ceilI(T val)
  {
    return static_cast<int>(std::ceil(val));
  }

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
  T cube(T val)
  {
    return val * val * val;
  }
  
  template<typename T>
  T length_squared(T x, T y)
  {
    return sq(x) + sq(y);
  }
  
  template<typename T>
  T length_squared(T x, T y, T z)
  {
    return sq(x) + sq(y) + sq(z);
  }
  
  template<typename T>
  T length_squared(T x, T y, T z, T w)
  {
    return sq(x) + sq(y) + sq(z) + sq(w);
  }
  
  template<typename T>
  T length(T x, T y)
  {
    return std::sqrt(length_squared(x, y));
  }
  
  template<typename T>
  T length(T x, T y, T z)
  {
    return std::sqrt(length_squared(x, y, z));
  }
  
  template<typename T>
  T length(T x, T y, T z, T w)
  {
    return std::sqrt(length_squared(x, y, z, w));
  }

  template<typename T>
  T distance_squared(T x0, T y0, T x1, T y1)
  {
    auto diff_x = x1 - x0;
    auto diff_y = y1 - y0;
    return length_squared(diff_x, diff_y);
  }
  
  template<typename T>
  T distance_squared(T x0, T y0, T z0, T x1, T y1, T z1)
  {
    auto diff_x = x1 - x0;
    auto diff_y = y1 - y0;
    auto diff_z = z1 - z0;
    return length_squared(diff_x, diff_y, diff_z);
  }
  
  template<typename T>
  T distance_squared(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1)
  {
    auto diff_x = x1 - x0;
    auto diff_y = y1 - y0;
    auto diff_z = z1 - z0;
    auto diff_w = w1 - w0;
    return length_squared(diff_x, diff_y, diff_z, diff_w);
  }

  template<typename T>
  T distance(T x0, T y0, T x1, T y1)
  {
    return std::sqrt(distance_squared(x0, y0, x1, y1));
  }
  
  template<typename T>
  T distance(T x0, T y0, T z0, T x1, T y1, T z1)
  {
    return std::sqrt(distance_squared(x0, y0, z0, x1, y1, z1));
  }
  
  template<typename T>
  T distance(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1)
  {
    return std::sqrt(distance_squared(x0, y0, z0, w0, x1, y1, z1, w1));
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
  bool normalize(T& x, T& y, T& z)
  {
    auto len = length(x, y, z);
    if (len < 1e-10f)
      return false;
    x /= len;
    y /= len;
    z /= len;
    return true;
  }
  
  template<typename T>
  bool normalize(T& x, T& y, T& z, T& w)
  {
    auto len = length(x, y, z, w);
    if (len < 1e-10f)
      return false;
    x /= len;
    y /= len;
    z /= len;
    w /= len;
    return true;
  }
  
  // Normalizes the angle to the range [-0, 2pi).
  template<typename T>
  T normalize_angle(T ang)
  {
    while (ang < 0.f)
      ang += static_cast<T>(math::cld_2pi);
    while (ang >= static_cast<T>(math::cld_2pi))
      ang -= static_cast<T>(math::cld_2pi);
    return ang;
  }
  
  // Normalizes the angle to the range [-0, 2pi).
  template<typename T>
  T atan2n(T y, T x)
  {
    return normalize_angle(std::atan2(y, x));
  }
  
  template<typename T>
  T dot(T x0, T y0, T x1, T y1)
  {
    return x0*x1 + y0*y1;
  }
  
  template<typename T>
  T dot(T x0, T y0, T z0, T x1, T y1, T z1)
  {
    return x0*x1 + y0*y1 + z0*z1;
  }
  
  template<typename T>
  T dot(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1)
  {
    return x0*x1 + y0*y1 + z0*z1 + w0*w1;
  }

  
  template<typename T>
  T clamp(T val, T lo, T hi)
  {
    if (lo > hi)
      std::swap(lo, hi);
  
    if (val < lo)
      return lo;
    if (hi < val)
      return hi;
    return val;
  }
  
  template<typename ParamT, typename T>
  T lerp(ParamT t, T a, T b)
  {
    T tt = static_cast<T>(t);
    return a*(static_cast<T>(1)-tt) + b*tt;
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
  
  template<typename T0, typename T1>
  T1 linmap_clamped(T0 val_0, T0 start_0, T0 end_0, T1 start_1, T1 end_1)
  {
    auto t = value_to_param<T0>(val_0, start_0, end_0);
    return clamp(lerp<T1>(t, start_1, end_1), start_1, end_1);
  }

  template<typename T>
  bool in_range(T val, std::optional<T> start, std::optional<T> end, Range type)
  {
    switch (type)
    {
      case Range::Free:
        return true;
      case Range::Closed:
        return start.value_or(val) <= val && val <= end.value_or(val);
      case Range::Open:
        return start.value_or(val-1) < val && val < end.value_or(val+1);
      case Range::ClosedOpen:
        return start.value_or(val) <= val && val < end.value_or(val+1);
      case Range::OpenClosed:
        return start.value_or(val-1) < val && val <= end.value_or(val);
      case Range::ClosedFree:
        return start.value_or(val) <= val;
      case Range::FreeClosed:
        return val <= end.value_or(val);
      case Range::OpenFree:
        return start.value_or(val-1) < val;
      case Range::FreeOpen:
        return val < end.value_or(val+1);
    }
    return false;
  }
  
  template<typename T>
  bool in_range(T val, T start, T end, Range type)
  {
    return in_range<T>(val, std::optional<T>(start), std::optional<T>(end), type);
  }
  
  template<typename T>
  bool in_range(T val, T start, std::nullopt_t, Range type)
  {
    return in_range<T>(val, std::optional<T>(start), std::optional<T>{}, type);
  }
  
  template<typename T>
  bool in_range(T val, std::nullopt_t, T end, Range type)
  {
    return in_range<T>(val, std::optional<T>{}, std::optional<T>(end), type);
  }
  
  template<typename T>
  bool in_range(T val, std::nullopt_t, std::nullopt_t, Range type)
  {
    return in_range<T>(val, std::optional<T>{}, std::optional<T>{}, type);
  }


  template<typename T>
  bool in_range(T val, const RangeData<T>& rd)
  {
    return in_range(val, rd.start, rd.end, rd.range);
  }

  template<typename T>
  bool in_unit_range(T val, Range type)
  {
    return in_range(val, static_cast<T>(0), static_cast<T>(1), type);
  }
  
  // start <= v && v <= end
  // in_r_c(v, start, end)   // shorter
  template<typename T>
  inline bool in_r_c(T val, T start, T end) noexcept
  {
    return start <= val && val <= end;
  }
  
  // start < v && v < end
  // in_r_c(v, start, end)   // one char longer
  template<typename T>
  inline bool in_r_o(T val, T start, T end) noexcept
  {
    return start < val && val < end;
  }
  
  // start <= v && v < end
  // in_r_co(v, start, end)   // one char longer
  template<typename T>
  inline bool in_r_co(T val, T start, T end) noexcept
  {
    return start <= val && val < end;
  }
  
  // start < v && v <= end
  // in_r_co(v, start, end)   // one char longer
  template<typename T>
  inline bool in_r_oc(T val, T start, T end) noexcept
  {
    return start < val && val <= end;
  }
  
  // 0.f <= v && v <= 1.f
  // in_r_cu(v)               // shorter
  template<typename T>
  inline bool in_r_cu(T val) noexcept
  {
    return static_cast<T>(0) <= val && val <= static_cast<T>(1);
  }
  
  // 0.f < v && v < 1.f
  // in_r_ou(v)               // shorter
  template<typename T>
  inline bool in_r_ou(T val) noexcept
  {
    return static_cast<T>(0) < val && val < static_cast<T>(1);
  }
  
  // 0.f <= v && v < 1.f
  // in_r_cou(v)              // shorter
  template<typename T>
  inline bool in_r_cou(T val) noexcept
  {
    return static_cast<T>(0) <= val && val < static_cast<T>(1);
  }
  
  // 0.f < v && v <= 1.f
  // in_r_ocu(v)              // shorter
  template<typename T>
  inline bool in_r_ocu(T val) noexcept
  {
    return static_cast<T>(0) < val && val <= static_cast<T>(1);
  }

  template<typename T>
  bool minimize(T& val, T test, const RangeData<T>& rd = {})
  {
    if (test < val && in_range(test, rd))
    {
      val = test;
      return true;
    }
    return false;
  }

  template<typename T>
  bool maximize(T& val, T test, const RangeData<T>& rd = {})
  {
    if (test > val && in_range(test, rd))
    {
      val = test;
      return true;
    }
    return false;
  }

  template<typename T>
  constexpr T get_max() noexcept
  {
    if constexpr (std::is_floating_point_v<T>)
      return std::numeric_limits<T>::infinity();
    else
      return std::numeric_limits<T>::max();
  }
  
  template<typename T>
  constexpr T get_min() noexcept
  {
    if constexpr (std::is_floating_point_v<T>)
      return -std::numeric_limits<T>::infinity();
    else
      return std::numeric_limits<T>::min();
  }


  template<typename T>
  bool fuz_zero(T v, T eps = std::numeric_limits<T>::epsilon())
  {
    return std::abs(v) < eps;
  }

  template<typename T>
  bool fuz_eq(T a, T b, T eps = std::numeric_limits<T>::epsilon())
  {
    return fuz_zero(a - b, eps);
  }
  
  template<typename T>
  T deg2rad(T deg) { return static_cast<T>(cd_pi / 180.) * deg; }
  
  template<typename T>
  T rad2deg(T rad) { return static_cast<T>(180. / cd_pi) * rad; }
  
  // Function to calculate the GCD of two numbers using Euclidean algorithm
  int gcd(int a, int b)
  {
    // Ensure non-negative values for the algorithm
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0)
    {
      int temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }
  
  float gcd(float a, float b)
  {
    // Ensure non-negative values for the algorithm
    a = std::abs(a);
    b = std::abs(b);
    
    while (b > 0.001)  // Using a small threshold for precision
    {
      float temp = std::fmod(a, b);
      a = b;
      b = temp;
    }
    
    return a;
  }
  
  bool toggle(bool& val)
  {
    val = !val;
    return val;
  }
}
