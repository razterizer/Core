//
//  StringHelper_tests.h
//  Core
//
//  Created by Rasmus Anthin on 2025-11-25.
//

#pragma once
#include "StringHelper.h"
#include <cassert>

namespace str
{

  void unit_tests()
  {
    {
      assert(is_digit('0'));
      assert(is_digit('9'));
      assert(!is_digit('.'));
      assert(!is_digit('A'));
    }
    {
      assert(to_digit('0') == 0);
      assert(to_digit('9') == 9);
      assert(to_digit('.') < 0);
      assert(to_digit('A') > 0);
    }
    {
      assert(hexch2int('0') == 0);
      assert(hexch2int('9') == 9);
      assert(hexch2int('.') == -1);
      assert(hexch2int('A') == 10);
      assert(hexch2int('F') == 15);
      assert(hexch2int('a') == 10);
      assert(hexch2int('f') == 15);
    }
    {
      assert(int2hexch(0) == '0');
      assert(int2hexch(9) == '9');
      assert(int2hexch(-1) == '?');
      assert(int2hexch(10) == 'A');
      assert(int2hexch(15) == 'F');
    }
    {
      assert(hex2int("0") == 0);
      assert(hex2int("9") == 9);
      assert(hex2int(".") == -1);
      assert(hex2int("A") == 10);
      assert(hex2int("F") == 15);
      assert(hex2int("a") == 10);
      assert(hex2int("f") == 15);
      assert(hex2int("FA") == 250);
      assert(hex2int("4D") == 77);
    }
    {
      assert(int2hex(0) == "0");
      assert(int2hex(9) == "9");
      assert(int2hex(-1) == "FFFFFFFF"); // 4 bytes!
      assert(int2hex(10) == "A");
      assert(int2hex(15) == "F");
      assert(int2hex(250) == "FA");
      assert(int2hex(77) == "4D");
    }
  }

}
