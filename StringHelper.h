//
//  StringHelper.h
//  Core
//
//  Created by Rasmus Anthin.
//

#pragma once
#include "Math.h"
#include "StlUtils.h"
#include <string>
#include <algorithm>

namespace str
{
  std::string rep_char(char c, int num)
  {
    std::string ret;
    for (int i=0; i<num; ++i)
      ret += c;
    return ret;
  }
  
  // #FIXME: Align, not adjust.
  enum class Adjustment { Left, Center, Right, LeftInteger };
  std::string adjust_str(const std::string& str, Adjustment adj, int width, int start_idx = 0, char empty_char = ' ')
  {
    if (static_cast<int>(str.size()) > width)
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
          math::minimize<int>(number_idx, idx, { 0, static_cast<int>(str.size()), Range::Closed });
        }
        //  0               s          w
        // "bla:            1234       "
        auto result = rep_char(empty_char, width);
        for (int i = 0; i < std::min<int>(start_idx, number_idx); ++i)
          result[i] = str[i];
        for (int i = 0; i < static_cast<int>(str.length()); ++i)
          if (start_idx + i < width && number_idx + i < static_cast<int>(str.length()))
            result[start_idx + i] = str[number_idx + i];
        result = result.substr(0, width);
        return result;
      }
      default:
        return str;
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
  
  template<typename char_t>
  std::basic_string<char_t> to_lower(const std::basic_string<char_t>& str)
  {
    std::basic_string<char_t> ret = str;
    size_t len = str.length();
    for (size_t c_idx = 0; c_idx < len; ++c_idx)
      ret[c_idx] = to_lower(str[c_idx]);
    return ret;
  }
  
  template<typename char_t>
  std::basic_string<char_t> to_upper(const std::basic_string<char_t>& str)
  {
    std::basic_string<char_t> ret = str;
    size_t len = str.length();
    for (size_t c_idx = 0; c_idx < len; ++c_idx)
      ret[c_idx] = to_upper(str[c_idx]);
    return ret;
  }
  
  bool is_digit(char ch)
  {
    return '0' <= ch && ch <= '9';
  }

  bool is_vowel(char ch)
  {
    auto chl = to_lower(ch);
    const char ch_aring = '\xE5';
    const char ch_auml = '\xE4';
    const char ch_ouml = '\xF6';
    std::vector<char> vowels { 'a', 'o', 'u', ch_aring, 'e', 'i', 'y', ch_auml, ch_ouml };
    return std::find(vowels.begin(), vowels.end(), chl) != vowels.end();
  }
  
  bool is_letter(char ch)
  {
    auto chl = to_lower(ch);
    const char ch_aring = '\xE5';
    const char ch_auml = '\xE4';
    const char ch_ouml = '\xF6';
    return ('a' <= chl && chl <= 'z')
      || (ch == ch_aring) || (ch == ch_auml) || (ch == ch_ouml);
  }

  std::string cat(const std::vector<std::string>& strings)
  {
    std::string ret;
    for (const auto& str : strings)
      ret += str;
    return ret;
  }

  enum class BracketType { None, Parentheses, SquareBrackets, Braces, MatrixStyle };

  template<typename Cont>
  std::string row_vector(const Cont& c, BracketType bracket = BracketType::SquareBrackets, const std::string& separator = ", ")
  {
    std::string ret;
    switch (bracket)
    {
      case BracketType::None: break;
      case BracketType::Parentheses: ret = "("; break;
      case BracketType::SquareBrackets: ret = "["; break;
      case BracketType::Braces: ret = "{"; break;
      case BracketType::MatrixStyle: ret = "("; break;
    }
    ret += " ";
    ret += std::to_string(c.front());
    auto N = c.size();
    for (size_t e_idx = 1; e_idx < N; ++e_idx)
      ret += separator + std::to_string(c[e_idx]);
    ret += " ";
    switch (bracket)
    {
      case BracketType::None: break;
      case BracketType::Parentheses: ret += ")"; break;
      case BracketType::SquareBrackets: ret += "]"; break;
      case BracketType::Braces: ret += "}"; break;
      case BracketType::MatrixStyle: ret += ")"; break;
    }
    ret += "\n";
    return ret;
  }

  template<typename Cont>
  std::string column_vector(const Cont& c, BracketType bracket = BracketType::SquareBrackets)
  {
    std::vector<std::string> lines;
    size_t max_width = 0;
    int N = static_cast<int>(c.size());
    int l_idx = 0;
    for (const auto& v : c)
    {
      std::string str;
      switch (bracket)
      {
        case BracketType::None: break;
        case BracketType::Parentheses: str = "("; break;
        case BracketType::SquareBrackets: str = "["; break;
        case BracketType::Braces: str = "{"; break;
        case BracketType::MatrixStyle: str = N == 1 ? "(" : (l_idx == 0 ? "/" : (l_idx == N - 1 ? "\\" : "|")); break;
      }
      str += " ";
      str += std::to_string(v);
      lines.emplace_back(str);
      math::maximize(max_width, lines.back().size());
      l_idx++;
    }
    
    l_idx = 0;
    for (auto& str : lines)
    {
      str = adjust_str(str, Adjustment::Left, static_cast<int>(max_width));
      str += " ";
      switch (bracket)
      {
        case BracketType::None: break;
        case BracketType::Parentheses: str += ")"; break;
        case BracketType::SquareBrackets: str += "]"; break;
        case BracketType::Braces: str += "}"; break;
        case BracketType::MatrixStyle: str += N == 1 ? ")" : (l_idx == 0 ? "\\" : (l_idx == N - 1 ? "/" : "|")); break;
      }
      str += "\n";
      l_idx++;
    }
    
    return cat(lines);
  }
  
  // trim from start (in place)
  inline void ltrim(std::string& s)
  {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
      [](unsigned char ch) { return !std::isspace(ch); }
    ));
  }

  // trim from end (in place)
  inline void rtrim(std::string& s)
  {
    s.erase(std::find_if(s.rbegin(), s.rend(),
      [](unsigned char ch) { return !std::isspace(ch); }).base(),
      s.end()
    );
  }
  
  // trim from both ends (in place)
  inline void trim(std::string &s)
  {
    rtrim(s);
    ltrim(s);
  }

  // trim from start (copying)
  inline std::string ltrim_ret(std::string s)
  {
    ltrim(s);
    return s;
  }

  // trim from end (copying)
  inline std::string rtrim_ret(std::string s)
  {
    rtrim(s);
    return s;
  }

  // trim from both ends (copying)
  inline std::string trim_ret(std::string s)
  {
    trim(s);
    return s;
  }
  
  inline void remove_spaces(std::string& str)
  {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
  }
  
  bool is_an(const std::string& str)
  {
    auto strl = trim_ret(to_lower(str));
    if (strl.empty())
      return false;
    
    char ch0 = strl[0];
    auto N = strl.size();
    char ch1 = N > 1 ? strl[1] : '?';
    char ch2 = N > 2 ? strl[2] : '?';
    
    // Handling cases like "ymca".
    if (ch0 == 'y' && (N > 1 && is_vowel(ch1)))
      return false;
    
    // Handling cases like "npc". Consonant after 'n'. Starting consonants like 'f' [ef], 'n' [en], 'r' [ar] etc.
    if (ch0 == 'f' || ch0 == 'l' || ch0 == 'm' || ch0 == 'n' || ch0 == 'r' || ch0 == 's' || ch0 == 'x')
      if (N > 1 && !is_vowel(ch1))
        return true;

    // Handling cases like "honest", "hour" where 'h' is silent.
    if (ch0 == 'h' && (N > 2 && ch1 == 'o' && ch2 == 'u'))
      return true;
    
    // Handling cases like "unicorn", "unique", "use", "usage case" where 'u' sounds like "you".
    if (strl.starts_with("uni") || strl.starts_with("use") || strl.starts_with("usa"))
      return false;

    // Return true if the first character is a vowel.
    return is_vowel(ch0);
  }
  
  // Returns input string (noun + rest of string) with prepended indefinite article.
  std::string indef_art(const std::string& str)
  {
    return std::string("") + (is_an(str) ? "an" : "a") + " " + str;
  }
  
  // Makes sure the first letter of the string is in uppercase.
  std::string anfangify(std::string str)
  {
    str[0] = to_upper(str[0]);
    return str;
  }
  
  // min_scope_size : Allows you to ignore characters inside a scope regarded as scope_delim characters,
  //                  but then your scopes have to contain strings no shorter than this limit.
  template<typename CharT = char>
  std::vector<std::basic_string<CharT>> tokenize(const std::basic_string<CharT>& str,
                                                 const std::vector<CharT>& delim,
                                                 const std::vector<CharT>& scope_delim = {},
                                                 size_t min_scope_size = 1)
  {
    std::vector<std::basic_string<CharT>> tokens;
    size_t start = 0;
    bool in_scope = false;
    
    for (size_t pos = 0; pos < str.size(); ++pos)
    {
      if (in_scope)
      {
        if (pos >= start + min_scope_size && stlutils::contains(scope_delim, str[pos]))
        {
          tokens.emplace_back(str.substr(start, pos - start));
          start = pos + 1;
          in_scope = false;
        }
      }
      else
      {
        if (stlutils::contains(scope_delim, str[pos]))
        {
          in_scope = true;
          start = pos + 1;
        }
        else if (stlutils::contains(delim, str[pos]))
        {
          if (pos != start)
            tokens.emplace_back(str.substr(start, pos - start));
          start = pos + 1;
        }
      }
    }
    
    if (start != str.size())
      tokens.emplace_back(str.substr(start));
    
    return tokens;
  }
  
  template<typename Cont>
  std::vector<std::string> to_string_vector(const Cont& c)
  {
    std::vector<std::string> string_vec(std::size(c));
    std::transform(std::begin(c), std::end(c), string_vec.begin(), [](auto v) { return std::to_string(v); });
    return string_vec;
  }
  
  
  
}
