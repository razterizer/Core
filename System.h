//
//  System.h
//  Core
//
//  Created by Rasmus Anthin on 2025-08-03.
//

#pragma once
#include <cstdio>
#include <memory>
#include <stdexcept>
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


}
