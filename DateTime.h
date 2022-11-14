#pragma once
#include "StringHelper.h"
#include "Rand.h"

namespace datetime
{

  template<int N, int V0>
  class datetime_unit_t
  {
    int val = V0;
    int carry = 0;
    bool tared = false;
    
  public:
    datetime_unit_t(int v) : val(v) { /*carry = normalize();*/ }
    datetime_unit_t(const datetime_unit_t& dtu) : val(dtu.val) {}
    
    void normalize()
    {
      carry = 0;
      val -= V0;
      if (std::abs(val) >= N)
      {
        carry = val / N;
        val -= carry * N;
      }
      if (val < 0)
      {
        carry--;
        val += N;
      }
      val += V0;
    }
  
    datetime_unit_t operator+(int v) const
    {
      datetime_unit_t new_val(val);
      new_val += v;
      return new_val;
    }
  
    datetime_unit_t operator-(int v) const
    {
      datetime_unit_t new_val(val);
      new_val -= v;
      return new_val;
    }
  
    void operator+=(int v)
    {
      val += v;
      normalize();
    }
  
    void operator-=(int v)
    {
      *this += (-v);
    }
    
    void tare()
    {
      if (!tared)
      {
        val -= V0;
        tared = true;
      }
    }
    
    void untare()
    {
      if (tared)
      {
        val += V0;
        tared = false;
      }
    }
  
    int get_val() const { return val; }
    int get_carry() const { return carry; }
  
    operator const int&() const { return val; }
  
    bool in_range(int v_before, int v_after, Range type) const
    {
      //e.g. before = 21, after = 1, hour = 23 or 0 or 17.
      if (v_before <= v_after) // 0 .. 23
        return math::in_range<int>(val, v_before, v_after, type);
      else if (val > v_after)
        return math::in_range<int>(val, v_before, v_after + N, type);
      else if (val < v_before)
        return math::in_range<int>(val, v_before - N, v_after, type);
      return false;
    }
  };

  using month_t = datetime_unit_t<12, 1>;
  using day_t = datetime_unit_t<30, 1>;
  using hour_t = datetime_unit_t<24, 0>;
  using sexagesimal_t = datetime_unit_t<60, 0>;

  // ////////////////////////////////////////////////

  struct Date
  {
    int year = 0;
    month_t month = 0;
    day_t day = 0;
    
    Date() = default;
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    
    void tare()
    {
      month.tare();
      day.tare();
    }
    
    void untare()
    {
      month.untare();
      day.untare();
    }
    
    void normalize()
    {
      day.normalize();
      month = month.get_val() + day.get_carry();
      month.normalize();
      year += month.get_carry();
    }
    
    // 1999-12-30 23:59:59 -> 2000-01-01 00:00:00
    float to_years() const { return static_cast<float>(year) + static_cast<float>(month - 1)/12 + static_cast<float>(day - 1)/360; }
    float to_months() const { return static_cast<float>(year)*12 + static_cast<float>(month - 1) + static_cast<float>(day - 1)/30; }
    float to_days() const { return static_cast<float>(year)*360 + static_cast<float>(month - 1)*30 + static_cast<float>(day - 1); }
    
    void from_years(float years)
    {
      year = static_cast<int>(years);
      float months = (years - year)*12;
      month = static_cast<int>(months);
      float days = (months - month)*30;
      day = static_cast<int>(days);
      
      month = month.get_val() + 1; // Or month = month + 1 ?
      day = day.get_val() + 1; // Or day = day + 1 ?
    }
    
    void from_months(float months)
    {
      //from_years(months/12);
      
      int month_i = static_cast<int>(months);
      float years = static_cast<float>(month_i - 1)/12.f;
      int year_i = static_cast<int>(years);
      int month_carry = year_i * 12;
      month_i -= month_carry;
      months -= month_carry;
      
      float days = (months - month_i)*30;
      int day_i = static_cast<int>(days);
      
      day = day_i + 1;
      month = month_i + 1;
      year = year_i;
    }
    
