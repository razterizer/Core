//
//  Utf8.h
//  Core
//
//  Created by Rasmus Anthin on 2025-12-12.
//

#pragma once
#include "System.h"
#include <string>
#include <unordered_map>
#include <iostream>


namespace utf8
{

  static const std::unordered_map<char32_t, uint8_t> CP437 =
  {
    // Extended box drawing, blocks, symbols
    {0x00C7, 0x80}, {0x00FC, 0x81}, {0x00E9, 0x82}, {0x00E2, 0x83},
    {0x00E4, 0x84}, {0x00E0, 0x85}, {0x00E5, 0x86}, {0x00E7, 0x87},
    {0x00EA, 0x88}, {0x00EB, 0x89}, {0x00E8, 0x8A}, {0x00EF, 0x8B},
    {0x00EE, 0x8C}, {0x00EC, 0x8D}, {0x00C4, 0x8E}, {0x00C5, 0x8F},

    {0x00C9, 0x90}, {0x00E6, 0x91}, {0x00C6, 0x92}, {0x00F4, 0x93},
    {0x00F6, 0x94}, {0x00F2, 0x95}, {0x00FB, 0x96}, {0x00F9, 0x97},
    {0x00FF, 0x98}, {0x00D6, 0x99}, {0x00DC, 0x9A}, {0x00F8, 0x9B},
    {0x00A3, 0x9C}, {0x00D8, 0x9D}, {0x00D7, 0x9E}, {0x0192, 0x9F},

    {0x00E1, 0xA0}, {0x00ED, 0xA1}, {0x00F3, 0xA2}, {0x00FA, 0xA3},
    {0x00F1, 0xA4}, {0x00D1, 0xA5}, {0x00AA, 0xA6}, {0x00BA, 0xA7},
    {0x00BF, 0xA8}, {0x2310, 0xA9}, {0x00AC, 0xAA}, {0x00BD, 0xAB},
    {0x00BC, 0xAC}, {0x00A1, 0xAD}, {0x00AB, 0xAE}, {0x00BB, 0xAF},

    {0x2591, 0xB0}, {0x2592, 0xB1}, {0x2593, 0xB2},

    {0x2502, 0xB3}, {0x2524, 0xB4}, {0x2561, 0xB5}, {0x2562, 0xB6},
    {0x2556, 0xB7}, {0x2555, 0xB8}, {0x2563, 0xB9}, {0x2551, 0xBA},
    {0x2557, 0xBB}, {0x255D, 0xBC}, {0x255C, 0xBD}, {0x255B, 0xBE},

    {0x2510, 0xBF}, {0x2514, 0xC0}, {0x2534, 0xC1}, {0x252C, 0xC2},
    {0x251C, 0xC3}, {0x2500, 0xC4}, {0x253C, 0xC5}, {0x255E, 0xC6},
    {0x255F, 0xC7}, {0x255A, 0xC8}, {0x2554, 0xC9}, {0x2569, 0xCA},
    {0x2566, 0xCB}, {0x2560, 0xCC}, {0x2550, 0xCD}, {0x256C, 0xCE},

    {0x2567, 0xCF}, {0x2568, 0xD0}, {0x2564, 0xD1}, {0x2565, 0xD2},
    {0x2559, 0xD3}, {0x2558, 0xD4}, {0x2552, 0xD5}, {0x2553, 0xD6},
    {0x256B, 0xD7}, {0x256A, 0xD8}, {0x2518, 0xD9}, {0x250C, 0xDA},
    {0x2588, 0xDB}, {0x2584, 0xDC}, {0x258C, 0xDD}, {0x2590, 0xDE},
    {0x2580, 0xDF},

    // More symbols  
    {0x03B1, 0xE0}, {0x00DF, 0xE1}, {0x0393, 0xE2}, {0x03C0, 0xE3},
    {0x03A3, 0xE4}, {0x03C3, 0xE5}, {0x00B5, 0xE6}, {0x03C4, 0xE7},
    {0x03A6, 0xE8}, {0x0398, 0xE9}, {0x03A9, 0xEA}, {0x03B4, 0xEB},
    {0x221E, 0xEC}, {0x03C6, 0xED}, {0x03B5, 0xEE}, {0x2229, 0xEF},

    {0x2261, 0xF0}, {0x00B1, 0xF1}, {0x2265, 0xF2}, {0x2264, 0xF3},
    {0x2320, 0xF4}, {0x2321, 0xF5}, {0x00F7, 0xF6}, {0x2248, 0xF7},
    {0x00B0, 0xF8}, {0x2219, 0xF9}, {0x00B7, 0xFA}, {0x221A, 0xFB},
    {0x207F, 0xFC}, {0x00B2, 0xFD}, {0x25A0, 0xFE}, {0x00A0, 0xFF}
  };
  
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
  
  inline std::string wstring_to_utf8(const std::wstring& ws)
  {
    std::string out;
    out.reserve(ws.size() * 4); // worst case.
    
#if WCHAR_MAX == 0xFFFF
    // ---------- Windows: UTF-16 decoding ----------
    for (size_t i = 0; i < ws.size(); ++i)
    {
      wchar_t wc = ws[i];
      
      if (wc >= 0xD800 && wc <= 0xDBFF)
      {
        // High surrogate.
        if (i + 1 < ws.size())
        {
          wchar_t wc2 = ws[i + 1];
          if (wc2 >= 0xDC00 && wc2 <= 0xDFFF)
          {
            // Valid surrogate pair.
            uint32_t cp = 0x10000
            + (((wc - 0xD800) << 10)
               |  (wc2 - 0xDC00));
            out += encode_char32(cp);
            ++i;
            continue;
          }
        }
        
        // Invalid pair.
        out += encode_char32(0xFFFD);
      }
      else if (wc >= 0xDC00 && wc <= 0xDFFF)
      {
        // Lone low surrogate.
        out += encode_char32(0xFFFD);
      }
      else
      {
        // BMP wchar.
        out += encode_char32(static_cast<uint32_t>(wc));
      }
    }
#else
    // ---------- macOS / Linux: wchar_t = UTF-32 ----------
    for (wchar_t wc : ws)
      out += encode_char32(static_cast<uint32_t>(wc));
#endif
    
    return out;
  }

  inline void print_char32(char32_t cp)
  {
    if (sys::is_windows_cmd())
    {
      // Windows classic cmd.exe: ASCII only.
      if (cp <= 0x7F)
        std::cout << static_cast<char>(cp);
      else
      {
        auto it = CP437.find(cp);
        if (it != CP437.end())
          std::cout << it-> second;
        else
          std::cout << '?';
      }
    }
    else
    {
      // All UTF-8 capable terminals (MacOS, Linux, Windows Terminal).
      std::cout << encode_char32(cp);
    }
  }
  
}
