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
  
  for (int i = 1; i < argc; ++i)
  {
    if (std::strcmp(argv[i], "--help") == 0)
      show_help = true;
    else if (i + 1 < argc && std::strcmp(argv[i], "--fg") == 0)
      fg = std::atoi(argv[i + 1]);
    else if (i + 1 < argc && std::strcmp(argv[i], "--bg") == 0)
      bg = std::atoi(argv[i + 1]);
  }
  
  if (show_help)
  {
    std::cout << "examples --help |" << std::endl;
    std::cout << "   [--fg <fg_color>]" << std::endl;
    std::cout << "   [--bg <bg_color>]" << std::endl;
  
    return 0;
  }

  utf8::example1(fg, bg);
  
  return 0;
}
