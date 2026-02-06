//
//  StringHelper.h
//  Core
//
//  Created by Rasmus Anthin.
//

#pragma once
#include "MathUtils.h"
#include "StlUtils.h"
#include <string>
#include <algorithm>
#include <cstdint>
#include <cctype>
#include <cwctype>

namespace str
{
  template<typename StrT = std::string, typename CharT = std::string::value_type>
  StrT rep_char(CharT c, int num)
  {
    StrT ret;
    for (int i = 0; i < num; ++i)
      ret += c;
    return ret;
  }
  
  template<typename StrT = std::string>
  StrT rep_str(const StrT& str, int num)
  {
    StrT ret;
    for (int i = 0; i < num; ++i)
      ret += str;
    return ret;
  }
  
  // #FIXME: Align, not adjust.
  enum class Adjustment { Left, Center, Right, LeftInteger };
  template<typename StrT, typename KeyT>
  StrT adjust_str(const StrT& str, Adjustment adj, int width, int start_idx, KeyT empty_char)
  {
    if (static_cast<int>(str.size()) > width)
      return str.substr(0, width);
    
    auto offset_str = rep_char<StrT, KeyT>(empty_char, start_idx);
  
    int remaining = width - static_cast<int>(str.size());
    switch (adj)
    {
      case Adjustment::Left: return offset_str + str + rep_char<StrT, KeyT>(empty_char, remaining);
      case Adjustment::Center:
      {
        StrT result;
        if (remaining % 2 == 0)
        {
          int remain_half = remaining / 2;
          auto spaces = rep_char<StrT, KeyT>(empty_char, remain_half);
          result = offset_str + spaces + str + spaces;
        }
        else
        {
          // Prefer slightly left adjustment over right adjustment.
          int remain_left = (remaining - 1) / 2;
          int remain_right = (remaining + 1) / 2;
          auto spaces_left = rep_char<StrT, KeyT>(empty_char, remain_left);
          auto spaces_right = rep_char<StrT, KeyT>(empty_char, remain_right);
          result = offset_str + spaces_left + str + spaces_right;
        }
        result = result.substr(0, width);
        return result;
      }
      case Adjustment::Right:
      {
        auto result = offset_str + rep_char<StrT, KeyT>(empty_char, remaining) + str;
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
        auto result = rep_char<StrT, KeyT>(empty_char, width);
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
  
  std::string adjust_str(const std::string& str, Adjustment adj, int width, int start_idx = 0, char empty_char = ' ')
  {
    return adjust_str<std::string, char>(str,
                                         adj,
                                         width,
                                         start_idx,
                                         empty_char);
  }

  inline char to_lower(char ch)
  {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
  }

  inline char to_upper(char ch)
  {
    return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
  }

  inline wchar_t to_lower(wchar_t ch)
  {
    return static_cast<wchar_t>(std::towlower(ch));
  }

  inline wchar_t to_upper(wchar_t ch)
  {
    return static_cast<wchar_t>(std::towupper(ch));
  }
  
  template<class char_t>
  inline char_t to_lower(char_t) = delete;

  template<class char_t>
  inline char_t to_upper(char_t) = delete;
  
  template<typename char_t>
  inline std::basic_string<char_t> to_lower(const std::basic_string<char_t>& str)
  {
    static_assert(std::is_same_v<char_t, char> || std::is_same_v<char_t, wchar_t>,
                  "to_lower() only supports char and wchar_t!");
    std::basic_string<char_t> ret = str;
    size_t len = str.length();
    for (size_t c_idx = 0; c_idx < len; ++c_idx)
      ret[c_idx] = to_lower(str[c_idx]);
    return ret;
  }
  
  template<typename char_t>
  inline std::basic_string<char_t> to_upper(const std::basic_string<char_t>& str)
  {
    static_assert(std::is_same_v<char_t, char> || std::is_same_v<char_t, wchar_t>,
                  "to_upper() only supports char and wchar_t!");
    std::basic_string<char_t> ret = str;
    size_t len = str.length();
    for (size_t c_idx = 0; c_idx < len; ++c_idx)
      ret[c_idx] = to_upper(str[c_idx]);
    return ret;
  }
  
  template<typename char_t>
  inline std::basic_string<char_t> to_lower(std::basic_string_view<char_t> sv)
  {
    static_assert(std::is_same_v<char_t, char> || std::is_same_v<char_t, wchar_t>,
                  "to_lower() only supports char and wchar_t!");
    std::basic_string<char_t> ret;
    size_t len = sv.length();
    ret.resize(len);
    for (size_t c_idx = 0; c_idx < len; ++c_idx)
      ret[c_idx] = to_lower(sv[c_idx]);
    return ret;
  }
  
  template<typename char_t>
  inline std::basic_string<char_t> to_upper(std::basic_string_view<char_t> sv)
  {
    static_assert(std::is_same_v<char_t, char> || std::is_same_v<char_t, wchar_t>,
                  "to_upper() only supports char and wchar_t!");
    std::basic_string<char_t> ret;
    size_t len = sv.length();
    ret.resize(len);
    for (size_t c_idx = 0; c_idx < len; ++c_idx)
      ret[c_idx] = to_upper(sv[c_idx]);
    return ret;
  }
  
  template<typename char_t>
  inline char_t* to_lower_mut(char_t* cstr)
  {
    static_assert(std::is_same_v<char_t, char> || std::is_same_v<char_t, wchar_t>,
                  "to_lower_mut() only supports char and wchar_t!");
    if (cstr == nullptr)
      return nullptr;
    // char {} = '\0'.
    for (char_t* p = cstr; *p != char_t {}; ++p)
      *p = to_lower(*p);
    return cstr;
  }

  template<typename char_t>
  inline char_t* to_upper_mut(char_t* cstr)
  {
    static_assert(std::is_same_v<char_t, char> || std::is_same_v<char_t, wchar_t>,
                  "to_upper_mut() only supports char and wchar_t!");
    if (cstr == nullptr)
      return nullptr;
    // char {} = '\0'.
    for (char* p = cstr; *p != char_t {}; ++p)
      *p = to_upper(*p);
    return cstr;
  }
  
  // #NOTE: Returns the argument.
  template<typename char_t>
  inline char_t* to_lower_mut(char_t* cstr, size_t n)
  {
    static_assert(std::is_same_v<char_t, char> || std::is_same_v<char_t, wchar_t>,
                  "to_lower_mut() only supports char and wchar_t!");
    if (cstr == nullptr)
      return nullptr;
    for (size_t i = 0; i < n; ++i)
      cstr[i] = to_lower(cstr[i]);
    return cstr;
  }

  // #NOTE: Returns the argument.
  template<typename char_t>
  inline char_t* to_upper_mut(char_t* cstr, size_t n)
  {
    static_assert(std::is_same_v<char_t, char> || std::is_same_v<char_t, wchar_t>,
                  "to_upper_mut() only supports char and wchar_t!");
    if (cstr == nullptr)
      return nullptr;
    for (size_t i = 0; i < n; ++i)
      cstr[i] = to_upper(cstr[i]);
    return cstr;
  }
  
  template<typename char_t>
  inline const char_t* to_lower_mut(const char_t*) = delete;

  template<typename char_t>
  inline const char_t* to_upper_mut(const char_t*) = delete;
  
  bool is_digit(char ch)
  {
    return '0' <= ch && ch <= '9';
  }
  
  int to_digit(char ch)
  {
    return ch - '0';
  }
  
  int hexch2int(char ch)
  {
    if (is_digit(ch))
      return to_digit(ch);
    if ('A' <= ch && ch <= 'F')
      return 10 + (ch - 'A');
    if ('a' <= ch && ch <= 'f')
      return 10 + (ch - 'a');
    return -1;
  }
  
  char int2hexch(uint8_t v)
  {
    static const char hex_chars[] = "0123456789ABCDEF";
    if (0 <= v && v <= 15)
        return hex_chars[v];
    return '?';
  }
  
  template<typename RetT = int>
  RetT hex2int(const std::string& str)
  {
    int len = static_cast<int>(str.length());
    RetT ret = 0;
    for (int i = 0; i < len; ++i)
    {
      auto ch = str[i];
      auto v = hexch2int(ch);
      if (v == -1)
        return -1;
      ret = ret*16 + static_cast<RetT>(v);
    }
    return ret;
  }
  
  std::string int2hex(int32_t val)
  {
    if (val == 0)
      return "0";
    
    std::string ret;
    // Use unsigned to handle proper bit manipulation.
    auto uval = static_cast<uint32_t>(val);
    
    while (uval > 0)
    {
      uint8_t digit = uval & 0xF;  // Get lowest 4 bits (equivalent to % 16).
      ret.push_back(int2hexch(digit));
      uval >>= 4;  // Shift right by 4 bits (equivalent to / 16).
    }
    
    std::reverse(ret.begin(), ret.end());
    return ret;
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
  
  // scope_delim : Defines scoped regions in which delimiter characters are ignored.
  //               When a scope start delimiter is encountered, tokenization
  //               continues without splitting until a matching scope delimiter
  //               is found. The scope delimiter characters themselves are not
  //               included in the resulting tokens.
  //
  //   Example:
  //     tokenize("(A,B)", { ',' }, { '(' , ')' }) -> { "A,B" }
  //
  // min_scope_size : Allows you to ignore characters inside a scope regarded as scope_delim characters,
  //                  but then your scopes have to contain strings no shorter than this limit.
  // for std::string: KeyT=char, key_pred(char)=char
  // for GlyphString: KeyT=char32_t, key_pred(const Glyph&)=char32_t (From Termin8or)
  template<typename StrT, typename KeyT, typename KeyLambda>
  std::vector<StrT> tokenize(const StrT& str,
                             const std::vector<KeyT>& delim,
                             const std::vector<KeyT>& scope_delim = {},
                             size_t min_scope_size = 1,
                             KeyLambda key_pred = {})
  {
    std::vector<StrT> tokens;
    size_t start = 0;
    bool in_scope = false;
    
    for (size_t pos = 0; pos < str.size(); ++pos)
    {
      auto ch_curr = key_pred(str[pos]);
      if (in_scope)
      {
        if (pos >= start + min_scope_size && stlutils::contains(scope_delim, ch_curr))
        {
          tokens.emplace_back(str.substr(start, pos - start));
          start = pos + 1;
          in_scope = false;
        }
      }
      else
      {
        if (stlutils::contains(scope_delim, ch_curr))
        {
          in_scope = true;
          start = pos + 1;
        }
        else if (stlutils::contains(delim, ch_curr))
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
  
  template<typename StrT, typename KeyT>
  std::vector<StrT> tokenize(const StrT& str,
                             const std::vector<KeyT>& delim,
                             const std::vector<KeyT>& scope_delim = {},
                             size_t min_scope_size = 1)
  {
    return tokenize<StrT, KeyT>(str,
                                delim,
                                scope_delim,
                                min_scope_size,
                                [](const auto& cell) -> KeyT { return static_cast<KeyT>(cell); });
  }

  
  std::vector<std::string> tokenize(const std::string& str,
                             const std::vector<char>& delim,
                             const std::vector<char>& scope_delim = {},
                             size_t min_scope_size = 1)
  {
    return tokenize<std::string>(str,
                                 delim,
                                 scope_delim,
                                 min_scope_size,
                                 [](char ch) { return ch; });
  }
  
  template<typename Cont>
  std::vector<std::string> to_string_vector(const Cont& c)
  {
    std::vector<std::string> string_vec(std::size(c));
    std::transform(std::begin(c), std::end(c), string_vec.begin(), [](auto v) { return std::to_string(v); });
    return string_vec;
  }
  
  std::string flatten(const std::vector<std::string>& string_vec, const std::string& separator = ", ")
  {
    std::string ret;
    size_t len = string_vec.size();
    for (size_t i = 0; i < len; ++i)
    {
      ret += string_vec[i];
      if (i + 1 < len)
        ret += separator;
    }
    return ret;
  }
  
  int count_substr(const std::string& str, const std::string& substr,
                   bool allow_overlap = false)
  {
    if (substr.empty())
      return 0;
    
    int count = 0;
    size_t pos = 0;
    size_t step = allow_overlap ? 1 : substr.length();
    
    while ((pos = str.find(substr, pos)) != std::string::npos)
    {
      ++count;
      pos += step;
    }
    
    return count;
  }
  
  int lenI(std::string_view sv)
  {
    return static_cast<int>(sv.length());
  }
  
  int lenI(const std::string& str)
  {
    return static_cast<int>(str.length());
  }
  
  int lenI(const char* str)
  {
    return static_cast<int>(std::strlen(str));
  }
  
  int lenI(std::wstring_view sv)
  {
    return static_cast<int>(sv.length());
  }
  
  int lenI(const std::wstring& str)
  {
    return static_cast<int>(str.length());
  }
  
  int lenI(const wchar_t* str)
  {
    return static_cast<int>(std::wcslen(str));
  }
  
}
