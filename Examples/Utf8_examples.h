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
#include "Term.h"
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>
#include <clocale>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#endif

namespace utf8
{

  void example1(int fg = -1, int bg = -1,
                int codepage = 65001,
                int filter_glyph_width = -2,
                const std::string& filter_block_name = "")
  {
    std::setlocale(LC_CTYPE, "");

    const auto term = term::init_terminal_mode(codepage);

    auto f_fg_color = [](int fg)
    {
      if (0 <= fg && fg <= 7)
        return 30 + fg;
      if (8 <= fg && fg <= 15)
        return 90 + (fg - 8);
      return -1;
    };
    
    auto f_bg_color = [](int bg)
    {
      if (0 <= bg && bg <= 7)
        return 40 + bg;
      if (8 <= bg && bg <= 15)
        return 100 + (bg - 8);
      return -1;
    };

    using ColorStrFunc = std::function<std::string(int, int)>;
    using ResetStrFunc = std::function<std::string()>;

    ColorStrFunc f_color_str = [f_fg_color, f_bg_color](int fg, int bg)
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

    ResetStrFunc f_reset_str = []() { return "\033[0m"; };

    // Disable ANSI colors if VT isn't enabled (prevents printing raw ESC sequences).
    const bool ansi_ok = term::use_ansi_colors(term);
    if (!ansi_ok)
    {
      f_color_str = [](int, int) { return std::string {}; };
      f_reset_str = []() { return std::string {}; };
    }

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
      if (tokens.size() != 3)
        continue;
      //std::cout << tokens.size() << std::endl;
      //std::cout << tokens[0] << ", " << tokens[1] << ", " << tokens[2] << std::endl;
      blocks.emplace_back(str::hex2int<char32_t>(tokens[0]), str::hex2int<char32_t>(tokens[1]), tokens[2]);
    }
    
    // /////////////// Print blocks ////////////////////////
            
    auto f_print_utf8_table = [f_color_str, f_reset_str, term, fg, bg, filter_glyph_width, filter_block_name](std::string_view block, char32_t cp_start, char32_t cp_end)
    {
      if (!filter_block_name.empty() && str::to_lower(block).find(str::to_lower(filter_block_name).c_str()) == std::string::npos)
        return true;
    
      std::cout << str::rep_char('=', 10) << std::endl;
      std::cout << block << ':' << std::endl;
      int max_cp_cols = static_cast<int>(str::int2hex(cp_end).length());
      std::string cp_bar = str::rep_char('-', max_cp_cols);
      std::cout << " cp " << str::rep_char(' ', max_cp_cols - 2) << "w  glyph" << std::endl;
      std::cout << "+" << cp_bar << "+--+---+\n";
      for (char32_t cp = cp_start; cp <= cp_end; ++cp)
      {
        // Always get UTF-8 (for VT/UTF-16 console path) and legacy bytes (for cp437/other).
        const std::string enc_utf8 = utf8::encode_char32_codepage(cp, 65001);
        const std::string enc_legacy = utf8::encode_char32_codepage(cp, term.codepage);
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
