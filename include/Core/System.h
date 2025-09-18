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
#define popen _popen
#define pclose _pclose
#endif

namespace sys
{

  std::string exec(const char* cmd)
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
  
  bool is_wsl()
  {
#ifdef __linux__
    std::ifstream version_file("/proc/version");
    std::string version;
    if (version_file && std::getline(version_file, version))
    {
      auto version_lower = str::to_lower(version);
      //std::cout << version << std::endl;
      return version_lower.find("microsoft") != std::string::npos
          || version_lower.find("wsl") != std::string::npos;
    }
    return false;
#endif
    return false;
  }
  
  bool is_bsd()
  {
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
    return true;
#else
    return false;
#endif
  }
  
  bool is_linux()
  {
#ifdef __linux__
    return !is_wsl();
#endif
    return false;
  }
  
  bool is_windows()
  {
#ifdef _WIN32
    return true;
#endif
    return false;
  }
  
  bool is_apple()
  {
#ifdef __APPLE__
    return true;
#endif
    return false;
  }



}