    void from_days(float days)
    {
      //from_years(days/360);
      
      int day_i = static_cast<int>(days);
      
      float months = static_cast<float>(day_i - 1)/30.f;
      int month_i = static_cast<int>(months);
      int day_carry = month_i * 30;
      day_i -= day_carry;
      
      float years = static_cast<float>(month_i - 1)/12.f;
      int year_i = static_cast<int>(years);
      int month_carry = year_i * 12;
      month_i -= month_carry;
      
      day = day_i + 1;
      month = month_i + 1;
      year = year_i;
    }
    
    Date operator+(const Date& date) const
    {
      Date new_date = *this;
      new_date += date;
      return new_date;
    }
    
    Date operator-(const Date& date) const
    {
      Date new_date = *this;
      new_date -= date;
      return new_date;
    }
    
    Date operator+() const
    {
      return *this;
    }
    
    Date operator-() const
    {
      return { -year, -month, -day };
    }
    
    void operator+=(const Date& date)
    {
      day = day.get_val() + date.day;
      month = month.get_val() + date.month.get_val() + day.get_carry(); // Avoids wrapping with carry.
      year += date.year + month.get_carry();
      normalize();
    }
    
    void operator-=(const Date& date)
    {
      *this += (-date);
    }
    
    bool operator==(const Date& date) const
    {
      return year == date.year && month == date.month && day == date.day;
    }
    
    Date add_years_ret(float years) const
    {
      Date apa = *this;
      Date bpa;
      bpa.from_years(years);
      bpa.tare();
      return apa + bpa;
    }
    
    void add_years(float years)
    {
      Date other;
      other.from_years(years);
      other.day = other.day.get_val() - 1;
      other.month = other.month.get_val() - 1;
      *this += other;
    }
    
    Date add_months_ret(float months) const
    {
      Date apa = *this;
      Date bpa;
      bpa.from_months(months);
      bpa.tare();
      return apa + bpa;
    }
    
    void add_months(float months)
    {
      Date other;
      other.from_months(months);
      other.day = other.day.get_val() - 1;
      other.month = other.month.get_val() - 1;
      *this += other;
    }
    
    Date add_days_ret(float days) const
    {
      Date apa = *this;
      Date bpa;
      bpa.from_days(days);
      bpa.tare();
      return apa + bpa;
    }
    
    void add_days(float days)
    {
      Date other;
      other.from_days(days);
      other.day = other.day.get_val() - 1;
      other.month = other.month.get_val() - 1;
      *this += other;
    }
    
    bool in_range(const Date& date_before, const Date& date_after, Range type) const
    {
      auto years_here = to_years();
      auto years_before = date_before.to_years();
      auto years_after = date_after.to_years();
      if (years_before <= years_after) // 0 .. 23
        return math::in_range<float>(years_here, years_before, years_after, type);
      return false;
    }
  };

  struct Time
  {
    hour_t Hour = 0; // 24-hour format.
    sexagesimal_t minute = 0;
    sexagesimal_t second = 0;
    
    Time() = default;
    Time(int H, int m, int s) : Hour(H), minute(m), second(s) {}
    
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
    
    Time operator+() const
    {
      return *this;
    }
    
    Time operator-() const
    {
      return { -Hour, -minute, -second };
    }
    
    void operator+=(const Time& time)
    {
      second += time.second;
      minute += time.minute.get_val() + second.get_carry(); // Avoids wrapping with carry.
      Hour += time.Hour.get_val() + minute.get_carry(); // Avoids wrapping with carry.
    }
    
    void operator-=(const Time& time)
    {
      *this += (-time);
    }
    
    bool operator==(const Time& time) const
    {
      return Hour == time.Hour && minute == time.minute && second == time.second;
    }
    
    Time add_hours_ret(float hours) const
    {
      Time apa = *this;
      Time bpa;
      bpa.from_hours(hours);
      return apa + bpa;
    }
    
    void add_hours(float hours)
    {
      Time other;
      other.from_hours(hours);
      *this += other;
    }
    
    Time add_minutes_ret(float minutes) const
    {
      Time apa = *this;
      Time bpa;
      bpa.from_minutes(minutes);
      return apa + bpa;
    }
    
    void add_minutes(float minutes)
    {
      Time other;
      other.from_minutes(minutes);
      *this += other;
    }
    
    Time add_seconds_ret(float seconds) const
    {
      Time apa = *this;
      Time bpa;
      bpa.from_seconds(seconds);
      return apa + bpa;
    }
    
