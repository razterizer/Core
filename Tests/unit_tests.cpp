//
//  unit_tests.cpp
//  Core
//
//  Created by Rasmus Anthin on 2024-09-21.
//

#include "Benchmark_tests.h"
#include "DateTime_tests.h"
#include "FlankDetector_tests.h"
#include "Histogram_tests.h"
#include "Math_tests.h"
#include "StringHelper_tests.h"
#include <iostream>


int main(int argc, char** argv)
{
  const int c_sep_width = 80;

  std::cout << str::adjust_str(" Benchmark Tests ", str::Adjustment::Center, c_sep_width, 0, '#') << std::endl;
  benchmark::unit_tests();
  std::cout << str::rep_char('=', c_sep_width) << std::endl;

  std::cout << str::adjust_str(" DateTime Tests ", str::Adjustment::Center, c_sep_width, 0, '#') << std::endl;
  datetime::unit_tests();
  std::cout << str::rep_char('=', c_sep_width) << std::endl;
  
  std::cout << str::adjust_str(" FlankDetector Tests ", str::Adjustment::Center, c_sep_width, 0, '#') << std::endl;
  flankdetector::unit_tests();
  std::cout << str::rep_char('=', c_sep_width) << std::endl;
  
  std::cout << str::adjust_str(" Histogram Tests ", str::Adjustment::Center, c_sep_width, 0, '#') << std::endl;
  hist::unit_tests();
  std::cout << str::rep_char('=', c_sep_width) << std::endl;
  
  std::cout << str::adjust_str(" MathUtils Tests ", str::Adjustment::Center, c_sep_width, 0, '#') << std::endl;
  math::unit_tests();
  std::cout << str::rep_char('=', c_sep_width) << std::endl;
  
  std::cout << str::adjust_str(" StringHelper Tests ", str::Adjustment::Center, c_sep_width, 0, '#') << std::endl;
  str::unit_tests();
  std::cout << str::rep_char('=', c_sep_width) << std::endl;
  
  return 0;
}
