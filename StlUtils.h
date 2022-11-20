//
//  StlUtils.h
//  Core Lib
//
//  Created by Rasmus Anthin on 2022-11-19.
//

#pragma once

namespace stlutils
{

  template<typename Cont>
  typename Cont::value_type sum(const Cont& c)
  {
    return std::accumulate(c.begin(), c.end(), static_cast<typename Cont::value_type>(0));
  }

  template<typename Cont, typename RetT>
  RetT average(const Cont& c)
  {
    if (c.empty())
      return static_cast<RetT>(0);
    auto N = c.size();
    auto s = sum(c);
    return static_cast<RetT>(s)/static_cast<RetT>(N);
  }

}
