#pragma once
#include <string>

std::string rep_char(char c, int num)
{
  std::string ret;
  for (int i=0; i<num; ++i)
    ret += c;
  return ret;
}

enum class Adjustment { Left, Center, Right };
std::string adjust_str(const std::string& str, Adjustment adj, int width, char empty_char = ' ')
{
  if (str.size() > width)
    return str.substr(0, width);
  
  int remaining = width - static_cast<int>(str.size());
  switch (adj)
  {
    case Adjustment::Left: return str + rep_char(empty_char, remaining);
    case Adjustment::Center:
    {
      if (width % 2 == 0)
      {
        int remain_half = width / 2;
        auto spaces = rep_char(empty_char, remain_half);
        return spaces + str + spaces;
      }
      else
      {
        // Prefer slightly left adjustment over right adjustment.
        int remain_left = (width - 1) / 2;
        int remain_right = (width + 1) / 2;
        auto spaces_left = rep_char(empty_char, remain_left);
        auto spaces_right = rep_char(empty_char, remain_right);
        return spaces_left + str + spaces_right;
      }
    }
    case Adjustment::Right: return rep_char(empty_char, remaining) + str;
  }
}
