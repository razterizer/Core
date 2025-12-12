//
//  Utf8.h
//  Core
//
//  Created by Rasmus Anthin on 2025-12-12.
//

#pragma once
#include <string>

namespace utf8
{
  
  inline std::string encode_char32(char32_t cp)
  {
    std::string out;
    
    if (cp <= 0x7F)
    {
      out.push_back(static_cast<char>(cp));
    }
    else if (cp <= 0x7FF)
    {
      out.push_back(static_cast<char>(0xC0 | (cp >> 6)));
      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    }
    else if (cp <= 0xFFFF)
    {
      out.push_back(static_cast<char>(0xE0 | (cp >> 12)));
      out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    }
    else if (cp <= 0x10FFFF)
    {
      out.push_back(static_cast<char>(0xF0 | (cp >> 18)));
      out.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
      out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    }
    else
      out.push_back('?'); // Fallback for invalid range.
    
    return out;
  }

  
}
