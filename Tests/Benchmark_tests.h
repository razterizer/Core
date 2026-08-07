//
//  Benchmark_tests.h
//  Core
//
//  Created by Rasmus Anthin on 2025-11-13.
//

#pragma once
#include "Benchmark.h"
#include "Delay.h"
#include "MathUtils.h"
#include <cassert>

namespace benchmark
{

  void unit_tests()
  {
    auto fun = []()
    {
      Delay::sleep(350e3);
    };
    
    auto fubar = [](int i)
    {
      Delay::sleep(10e3);
      return i+1;
    };
    
    {
      auto time_ms = calc_time_ms(fun);
      std::cout << "time [ms] = " << time_ms << std::endl;
      assert(math::fuz_eq(time_ms, 350.f, 15.f));
    }
    
    {
      TicTocTimer timer;
      benchmark::tic(timer);
      fun();
      auto time_ms = benchmark::toc(timer);
      std::cout << "time [ms] = " << time_ms << std::endl;
      assert(math::fuz_eq(time_ms, 350.f, 15.f));
    }
    
    {
      benchmark::tic();
      fun();
      auto time_ms = benchmark::toc();
      std::cout << "time [ms] = " << time_ms << std::endl;
      assert(math::fuz_eq(time_ms, 350.f, 15.f));
    }
    
    {
      benchmark::Benchmark bm;
      bm.reg(BM_FUNC(fun()));
    }
    
    {
      benchmark::Benchmark bm;
      bm.reg(BM_FUNC(fun()));
      bm.reg(BM_FUNC(fubar(15)));
    }
    
    {
      benchmark::Benchmark bm;
      bm.reg(BM_FUNC(fubar(15)));
      bm.reg(BM_FUNC(fubar(157)));
      bm.reg(BM_FUNC(fubar(3334)));
    }
    
    {
      benchmark::Benchmark bm;
      bm.reg(BM_FUNC(fubar(15)));
      bm.start("test");
      int n = 0;
      for (int i = 0; i < 1e5; ++i)
        n++;
      std::cout << n << std::endl;
      bm.stop("test");
    }
  }

}
