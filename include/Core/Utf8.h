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
  
  inline char32_t decode_next_char32(const std::string& s, size_t& i)
  {
    const auto* data = reinterpret_cast<const unsigned char*>(s.data());
    const auto len = s.size();
    if (i >= len)
      return 0;
    
    unsigned char b0 = data[i++];
    
    if (b0 < 0x80)
      return b0;
    
    auto next_byte = [&](char32_t& acc, int shift) -> bool
    {
      if (i >= len)
        return false;
      unsigned char bx = data[i++];
      if ((bx & 0xC0) != 0x80)
        return false;
      acc |= static_cast<char32_t>(bx & 0x3F) << shift;
      return true;
    };
    
    if ((b0 & 0xE0) == 0xC0)
    {
      char32_t cp = static_cast<char32_t>(b0 & 0x1F) << 6;
      if (!next_byte(cp, 0))
        return 0xFFFD;
      return cp;
    }
    if ((b0 & 0xF0) == 0xE0)
    {
      char32_t cp = static_cast<char32_t>(b0 & 0x0F) << 12;
      if (!next_byte(cp, 6)) return 0xFFFD;
      if (!next_byte(cp, 0)) return 0xFFFD;
      return cp;
    }
    if ((b0 & 0xF8) == 0xF0)
    {
      char32_t cp = static_cast<char32_t>(b0 & 0x07) << 18;
      if (!next_byte(cp, 12)) return 0xFFFD;
      if (!next_byte(cp, 6))  return 0xFFFD;
      if (!next_byte(cp, 0))  return 0xFFFD;
      return cp;
    }
    
    // Invalid leading byte.
    return 0xFFFD;
  }
  
  inline std::string encode_wchar(wchar_t wc)
  {
#if WCHAR_MAX == 0xFFFF
    // ---------- Windows: UTF-16 wchar_t ----------
    uint32_t cp;
    
    // Check if wchar_t is a surrogate.
    if (wc >= 0xD800 && wc <= 0xDBFF)
    {
      // High surrogate without matching low surrogate → invalid.
      cp = 0xFFFD;
    }
    else if (wc >= 0xDC00 && wc <= 0xDFFF)
    {
      // Lone low surrogate → invalid.
      cp = 0xFFFD;
    }
    else
    {
      cp = static_cast<uint32_t>(wc);
    }
    
    return encode_char32(cp);
    
#else
    // ---------- macOS / Linux: UTF-32 wchar_t ----------
    return encode_char32(static_cast<char32_t>(wc));
#endif
  }
  
}
