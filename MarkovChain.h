//
//  MarkovChain.h
//  Core Lib
//
//  Created by Rasmus Anthin on 2022-11-15.
//

#pragma once
#include <map>
#include <optional>
#include "Rand.h"

namespace markov_chain
{

  template<typename T>
  class MarkovChain
  {
  public:
    using MarkovChainTransitionTable = std::map<T, std::map<T, float>>;
    MarkovChainTransitionTable mctt;
    T empty_item;
    
    MarkovChain(T empty_val) : empty_item(empty_val) {}
  
    void add_transition(T from, T to)
    {
      auto& targets = mctt[from];
      auto it = targets.find(to);
      if (it != targets.end())
        it->second++;
      else
        targets[to]++;
    }
  
    void normalize_transition_weights()
    {
      for (auto& targets : mctt)
      {
        int tot = 0;
        for (const auto& trg : targets.second)
          tot += trg.second;
        if (tot > 0)
        {
          for (auto& trg : targets.second)
            trg.second /= tot;
        }
      }
    }
    
    T generate()
    {
      auto N = mctt.size();
      if (N == 0)
        return empty_item;
      auto rnd_idx = rnd::randomize_int(0, static_cast<int>(N) - 1);
      int ctr = 0;
      const T* start_item_ptr = nullptr;
      for (auto& item : mctt)
      {
        if (rnd_idx == ctr++)
        {
          start_item_ptr = &item.first;
          break;
        }
      }
      if (start_item_ptr == nullptr)
        return empty_item;
      
      T item = *start_item_ptr;
      
      T ret = item;
      while (item != "")
      {
        auto t = rnd::calc_t_rnd();
        const auto& entry = mctt[item];
        for (const auto& trg : entry)
        {
          if (t < trg.second)
          {
            item = trg.first;
            ret += item;
          }
        }
      }
      
      return ret;
    }
  };

}
