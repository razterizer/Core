#pragma once
#include "StringHelper.h"

namespace datetime
{

  struct Date
  {
    int year = 0;
    int month = 0;
    int day = 0;
  };

  class hour_type
  {
    int hour = 0; // 24-hour format
    
    void offset_hour(int h)
    {
      if (hour + h < 0)
        hour += 24;
      else if (hour == 23 && h > 0)
        hour = -1;
      //if (hour == 0)
      //{
      //  if (h < 0)
      //    hour = 24;
      //}
      //else if (hour == 23)
      //{
      //  if (h > 0)
      //    hour = -1;
      //}
    }
    
  public:
    hour_type(int h) : hour(h) {}
    
    void operator+=(int h)
    {
      hour += h;
    }
    
    void operator-=(int h)
    {
      hour -= h;
    }
    
    int operator+(int h) const
    {
      hour_type new_hour(hour);
      new_hour += h;
      return new_hour.hour;
    }
    
    int operator-(int h) const
    {
      hour_type new_hour(hour);
      new_hour -= h;
      return new_hour.hour;
    }
    
    //void operator+=(int h)
    //{
    //  offset_hour(h);
    //  hour += h;
    //  // #FIXME: Handle overflow? E.g. 7 + 20
    //}
    //
    //void operator-=(int h)
    //{
    //  *this += (-h);
    //  // #FIXME: Handle underflow? E.g. 7 - 20
    //}
    
    operator const int&() const { return hour; }
    
    bool in_closed_range(int h_before, int h_after) const
    {
      //e.g. before = 21, after = 1, hour = 23 or 0 or 17.
      if (h_before <= h_after) // 0 .. 23
        return h_before <= hour && hour <= h_after;
      else if (hour > h_after)
        return h_before <= hour && hour <= h_after + 24;
      else if (hour < h_before)
        return h_before - 24 <= hour && hour <= h_after;
      return false;
    }
  };

  class sexagesimal_type
  {
    int val = 0;
    
    void offset_val(int v)
    {
      if (val == 0)
      {
        if (v < 0)
          val = 60;
      }
      else if (val == 59)
      {
        if (v > 0)
          val = -1;
      }
    }
  public:
    sexagesimal_type(int v) : val(v) {}
    
    //// Mutable function that returns the carry.
    //int add_w_carry(int v)
    //{
    //
    //}
    
    void operator+=(int v)
    {
      val += v;
    }
    
    void operator-=(int v)
    {
      val -= v;
    }
    
    //int operator+(int v) const
    //{
    //  sexagesimal_type new_val(val);
    //  new_val += v;
    //  return new_val.val;
    //}
    //
    //int operator-(int v) const
    //{
    //  sexagesimal_type new_val(val);
    //  new_val -= v;
    //  return new_val.val;
    //}
    //
    //void operator+=(int v)
    //{
    //  offset_val(v);
    //  val += v;
    //  // #FIXME: Handle overflow? E.g. 27 + 50
    //}
    //
    //void operator-=(int v)
    //{
    //  *this += (-v);
    //  // #FIXME: Handle underflow? E.g. 27 - 50
    //}
    
    operator const int&() const { return val; }
    
    bool in_closed_range(int v_before, int v_after) const
    {
      if (v_before <= v_after) // 0 .. 59
        return v_before <= val && val <= v_after;
      else if (val > v_after)
        return v_before <= val && val <= v_after + 60;
      else if (val < v_before)
        return v_before - 60 <= val && val <= v_after;
      return false;
    }
  };

  struct Time
  {
    hour_type Hour = 0; // 24-hour format.
    sexagesimal_type minute = 0;
    sexagesimal_type second = 0;
    
    float to_hours() const { return static_cast<float>(Hour) + static_cast<float>(minute)/60 + static_cast<float>(second)/3600; }
    float to_minutes() const { return static_cast<float>(Hour)*60 + static_cast<float>(minute) + static_cast<float>(second)/60; }
    float to_seconds() const { return static_cast<float>(Hour)*3600 + static_cast<float>(minute)*60 + static_cast<float>(second); }
    
    void from_hours(float hours)
    {
      Hour = static_cast<int>(hours);
      float minutes = (hours - Hour)*60;
      minute = static_cast<int>(minutes);
      float seconds = (minutes - minute)*60;
      second = static_cast<int>(seconds);
    }
    
    void from_minutes(float minutes)
    {
      from_hours(minutes/60);
    }
    
    void from_seconds(float seconds)
    {
      from_hours(seconds/3600);
    }
    
    Time operator+(const Time& time) const
    {
      Time new_time = *this;
      new_time += time;
      return new_time;
    }
    
    Time operator-(const Time& time) const
    {
      Time new_time = *this;
      new_time -= time;
      return new_time;
    }
    
