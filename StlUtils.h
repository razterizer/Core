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

  template<typename Cont>
  Cont comp_prod(const Cont& cA, const Cont& cB)
  {
    assert(cA.size() == cB.size());
    if (cA.size() != cB.size())
      return {};
    Cont ret = cB;
    std::transform(cA.begin(), cA.end(), cB.begin(), ret.begin(), std::multiplies<float>());
    return ret;
  }

  template<typename Cont>
  typename Cont::value_type dot(const Cont& cA, const Cont& cB)
  {
    auto cp = comp_prod(cA, cB);
    return sum(cp);
  }

}
