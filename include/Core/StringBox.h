//
//  StringBox.h
//  Core
//
//  Created by Rasmus Anthin on 2022-11-22.
//

#pragma once
#include "StringHelper.h"
#include <vector>
#include <string>
#include <iostream>


namespace str
{
  
  template<typename StrT = std::string>
  struct StringBox
  {
    std::vector<StrT> text_lines;
    
    StringBox() = default;
    StringBox(size_t N) : text_lines(N) {}
    StringBox(const std::vector<StrT>& texts) : text_lines(texts) {}
    template<typename KeyLambda>
    StringBox(const StrT& text, KeyLambda key_pred = [](auto cell) { return cell; })
    {
      text_lines = tokenize<StrT, typename StrT::value_type>(text, { U'\n' }, {}, 1, key_pred);
    }
    
    StrT& operator[](size_t r_idx) { return text_lines[r_idx]; }
    const StrT& operator[](size_t r_idx) const { return text_lines[r_idx]; }

    
    void print() const
    {
      for (const auto& tl : text_lines)
        std::cout << tl << '\n';
    }
    
    size_t size() const { return text_lines.size(); }
    
    bool empty() const noexcept { return text_lines.empty(); }
  };

}
