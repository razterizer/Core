#pragma once
#include "StringHelper.h"

namespace datetime
{
  struct DateTime
  {
    int year = 0;
    int month = 0;
    int day = 0;
    int Hour = 0; // 24-hour format.
    int minute = 0;
    int second = 0;
  };

  void update_date_time(DateTime& date_time, const DateTime& date_time_0, float time_s)
  {
    float year_f = time_s / (3600*24*30*12);
    int year_i = static_cast<int>(year_f);
    float month_f = (year_f - year_i)*12;
    int month_i = static_cast<int>(month_f);
    float day_f = (month_f - month_i)*30;
    int day_i = static_cast<int>(day_f);
    float Hour_f = (day_f - day_i)*24;
    int Hour_i = static_cast<int>(Hour_f);
    float minute_f = (Hour_f - Hour_i)*60;
    int minute_i = static_cast<int>(minute_f);
    float second_f = (minute_f - minute_i)*60;
    int second_i = static_cast<int>(second_f);
    year_i += date_time_0.year;
    month_i += date_time_0.month;
    day_i += date_time_0.day;
    Hour_i += date_time_0.Hour;
    minute_i += date_time_0.minute;
    second_i += date_time_0.second;
    date_time.year = year_i;
    date_time.month = month_i;
    date_time.day = day_i;
    date_time.Hour = Hour_i;
    date_time.minute = minute_i;
    date_time.second = second_i;
  }

  std::string get_date_time_str(const DateTime& date_time)
  {
    auto date_time_str = std::to_string(date_time.year) +
    "-" + adjust_str(std::to_string(date_time.month), Adjustment::Right, 2, '0') +
    "-" + adjust_str(std::to_string(date_time.day), Adjustment::Right, 2, '0') +
    " " + adjust_str(std::to_string(date_time.Hour), Adjustment::Right, 2, '0') +
    ":" + adjust_str(std::to_string(date_time.minute), Adjustment::Right, 2, '0') +
    ":" + adjust_str(std::to_string(date_time.second), Adjustment::Right, 2, '0');
    return date_time_str;
  }
}
