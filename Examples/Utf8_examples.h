//
//  Utf8_examples.h
//  Core
//
//  Created by Rasmus Anthin on 2025-12-16.
//

#pragma once
#include "Utf8.h"
#include "StringHelper.h"
#include "Keyboard.h"
#include "TextIO.h"
#include <iostream>


namespace utf8
{

  void example1(int fg = -1, int bg = -1,
                int codepage = 65001,
                int filter_glyph_width = -2,
                const std::string& filter_block_name = "")
  {
    std::setlocale(LC_CTYPE, "");
  
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
    
    // /////////////// Parse Blocks.txt ////////////////////
    
    std::vector<std::string> lines;
    if (!TextIO::read_file("Blocks.txt", lines))
      return;
      
    std::vector<std::tuple<char32_t, char32_t, std::string>> blocks;
    for (const auto& l : lines)
    {
      // 0000..007F; Basic Latin
      if (l.empty())
        continue;
      if (l.starts_with("#"))
        continue;
      auto tokens = str::tokenize(l, { '.', ';' });
      //std::cout << tokens.size() << std::endl;
      //std::cout << tokens[0] << ", " << tokens[1] << ", " << tokens[2] << std::endl;
      blocks.emplace_back(str::hex2int<char32_t>(tokens[0]), str::hex2int<char32_t>(tokens[1]), tokens[2]);
    }
    
    // /////////////// Print blocks ////////////////////////
            
    auto f_print_utf8_table = [f_color_str, f_reset_str, codepage, fg, bg, filter_glyph_width, filter_block_name](std::string_view block, char32_t cp_start, char32_t cp_end)
    {
      if (!filter_block_name.empty() && block.find(filter_block_name.c_str()) == std::string::npos)
        return true;
    
      std::cout << str::rep_char('=', 10) << std::endl;
      std::cout << block << ':' << std::endl;
      int max_cp_cols = static_cast<int>(str::int2hex(cp_end).length());
      std::string cp_bar = str::rep_char('-', max_cp_cols);
      std::cout << " cp " << str::rep_char(' ', max_cp_cols - 2) << "w  glyph" << std::endl;
      std::cout << "+" << cp_bar << "+--+---+\n";
      for (char32_t cp = cp_start; cp <= cp_end; ++cp)
      {
        auto enc_str = utf8::encode_char32_codepage(cp, codepage);
        wchar_t wc = static_cast<wchar_t>(cp);
        auto w = wcwidth(wc);
        if (filter_glyph_width != -2 && w != filter_glyph_width)
          continue;
        auto str = " " + enc_str + " ";
        std::cout << "|"
        << str::adjust_str(str::int2hex(cp), str::Adjustment::Right, max_cp_cols)
        << "|"
        << str::adjust_str(std::to_string(w), str::Adjustment::Right, 2)
        << "|" << f_color_str(fg, bg)
        << str
        << f_reset_str() << "|"
        << "\n";
      }
      std::cout << "+" << cp_bar << "+--+---+\n";
      std::cout << "-- " << block << " --" << std::endl;
      
      return keyboard::press_any_key_or_quit();
    };
    
    for (const auto& b : blocks)
    {
      const auto& [start, end, name] = b;
      if (!f_print_utf8_table(name, start, end))
        return;
    }
  }

}
