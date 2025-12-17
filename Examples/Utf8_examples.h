//
//  Utf8_examples.h
//  Core
//
//  Created by Rasmus Anthin on 2025-12-16.
//

#pragma once
#include "Utf8.h"
#include "StringHelper.h"
#include <iostream>


namespace utf8
{

  void example1(int fg = -1, int bg = -1)
  {
    int codepage = 65001;
    
    auto f_fg_color = [](int fg)
    {
      if (0 <= fg && fg <= 7)
        return 30 + fg;
      if (8 <= fg && fg <= 15)
        return 82 + fg;
      return -1;
    };
    
    auto f_bg_color = [](int bg)
    {
      if (0 <= bg && bg <= 7)
        return 40 + bg;
      if (8 <= bg && bg <= 15)
        return 92 + bg;
      return -1;
    };
    
    auto f_color_str = [f_fg_color, f_bg_color](int fg, int bg)
    {
      std::string str = "\033[";
      auto fg_col = f_fg_color(fg);
      if (fg_col != -1)
        str += std::to_string(fg_col);
      auto bg_col = f_bg_color(bg);
      if (bg_col != -1)
      {
        if (fg_col != -1)
          str += ";";
        str += std::to_string(bg_col);
      }
      str += "m";
      return str;
    };
    
    auto f_reset_str = []() { return "\033[0m"; };
  
    std::cout << "ASCII:" << std::endl;
    std::cout << " cp glyph" << std::endl;
    std::cout << "+--+---+\n";
    for (char32_t cp = 0x00; cp <= 0x7F; ++cp)
    {
      auto enc_str = utf8::encode_char32_codepage(cp, codepage);
      if (wcwidth(cp) != 1)
        continue;
      auto str = " " + enc_str + " ";
      std::cout << "|"
        << str::adjust_str(str::int2hex(cp), str::Adjustment::Right, 2)
        << "|"
        << str
        << "|"
        << "\n";
    }
    std::cout << "+--+---+\n";
    
    auto f_print_utf8_table = [f_color_str, f_reset_str, codepage, fg, bg](char32_t cp_start, char32_t cp_end)
    {
      std::cout << " cp w  glyph" << std::endl;
      std::cout << "+--+--+---+\n";
      for (char32_t cp = cp_start; cp <= cp_end; ++cp)
      {
        auto enc_str = utf8::encode_char32_codepage(cp, codepage);
        auto w = wcwidth(cp);
        //if (wcwidth(cp) != 1)
        //  continue;
        auto str = " " + enc_str + " ";
        std::cout << "|"
        << str::adjust_str(str::int2hex(cp), str::Adjustment::Right, 2)
        << "|"
        << w
        << "|" << f_color_str(fg, bg)
        << str
        << f_reset_str() << "|"
        << "\n";
      }
      std::cout << "+--+--+---+\n";
    };
        
    std::cout << "UTF-8 Latin 1 Supplement:" << std::endl;
    f_print_utf8_table(0xA0, 0xFF);
    
    std::cout << "UTF-8 Latin Extended A:" << std::endl;
    f_print_utf8_table(0x100, 0x17F);
    
    std::cout << "UTF-8 Latin Extended B:" << std::endl;
    f_print_utf8_table(0x180, 0x24F);
    
    std::cout << "UTF-8 Latin Extended Additional:" << std::endl;
    f_print_utf8_table(0x1E00, 0x1EFF);
    
    std::cout << "UTF-8 Latin Extended C:" << std::endl;
    f_print_utf8_table(0x2C60, 0x2C7F);
    
    std::cout << "UTF-8 Latin Extended D:" << std::endl;
    f_print_utf8_table(0xA720, 0xA7FF);
    
    std::cout << "UTF-8 Latin Extended E:" << std::endl;
    f_print_utf8_table(0xAB30, 0xAB6F);
  }

}
