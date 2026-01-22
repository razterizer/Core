//
//  System.h
//  Core
//
//  Created by Rasmus Anthin on 2025-08-03.
//

#pragma once
#include "StringHelper.h" // to_lower(std::string)
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace sys
{

  inline std::string exec(const char* cmd)
  {
    std::array<char, 256> buffer;
    std::string result;

    // Open pipe
    std::unique_ptr<FILE, int(*)(FILE*)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
      throw std::runtime_error("popen() failed!");

    // Read output
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr)
      result += buffer.data();

    // Optional: trim trailing newlines
    result.erase(std::find_if(result.rbegin(), result.rend(),
        [](unsigned char ch) { return ch != '\n' && ch != '\r'; }).base(),
        result.end());

    return result;
  }
  
  inline bool is_wsl()
  {
#ifdef __linux__
    static const bool result = []()
    {
      std::ifstream version_file("/proc/version");
      std::string version;
      
      if (!version_file || !std::getline(version_file, version))
        return false;
      
      auto version_lower = str::to_lower(version);
      return version_lower.find("microsoft") != std::string::npos
          || version_lower.find("wsl") != std::string::npos;
    }();
    
    return result;
#else
    return false;
#endif
  }
  
  inline bool is_bsd()
  {
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
    return true;
#else
    return false;
#endif
  }
  
  inline bool is_linux()
  {
#ifdef __linux__
    return !is_wsl();
#endif
    return false;
  }
  
  inline bool is_windows()
  {
#ifdef _WIN32
    return true;
#endif
    return false;
  }
  
  inline bool is_apple()
  {
#ifdef __APPLE__
    return true;
#endif
    return false;
  }
  
  inline bool is_windows_cmd()
  {
#ifdef _WIN32
    static const bool result = []() {
      DWORD mode = 0;
      HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
      
      // If stdout is not a console -> always ANSI mode.
      if (!GetConsoleMode(h, &mode))
        return false;
      
      // If VT processing is enabled -> ANSI mode.
      if (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)
        return false;
      
      // Otherwise it's a classic cmd.exe or legacy console.
      return true;
    }();
    
    return result;
#else
    return false;
#endif
  }



}

