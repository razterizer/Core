//
//  FlankDetector_tests.h
//  Core
//
//  Created by Rasmus Anthin on 2025-08-04.
//

#pragma once
#include "../FlankDetector.h"

namespace flankdetector
{

  void unit_tests()
  {
    {
      FlankDetector<float> flank;
      flank.update(0.f);
      assert(flank.pos_flank(0.5f) == false);
      assert(flank.neg_flank(0.5f) == false);
      assert(flank.prev() == 0.f);
      assert(flank.curr() == 0.f);
      flank.update(0.4f);
      assert(flank.pos_flank(0.5f) == false);
      assert(flank.neg_flank(0.5f) == false);
      assert(flank.prev() == 0.f);
      assert(flank.curr() == 0.4f);
      flank.update(1.f);
      assert(flank.pos_flank(0.5f) == true);
      assert(flank.neg_flank(0.5f) == false);
      assert(flank.prev() == 0.4f);
      assert(flank.curr() == 1.f);
      flank.update(0.9f);
      assert(flank.pos_flank(0.5f) == false);
      assert(flank.neg_flank(0.5f) == false);
      assert(flank.prev() == 1.f);
      assert(flank.curr() == 0.9f);
      flank.update(0.3999f);
      assert(flank.pos_flank(0.5f) == false);
      assert(flank.neg_flank(0.5f) == true);
      assert(flank.prev() == 0.9f);
      assert(flank.curr() == 0.3999f);
    }
    {
      FlankDetector<int> flank;
      flank.update(0);
      assert(flank.pos_flank(2) == false);
      assert(flank.neg_flank(3) == false);
      assert(flank.prev() == 0);
      assert(flank.curr() == 0);
      flank.update(1);
      assert(flank.pos_flank(2) == false);
      assert(flank.neg_flank(3) == false);
      assert(flank.prev() == 0);
      assert(flank.curr() == 1);
      flank.update(3);
      assert(flank.pos_flank(2) == false);
      assert(flank.neg_flank(3) == false);
      assert(flank.prev() == 1);
      assert(flank.curr() == 3);
      flank.update(7);
      assert(flank.pos_flank(2) == true);
      assert(flank.neg_flank(3) == false);
      assert(flank.prev() == 3);
      assert(flank.curr() == 7);
      flank.update(4);
      assert(flank.pos_flank(2) == false);
      assert(flank.neg_flank(3) == false);
      assert(flank.prev() == 7);
      assert(flank.curr() == 4);
      flank.update(0);
      assert(flank.pos_flank(2) == false);
      assert(flank.neg_flank(3) == true);
      assert(flank.prev() == 4);
      assert(flank.curr() == 0);
    }
    {
      FlankDetector<bool> flank;
      flank.update(false);
      assert(flank.pos_flank(false) == false);
      assert(flank.neg_flank(false) == false);
      assert(flank.pos_flank(true) == false);
      assert(flank.neg_flank(true) == false);
      assert(flank.prev() == false);
      assert(flank.curr() == false);
      flank.update(true);
      assert(flank.pos_flank(false) == true);
      assert(flank.neg_flank(false) == false);
      assert(flank.pos_flank(true) == false);
      assert(flank.neg_flank(true) == false);
      assert(flank.prev() == false);
      assert(flank.curr() == true);
      flank.update(false);
      assert(flank.pos_flank(false) == false);
      assert(flank.neg_flank(false) == true);
      assert(flank.pos_flank(true) == false);
      assert(flank.neg_flank(true) == false);
      assert(flank.prev() == true);
      assert(flank.curr() == false);
    }
  }

}
