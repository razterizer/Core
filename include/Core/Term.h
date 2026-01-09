//
//  Term.h
//  Core
//
//  Created by Rasmus Anthin on 2026-01-09.
//

#pragma once
#include "System.h"
#include "StringHelper.h"
#include <mutex>    // once_flag, call_once
#include <clocale>  // setlocale, LC_CTYPE
#include <cwchar>   // wcwidth (or <wchar.h>)
#include <iostream> // std::cout.write()
#ifdef _WIN32
#include <windows.h>
#endif

namespace term
{
  
  inline void init_locale()
  {
    static std::once_flag flag;
    std::call_once(flag, []()
    {
      std::setlocale(LC_CTYPE, "");
    });
  }
  
#ifdef _WIN32
  inline bool is_console_stdout()
  {
    DWORD mode = 0;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE) return false;
    return GetConsoleMode(h, &mode) != 0;
  }
  
  inline bool enable_vt_on_stdout()
  {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE)
      return false;
    
    DWORD mode = 0;
    if (!GetConsoleMode(h, &mode))
      return false;
    
    DWORD newMode = mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    return SetConsoleMode(h, newMode) != 0;
  }
  
  inline std::wstring utf8_to_utf16(std::string_view s)
  {
    if (s.empty())
      return {};
    
    int wlen = MultiByteToWideChar(CP_UTF8, 0, s.data(), str::lenI(s)), nullptr, 0);
    if (wlen <= 0)
      return {};
    
    std::wstring ws;
    ws.resize((size_t)wlen);
    MultiByteToWideChar(CP_UTF8, 0, s.data(), str::lenI(s), ws.data(), wlen);
    return ws;
  }
  
  inline void write_console_w(std::wstring_view ws)
  {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;
    WriteConsoleW(h, ws.data(), static_cast<DWORD>(ws.size()), &written, nullptr);
  }
  
  inline void write_console_a(std::string_view s)
  {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written = 0;
    WriteConsoleA(h, s.data(), (DWORD)s.size(), &written, nullptr);
  }
#endif
  
  struct WinMode
  {
    bool is_console = false;
    bool vt_enabled = false;
    int codepage = 65001;
  };
  
  inline WinMode init_windows_mode(int requested_codepage)
  {
    static WinMode m = [requested_codepage]()
    {
      WinMode m;
      m.codepage = requested_codepage;
      
#ifdef _WIN32
      m.is_console = is_console_stdout();
      
      // If not a console (redirected), don't try to manage console modes.
      if (!m.is_console)
        return m;
      
      // Try enable VT processing (works in Windows Terminal / recent conhost).
      m.vt_enabled = enable_vt_on_stdout();
      
      // If VT is enabled, force UTF-8 output for predictable behavior.
      if (m.vt_enabled)
        m.codepage = 65001;
      
      SetConsoleOutputCP((UINT)m.codepage);
#endif
      return m;
    }();
    return m;
  }
  
  inline bool use_ansi_colors(const WinMode& m)
  {
#ifdef _WIN32
    return m.is_console && m.vt_enabled;
#else
    (void)m;
    return true;
#endif
  }
  
  inline void out_text(const WinMode& m, std::string_view s_utf8, std::string_view s_bytes_for_legacy = {})
  {
#ifdef _WIN32
    if (m.is_console)
    {
      if (m.vt_enabled)
      {
        // Console consumes UTF-16; send Unicode directly (avoids mojibake).
        write_console_w(utf8_to_utf16(s_utf8));
      }
      else
      {
        // Legacy: write bytes using current output codepage (e.g. 437).
        const auto& bytes = !s_bytes_for_legacy.empty() ? s_bytes_for_legacy : s_utf8;
        write_console_a(bytes);
      }
      return;
    }
#endif
    // Not Windows or not a console (redirected): emit UTF-8 bytes.
    std::cout.write(s_utf8.data(), (std::streamsize)s_utf8.size());
  }
  
  inline void out_line(const WinMode& m, std::string_view s_utf8, std::string_view s_bytes_for_legacy = {})
  {
    out_text(m, s_utf8, s_bytes_for_legacy);
    out_text(m, "\n", "\n");
  }
  
}