    void operator+=(const Time& time)
    {
      second += time.second;
      int minute_carry = 0;
      if (std::abs(second) > 60)
      {
        minute_carry = second / 60;
        second -= minute_carry * 60;
      }
      else if (second < 0)
      {
        minute_carry = -1;
        second += 60;
      }
      
      minute += time.minute + minute_carry;
      int hour_carry = 0;
      if (std::abs(minute) > 60)
      {
        hour_carry = minute / 60;
        minute -= hour_carry * 60;
      }
      else if (minute < 0)
      {
        hour_carry = -1;
        minute += 60;
      }
      
      Hour += time.Hour + hour_carry;
      int day_carry = 0;
      if (std::abs(Hour) > 24)
      {
        day_carry = Hour / 24;
        Hour -= day_carry * 24;
      }
      else if (Hour < 0)
      {
        day_carry = -1;
        Hour += 24;
      }
    }
    
    void operator-=(const Time& time)
    {
      second -= time.second;
      int minute_carry = 0;
      if (std::abs(second) > 60)
      {
        minute_carry = second / 60;
        second -= minute_carry * 60;
      }
      else if (second < 0) // 2:1 - 0:2 = 0:59
      {
        minute_carry = -1;
        second += 60;
      }
      
      minute -= time.minute - minute_carry;
      int hour_carry = 0;
      if (std::abs(minute) > 60)
      {
        hour_carry = minute / 60;
        minute -= hour_carry * 60;
      }
      else if (minute < 0)
      {
        hour_carry = -1;
        minute += 60;
      }
      
      Hour -= time.Hour - hour_carry;
      int day_carry = 0;
      if (std::abs(Hour) > 24)
      {
        day_carry = Hour / 24;
        Hour -= day_carry * 24;
      }
      else if (Hour < 0)
      {
        day_carry = -1;
        Hour += 24;
      }
    }
    
    Time add_hours(float hours)
    {
      Time apa = *this;
      Time bpa;
      bpa.from_hours(hours);
      return apa + bpa;
    }
    
    Time add_minutes(float minutes)
    {
      Time apa = *this;
      Time bpa;
      bpa.from_minutes(minutes);
      return apa + bpa;
    }
    
    Time add_seconds(float seconds)
    {
      Time apa = *this;
      Time bpa;
      bpa.from_seconds(seconds);
      return apa + bpa;
    }
    
    bool in_closed_range(const Time& time_before, const Time& time_after) const
    {
      // #FIXME: Verify!
      auto hours_here = to_hours();
      auto hours_before = time_before.to_hours();
      auto hours_after = time_after.to_hours();
      if (hours_before <= hours_after) // 0 .. 23
        return hours_before <= hours_here && hours_here <= hours_after;
      else if (hours_here > hours_after)
        return hours_before <= hours_here && hours_here <= hours_after + 24;
      else if (hours_here < hours_before)
        return hours_before - 24 <= hours_here && hours_here <= hours_after;
      return false;
    }
  };

// ///////////////////////////////////////////////////////

  struct DateTime
  {
    Date date;
    Time time;
  };

// ///////////////////////////////////////////////////////

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
    const auto& date_0 = date_time_0.date;
    const auto& time_0 = date_time_0.time;
    year_i += date_0.year;
    month_i += date_0.month;
    day_i += date_0.day;
    Hour_i += time_0.Hour;
    minute_i += time_0.minute;
    second_i += time_0.second;
    auto& date = date_time.date;
    auto& time = date_time.time;
    date.year = year_i;
    date.month = month_i;
    date.day = day_i;
    time.Hour = Hour_i;
    time.minute = minute_i;
    time.second = second_i;
  }

  Time randomize_time(const Time& start, const Time& end)
  {
    auto start_s = start.to_seconds();
    auto end_s = end.to_seconds();
    auto rand_s = rnd::randomize_float(start_s, end_s);
    Time rand_time;
    rand_time.from_seconds(rand_s);
    return rand_time;
  }

  std::string get_date_time_str(const DateTime& date_time)
  {
    const auto& date = date_time.date;
    const auto& time = date_time.time;
    auto date_time_str = std::to_string(date.year) +
    "-" + str::adjust_str(std::to_string(date.month), str::Adjustment::Right, 2, '0') +
    "-" + str::adjust_str(std::to_string(date.day), str::Adjustment::Right, 2, '0') +
    " " + str::adjust_str(std::to_string(time.Hour), str::Adjustment::Right, 2, '0') +
    ":" + str::adjust_str(std::to_string(time.minute), str::Adjustment::Right, 2, '0') +
    ":" + str::adjust_str(std::to_string(time.second), str::Adjustment::Right, 2, '0');
    return date_time_str;
  }
}