    void add_seconds(float seconds)
    {
      Time other;
      other.from_seconds(seconds);
      *this += other;
    }
    
    int get_carry() const { return Hour.get_carry(); }
    
    bool in_range(const Time& time_before, const Time& time_after, Range type) const
    {
      auto hours_here = to_hours();
      auto hours_before = time_before.to_hours();
      auto hours_after = time_after.to_hours();
      if (hours_before <= hours_after) // 0 .. 23
        return math::in_range<float>(hours_here, hours_before, hours_after, type);
      else if (hours_here > hours_after)
        return math::in_range<float>(hours_here, hours_before, hours_after + 24, type);
      else if (hours_here < hours_before)
        return math::in_range<float>(hours_here, hours_before - 24, hours_after, type);
      return false;
    }
  };

// ///////////////////////////////////////////////////////

  struct DateTime
  {
    Date date;
    Time time;
    
    DateTime() = default;
    DateTime(int y, int M, int d, int H, int m, int s)
      : date(y, M, d)
      , time(H, m, s)
    {}
    DateTime(const Date& d, const Time& t)
      : date(d), time(t)
    {}
    
    float to_years() const { return date.to_years() + time.to_hours()/8'640; }
    float to_months() const { return date.to_months() + time.to_hours()/720; }
    float to_days() const { return date.to_days() + time.to_hours()/24; }
    float to_hours() const { return date.to_days()*24 + time.to_hours(); }
    float to_minutes() const { return date.to_days()*1'440 + time.to_minutes(); }
    float to_seconds() const { return date.to_days()*86'400 + time.to_seconds(); }
    
    void from_years(float years)
    {
      date.year = static_cast<int>(years);
      float months = (years - date.year)*12;
      date.month = static_cast<int>(months);
      float days = (months - date.month)*30;
      date.day = static_cast<int>(days);
      float hours = (days - date.day)*24;
      time.Hour = static_cast<int>(hours);
      float minutes = (hours - time.Hour)*60;
      time.minute = static_cast<int>(minutes);
      float seconds = (minutes - time.minute)*60;
      time.second = static_cast<int>(seconds);
      
      date.month = date.month.get_val() + 1; // Or month = month + 1 ?
      date.day = date.day.get_val() + 1; // Or day = day + 1 ?
    }
    
    void from_months(float months)
    {
      //from_years(months/12);
      
      int month_i = static_cast<int>(months);
      float years = static_cast<float>(month_i - 1)/12.f;
      int year_i = static_cast<int>(years);
      int month_carry = year_i * 12;
      month_i -= month_carry;
      months -= month_carry;
      
      float days = (months - month_i)*30;
      int day_i = static_cast<int>(days);
      
      float hours = (days - day_i)*24;
      time.Hour = static_cast<int>(hours);
      float minutes = (hours - time.Hour)*60;
      time.minute = static_cast<int>(minutes);
      float seconds = (minutes - time.minute)*60;
      time.second = static_cast<int>(seconds);
      
      date.day = day_i + 1;
      date.month = month_i + 1;
      date.year = year_i;
    }
    
    void from_days(float days)
    {
      //from_years(days/360);
      
      int day_i = static_cast<int>(days);
      
      float months = static_cast<float>(day_i - 1)/30.f;
      int month_i = static_cast<int>(months);
      int day_carry = month_i * 30;
      day_i -= day_carry;
      
      float years = static_cast<float>(month_i - 1)/12.f;
      int year_i = static_cast<int>(years);
      int month_carry = year_i * 12;
      month_i -= month_carry;
      
      float hours = (days - day_i)*24;
      time.Hour = static_cast<int>(hours);
      float minutes = (hours - time.Hour)*60;
      time.minute = static_cast<int>(minutes);
      float seconds = (minutes - time.minute)*60;
      time.second = static_cast<int>(seconds);
      
      date.day = day_i + 1;
      date.month = month_i + 1;
      date.year = year_i;
    }
    
    void from_hours(float hours)
    {
      int hour_i = static_cast<int>(hours);
      
      float days = static_cast<float>(hour_i)/24.f;
      int day_i = static_cast<int>(days);
      int hour_carry = day_i * 24;
      hour_i -= hour_carry;
      hours -= hour_carry;
      
      float months = static_cast<float>(day_i - 1)/30.f;
      int month_i = static_cast<int>(months);
      int day_carry = month_i * 30;
      day_i -= day_carry;
      
      float years = static_cast<float>(month_i - 1)/12.f;
      int year_i = static_cast<int>(years);
      int month_carry = year_i * 12;
      month_i -= month_carry;
      
      time.Hour = hour_i;
      float minutes = (hours - time.Hour)*60;
      time.minute = static_cast<int>(minutes);
      float seconds = (minutes - time.minute)*60;
      time.second = static_cast<int>(seconds);
      
      date.day = day_i + 1;
      date.month = month_i + 1;
      date.year = year_i;
    }
    
    DateTime operator+(const DateTime& datetime) const
    {
      DateTime new_datetime = *this;
      new_datetime += datetime;
      return new_datetime;
    }
    
    DateTime operator-(const DateTime& datetime) const
    {
      DateTime new_datetime = *this;
      new_datetime -= datetime;
      return new_datetime;
    }
    
    DateTime operator+() const
    {
      return *this;
    }
    
    DateTime operator-() const
    {
      return { -date, -time };
    }
    
    void operator+=(const DateTime& datetime)
    {
      time += datetime.time;
      date.day = date.day.get_val() + time.get_carry();
      date += datetime.date;
    }
    
    void operator-=(const DateTime& datetime)
    {
      *this += (-datetime);
    }
    
    bool operator==(const DateTime& datetime) const
    {
      return date == datetime.date && time == datetime.time;
    }
    
    DateTime add_years_ret(float years) const
    {
      DateTime apa = *this;
      DateTime bpa;
      bpa.from_years(years);
      bpa.date.tare();
      return apa + bpa;
    }
    
    void add_years(float years)
    {
      DateTime other;
      other.from_years(years);
      other.date.day = other.date.day.get_val() - 1;
      other.date.month = other.date.month.get_val() - 1;
      *this += other;
    }
    
    DateTime add_months_ret(float months) const
    {
      DateTime apa = *this;
      DateTime bpa;
      bpa.from_months(months);
      bpa.date.tare();
      return apa + bpa;
    }
    
    void add_months(float months)
    {
      DateTime other;
      other.from_months(months);
      other.date.day = other.date.day.get_val() - 1;
      other.date.month = other.date.month.get_val() - 1;
      *this += other;
    }
    
    DateTime add_days_ret(float days) const
    {
      DateTime apa = *this;
      DateTime bpa;
      bpa.from_days(days);
      bpa.date.tare();
      return apa + bpa;
    }
    
    void add_days(float days)
    {
      DateTime other;
      other.from_days(days);
      other.date.day = other.date.day.get_val() - 1;
      other.date.month = other.date.month.get_val() - 1;
      *this += other;
    }

    bool in_range(const DateTime& datetime_before, const DateTime& datetime_after, Range type) const
    {
      auto days_here = to_days();
      auto days_before = datetime_before.to_days();
      auto days_after = datetime_after.to_days();
      if (days_before <= days_after) // 0 .. 23
        return math::in_range<float>(days_here, days_before, days_after, type);
      return false;
    }
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

  Date randomize_date(const Date& start, const Date& end)
  {
    auto start_d = start.to_days();
    auto end_d = end.to_days();
    auto rand_d = rnd::randomize_float(start_d, end_d);
    Date rand_date;
    rand_date.from_days(rand_d);
    return rand_date;
  }

  std::string get_date_time_str(const DateTime& date_time)
  {
    const auto& date = date_time.date;
    const auto& time = date_time.time;
    auto date_time_str = std::to_string(date.year) +
    "-" + str::adjust_str(std::to_string(date.month), str::Adjustment::Right, 2, 0, '0') +
    "-" + str::adjust_str(std::to_string(date.day), str::Adjustment::Right, 2, 0, '0') +
    " " + str::adjust_str(std::to_string(time.Hour), str::Adjustment::Right, 2, 0, '0') +
    ":" + str::adjust_str(std::to_string(time.minute), str::Adjustment::Right, 2, 0, '0') +
    ":" + str::adjust_str(std::to_string(time.second), str::Adjustment::Right, 2, 0, '0');
    return date_time_str;
  }
}
