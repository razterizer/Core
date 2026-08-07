//
//  examples.cpp
//  Core
//
//  Created by Rasmus Anthin on 2025-12-16.
//

#include "Utf8_examples.h"
#include <iostream>

int main(int argc, char** argv)
{
  bool show_help = false;
  int fg = -1;
  int bg = -1;
  int codepage = 65001;
  int filter_glyph_width = -2;
  std::string filter_block_name;
  
  for (int i = 1; i < argc; ++i)
  {
    if (std::strcmp(argv[i], "--help") == 0)
      show_help = true;
    else if (i + 1 < argc && std::strcmp(argv[i], "--fg") == 0)
      fg = std::atoi(argv[i + 1]);
    else if (i + 1 < argc && std::strcmp(argv[i], "--bg") == 0)
      bg = std::atoi(argv[i + 1]);
    else if (i + 1 < argc && std::strcmp(argv[i], "--codepage") == 0)
      codepage = std::atoi(argv[i + 1]);
    else if (i + 1 < argc && std::strcmp(argv[i], "--filter_glyph_width") == 0)
      filter_glyph_width = std::atoi(argv[i + 1]);
    else if (i + 1 < argc && std::strcmp(argv[i], "--filter_block_name") == 0)
      filter_block_name = argv[i + 1];
  }
  
  if (show_help)
  {
    std::cout << "examples --help |" << std::endl;
    std::cout << "   [--fg <fg_color>]" << std::endl;
    std::cout << "   [--bg <bg_color>]" << std::endl;
    std::cout << "   [--codepage <cp>]" << std::endl;
    std::cout << "   [--filter_glyph_width <gw>]" << std::endl;
    std::cout << "   [--filter_block_name <bn>]" << std::endl;
    std::cout << std::endl;
    std::cout << "  <cp> := 65001*|437" << std::endl;
    std::cout << "  <gw> := -1|0|1|2" << std::endl;
    std::cout << "  * : default value" << std::endl;
  
    return 0;
  }

  utf8::example1(fg, bg,
                 codepage,
                 filter_glyph_width,
                 filter_block_name);
  
  return 0;
}
