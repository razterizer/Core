//
//  Math_tests.h
//  Core
//
//  Created by Rasmus Anthin on 2025-08-04.
//

#pragma once
#include "Math.h"
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
  }

}
