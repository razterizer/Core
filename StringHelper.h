#pragma once
#include "Math.h"
#include <string>

namespace str
{
  std::string rep_char(char c, int num)
  {
    std::string ret;
    for (int i=0; i<num; ++i)
      ret += c;
    return ret;
  }
  
  enum class Adjustment { Left, Center, Right, LeftInteger };
  std::string adjust_str(const std::string& str, Adjustment adj, int width, int start_idx = 0, char empty_char = ' ')
  {
    if (str.size() > width)
      return str.substr(0, width);
    
    auto offset_str = rep_char(empty_char, start_idx);
  
    int remaining = width - static_cast<int>(str.size());
    switch (adj)
    {
      case Adjustment::Left: return offset_str + str + rep_char(empty_char, remaining);
      case Adjustment::Center:
      {
        std::string result;
        if (width % 2 == 0)
        {
          int remain_half = remaining / 2;
          auto spaces = rep_char(empty_char, remain_half);
          result = offset_str + spaces + str + spaces;
        }
        else
        {
          // Prefer slightly left adjustment over right adjustment.
          int remain_left = (remaining - 1) / 2;
          int remain_right = (remaining + 1) / 2;
          auto spaces_left = rep_char(empty_char, remain_left);
          auto spaces_right = rep_char(empty_char, remain_right);
          result = offset_str + spaces_left + str + spaces_right;
        }
        result = result.substr(0, width);
        return result;
      }
      case Adjustment::Right:
      {
        auto result = offset_str + rep_char(empty_char, remaining) + str;
        result = result.substr(0, width);
        return result;
      }
      case Adjustment::LeftInteger:
      {
        int number_idx = static_cast<int>(str.size()) - 1;
        for (int i = 0; i <= 9; ++i)
        {
          auto needle = std::to_string(i);
          auto idx = static_cast<int>(str.find(needle));
          math::minimize<int>(number_idx, idx, { 0, str.size(), Range::Closed });
        }
        //  0               s          w
        // "bla:            1234       "
        auto result = rep_char(empty_char, width);
        for (size_t i = 0; i < std::min(start_idx, number_idx); ++i)
          result[i] = str[i];
        for (size_t i = 0; i < str.length(); ++i)
          if (start_idx + i < width && number_idx + i < str.length())
            result[start_idx + i] = str[number_idx + i];
        result = result.substr(0, width);
        return result;
      }
    }
  }

  // char or wchar_t
  template<typename char_t>
  char_t to_lower(char_t ch)
  {
    return std::tolower(ch);
  }

  // char or wchar_t
  template<typename char_t>
  char_t to_upper(char_t ch)
  {
    return std::toupper(ch);
  }

  bool is_wovel(char ch)
  {
    auto chl = tolower(ch);
    const char ch_aring = '\xE5';
    const char ch_auml = '\xE4';
    const char ch_ouml = '\xF6';
    std::vector<char> wovels { 'a', 'o', 'u', ch_aring, 'e', 'i', 'y', ch_auml, ch_ouml };
    return std::find(wovels.begin(), wovels.end(), chl) != wovels.end();
  }

}
