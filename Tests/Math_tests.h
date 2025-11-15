//
//  Math_tests.h
//  Core
//
//  Created by Rasmus Anthin on 2025-08-04.
//

#pragma once
#include "MathUtils.h"
#include <cassert>

namespace math
{

  void unit_tests()
  {
    {
      assert(roundI(3.5f) == 4);
      assert(roundI(3.5) == 4);
      assert(roundI(1.2f) == 1);
      assert(roundI(1.2) == 1);
      assert(roundI(4.9f) == 5);
      assert(roundI(4.9) == 5);
    }
    
    {
      assert(floorI(3.5f) == 3);
      assert(floorI(3.5) == 3);
      assert(floorI(1.2f) == 1);
      assert(floorI(1.2) == 1);
      assert(floorI(4.9f) == 4);
      assert(floorI(4.9) == 4);
    }
    {
      assert(ceilI(3.5f) == 4);
      assert(ceilI(3.5) == 4);
      assert(ceilI(1.2f) == 2);
      assert(ceilI(1.2) == 2);
      assert(ceilI(4.9f) == 5);
      assert(ceilI(4.9) == 5);
    }
    {
      assert(sgn(-1.5f) == -1);
      assert(sgn(-1.5) == -1);
      assert(sgn(0.f) == 0);
      assert(sgn(0.) == 0);
      assert(sgn(4.9f) == 1);
      assert(sgn(4.9) == 1);
    }
    {
      assert(sign(-1.5f) == -1);
      assert(sign(-1.5) == -1);
      assert(sign(0.f) == 1);
      assert(sign(0.) == 1);
      assert(sign(4.9f) == 1);
      assert(sign(4.9) == 1);
    }
    {
      assert(sq(-1.5f) == 2.25f);
      assert(sq(-1.5) == 2.25);
      assert(sq(0.f) == 0.f);
      assert(sq(0.) == 0.);
      assert(sq(4.9f) == 24.01f);
      assert(std::abs(sq(4.9) - 24.01) < 1e-9);
    }
    {
      assert(cube(-1.5f) == -3.375f);
      assert(cube(-1.5) == -3.375);
      assert(cube(0.f) == 0.f);
      assert(cube(0.) == 0.);
      assert(cube(4.9f) == 117.649f);
      assert(std::abs(cube(4.9) - 117.649) < 1e-9);
    }
    {
      assert(length_squared(3, 2) == 13);
      assert(length_squared(-7.f, 3.f) == 58.f);
      assert(length_squared(4., -1.) == 17.);
      assert(length_squared(0, 0) == 0);
    }
    {
      assert(length_squared(3, 2, -5) == 38);
      assert(length_squared(-7.f, 3.f, 1.f) == 59.f);
      assert(length_squared(4., -1., 0.) == 17.);
      assert(length_squared(0, 0, 0) == 0);
    }
    {
      assert(length_squared(3, 2, -5, 2) == 42);
      assert(length_squared(-7.f, 3.f, 1.f, 0.f) == 59.f);
      assert(length_squared(4., -1., 0., 6.) == 53.);
      assert(length_squared(0, 0, 0, 0) == 0);
    }
    {
      assert(length(3, 2) == 3);
      assert(length(-7.f, 3.f) == 7.61577311f);
      assert(fuz_eq(length(4., -1.), 4.12310563, 1e-8));
      assert(length(0, 0) == 0);
    }
    {
      assert(length(3, 2, -5) == 6);
      assert(length(-7.f, 3.f, 1.f) == 7.68114575f);
      assert(fuz_eq(length(4., -1., 0.), 4.12310563, 1e-8));
      assert(length(0, 0, 0) == 0);
    }
    {
      assert(length(3, 2, -5, 2) == 6);
      assert(fuz_eq(length(-7.f, 3.f, 1.f, 0.f), 7.68114575f, 1e-8f));
      assert(fuz_eq(length(4., -1., 0., 6.), 7.28010989, 1e-8));
      assert(length(0, 0, 0, 0) == 0);
    }
    {
      assert(distance_squared(-1,2, 3,1) == 17);
      assert(distance_squared(13.f,7.f, 2.5f,-2.f) == 191.25f);
      assert(distance_squared(11.,5., 1.,25.) == 500.);
      assert(distance_squared(0,0, 0,0) == 0);
    }
    {
      assert(distance_squared(-1,2,2, 3,1,7) == 42);
      assert(distance_squared(13.f,7.f,-6.f, 2.5f,-2.f,8.f) == 387.25f);
      assert(distance_squared(11.,5.,50., 1.,25.,0.) == 3000.);
      assert(distance_squared(0,0, 0,0) == 0);
    }
    {
      assert(distance_squared(-1,2,2,-7, 3,1,7,3) == 142);
      assert(distance_squared(13.f,7.f,-6.f,1.4f, 2.5f,-2.f,8.f,-5.7f) == 437.66f);
      assert(distance_squared(11.,5.,50.,3.3, 1.,25.,0.,1.) == 3005.29);
      assert(distance_squared(0,0,0, 0,0,0) == 0);
    }
    {
      assert(distance(-1,2, 3,1) == 4);
      assert(distance(13.f,7.f, 2.5f,-2.f) == 13.82931669f);
      assert(fuz_eq(distance(11.,5., 1.,25.), 22.36067977, 1e-8));
      assert(distance(0,0, 0,0) == 0);
    }
    {
      assert(distance(-1,2,2, 3,1,7) == 6);
      assert(distance(13.f,7.f,-6.f, 2.5f,-2.f,8.f) == 19.67866865f);
      assert(fuz_eq(distance(11.,5.,50., 1.,25.,0.), 54.77225575, 1e-8));
      assert(distance(0,0, 0,0) == 0);
    }
    {
      assert(distance(-1,2,2,-7, 3,1,7,3) == 11);
      assert(distance(13.f,7.f,-6.f,1.4f, 2.5f,-2.f,8.f,-5.7f) == 20.92032505f);
      assert(fuz_eq(distance(11.,5.,50.,3.3, 1.,25.,0.,1.), 54.82052535, 1e-8));
      assert(distance(0,0,0, 0,0,0) == 0);
    }
    {
      float x = -7.f;
      float y = 3.f;
      // 7.61577311f
      assert(normalize(x, y));
      assert(x == -0.91914503f);
      assert(y == 0.3939193f);
      x = 0.f;
      y = 0.f;
      assert(!normalize(x, y));
      assert(x == 0.f);
      assert(y == 0.f);
    }
    {
      float x = -7.f;
      float y = 3.f;
      float z = 1.f;
      // 7.68114575f
      assert(normalize(x, y, z));
      assert(fuz_eq(x, -0.91132238f, 1e-7f));
      assert(y == 0.39056673f);
      assert(z == 0.13018891f);
      x = 0.f;
      y = 0.f;
      z = 0.f;
      assert(!normalize(x, y, z));
      assert(x == 0.f);
      assert(y == 0.f);
      assert(z == 0.f);
    }
    {
      float x = -7.f;
      float y = 3.f;
      float z = 1.f;
      float w = 0.f;
      // 7.68114575f
      assert(normalize(x, y, z, w));
      assert(fuz_eq(x, -0.91132238f, 1e-7f));
      assert(y == 0.39056673f);
      assert(z == 0.13018891f);
      assert(w == 0.f);
      x = 0.f;
      y = 0.f;
      z = 0.f;
      w = 0.f;
      assert(!normalize(x, y, z, w));
      assert(x == 0.f);
      assert(y == 0.f);
      assert(z == 0.f);
      assert(w == 0.f);
    }
    {
      assert(normalize_angle(0.f) == 0.f);
      assert(normalize_angle(-0.f) == -0.f);
      assert(normalize_angle(-c_pi) == c_pi);
      assert(normalize_angle(c_pi) == c_pi);
      assert(normalize_angle(c_2pi) == 0);
      assert(fuz_eq(normalize_angle(3*c_pi), c_pi, 1e-6f));
      assert(normalize_angle(4*c_pi) == 0.f);
      assert(normalize_angle(-c_2pi) == 0.f);
      assert(normalize_angle(-c_pi_2) == c_3pi_2);
    }
    {
      // Basic quadrants.
      assert(atan2n(0.f, 1.f) == 0.f);
      assert(atan2n(1.f, 0.f) == c_pi_2);
      assert(atan2n(0.f, -1.f) == c_pi);
      assert(atan2n(-1.f, 0.f) == c_3pi_2);

      // Diagonals.
      assert(atan2n(1.f, 1.f) == c_pi_4);
      assert(atan2n(1.f, -1.f) == c_3pi_4);
      assert(atan2n(-1., -1.) == cd_5pi_4);
      assert(atan2n(-1., 1.) == cd_7pi_4);

      // Edge cases around wrap-around.
      assert(atan2n(0.f, -1.f) == c_pi);                      // π
      assert(atan2n(-0.f, -1.f) == c_pi);                     // still π
      assert(atan2n(-0.f, 1.f) == 0.f);                       // normalized to 0
      assert(atan2n(-1.f, 0.f) == c_3pi_2);                   // wraps around correctly

      // Sanity check for normalization.
      assert(atan2n(0.f, -1.f) == normalize_angle(std::atan2(0.f, -1.f)));
      assert(atan2n(-1.f, 0.f) == normalize_angle(std::atan2(-1.f, 0.f)));
    }
    {
      // Basic orthogonal and parallel vectors.
      assert(dot(1.f, 0.f, 1.f, 0.f) == 1.f);      // same direction → 1
      assert(dot(0.f, 1.f, 0.f, 1.f) == 1.f);      // same direction → 1
      assert(dot(1.f, 0.f, 0.f, 1.f) == 0.f);      // perpendicular → 0
      assert(dot(1.f, 0.f, -1.f, 0.f) == -1.f);    // opposite → -1

      // 45° diagonal combinations.
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 0.f), 1.f, 1e-6f));     // projection along x
      assert(fuz_eq(dot(1.f, 1.f, 0.f, 1.f), 1.f, 1e-6f));     // projection along y
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f), 2.f, 1e-6f));     // same diagonal
      assert(fuz_eq(dot(1.f, 1.f, -1.f, -1.f), -2.f, 1e-6f));  // opposite diagonal
      assert(fuz_eq(dot(1.f, 1.f, -1.f, 1.f), 0.f, 1e-6f));    // orthogonal diagonals

      // Double precision coverage.
      assert(dot(1.0, 0.0, 1.0, 0.0) == 1.0);
      assert(dot(1.0, 0.0, 0.0, 1.0) == 0.0);
      assert(dot(1.0, 1.0, 1.0, 1.0) == 2.0);
      assert(dot(1.0, 1.0, -1.0, -1.0) == -2.0);
      assert(dot(1.0, 1.0, -1.0, 1.0) == 0.0);
    }
    {
      // Basic axis-aligned vectors.
      assert(dot(1.f, 0.f, 0.f, 1.f, 0.f, 0.f) == 1.f);    // same X-axis
      assert(dot(0.f, 1.f, 0.f, 0.f, 1.f, 0.f) == 1.f);    // same Y-axis
      assert(dot(0.f, 0.f, 1.f, 0.f, 0.f, 1.f) == 1.f);    // same Z-axis
      assert(dot(1.f, 0.f, 0.f, -1.f, 0.f, 0.f) == -1.f);  // opposite X-axis
      assert(dot(0.f, 1.f, 0.f, 0.f, -1.f, 0.f) == -1.f);  // opposite Y-axis
      assert(dot(0.f, 0.f, 1.f, 0.f, 0.f, -1.f) == -1.f);  // opposite Z-axis

      // Orthogonal pairs.
      assert(dot(1.f, 0.f, 0.f, 0.f, 1.f, 0.f) == 0.f);
      assert(dot(0.f, 1.f, 0.f, 0.f, 0.f, 1.f) == 0.f);
      assert(dot(1.f, 0.f, 0.f, 0.f, 0.f, 1.f) == 0.f);

      // Diagonal vectors.
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f, 1.f, 1.f), 3.f, 1e-6f));     // same direction
      assert(fuz_eq(dot(1.f, 1.f, 1.f, -1.f, -1.f, -1.f), -3.f, 1e-6f)); // opposite
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f, 0.f, 0.f), 1.f, 1e-6f));     // projection along X
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 0.f, 1.f, 0.f), 1.f, 1e-6f));     // projection along Y
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 0.f, 0.f, 1.f), 1.f, 1e-6f));     // projection along Z

      // Double precision coverage.
      assert(dot(1.0, 0.0, 0.0, 1.0, 0.0, 0.0) == 1.0);
      assert(dot(1.0, 1.0, 1.0, 1.0, 1.0, 1.0) == 3.0);
      assert(dot(1.0, 1.0, 1.0, -1.0, -1.0, -1.0) == -3.0);
      assert(dot(1.0, 0.0, 0.0, 0.0, 1.0, 0.0) == 0.0);
      assert(dot(0.0, 1.0, 0.0, 0.0, 0.0, 1.0) == 0.0);
    }
    {
      // Basic axis-aligned vectors.
      assert(dot(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f) == 1.f);     // same X-axis
      assert(dot(0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f) == 1.f);     // same Y-axis
      assert(dot(0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f) == 1.f);     // same Z-axis
      assert(dot(0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f) == 1.f);     // same W-axis
      assert(dot(1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f) == -1.f);   // opposite X
      assert(dot(0.f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f) == -1.f);   // opposite Y
      assert(dot(0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f) == -1.f);   // opposite Z
      assert(dot(0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f) == -1.f);   // opposite W

      // Orthogonal checks.
      assert(dot(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f) == 0.f);
      assert(dot(0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f) == 0.f);
      assert(dot(0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f) == 0.f);

      // Diagonal directions.
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f), 4.f, 1e-6f));     // same direction
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f, -1.f, -1.f, -1.f, -1.f), -4.f, 1e-6f));// opposite
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f), 1.f, 1e-6f));     // projection on X
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 0.f), 1.f, 1e-6f));     // projection on Y
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f), 1.f, 1e-6f));     // projection on Z
      assert(fuz_eq(dot(1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f), 1.f, 1e-6f));     // projection on W

      // Double precision coverage.
      assert(dot(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0) == 1.0);
      assert(dot(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0) == 4.0);
      assert(dot(1.0, 1.0, 1.0, 1.0, -1.0, -1.0, -1.0, -1.0) == -4.0);
      assert(dot(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0) == 0.0);
      assert(dot(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0) == 0.0);
      assert(dot(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0) == 0.0);
    }
    {
      // Within range.
      assert(clamp(5.f, 0.f, 10.f) == 5.f);
      assert(clamp(5.0, 0.0, 10.0) == 5.0);

      // Below range.
      assert(clamp(-1.f, 0.f, 10.f) == 0.f);
      assert(clamp(-1.0, 0.0, 10.0) == 0.0);

      // Above range.
      assert(clamp(11.f, 0.f, 10.f) == 10.f);
      assert(clamp(11.0, 0.0, 10.0) == 10.0);

      // Edge values (exactly at bounds).
      assert(clamp(0.f, 0.f, 10.f) == 0.f);
      assert(clamp(10.f, 0.f, 10.f) == 10.f);
      assert(clamp(0.0, 0.0, 10.0) == 0.0);
      assert(clamp(10.0, 0.0, 10.0) == 10.0);

      // Negative ranges.
      assert(clamp(-5.f, -10.f, -1.f) == -5.f);    // inside range
      assert(clamp(-15.f, -10.f, -1.f) == -10.f);  // below
      assert(clamp(0.f, -10.f, -1.f) == -1.f);     // above

      // Degenerate (lo == hi).
      assert(clamp(5.f, 3.f, 3.f) == 3.f);
      assert(clamp(-2.f, -5.f, -5.f) == -5.f);
      assert(clamp(5.0, 3.0, 3.0) == 3.0);
      assert(clamp(-2.0, -5.0, -5.0) == -5.0);

      // Floating-point tolerance checks.
      assert(fuz_eq(clamp(1.000001f, 0.f, 1.f), 1.f, 1e-6f));
      assert(fuz_eq(clamp(-0.00001f, 0.f, 1.f), 0.f, 1e-6f));
    }
    {
      // Basic interpolation.
      assert(lerp(0.f, 0.f, 10.f) == 0.f);    // t = 0 → a
      assert(lerp(1.f, 0.f, 10.f) == 10.f);   // t = 1 → b
      assert(lerp(0.5f, 0.f, 10.f) == 5.f);   // midpoint
      assert(lerp(0.25f, 0.f, 8.f) == 2.f);   // quarter point
      assert(lerp(0.75f, 0.f, 8.f) == 6.f);   // three-quarter point

      // Negative values.
      assert(lerp(0.5f, -10.f, 10.f) == 0.f);
      assert(lerp(0.25f, -4.f, 4.f) == -2.f);
      assert(lerp(0.75f, -4.f, 4.f) == 2.f);

      // Extrapolation (t < 0 or t > 1).
      assert(lerp(-0.5f, 0.f, 10.f) == -5.f); // below range
      assert(lerp(1.5f, 0.f, 10.f) == 15.f);  // above range

      // Double precision.
      assert(lerp(0.f, 0.0, 10.0) == 0.0);
      assert(lerp(1.0f, 0.0, 10.0) == 10.0);
      assert(lerp(0.5f, 0.0, 10.0) == 5.0);

      // Degenerate case (a == b).
      assert(lerp(0.0f, 3.f, 3.f) == 3.f);
      assert(lerp(0.5f, 3.f, 3.f) == 3.f);
      assert(lerp(1.0f, 3.f, 3.f) == 3.f);
    }
    {
      // Basic ascending range.
      assert(value_to_param(0.f, 0.f, 10.f) == 0.f);
      assert(value_to_param(5.f, 0.f, 10.f) == 0.5f);
      assert(value_to_param(10.f, 0.f, 10.f) == 1.f);

      // Descending range.
      assert(value_to_param(5.f, 10.f, 0.f) == 0.5f);
      assert(value_to_param(0.f, 10.f, 0.f) == 1.f);
      assert(value_to_param(10.f, 10.f, 0.f) == 0.f);

      // Extrapolation.
      assert(value_to_param(-5.f, 0.f, 10.f) == -0.5f);
      assert(value_to_param(15.f, 0.f, 10.f) == 1.5f);

      // Degenerate case (start == end).
      assert(value_to_param(5.f, 5.f, 5.f) == 1.f);   // val >= start
      assert(value_to_param(0.f, 5.f, 5.f) == 0.f);   // val < start

      // Double precision equivalents.
      assert(value_to_param(5.0, 0.0, 10.0) == 0.5);
      assert(value_to_param(10.0, 0.0, 10.0) == 1.0);
      assert(value_to_param(-5.0, 0.0, 10.0) == -0.5);
    }
    {
      // Basic ascending range.
      assert(value_to_param_clamped(0.f, 0.f, 10.f) == 0.f);
      assert(value_to_param_clamped(5.f, 0.f, 10.f) == 0.5f);
      assert(value_to_param_clamped(10.f, 0.f, 10.f) == 1.f);

      // Values below and above range should be clamped.
      assert(value_to_param_clamped(-5.f, 0.f, 10.f) == 0.f); // clamped low
      assert(value_to_param_clamped(15.f, 0.f, 10.f) == 1.f); // clamped high

      // Descending range.
      assert(value_to_param_clamped(5.f, 10.f, 0.f) == 0.5f);
      assert(value_to_param_clamped(-5.f, 10.f, 0.f) == 1.f); // clamped high
      assert(value_to_param_clamped(15.f, 10.f, 0.f) == 0.f); // clamped low

      // Degenerate case (start == end).
      assert(value_to_param_clamped(5.f, 5.f, 5.f) == 1.f);
      assert(value_to_param_clamped(0.f, 5.f, 5.f) == 0.f);

      // Double precision equivalents.
      assert(value_to_param_clamped(5.0, 0.0, 10.0) == 0.5);
      assert(value_to_param_clamped(-5.0, 0.0, 10.0) == 0.0);
      assert(value_to_param_clamped(15.0, 0.0, 10.0) == 1.0);
    }
    {
      // Ascending positive step.
      {
        auto v = linspace(0.f, 1.f, 5.f);
        assert(v.size() == 6);
        assert(v[0] == 0.f);
        assert(v[1] == 1.f);
        assert(v[2] == 2.f);
        assert(v[3] == 3.f);
        assert(v[4] == 4.f);
        assert(v[5] == 5.f);
      }

      // Descending negative step.
      {
        auto v = linspace(5.f, -1.f, 0.f);
        assert(v.size() == 6);
        assert(v[0] == 5.f);
        assert(v[1] == 4.f);
        assert(v[2] == 3.f);
        assert(v[3] == 2.f);
        assert(v[4] == 1.f);
        assert(v[5] == 0.f);
      }

      // Step exactly fitting range.
      {
        auto v = linspace(0.f, 2.f, 8.f);
        assert(v.size() == 5);
        assert(v.back() == 8.f);
      }

      // Step not perfectly fitting end.
      {
        auto v = linspace(0.f, 3.f, 10.f);
        assert(v.size() == 4);          // 0, 3, 6, 9 (12 would exceed 10)
        assert(v[0] == 0.f);
        assert(v[3] == 9.f);
      }

      // Negative range with negative step.
      {
        auto v = linspace(-1.f, -1.f, -5.f); // -1, -2, -3, -4, -5
        assert(v.size() == 5);
        assert(v.front() == -1.f);
        assert(v.back() == -5.f);
      }

      // Zero step → expect empty result.
      {
        auto v = linspace(0.f, 0.f, 10.f);
        assert(v.empty());
      }

      // Double precision variant.
      {
        auto v = linspace(0.0, 0.5, 2.0);
        assert(v.size() == 5);
        assert(v[0] == 0.0);
        assert(v[1] == 0.5);
        assert(v[2] == 1.0);
        assert(v[3] == 1.5);
        assert(v[4] == 2.0);
      }
    }
    {
      // Basic ascending map.
      assert(linmap(0.f, 0.f, 10.f, 0.f, 100.f)   == 0.f);
      assert(linmap(5.f, 0.f, 10.f, 0.f, 100.f)   == 50.f);
      assert(linmap(10.f, 0.f, 10.f, 0.f, 100.f)  == 100.f);

      // Reverse mapping (input reversed).
      assert(linmap(0.f, 10.f, 0.f, 0.f, 100.f)   == 100.f);
      assert(linmap(5.f, 10.f, 0.f, 0.f, 100.f)   == 50.f);
      assert(linmap(10.f, 10.f, 0.f, 0.f, 100.f)  == 0.f);

      // Reverse output range.
      assert(linmap(0.f, 0.f, 10.f, 100.f, 0.f)   == 100.f);
      assert(linmap(5.f, 0.f, 10.f, 100.f, 0.f)   == 50.f);
      assert(linmap(10.f, 0.f, 10.f, 100.f, 0.f)  == 0.f);

      // Negative ranges.
      assert(linmap(-5.f, -10.f, 0.f, 0.f, 100.f) == 50.f);
      assert(linmap(-10.f, -10.f, 0.f, 0.f, 100.f)== 0.f);
      assert(linmap(0.f, -10.f, 0.f, 0.f, 100.f)  == 100.f);

      // Mixed types (float → double).
      assert(linmap(5.f, 0.f, 10.f, 0.0, 1.0)     == 0.5);
      assert(linmap(2.5f, 0.f, 10.f, 0.0, 1.0)    == 0.25);

      // Degenerate input range (start == end).
      assert(linmap(5.f, 5.f, 5.f, 0.f, 100.f)    == 100.f);  // val ≥ start
      assert(linmap(0.f, 5.f, 5.f, 0.f, 100.f)    == 0.f);    // val < start

      // Double precision case.
      assert(linmap(5.0, 0.0, 10.0, 0.0, 1.0)     == 0.5);
      assert(linmap(10.0, 0.0, 10.0, 0.0, 1.0)    == 1.0);
      assert(linmap(0.0, 0.0, 10.0, 0.0, 1.0)     == 0.0);
    }
    {
      // Basic ascending map (within range).
      assert(linmap_clamped(0.f, 0.f, 10.f, 0.f, 100.f)   == 0.f);
      assert(linmap_clamped(5.f, 0.f, 10.f, 0.f, 100.f)   == 50.f);
      assert(linmap_clamped(10.f, 0.f, 10.f, 0.f, 100.f)  == 100.f);

      // Values below and above input range → clamped to output range.
      assert(linmap_clamped(-5.f, 0.f, 10.f, 0.f, 100.f)  == 0.f);    // clamped low
      assert(linmap_clamped(15.f, 0.f, 10.f, 0.f, 100.f)  == 100.f);  // clamped high

      // Reversed input range (descending).
      assert(linmap_clamped(0.f, 10.f, 0.f, 0.f, 100.f)   == 100.f);
      assert(linmap_clamped(5.f, 10.f, 0.f, 0.f, 100.f)   == 50.f);
      assert(linmap_clamped(10.f, 10.f, 0.f, 0.f, 100.f)  == 0.f);
      assert(linmap_clamped(-5.f, 10.f, 0.f, 0.f, 100.f)  == 100.f);  // below → clamped high
      assert(linmap_clamped(15.f, 10.f, 0.f, 0.f, 100.f)  == 0.f);    // above → clamped low

      // Reverse output range (descending).
      assert(linmap_clamped(0.f, 0.f, 10.f, 100.f, 0.f)   == 100.f);
      assert(linmap_clamped(5.f, 0.f, 10.f, 100.f, 0.f)   == 50.f);
      assert(linmap_clamped(10.f, 0.f, 10.f, 100.f, 0.f)  == 0.f);
      assert(linmap_clamped(-5.f, 0.f, 10.f, 100.f, 0.f)  == 100.f);  // clamped high
      assert(linmap_clamped(15.f, 0.f, 10.f, 100.f, 0.f)  == 0.f);    // clamped low

      // Negative ranges.
      assert(linmap_clamped(-5.f, -10.f, 0.f, 0.f, 100.f) == 50.f);
      assert(linmap_clamped(-15.f, -10.f, 0.f, 0.f, 100.f)== 0.f);    // below
      assert(linmap_clamped(5.f, -10.f, 0.f, 0.f, 100.f)  == 100.f);  // above

      // Mixed types (float → double).
      assert(linmap_clamped(5.f, 0.f, 10.f, 0.0, 1.0)     == 0.5);
      assert(linmap_clamped(-5.f, 0.f, 10.f, 0.0, 1.0)    == 0.0);
      assert(linmap_clamped(15.f, 0.f, 10.f, 0.0, 1.0)    == 1.0);

      // Degenerate input range (start == end).
      assert(linmap_clamped(5.f, 5.f, 5.f, 0.f, 100.f)    == 100.f); // val ≥ start
      assert(linmap_clamped(0.f, 5.f, 5.f, 0.f, 100.f)    == 0.f);   // val < start

      // Double precision case.
      assert(linmap_clamped(5.0, 0.0, 10.0, 0.0, 1.0)     == 0.5);
      assert(linmap_clamped(-5.0, 0.0, 10.0, 0.0, 1.0)    == 0.0);
      assert(linmap_clamped(15.0, 0.0, 10.0, 0.0, 1.0)    == 1.0);
    }
    {
      const float val_mid = 5.f;
      const float val_lo  = 0.f;
      const float val_hi  = 10.f;

      // --- Range::Free ---
      assert(in_range(val_mid, val_lo, val_hi, Range::Free));
      assert(in_range(val_lo, val_lo, val_hi, Range::Free));
      assert(in_range(val_hi, val_lo, val_hi, Range::Free));

      // --- Range::Closed [start,end] ---
      assert(in_range(5.f, 0.f, 10.f, Range::Closed));  // inside
      assert(in_range(0.f, 0.f, 10.f, Range::Closed));  // inclusive low
      assert(in_range(10.f, 0.f, 10.f, Range::Closed)); // inclusive high
      assert(!in_range(-1.f, 0.f, 10.f, Range::Closed)); // below
      assert(!in_range(11.f, 0.f, 10.f, Range::Closed)); // above

      // --- Range::Open (start,end) ---
      assert(in_range(5.f, 0.f, 10.f, Range::Open));   // inside
      assert(!in_range(0.f, 0.f, 10.f, Range::Open));  // exclusive low
      assert(!in_range(10.f, 0.f, 10.f, Range::Open)); // exclusive high

      // --- Range::ClosedOpen [start,end) ---
      assert(in_range(5.f, 0.f, 10.f, Range::ClosedOpen));
      assert(in_range(0.f, 0.f, 10.f, Range::ClosedOpen));  // inclusive low
      assert(!in_range(10.f, 0.f, 10.f, Range::ClosedOpen)); // exclusive high

      // --- Range::OpenClosed (start,end] ---
      assert(in_range(5.f, 0.f, 10.f, Range::OpenClosed));
      assert(!in_range(0.f, 0.f, 10.f, Range::OpenClosed)); // exclusive low
      assert(in_range(10.f, 0.f, 10.f, Range::OpenClosed)); // inclusive high

      // --- Range::ClosedFree [start,∞) ---
      assert(in_range(5.f, 0.f, std::nullopt, Range::ClosedFree));  // inside
      assert(in_range(0.f, 0.f, std::nullopt, Range::ClosedFree));  // inclusive low
      assert(!in_range(-1.f, 0.f, std::nullopt, Range::ClosedFree)); // below

      // --- Range::FreeClosed (-∞,end] ---
      assert(in_range(5.f, std::nullopt, 10.f, Range::FreeClosed));  // inside
      assert(in_range(10.f, std::nullopt, 10.f, Range::FreeClosed)); // inclusive high
      assert(!in_range(11.f, std::nullopt, 10.f, Range::FreeClosed)); // above

      // --- Range::OpenFree (start,∞) ---
      assert(in_range(5.f, 0.f, std::nullopt, Range::OpenFree));   // inside
      assert(!in_range(0.f, 0.f, std::nullopt, Range::OpenFree));  // exclusive low
      assert(in_range(1000.f, 0.f, std::nullopt, Range::OpenFree)); // large OK

      // --- Range::FreeOpen (-∞,end) ---
      assert(in_range(5.f, std::nullopt, 10.f, Range::FreeOpen));  // inside
      assert(!in_range(10.f, std::nullopt, 10.f, Range::FreeOpen)); // exclusive high
      assert(in_range(-1000.f, std::nullopt, 10.f, Range::FreeOpen)); // large negative OK

      // --- Optional parameter edge tests ---
      assert(in_range(5.f, std::nullopt, std::nullopt, Range::Free));  // always true
      assert(!in_range(5.f, 10.f, std::nullopt, Range::ClosedFree)); // below start
      assert(in_range(15.f, 10.f, std::nullopt, Range::ClosedFree)); // above start
      assert(in_range(-5.f, std::nullopt, 0.f, Range::FreeClosed));  // below, but end limits ok
      assert(!in_range(5.f, std::nullopt, 0.f, Range::FreeClosed));  // above end
    }
    {
      // --- Basic Closed range ---
      {
        RangeData<float> rd(0.f, 10.f, Range::Closed);
        assert(in_range(5.f, rd));   // inside
        assert(in_range(0.f, rd));   // inclusive low
        assert(in_range(10.f, rd));  // inclusive high
        assert(!in_range(-1.f, rd)); // below
        assert(!in_range(11.f, rd)); // above
      }

      // --- Open range ---
      {
        RangeData<float> rd(0.f, 10.f, Range::Open);
        assert(in_range(5.f, rd));   // inside
        assert(!in_range(0.f, rd));  // exclusive low
        assert(!in_range(10.f, rd)); // exclusive high
      }

      // --- ClosedOpen [start, end) ---
      {
        RangeData<float> rd(0.f, 10.f, Range::ClosedOpen);
        assert(in_range(5.f, rd));
        assert(in_range(0.f, rd));    // inclusive low
        assert(!in_range(10.f, rd));  // exclusive high
      }

      // --- OpenClosed (start, end] ---
      {
        RangeData<float> rd(0.f, 10.f, Range::OpenClosed);
        assert(in_range(5.f, rd));
        assert(!in_range(0.f, rd));   // exclusive low
        assert(in_range(10.f, rd));   // inclusive high
      }

      // --- ClosedFree [start, ∞) ---
      {
        RangeData<float> rd(0.f, std::nullopt, Range::ClosedFree);
        assert(in_range(0.f, rd));
        assert(in_range(1000.f, rd));
        assert(!in_range(-1.f, rd));
      }

      // --- FreeClosed (-∞, end] ---
      {
        RangeData<float> rd(std::nullopt, 10.f, Range::FreeClosed);
        assert(in_range(10.f, rd));
        assert(in_range(-1000.f, rd));
        assert(!in_range(11.f, rd));
      }

      // --- OpenFree (start, ∞) ---
      {
        RangeData<float> rd(0.f, std::nullopt, Range::OpenFree);
        assert(!in_range(0.f, rd));   // exclusive low
        assert(in_range(1.f, rd));    // inside
        assert(in_range(100.f, rd));  // large OK
      }

      // --- FreeOpen (-∞, end) ---
      {
        RangeData<float> rd(std::nullopt, 10.f, Range::FreeOpen);
        assert(in_range(5.f, rd));     // inside
        assert(!in_range(10.f, rd));   // exclusive high
        assert(in_range(-100.f, rd));  // large negative OK
      }

      // --- Free (unbounded) ---
      {
        RangeData<float> rd(std::nullopt, std::nullopt, Range::Free);
        assert(in_range(-1000.f, rd));
        assert(in_range(0.f, rd));
        assert(in_range(1000.f, rd));
      }

      // --- Mixed type sanity (double) ---
      {
        RangeData<double> rd(0.0, 1.0, Range::Closed);
        assert(in_range(0.5, rd));
        assert(!in_range(-0.1, rd));
        assert(!in_range(1.1, rd));
      }

      // --- Default constructed RangeData (Free) ---
      {
        RangeData<float> rd; // default = Range::Free
        assert(in_range(0.f, rd));   // always true
        assert(in_range(-123.f, rd));
        assert(in_range(999.f, rd));
      }
    }
    {
      // --- Range::Free ---
      assert(in_unit_range(0.f, Range::Free));
      assert(in_unit_range(-5.f, Range::Free));
      assert(in_unit_range(100.f, Range::Free));

      // --- Range::Closed [0,1] ---
      assert(in_unit_range(0.f, Range::Closed));
      assert(in_unit_range(0.5f, Range::Closed));
      assert(in_unit_range(1.f, Range::Closed));
      assert(!in_unit_range(-0.01f, Range::Closed));
      assert(!in_unit_range(1.01f, Range::Closed));

      // --- Range::Open (0,1) ---
      assert(in_unit_range(0.5f, Range::Open));
      assert(!in_unit_range(0.f, Range::Open));
      assert(!in_unit_range(1.f, Range::Open));
      assert(!in_unit_range(-0.5f, Range::Open));
      assert(!in_unit_range(1.5f, Range::Open));

      // --- Range::ClosedOpen [0,1) ---
      assert(in_unit_range(0.f, Range::ClosedOpen));
      assert(in_unit_range(0.5f, Range::ClosedOpen));
      assert(!in_unit_range(1.f, Range::ClosedOpen));

      // --- Range::OpenClosed (0,1] ---
      assert(in_unit_range(0.5f, Range::OpenClosed));
      assert(in_unit_range(1.f, Range::OpenClosed));
      assert(!in_unit_range(0.f, Range::OpenClosed));

      // --- Range::ClosedFree [0,∞) ---
      assert(in_unit_range(0.f, Range::ClosedFree));
      assert(in_unit_range(5.f, Range::ClosedFree));
      assert(!in_unit_range(-0.5f, Range::ClosedFree));

      // --- Range::FreeClosed (-∞,1] ---
      assert(in_unit_range(1.f, Range::FreeClosed));
      assert(in_unit_range(-5.f, Range::FreeClosed));
      assert(!in_unit_range(2.f, Range::FreeClosed));

      // --- Range::OpenFree (0,∞) ---
      assert(in_unit_range(0.5f, Range::OpenFree));
      assert(in_unit_range(5.f, Range::OpenFree));
      assert(!in_unit_range(0.f, Range::OpenFree));

      // --- Range::FreeOpen (-∞,1) ---
      assert(in_unit_range(0.5f, Range::FreeOpen));
      assert(in_unit_range(-5.f, Range::FreeOpen));
      assert(!in_unit_range(1.f, Range::FreeOpen));

      // --- Double precision sanity check ---
      assert(in_unit_range(0.5, Range::Closed));
      assert(!in_unit_range(-0.1, Range::Closed));
      assert(!in_unit_range(1.1, Range::Closed));
    }
    {
      // --- Basic unbounded behavior (default RangeData = Free) ---
      {
        float val = 10.f;
        assert(minimize(val, 5.f));      // test < val → updated
        assert(val == 5.f);
        assert(!minimize(val, 7.f));     // test > val → unchanged
        assert(val == 5.f);
      }

      // --- With Closed range [0,10] ---
      {
        float val = 10.f;
        RangeData<float> rd(0.f, 10.f, Range::Closed);

        assert(minimize(val, 9.f, rd));  // inside range, smaller → updates
        assert(val == 9.f);
        assert(!minimize(val, 15.f, rd)); // outside range → ignored
        assert(val == 9.f);
        assert(minimize(val, 0.f, rd));  // lower bound okay → updates
        assert(val == 0.f);
        assert(!minimize(val, -1.f, rd));// below range → ignored
      }

      // --- With Open range (0,10) ---
      {
        float val = 10.f;
        RangeData<float> rd(0.f, 10.f, Range::Open);

        assert(!minimize(val, 0.f, rd));  // exclusive low → ignored
        assert(val == 10.f);
        assert(minimize(val, 5.f, rd));   // inside → updates
        assert(val == 5.f);
      }

      // --- With upper-unbounded range [0,∞) ---
      {
        float val = 100.f;
        RangeData<float> rd(0.f, std::nullopt, Range::ClosedFree);

        assert(minimize(val, 50.f, rd));   // inside range → updates
        assert(val == 50.f);
        assert(!minimize(val, -1.f, rd));  // below range → ignored
        assert(val == 50.f);
      }

      // --- With lower-unbounded range (-∞,10] ---
      {
        float val = 10.f;
        RangeData<float> rd(std::nullopt, 10.f, Range::FreeClosed);

        assert(minimize(val, 9.f, rd));    // inside range → updates
        assert(val == 9.f);
        assert(!minimize(val, 11.f, rd));  // above end → ignored
        assert(val == 9.f);
      }

      // --- RangeData Free (default constructed) ---
      {
        float val = 5.f;
        RangeData<float> rd; // Range::Free → always true
        assert(minimize(val, 3.f, rd));
        assert(val == 3.f);
      }

      // --- Double precision sanity ---
      {
        double val = 20.0;
        RangeData<double> rd(0.0, 100.0, Range::Closed);

        assert(minimize(val, 10.0, rd));  // updates
        assert(val == 10.0);
        assert(!minimize(val, 50.0, rd)); // test > val → no update
        assert(val == 10.0);
      }
    }
    {
      // --- Basic unbounded behavior (default RangeData = Free) ---
      {
        float val = 5.f;
        assert(maximize(val, 10.f));     // test > val → updates
        assert(val == 10.f);
        assert(!maximize(val, 7.f));     // test < val → unchanged
        assert(val == 10.f);
      }

      // --- With Closed range [0,10] ---
      {
        float val = 0.f;
        RangeData<float> rd(0.f, 10.f, Range::Closed);

        assert(maximize(val, 5.f, rd));   // inside range → updates
        assert(val == 5.f);
        assert(!maximize(val, 15.f, rd)); // outside range → ignored
        assert(val == 5.f);
        assert(maximize(val, 10.f, rd));  // inclusive upper bound → updates
        assert(val == 10.f);
        assert(!maximize(val, 11.f, rd)); // above range → ignored
      }

      // --- With Open range (0,10) ---
      {
        float val = 0.f;
        RangeData<float> rd(0.f, 10.f, Range::Open);

        assert(!maximize(val, 0.f, rd));  // exclusive low → ignored
        assert(maximize(val, 5.f, rd));   // inside → updates
        assert(val == 5.f);
        assert(!maximize(val, 10.f, rd)); // exclusive high → ignored
      }

      // --- With upper-unbounded range [0,∞) ---
      {
        float val = 0.f;
        RangeData<float> rd(0.f, std::nullopt, Range::ClosedFree);

        assert(maximize(val, 50.f, rd));  // inside range → updates
        assert(val == 50.f);
        assert(!maximize(val, -1.f, rd)); // below range → ignored
        assert(val == 50.f);
      }

      // --- With lower-unbounded range (-∞,10] ---
      {
        float val = 0.f;
        RangeData<float> rd(std::nullopt, 10.f, Range::FreeClosed);

        assert(maximize(val, 5.f, rd));   // inside → updates
        assert(val == 5.f);
        assert(maximize(val, 10.f, rd));  // inclusive upper bound → updates
        assert(val == 10.f);
        assert(!maximize(val, 15.f, rd)); // outside → ignored
        assert(val == 10.f);
      }

      // --- RangeData Free (default constructed) ---
      {
        float val = 3.f;
        RangeData<float> rd; // Range::Free → always true
        assert(maximize(val, 5.f, rd));
        assert(val == 5.f);
      }

      // --- Double precision sanity ---
      {
        double val = 10.0;
        RangeData<double> rd(0.0, 100.0, Range::Closed);

        assert(maximize(val, 20.0, rd)); // updates
        assert(val == 20.0);
        assert(!maximize(val, 15.0, rd)); // test < val → no update
        assert(val == 20.0);
      }
    }
    {
      // --- Floating-point types ---
      {
        constexpr float f = get_max<float>();
        constexpr double d = get_max<double>();

        assert(std::isinf(f));
        assert(std::isinf(d));
        assert(f > 0.f);
        assert(d > 0.0);
      }

      // --- Integer types ---
      {
        constexpr int i = get_max<int>();
        constexpr long l = get_max<long>();
        constexpr unsigned u = get_max<unsigned>();

        assert(i == std::numeric_limits<int>::max());
        assert(l == std::numeric_limits<long>::max());
        assert(u == std::numeric_limits<unsigned>::max());
      }

      // --- Mixed sanity checks ---
      {
        // Ensure behavior differs between float and int
        constexpr float f = get_max<float>();
        constexpr int i = get_max<int>();
        assert(std::isinf(f));
        assert(i != std::numeric_limits<float>::infinity());
      }

      // --- Compile-time constexpr verification ---
      {
        assert(std::isinf(get_max<float>()));
        assert(get_max<int>() == std::numeric_limits<int>::max());
      }
    }
    {
      // --- Floating-point types ---
      {
        constexpr float f = get_min<float>();
        constexpr double d = get_min<double>();

        assert(std::isinf(f));
        assert(std::isinf(d));
        assert(f < 0.f);
        assert(d < 0.0);
      }

      // --- Integer types ---
      {
        constexpr int i = get_min<int>();
        constexpr long l = get_min<long>();
        constexpr unsigned u = get_min<unsigned>();

        assert(i == std::numeric_limits<int>::min());
        assert(l == std::numeric_limits<long>::min());
        assert(u == std::numeric_limits<unsigned>::min());
      }

      // --- Mixed sanity checks (no casting infinities to ints) ---
      {
        // Floats: get_min<float>() is -inf and is strictly less than the most negative finite value
        constexpr float fmin = get_min<float>();
        constexpr float fmax = get_max<float>();
        assert(std::isinf(fmin) && fmin < -std::numeric_limits<float>::max());
        assert(std::isinf(fmax) && fmax >  std::numeric_limits<float>::max());

        // Ints: values are finite and exactly the numeric_limits extrema
        constexpr int imin = get_min<int>();
        constexpr int imax = get_max<int>();
        assert(imin == std::numeric_limits<int>::min());
        assert(imax == std::numeric_limits<int>::max());
      }

      // --- Compile-time constexpr verification ---
      {
        assert(std::isinf(get_min<float>()));
        assert(get_min<int>() == std::numeric_limits<int>::min());
      }
    }
    {
      // --- Float tests ---
      {
        assert(fuz_zero(0.f));                        // exactly zero
        assert(fuz_zero(1e-8f));                      // within default epsilon (~1.19e-7)
        assert(!fuz_zero(1e-4f));                     // above epsilon
        assert(!fuz_zero(-1e-4f));                    // symmetric negative above epsilon
        assert(fuz_zero(-1e-8f));                     // within epsilon on negative side
        assert(!fuz_zero(0.001f, 1e-5f));             // using custom epsilon → false
        assert(fuz_zero(0.001f, 1e-2f));              // custom larger epsilon → true
      }
      
      // --- Double tests ---
      {
        assert(fuz_zero(0.0));
        assert(fuz_zero(1e-17));                      // within default epsilon (~2.22e-16)
        assert(!fuz_zero(1e-14));                     // above epsilon
        assert(fuz_zero(-1e-17));                     // within epsilon (negative)
        assert(!fuz_zero(-1e-14));                    // outside epsilon
        assert(fuz_zero(1e-8, 1e-6));                 // custom epsilon makes it true
      }

      // --- Edge case sanity ---
      {
        // Large magnitude should never count as zero
        assert(!fuz_zero(1000.f));
        assert(!fuz_zero(-1000.0));
        // Smallest representable epsilon check
        assert(!fuz_zero(std::numeric_limits<float>::epsilon() * 10.f)); // borderline but > eps
        assert(fuz_zero(std::numeric_limits<float>::epsilon() / 2.f));   // within eps
      }
    }
    {
      // --- Float tests ---
      {
        assert(fuz_eq(0.f, 0.f));                       // exact equality
        assert(fuz_eq(1.f, 1.f));                       // same finite values
        assert(fuz_eq(1.f + 1e-8f, 1.f));               // within float epsilon (~1.19e-7)
        assert(!fuz_eq(1.f + 1e-4f, 1.f));              // above epsilon
        assert(fuz_eq(-1e-8f, 0.f));                    // symmetric
        assert(fuz_eq(0.001f, 0.001001f, 1e-3f));       // custom epsilon true
        assert(!fuz_eq(0.001f, 0.0015f, 1e-4f));        // custom epsilon false
      }

      // --- Double tests ---
      {
        assert(fuz_eq(0.0, 0.0));                       // exact equality
        assert(fuz_eq(1.0, 1.0));                       // identical
        assert(fuz_eq(1.0 + 1e-17, 1.0));               // within double epsilon (~2.22e-16)
        assert(!fuz_eq(1.0 + 1e-12, 1.0));              // well above epsilon
        assert(fuz_eq(-1e-17, 0.0));                    // symmetric around zero
        assert(fuz_eq(1.0, 1.000001, 1e-5));            // custom epsilon true
        assert(!fuz_eq(1.0, 1.000001, 1e-7));           // custom epsilon false
      }

      // --- Edge and sign tests ---
      {
        assert(fuz_eq(-0.f, 0.f));                      // -0 == +0
        assert(!fuz_eq(1000.f, -1000.f));               // opposite sign, large difference
        assert(fuz_eq(1000.f, 1000.00001f, 1e-2f));     // large value, large epsilon
      }

      // --- Mixed sanity checks ---
      {
        assert(!fuz_eq(1.f, 2.f));                      // far apart
        assert(fuz_eq(1.f, 1.f + 1e-8f));               // within float epsilon
        assert(!fuz_eq(1.f, 1.f + 1e-5f));              // outside float epsilon
      }
    }
    {
      // --- Canonical degree-to-radian conversions ---
      assert(deg2rad(0.f) == 0.f);
      assert(deg2rad(180.f) == c_pi);              // 180° = π
      assert(deg2rad(90.f) == c_pi_2);            // 90°  = π/2
      assert(deg2rad(45.f) ==  c_pi_4);            // 45°  = π/4
      assert(deg2rad(360.f) == c_2pi);             // 360° = 2π
      assert(deg2rad(-180.f) == -c_pi);            // negative angles

      // --- Double precision checks ---
      assert(deg2rad(180.0) == cd_pi);
      assert(deg2rad(90.0) == cd_pi_2);
      assert(deg2rad(45.0) == cd_pi_4);
      assert(deg2rad(360.0) == cd_2pi);
      assert(deg2rad(-180.0) == -cd_pi);

      // --- Round-trip verification with rad2deg() ---
      assert(rad2deg(deg2rad(180.f)) == 180.f);
      assert(rad2deg(deg2rad(90.f)) == 90.f);
      assert(rad2deg(deg2rad(45.f)) == 45.f);
      assert(rad2deg(deg2rad(-180.f)) == -180.f);
      assert(rad2deg(deg2rad(360.f)) == 360.f);

      // --- Edge sanity ---
      assert(deg2rad(0.5f) == c_pi / 360.f);        // tiny fraction
      assert(deg2rad(-0.5f) == -c_pi / 360.f);
    }
    {
      // --- Canonical radian-to-degree conversions (float) ---
      assert(rad2deg(0.f) == 0.f);
      assert(rad2deg(c_pi) == 180.f);   // π   → 180°
      assert(rad2deg(c_pi_2) == 90.f);    // π/2 → 90°
      assert(rad2deg(c_pi_4) == 45.f);    // π/4 → 45°
      assert(rad2deg(c_2pi) == 360.f);   // 2π  → 360°
      assert(rad2deg(-c_pi) == -180.f);   // -π  → -180°

      // --- Double precision checks ---
      assert(rad2deg(cd_pi) == 180.0);
      assert(rad2deg(cd_pi_2) == 90.0);
      assert(rad2deg(cd_pi_4) == 45.0);
      assert(rad2deg(cd_2pi) == 360.0);
      assert(rad2deg(-cd_pi) == -180.0);

      // --- Round-trip verification with deg2rad() ---
      assert(deg2rad(rad2deg(c_pi)) == c_pi);
      assert(deg2rad(rad2deg(c_pi_2)) == c_pi_2);
      assert(deg2rad(rad2deg(c_pi_4)) == c_pi_4);
      assert(deg2rad(rad2deg(-c_pi)) == -c_pi);
      assert(deg2rad(rad2deg(c_2pi)) ==  c_2pi);

      // --- Edge sanity ---
      assert(rad2deg(c_pi / 360.f) == 0.5f);     // tiny fraction → 0.5°
      assert(rad2deg(-c_pi / 360.f) == -0.5f);
    }
    {
      // --- Basic positive integers ---
      assert(gcd(10, 5) == 5);
      assert(gcd(5, 10) == 5);        // order reversed
      assert(gcd(21, 14) == 7);
      assert(gcd(14, 21) == 7);
      assert(gcd(100, 25) == 25);
      assert(gcd(25, 100) == 25);
      assert(gcd(81, 27) == 27);

      // --- Coprime numbers ---
      assert(gcd(8, 15) == 1);
      assert(gcd(15, 8) == 1);
      assert(gcd(13, 7) == 1);

      // --- With zero ---
      assert(gcd(0, 5) == 5);
      assert(gcd(5, 0) == 5);
      assert(gcd(0, 0) == 0);         // both zero — conventional edge case

      // --- Negative values ---
      assert(gcd(-10, 5) == 5);
      assert(gcd(10, -5) == 5);
      assert(gcd(-10, -5) == 5);
      assert(gcd(-27, 9) == 9);
      assert(gcd(27, -9) == 9);

      // --- Large numbers ---
      assert(gcd(123456, 7890) == 6);
      assert(gcd(1'000'000, 2'500'000) == 500'000);

      // --- Symmetry sanity ---
      for (int a = -50; a <= 50; ++a)
        for (int b = -50; b <= 50; ++b)
          assert(gcd(a, b) == gcd(b, a));
    }
    {
      // --- Basic cases where gcd divides cleanly ---
      assert(gcd(10.f, 5.f) == 5.f);
      assert(gcd(5.f, 10.f) == 5.f);
      assert(gcd(21.f, 14.f) == 7.f);
      assert(gcd(14.f, 21.f) == 7.f);
      assert(gcd(100.f, 25.f) == 25.f);
      assert(gcd(81.f, 27.f) == 27.f);

      // --- Coprime-like floats ---
      assert(gcd(8.f, 15.f) == 1.f);   // close to 1
      assert(gcd(15.f, 8.f) == 1.f);

      // --- Values including zeros ---
      assert(gcd(0.f, 5.f) == 5.f);
      assert(gcd(5.f, 0.f) == 5.f);
      assert(gcd(0.f, 0.f) == 0.f);

      // --- Negative values ---
      assert(gcd(-10.f, 5.f) == 5.f);
      assert(gcd(10.f, -5.f) == 5.f);
      assert(gcd(-10.f, -5.f) == 5.f);

      // --- Non-integer ratios ---
      assert(gcd(10.5f, 5.25f) == 5.25f);
      assert(gcd(9.0f, 6.0f) == 3.0f);
      assert(fuz_eq(gcd(0.9f, 0.6f), 0.3f));

      // --- Large values ---
      assert(gcd(123456.f, 7890.f) == 6.f);
      assert(gcd(1'000'000.f, 2'500'000.f) == 500'000.f);

      // --- Precision sanity ---
      {
        float g = gcd(1.0f, 0.3333f);
        assert(g == 0.3333f);  // rough divisor
      }

      // --- Symmetry and non-negativity ---
      for (int a = -20; a <= 20; ++a)
        for (int b = -20; b <= 20; ++b)
          assert(gcd((float)a, (float)b) == gcd((float)b, (float)a));

      for (int a = -50; a <= 50; ++a)
        for (int b = -50; b <= 50; ++b)
          assert(gcd((float)a, (float)b) >= 0.f);
    }
    {
      bool v = false;
      assert(toggle(v) == true);
      assert(v == true);
      
      assert(toggle(v) == false);
      assert(v == false);
    }
    
    





  }

}
