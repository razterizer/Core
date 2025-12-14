//
//  Utf8_tests.h
//  Core
//
//  Created by Rasmus Anthin on 2025-12-12.
//

#pragma once
#include "Utf8.h"
#include "System.h"
#include <cassert>

namespace utf8
{

  void unit_tests()
  {
    {
      std::string encoded_utf8_str = utf8::encode_char32_utf8(0x0152);
      encoded_utf8_str += utf8::encode_char32_utf8(0x21CB);
      
      char32_t ch32 = utf8::none;
      size_t char_idx = 0;
      
      while (utf8::decode_next_utf8_char32(encoded_utf8_str, ch32, char_idx))
      {
        if (char_idx == 0) assert(ch32 == 0x0152);
        if (char_idx == 1) assert(ch32 == 0x21CB);
        ++char_idx;
      }
      std::cout << "---" << std::endl;
    }
    {
      utf8::print_char32(0x263A); // ☺
      utf8::print_char32(0x2588); // █
      std::cout << std::endl;
      std::cout << "---" << std::endl;
    }
    {
      std::vector<char32_t> cps = {
        0x41,       // 'A'
        0x00F6,     // ö
        0x0152,     // Œ
        0x2588,     // █
        0x21CB,     // ↋
        0x1F600     // 😀 (needs UTF-8, not printable on classic cmd.exe)
      };
      
      for (char32_t cp : cps)
      {
        std::string enc = utf8::encode_char32_utf8(cp);
        
        size_t idx = 0;
        char32_t dec = utf8::none;
        auto ret = utf8::decode_next_utf8_char32(enc, dec, idx);
        assert(ret);
        assert(cp == dec);
        
        std::string reenc = utf8::encode_char32_codepage(dec);
        
        bool ok = (cp == dec) && (enc == reenc);
        
        std::cout << "Testing U+"
        << std::hex << static_cast<uint32_t>(cp)
        << std::dec << " -> "
        << (ok ? "OK" : "FAIL")
        << "\n";
        
        if (!sys::is_windows_cmd())
          std::cout << enc << "\n";  // Print the glyph
      }
      std::cout << "---" << std::endl;
    }
    {
      std::string utf8 = utf8::encode_wstring_utf8(L"Hello ↋ Œ 😀");
      std::cout << utf8 << "\n";
      
      for (auto ch : utf8)
        std::cout << ch << ", "
                  << std::dec << static_cast<int>(ch) << ", "
                  << std::hex << static_cast<int>(ch) << std::endl;
      std::cout << std::dec << std::endl;
      std::cout << "---" << std::endl;
    }
    
  }
  
}
