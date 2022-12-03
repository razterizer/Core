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

  template<typename T>
  T sum(const std::vector<std::vector<T>>& v)
  {
    auto ret = static_cast<T>(0);
    for (const auto& r : v)
      ret += sum(r);
    return ret;
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
    std::transform(cA.begin(), cA.end(), cB.begin(), ret.begin(), std::multiplies<typename Cont::value_type>());
    return ret;
  }

  template<typename T>
  std::vector<std::vector<T>> comp_prod(const std::vector<std::vector<T>>& vA,
                                        const std::vector<std::vector<T>>& vB)
  {
    auto Nar = vA.size();
    auto Nac = vA.back().size();
    auto Nbr = vB.size();
    auto Nbc = vB.back().size();
    assert(Nar == Nbr);
    assert(Nac == Nbc);
    if (Nar != Nbr || Nac != Nbc)
      return {};
    std::vector<std::vector<T>> ret = vA; // Resizing by assignment.
    for (size_t r_idx = 0; r_idx < Nar; ++r_idx)
    {
      const auto& vA_r = vA[r_idx];
      const auto& vB_r = vB[r_idx];
      auto& ret_r = ret[r_idx];
      for (size_t c_idx = 0; c_idx < Nac; ++c_idx)
        ret_r[c_idx] = vA_r[c_idx] * vB_r[c_idx];
    }
    return ret;
  }

  template<typename Cont>
  Cont mult_scalar(const Cont& c, typename Cont::value_type s)
  {
    Cont ret = c;
    for (auto& v : ret)
      v *= s;
    return ret;
  }

  template<typename Cont>
  Cont add(const Cont& cA, const Cont& cB)
  {
    assert(cA.size() == cB.size());
    if (cA.size() != cB.size())
      return {};
    Cont ret = cB;
    std::transform(cA.begin(), cA.end(), cB.begin(), ret.begin(), std::plus<typename Cont::value_type>());
    return ret;
  }

  template<typename Cont>
  Cont subtract(const Cont& cA, const Cont& cB)
  {
    assert(cA.size() == cB.size());
    if (cA.size() != cB.size())
      return {};
    Cont ret = cB;
    std::transform(cA.begin(), cA.end(), cB.begin(), ret.begin(), std::minus<typename Cont::value_type>());
    return ret;
  }

  template<typename Cont>
  Cont add_scalar(const Cont& c, typename Cont::value_type s)
  {
    Cont ret = c;
    for (auto& v : ret)
      v += s;
    return ret;
  }

  template<typename Cont>
  Cont subtract_scalar(const Cont& c, typename Cont::value_type s)
  {
    Cont ret = c;
    for (auto& v : ret)
      v += s;
    return ret;
  }

  template<typename Cont>
  typename Cont::value_type dot(const Cont& cA, const Cont& cB)
  {
    auto cp = comp_prod(cA, cB);
    return sum(cp);
  }

  template<typename T>
  T dot(const std::vector<std::vector<T>>& vA, const std::vector<std::vector<T>>& vB)
  {
    auto cp = comp_prod(vA, vB);
    return sum(cp);
  }

  template<typename Cont>
  size_t max_element_idx(const Cont& c)
  {
    return std::distance(c.begin(), std::max_element(c.begin(), c.end()));
  }

  template<typename Cont>
  size_t min_element_idx(const Cont& c)
  {
    return std::distance(c.begin(), std::min_element(c.begin(), c.end()));
  }

  template<typename Cont>
  std::vector<size_t> argmax(const Cont& c)
  {
    // If all values are the same, then there is no maximum.
    if (std::all_of(c.begin(), c.end(), [&c](const auto v) { return v == c.back(); }))
      return {};
  
    std::vector<size_t> indices;
    typename Cont::value_type curr_max = math::get_min<typename Cont::value_type>();
    auto N = c.size();
    for (size_t e_idx = 0; e_idx < N; ++e_idx)
    {
      if (math::maximize(curr_max, c[e_idx]))
        indices.clear();
  
      if (c[e_idx] == curr_max)
        indices.push_back(e_idx);
    }
    return indices;
  }
  
  template<typename Cont>
  std::vector<size_t> argmin(const Cont& c)
  {
    // If all values are the same, then there is no minimum.
    if (std::all_of(c.begin(), c.end(), [&c](const auto v) { return v == c.back(); }))
      return {};
  
    std::vector<size_t> indices;
    typename Cont::value_type curr_min = math::get_max<typename Cont::value_type>();
    auto N = c.size();
    for (size_t e_idx = 0; e_idx < N; ++e_idx)
    {
      if (math::minimize(curr_min, c[e_idx]))
        indices.clear();
  
      if (c[e_idx] == curr_min)
        indices.push_back(e_idx);
    }
    return indices;
  }

  template<typename Cont>
  Cont cat(const Cont& c) { return c; }

  template<typename Cont, typename ... ContN>
  Cont cat(const Cont& c, ContN... cn)
  {
    Cont ret = c;
    auto ci = cat(cn...);
    ret.insert(ret.end(), ci.begin(), ci.end());
    return ret;
  }

  template<typename T>
  std::vector<T> repval(T val, size_t n)
  {
    std::vector<T> ret(n, val);
    return ret;
  }

  template<typename T>
  std::vector<T> subset(const std::vector<T>& v, size_t idx_begin, size_t idx_end)
  {
    auto N = v.size();
    assert(idx_begin < N);
    assert(idx_end < N);
    std::vector<T> ret(v.begin() + idx_begin, v.begin() + idx_end + 1);
    return ret;
  }

  template<typename T>
  std::vector<std::vector<T>> subset(const std::vector<std::vector<T>>& v,
                                     size_t r_idx_begin, size_t r_idx_end,
                                     size_t c_idx_begin, size_t c_idx_end)
  {
    auto Nr = v.size();
    auto Nc = v.back().size();
    assert(r_idx_begin < Nr);
    assert(r_idx_end < Nr);
    assert(c_idx_begin < Nc);
    assert(c_idx_end < Nc);
    std::vector<std::vector<T>> ret(v.begin() + r_idx_begin, v.begin() + r_idx_end + 1);
    for (auto& row : ret)
      row = std::vector<T> { row.begin() + c_idx_begin, row.begin() + c_idx_end + 1 };
    return ret;
  }

  template<typename T>
  std::vector<std::vector<T>> subset_columns(const std::vector<std::vector<T>>& v,
                                             size_t c_idx_begin, size_t c_idx_end)
  {
    auto Nc = v.back().size();
    assert(c_idx_begin < Nc);
    assert(c_idx_end < Nc);
    std::vector<std::vector<T>> ret(v.begin(), v.end());
    for (auto& row : ret)
      row = std::vector<T> { row.begin() + c_idx_begin, row.begin() + c_idx_end + 1 };
    return ret;
  }

}
