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
  
  inline int get_code_page()
  {
    return sys::is_windows_cmd() ? 437 : 65001;
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
    if (!is_console_stdout())
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
  
  inline void init_windows_console()
  {
#ifdef _WIN32
    static bool once [[maybe_unused]] = []()
    {
      // Only if stdout is a console.
      if (!is_console_stdout())
        return true;
      
      SetConsoleOutputCP(static_cast<UINT>(get_code_page()));
      return true;
    }();
#endif
  }
  
  // We assume single column and rely on encoder fallback.
  inline bool is_single_column(char32_t cp)
  {
    if (sys::is_windows_cmd())
    {
      // Treat as single-column if we can encode it to CP437 (or ASCII).
      // If you don’t have a predicate, just allow and rely on encoding fallback.
      return cp <= 0x10FFFF;
    }
    
    if (cp > 0x10FFFF)
      return false;
    
    init_locale();
    wchar_t wc = static_cast<wchar_t>(cp);
    int w = ::wcwidth(wc);
    return w == 1; //w <= 1;
  }
  
  inline char32_t get_single_column_char32(char32_t cp)
  {
    return is_single_column(cp) ? cp : U'?';
  }
  
  inline std::string encode_single_width_glyph(char32_t preferred,
                                               char32_t fallback = U'?')
  {
    char32_t cp = preferred;
    if (!is_single_column(cp))
      cp = fallback;
    if (!is_single_column(cp))
      cp = U'?';
    
    // Use 437 for cmd.exe for now as we only have a mapping from UTF-8 to CP437 atm.
    return utf8::encode_char32_codepage(cp, get_code_page());
  }
  
}
