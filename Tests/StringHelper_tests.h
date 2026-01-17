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
      char ch = 'W';
      
      char ch_lo = to_lower(ch);
      assert(ch_lo == 'w');
    }
    {
      char ch = 'w';
      
      char ch_hi = to_upper(ch);
      assert(ch_hi == 'W');
    }
    {
      std::string str = "Hej Hopp!";
      
      std::string str_lo = to_lower(str);
      assert(str_lo == "hej hopp!");
      
      std::string str_hi = to_upper(str);
      assert(str_hi == "HEJ HOPP!");
    }
    {
      std::string str = "Hej Hopp!";
      
      std::string str_lo = to_lower(std::string_view { str });
      assert(str_lo == "hej hopp!");
      
      std::string str_hi = to_upper(std::string_view { str });
      assert(str_hi == "HEJ HOPP!");
    }
    {
      char str[] = "Hej Hopp!";
      
      std::string str_lo = to_lower(std::string_view { str });
      assert(str_lo == "hej hopp!");
      
      std::string str_hi = to_upper(std::string_view { str });
      assert(str_hi == "HEJ HOPP!");
    }
    {
      char str[] = "Hej Hopp!";
      
      const char* str_lo = to_lower_mut(str);
      assert(std::strcmp(str_lo, "hej hopp!") == 0);
      assert(std::strcmp(str, "hej hopp!") == 0);
      
      const char* str_hi = to_upper_mut(str);
      assert(std::strcmp(str_hi, "HEJ HOPP!") == 0);
      assert(std::strcmp(str, "HEJ HOPP!") == 0);
    }
    {
      char str[] = "Hej Hopp!";
      
      const char* str_lo = to_lower_mut(str, 3);
      assert(std::strcmp(str_lo, "hej Hopp!") == 0);
      assert(std::strcmp(str, "hej Hopp!") == 0);
      
      const char* str_hi = to_upper_mut(str, 3);
      assert(std::strcmp(str_hi, "HEJ Hopp!") == 0);
      assert(std::strcmp(str, "HEJ Hopp!") == 0);
    }
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
    {
      std::string str = "()";
      
      auto tokens = tokenize(str, {}, { '(', ')' }, 0);
      //std::cout << tokens.size() << std::endl;
      //for (const auto& tok : tokens)
      //  std::cout << tok.size() << ": '" << tok << "'" << std::endl;
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 0);
      
      tokens = tokenize(str, { ',' }, { '(', ')' }, 0);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 0);
      
      tokens = tokenize(str, { ',', '(', ')' }, {}, 0);
      assert(tokens.size() == 0);
      
      tokens = tokenize(str, {}, { '(', ')' }, 1);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == ")");
      
      tokens = tokenize(str, { ',' }, { '(', ')' }, 1);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == ")");
      
      tokens = tokenize(str, { ',', '(', ')' }, {}, 1);
      assert(tokens.size() == 0);
      
      str = "(A)";
      
      tokens = tokenize(str, {}, { '(', ')' }, 0);
      //std::cout << tokens.size() << std::endl;
      //for (const auto& tok : tokens)
      //  std::cout << tok.size() << ": '" << tok << "'" << std::endl;
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == "A");
      
      tokens = tokenize(str, { ',' }, { '(', ')' }, 0);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == "A");
      
      tokens = tokenize(str, { ',', '(', ')' }, {}, 0);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == "A");
      
      tokens = tokenize(str, {}, { '(', ')' }, 1);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == "A");
      
      tokens = tokenize(str, { ',' }, { '(', ')' }, 1);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == "A");
      
      tokens = tokenize(str, { ',', '(', ')' }, {}, 1);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == "A");
      
      str = "(A,B)";
      
      tokens = tokenize(str, {}, { '(', ')' }, 0);
      //std::cout << tokens.size() << std::endl;
      //for (const auto& tok : tokens)
      //  std::cout << tok.size() << ": '" << tok << "'" << std::endl;
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 3);
      assert(tokens[0] == "A,B");
      
      tokens = tokenize(str, { ',' }, { '(', ')' }, 0);
      //std::cout << tokens.size() << std::endl;
      //for (const auto& tok : tokens)
      //  std::cout << tok.size() << ": '" << tok << "'" << std::endl;
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 3);
      assert(tokens[0] == "A,B");
      
      tokens = tokenize(str, { ',', '(', ')' }, {}, 0);
      assert(tokens.size() == 2);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == "A");
      assert(tokens[1].size() == 1);
      assert(tokens[1] == "B");
      
      tokens = tokenize(str, {}, { '(', ')' }, 1);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 3);
      assert(tokens[0] == "A,B");
      
      tokens = tokenize(str, { ',' }, { '(', ')' }, 1);
      assert(tokens.size() == 1);
      assert(tokens[0].size() == 3);
      assert(tokens[0] == "A,B");
      
      tokens = tokenize(str, { ',', '(', ')' }, {}, 1);
      assert(tokens.size() == 2);
      assert(tokens[0].size() == 1);
      assert(tokens[0] == "A");
      assert(tokens[1].size() == 1);
      assert(tokens[1] == "B");
    }
  }

}
