#pragma once
#include "DateTime.h"
#include <iostream>

namespace datetime
{

  void unit_tests()
  {
    
    // /////////////////////
    //    Minute/Second   //
    // /////////////////////
    
    // +=
    {
      sexagesimal_t second = 45;
      second += 5;
      assert(second == 50);
      assert(second.get_carry() == 0);
    }
    {
      sexagesimal_t second = 45;
      second += 18;
      assert(second == 3);
      assert(second.get_carry() == 1);
    }
    {
      sexagesimal_t second = 20;
      second += -10;
      assert(second == 10);
      assert(second.get_carry() == 0);
    }
    {
      sexagesimal_t second = 20;
      second += -24;
      assert(second == 56);
      assert(second.get_carry() == -1);
    }
    {
      sexagesimal_t second = 5;
      second += -7;
      assert(second == 58);
      assert(second.get_carry() == -1);
    }
    {
      sexagesimal_t second = -75;
      second += -230;
      // -75 + -230 = -305.
      // -305 + 5*60 = -5.
      // 60 - 5 = 55.
      assert(second == 55);
      assert(second.get_carry() == -6);
    }
    {
      sexagesimal_t second = -5;
      second += 200;
      // -5 + 200 = 195.
      // 195 - 3*60 = 15.
      assert(second == 15);
      assert(second.get_carry() == 3);
    }
    // -=
    {
      sexagesimal_t second = 10;
      second -= 5;
      assert(second == 5);
      assert(second.get_carry() == 0);
    }
    {
      sexagesimal_t second = 10;
      second -= 17;
      assert(second == 53);
      assert(second.get_carry() == -1);
    }
    {
      sexagesimal_t second = 10;
      second -= -7;
      assert(second == 17);
      assert(second.get_carry() == 0);
    }
    {
      sexagesimal_t second = 53;
      second -= -16;
      assert(second == 9);
      assert(second.get_carry() == 1);
    }
    {
      sexagesimal_t second = 12;
      second -= 140;
      // 12 - 140 = -128.
      // -128 + 2*60 = -8.
      // 60 - 8 = 52.
      assert(second == 52);
      assert(second.get_carry() == -3);
    }
    {
      sexagesimal_t second = 50;
      second -= -100;
      assert(second == 30);
      assert(second.get_carry() == 2);
    }
    // +
    {
      sexagesimal_t apa = 110;
      sexagesimal_t bpa = 43;
      auto cpa = apa + bpa;
      assert(cpa == 33);
      assert(cpa.get_carry() == 2);
    }
    // -
    {
      sexagesimal_t apa = 30;
      sexagesimal_t bpa = 44;
      auto cpa = apa - bpa; // 60 - 14 = 46
      assert(cpa == 46);
      assert(cpa.get_carry() == -1);
    }
    // in_range()
    {
      sexagesimal_t start = 7;
      sexagesimal_t val = 13;
      sexagesimal_t end = 15;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      sexagesimal_t start = -2;
      sexagesimal_t val = 0;
      sexagesimal_t end = 3;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      sexagesimal_t start = 5;
      sexagesimal_t val = 14;
      sexagesimal_t end = 11;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      sexagesimal_t start = 41;
      sexagesimal_t val = 57;
      sexagesimal_t end = 2;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      sexagesimal_t start = 21;
      sexagesimal_t val = 18;
      sexagesimal_t end = 3;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    
    // ///////////
    //   HOUR   //
    // ///////////
    
    // +=
    {
      hour_t hour = 10;
      hour += 5;
      assert(hour == 15);
      assert(hour.get_carry() == 0);
    }
    {
      hour_t hour = 20;
      hour += 10;
      assert(hour == 6);
      assert(hour.get_carry() == 1);
    }
    {
      hour_t hour = 82;
      hour += 19;
      assert(hour == 5); // 101 - 4*24.
      assert(hour.get_carry() == 4);
    }
    {
      hour_t hour = -50;
      hour += 2;
      assert(hour == 0);
      assert(hour.get_carry() == -2);
    }
    {
      hour_t hour = 20;
      hour += -10;
      assert(hour == 10);
      assert(hour.get_carry() == 0);
    }
    {
      hour_t hour = 20;
      hour += -24;
      assert(hour == 20);
      assert(hour.get_carry() == -1);
    }
    {
      hour_t hour = 5;
      hour += -7;
      assert(hour == 22);
      assert(hour.get_carry() == -1);
    }
    // -=
    {
      hour_t hour = 3;
      hour -= 88;
      // -85 + 3*24 = -13.
      // 24 - 13 = 11.
      assert(hour == 11);
      assert(hour.get_carry() == -4);
    }
    {
      hour_t hour = 100;
      hour -= 21;
      assert(hour == 7); // 79 - 3*24.
      assert(hour.get_carry() == 3);
    }
    {
      hour_t hour = 10;
      hour -= 5;
      assert(hour == 5);
      assert(hour.get_carry() == 0);
    }
    {
      hour_t hour = 10;
      hour -= 17;
      assert(hour == 17);
      assert(hour.get_carry() == -1);
    }
    {
      hour_t hour = 10;
      hour -= -7;
      assert(hour == 17);
      assert(hour.get_carry() == 0);
    }
    {
      hour_t hour = 15;
      hour -= -16;
      assert(hour == 7);
      assert(hour.get_carry() == 1);
    }
    // +
    {
      hour_t apa = 50;
      hour_t bpa = 31;
      auto cpa = apa + bpa; // 81 - 3*24 = 81 - 72
      assert(cpa == 9);
      assert(cpa.get_carry() == 3);
    }
    // -
    {
      hour_t apa = 30;
      hour_t bpa = 44;
      auto cpa = apa - bpa; // 24 - 14 = 10
      assert(cpa == 10);
      assert(cpa.get_carry() == -1);
    }
    // in_range()
    {
      hour_t start = 7;
      hour_t val = 13;
      hour_t end = 15;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      hour_t start = -2;
      hour_t val = 0;
      hour_t end = 3;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      hour_t start = 5;
      hour_t val = 14;
      hour_t end = 11;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      hour_t start = 21;
      hour_t val = 23;
      hour_t end = 2;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      hour_t start = 21;
      hour_t val = 18;
      hour_t end = 3;
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    
    // ///////////
    //   Time   //
    // ///////////

    // to_hours()
    {
      Time time { 20, 30, 51 };
      auto h = time.to_hours();
      assert(h == 20.514166666666668);
    }
    // to_minutes()
    {
      Time time { 30, 27, 59 };
      auto m = time.to_minutes();
      assert(m == 1827.9833333333333);
    }
    // to_seconds()
    {
      Time time { 23, 18, 02 };
      auto s = time.to_seconds();
      assert(s == 83882);
    }
    // from_hours()
    {
      Time time;
      time.from_hours(20.514167f);
      assert((time == Time { 20, 30, 51 }));
    }
    // from_minutes()
    {
      Time time;
      // Not exactly as in the to_minutes() test. Why? Probably rounding error?
      time.from_minutes(1827.98334f);
      assert((time == Time { 30, 27, 59 }));
    }
    // from_seconds()
    {
      Time time;
      time.from_seconds(83882);
      assert((time == Time { 23, 18, 02 }));
    }
    // +=
    {
      Time time { 10, 0, 0 };
      time.add_hours(5);
      assert((time == Time { 15, 0, 0 }));
      assert(time.get_carry() == 0);
    }
    {
      Time time { 20, 30, 51 };
      time += Time { 10, 29, 31 };
      assert((time == Time { 7, 0, 22 }));
      assert(time.get_carry() == 1);
    }
    {
      Time time { 82, 2, 35 };
      time += { 19, 50, 25 };
      assert((time == Time { 5, 53, 0 })); // 101 - 4*24.
      assert(time.get_carry() == 4);
    }
    {
      Time time { -50, -30, 67 };
      time += { 2, 40, -4 };
      assert((time == Time { 0, 11, 3 }));
      assert(time.get_carry() == -2);
    }
    {
      Time time { 20, 20, 20 };
      time += { -10, 0, 0 };
      assert((time == Time { 10, 20, 20 }));
      assert(time.get_carry() == 0);
    }
    {
      Time time { 20, 20, 20 };
      time += { -24, 20, 20 };
      assert((time == Time { 20, 40, 40 }));
      assert(time.get_carry() == -1);
    }
    {
      Time time = { 5, 10, 30 };
      time += { -7, -15, -55 };
      assert((time == Time { 21, 54, 35 }));
      assert(time.get_carry() == -1);
    }
    // -=
    {
      Time time = { 3, -3, 70 };
      time -= { 88, -1, 1 };
      // s : 70 - 1 = 69 = > 9s : +1m
      // m : -3 - -1 (+1) = -1 => 59m : -1h
      // h : 3 - 88 (-1) = -86 => -86 + 3*24 = -14h : -3d = 24h - 14h : -4d = 10h : -4d
      assert((time == Time { 10, 59, 9 }));
      assert(time.get_carry() == -4);
    }
    {
      Time time { 100, 50, 70 };
      time -= { 21, 70, 45 };
      assert((time == Time { 6, 40, 25 } ));
      assert(time.get_carry() == 3);
    }
    {
      Time time = { 10, 60, 60 };
      time -= { 5, 60, 60 };
      assert((time == Time { 5, 0, 0 }));
      assert(time.get_carry() == 0);
    }
    {
      Time time { 10, 4, 59 };
      time -= { 17, -54, -1 };
      assert((time == Time { 17, 59, 0 }));
      assert(time.get_carry() == -1);
    }
    {
      Time time { 10, 10, 10 };
      time -= { -7, 3, 7 };
      assert((time == Time { 17, 7, 3 }));
      assert(time.get_carry() == 0);
    }
    {
      Time time { 15, 16, 17 };
      time -= { -16, -15, 14 };
      assert((time == Time { 7, 31, 3 }));
      assert(time.get_carry() == 1);
    }
    // +
    {
      Time apa { 50, 30, 59 };
      Time bpa { 31, 28, 62 };
      auto cpa = apa + bpa; // 81 - 3*24 = 81 - 72
      assert((cpa == Time { 10, 0, 1 }));
      assert(cpa.get_carry() == 3);
    }
    // -
    {
      Time apa { 30, 2, 45 };
      Time bpa = { 44, 35, 6 };
      auto cpa = apa - bpa; // 24 - 14 = 10
      assert((cpa == Time { 9, 27, 39 }));
      assert(cpa.get_carry() == -1);
    }
    // add_hours_ret()
    {
      Time time { 6, 18, 0 };
      Time time2 = time.add_hours_ret(3.14f);
      assert((time2 == Time { 9, 26, 24 }));
      assert(time2.get_carry() == 0);
    }
    // add_hours()
    {
      Time time { 6, 18, 0 };
      time.add_hours(3.14f);
      assert((time == Time { 9, 26, 24 }));
      assert(time.get_carry() == 0);
    }
    // add_minutes_ret()
    {
      Time time { 16, 21, 39 };
      Time time2 = time.add_minutes_ret(39.65f);
      assert((time2 == Time { 17, 1, 18 }));
      assert(time2.get_carry() == 0);
    }
    // add_minutes()
    {
      Time time { 16, 21, 39 };
      time.add_minutes(39.65f);
      assert((time == Time { 17, 1, 18 }));
      assert(time.get_carry() == 0);
    }
    // add_seconds_ret()
    {
      Time time { 23, 55, 27 };
      Time time2 = time.add_seconds_ret(299.74f); // carry: 5m.
      assert((time2 == Time { 0, 0, 26 }));
      assert(time2.get_carry() == 1);
    }
    // add_seconds()
    {
      Time time { 23, 55, 27 };
      time.add_seconds(299.74f); // carry: 5m.
      assert((time == Time { 0, 0, 26 }));
      assert(time.get_carry() == 1);
    }
    // in_range()
    {
      Time start { 7, 17, 32 };
      Time val { 13, 27, 55 };
      Time end { 15, 14, 12 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      Time start { -2, 3, 14 };
      Time val { 0, 50, 7 };
      Time end { 3, 17, 35 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      Time start { 5, 17, 32 };
      Time val { 14, 7, 38 };
      Time end { 11, 0, 4 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      Time start { 21, 0, 0 };
      Time val { 23, 4, 52 };
      Time end { 2, 59, 31 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      Time start { 21, 12, 13 };
      Time val { 18, 2, 0 };
      Time end { 3, 13, 7 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      Time start { 21, 12, 13 };
      Time val { 21, 12, 12 };
      Time end { 3, 13, 7};
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      Time start { 21, 12, 13 };
      Time val { 21, 12, 14 };
      Time end { 3, 13, 7 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      Time start { 21, 12, 13 };
      Time val { 3, 13, 6 };
      Time end { 3, 13, 7 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      Time start { 21, 12, 13 };
      Time val { 3, 13, 8 };
      Time end { 3, 13, 7 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    
    // ///////////
    //   Date   //
    // ///////////

    // to_years()
    {
      Date date { 2000, 12, 21 };
      auto y = date.to_years();
      assert(y == 2000.9722222222224);
      // 2000.97f : https://www.wolframalpha.com/widgets/view.jsp?id=9920857cc88285c0a1609330d0167a1d
      // 2000 + (12 - 1)/12 + (21 - 1)/365
      // 2000 + 11/12 + 20/365 = 2000 + 0.916... + 0.0547945 = 2000.971461187 ~ 2000.97.
      // Simplified date system: All months are 30 days.
      // 2000 + (12 - 1)/12 + (21 - 1)/360 = 0.916... + 0.05... = 2000.972...
    }
    {
      Date date { 2022, 12, 30 };
      auto y = date.to_years();
      //y += 23/(24*30*12);
      //y += 59/(60*24*30*12);
      //y += 60/(3600*24*30*12);
      assert(y == 2022.9972222222223);
      // 2022-12-31 23:59:59 -> 2023-01-01 00:00:00 = 2023
      //float years = 2023 + (1 - 1)/12 + (1 - 1)/30
    }
    // to_months()
    {
      Date date { 2000, 5, 30 };
      auto m = date.to_months();
      assert(m == 24004.966666666667);
    }
    // to_days()
    {
      Date date { 1978, 6, 28 };
      auto d = date.to_days();
      assert(d == 712080 + 150 + 27);
    }
    // from_years()
    {
      Date date;
      date.from_years(2000.97223f);
      assert((date == Date { 2000, 12, 21 }));
    }
    // from_months()
    {
      Date date;
      date.from_months(24004.96666666f);
      assert((date == Date { 2000, 5, 30 }));
    }
    // from_days()
    {
      Date date;
      date.from_days(712080 + 150 + 27);
      assert((date == Date { 1978, 6, 28 }));
    }
    // +=
    {
      Date date { 2001, 10, 12 };
      date.add_years(5);
      assert((date == Date { 2006, 10, 12 }));
    }
    {
      Date date { 2000, 30, 51 }; // 1-based.
      date += Date { 10, 29, 31 }; // 0-based.
      assert((date == Date { 2015, 1, 22 })); // +5y, +2m
    }
    {
      Date date { 1882, 2, 25 }; // 1-based.
      date += { 19, 8, 6 }; // 0-based.
      assert((date == Date { 1901, 11, 1 }));
    }
    {
      Date date { 50, 30, 67 };
      date.normalize();
      assert((date == Date { 52, 8, 7 }));
    }
    {
      Date date { 50, 30, 67 };
      //date.normalize();
      // d: 1 + (66 - 2*30) = 1 + (36 - 30) = 1 + 6 = 7
      // m: 1 + ((29 + 2) - 2*12) = 1 + (31 - 2*12) = 1 + 7 = 8
      // y: 50 + 2 = 52
      // 52-08-07
      date += { 2, 40, 1 };
      // 52-08-07 + (2, 40, 1) = 57-12-08 (Julian calendar)
      // 52-08-07 + (2, 40, 1)
      // d: 1 + (6 + 1) = 1 + 7 = 8
      // m: 1 + (7 + 40) = 1 + 47 = 1 + (47 - 3*12) = 1 + (47 - 36) = 1 + 11 = 12
      // y: 52 + 2 + 3 = 57
      // 57-12-08
      assert((date == Date { 57, 12, 8 }));
    }
    {
      Date date { 2000, 4, 5 };
      date += { -10, -40, -6 };
      // d: 1 + (4 - 6) = 1 + (-2)
      // d: 1 + (-2 + 1*30) = 1 + 28 = 29;
      // m: 1 + (3 - 1 - 40) = 1 + (-38)
      // m: 1 + (-38 + 4*12) = 1 + 10 = 11
      // y: 2000 - 10 - 4 = 1986
      assert((date == Date { 1986, 11, 29 }));
    }
    {
      Date date { 2000, 4, 5 };
      date += { -2000, -3, -3 };
      assert((date == Date { 0, 1, 2 }));
    }
    {
      Date date = { 2000, 3, 3 };
      date += { 0, 1, 2 };
      assert((date == Date { 2000, 4, 5 }));
    }
    // -=
    {
      Date date = { 2000, 4, 5 };
      date -= { 10, 40, 6 };
      assert((date == Date { 1986, 11, 29 }));
    }
    {
      Date date { 57, 12, 8 };
      date -= { 2, 40, 1 };
      assert((date == Date { 52, 8, 7 } ));
    }
    // +
    {
      Date apa { 2000, 30, 51 };
      Date bpa { 10, 29, 31 };
      auto cpa = apa + bpa; // 81 - 3*24 = 81 - 72
      assert((cpa == Date { 2015, 1, 22 }));
    }
    // -
    {
      Date apa { 2000, 4, 5 };
      Date bpa = { 10, 40, 6 };
      auto cpa = apa - bpa; // 24 - 14 = 10
      assert((cpa == Date { 1986, 11, 29 }));
    }
    // add_years_ret()
    {
      Date date { 1884, 2, 1 };
      Date date2 = date.add_years_ret(3.14f);
      assert((date2 == Date { 1887, 3, 21 }));
    }
    // add_years()
    {
      Date date { 1884, 2, 1 };
      date.add_years(3.14f);
      assert((date == Date { 1887, 3, 21 }));
    }
    // add_months_ret()
    {
      Date date { 0, 1, 1 };
      Date date2 = date.add_months_ret(39.65f);
      // m: 1 + 39 = 1 + (39 - 3*12) = 1 + 3 = 4
      // y: 0 + 3 = 3
      // d: 1 + floor(19.5) = 1 + 19 = 20
      assert((date2 == Date { 3, 4, 20 }));
    }
    // add_months()
    {
      Date date { 0, 1, 1 };
      date.add_months(39.65f);
      assert((date == Date { 3, 4, 20 }));
    }
    // add_days_ret()
    {
      Date date { 1789, 5, 13 };
      Date date2 = date.add_days_ret(299);
      // d: (1 + 12) + 299 = 1 + (12 + 299) = 1 + 311
      // d: 1 + (311 - 10*30) = 1 + 11 = 12
      // m: (1 + 4) + 10 = 1 + 14
      // m: 1 + (14 - 1*12) = 1 + 2 = 3
      // y: 1789 + 1 = 1790
      assert((date2 == Date { 1790, 3, 12 }));
    }
    // add_days()
    {
      Date date { 1789, 5, 13 };
      date.add_days(299);
      assert((date == Date { 1790, 3, 12 }));
    }
    // in_range()
    {
      Date start { 1945, 3, 21 };
      Date val { 1945, 4, 1 };
      Date end { 1946, 3, 12 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      Date start { -2, 3, 14 };
      Date val { 0, 50, 7 };
      Date end { 3, 17, 35 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      Date start { 590, 1, 28 };
      Date val { 708, 7, 30 };
      Date end { 595, 1, 4 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      Date start { 590, 1, 28 };
      Date val { 590, 1, 27 };
      Date end { 595, 1, 4 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      Date start { 590, 1, 28 };
      Date val { 590, 1, 28 };
      Date end { 595, 1, 4 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    
    // ///////////////
    //   DateTime   //
    // ///////////////
    
    // to_years() -> from_years()
    {
      DateTime datetime { 2000, 12, 21, 13, 7, 77 };
      auto y = datetime.to_years();
      DateTime datetime2;
      datetime2.from_years(y);
      assert((datetime2 == DateTime { 2000, 12, 21, 13, 8, 17 }));
    }
    {
      DateTime datetime { 2022, 12, 30, 24, 30, 66 };
      auto y = datetime.to_years();
      DateTime datetime2;
      datetime2.from_years(y);
      assert((datetime2 == DateTime { 2023, 1, 1, 0, 31, 6 }));
    }
    {
      DateTime dt { 0, 1, 1, 23, 59, 60 };
      DateTime dt2;
      dt2.from_years(dt.to_years());
      assert((dt2 == DateTime { 0, 1, 2, 0, 0, 0 }));
      // years  double  0.0028935185185185184
    }
    {
      DateTime datetime { 2022, 12, 30, 23, 59, 60 };
      auto y = datetime.to_years();
      DateTime datetime2;
      datetime2.from_years(y);
      assert((datetime2 == DateTime { 2023, 1, 1, 0, 0, 0 }));
    }
    // to_months() -> from_months()
    {
      DateTime datetime { 2000, 5, 30, 3, 40, 76 };
      auto m = datetime.to_months();
      m++;
      DateTime datetime2;
      datetime2.from_months(m);
      assert((datetime2 == DateTime { 2000, 6, 30, 3, 41, 16 }));
    }
    {
      DateTime datetime { 2000, 12, 30, 23, 59, 60 };
      auto m = datetime.to_months();
      DateTime datetime2;
      datetime2.from_months(m);
      assert((datetime2 == DateTime { 2001, 1, 1, 0, 0, 0 }));
    }
    // to_days() -> from_days()
    {
      DateTime datetime { 1978, 6, 28, 23, 60, 59 };
      auto d = datetime.to_days();
      DateTime datetime2;
      datetime2.from_days(d);
      assert((datetime2 == DateTime { 1978, 6, 29, 0, 0, 59 }));
    }
    {
      DateTime datetime { 1978, 12, 30, 23, 59, 60 };
      auto d = datetime.to_days();
      DateTime datetime2;
      datetime2.from_days(d);
      assert((datetime2 == DateTime { 1979, 1, 1, 0, 0, 0 }));
    }
    // to_hours() -> from_hours()
    {
      DateTime datetime { 1978, 6, 28, 3, 14, 37 };
      auto h = datetime.to_hours();
      DateTime datetime2;
      datetime2.from_hours(h);
      //assert((datetime2 == DateTime { 1978, 6, 28, 3, 14, 37 }));
    }
    // to_minutes -> from_minutes()
    {
      DateTime datetime { 1984, 4, 6, 3, 0, 3 };
      auto m = datetime.to_minutes();
      DateTime datetime2;
      datetime2.from_minutes(m);
      assert((datetime2 == DateTime { 1984, 4, 6, 3, 0, 3 }));
    }
    // to_seconds -> from_seconds()
    {
      DateTime datetime { 1984, 4, 6, 14, 11, 53 };
      auto s = datetime.to_seconds();
      DateTime datetime2;
      datetime2.from_seconds(s);
      assert((datetime2 == DateTime { 1984, 4, 6, 14, 11, 53 }));
    }
    {
      DateTime datetime { 1978, 12, 30, 23, 59, 60 };
      auto h = datetime.to_hours();
      DateTime datetime2;
      datetime2.from_hours(h);
      assert((datetime2 == DateTime { 1979, 1, 1, 0, 0, 0 }));
    }
    // +=
    {
      DateTime datetime { 2000, 30, 51, 30, 5, 7 }; // 1-based.
      datetime += DateTime { 10, 29, 31, 0, 0, 5 }; // 0-based.
      assert((datetime == DateTime { 2015, 1, 23, 6, 5, 12 })); // +5y, +2m
    }
    {
      DateTime datetime { 2000, 4, 5, 13, 24, 0 };
      datetime += { -10, -40, -6, 4, 12, -5 };
      // d: 1 + (4 - 6) = 1 + (-2)
      // d: 1 + (-2 + 1*30) = 1 + 28 = 29;
      // m: 1 + (3 - 1 - 40) = 1 + (-38)
      // m: 1 + (-38 + 4*12) = 1 + 10 = 11
      // y: 2000 - 10 - 4 = 1986
      assert((datetime == DateTime { 1986, 11, 29, 17, 35, 55 }));
    }
    {
      DateTime datetime { 2000, 4, 5, 21, 7, 18 };
      datetime += { -2000, -3, -3, -19, -1, -7 };
      assert((datetime == DateTime { 0, 1, 2, 2, 6, 11 }));
    }
    {
      DateTime datetime = { 2000, 3, 3, 7, 10, 36 };
      datetime += { 0, 1, 2, 12, 40, 7 };
      assert((datetime == DateTime { 2000, 4, 5, 19, 50, 43 }));
    }
    // -=
    {
      DateTime datetime = { 2000, 4, 5, 17, 66, 19 };
      datetime -= { 10, 40, 6, 5, 19, 20 };
      assert((datetime == DateTime { 1986, 11, 29, 12, 46, 59 }));
    }
    {
      DateTime datetime { 57, 12, 8, 3, 41, 17 };
      datetime -= { 2, 40, 1, 7, 60, 23 };
      assert((datetime == DateTime { 52, 8, 6, 19, 40, 54 } ));
    }
    // +
    {
      DateTime apa { 2000, 30, 51, 12, 3, 20 };
      DateTime bpa { 10, 29, 31, 6, 17, 11 };
      auto cpa = apa + bpa; // 81 - 3*24 = 81 - 72
      assert((cpa == DateTime { 2015, 1, 22, 18, 20, 31 }));
    }
    // -
    {
      DateTime apa { 2000, 4, 5, 20, 7, 11 };
      DateTime bpa = { 10, 40, 6, 6, 8, 51 };
      auto cpa = apa - bpa; // 24 - 14 = 10
      assert((cpa == DateTime { 1986, 11, 29, 13, 58, 20 }));
    }
    // add_years_ret()
    {
      DateTime datetime { 1884, 2, 1, 10, 34, 18 };
      DateTime datetime2 = datetime.add_years_ret(3.14);
      assert((datetime2 == DateTime { 1887, 3, 21, 20, 10, 18 }));
    }
    // add_years()
    {
      DateTime datetime { 1884, 2, 1, 10, 34, 18 };
      datetime.add_years(3.14);
      assert((datetime == DateTime { 1887, 3, 21, 20, 10, 18 }));
    }
    // add_months_ret()
    {
      DateTime datetime { 0, 1, 1, 0, 0, 0 };
      DateTime datetime2 = datetime.add_months_ret(39.65);
      // m: 1 + 39 = 1 + (39 - 3*12) = 1 + 3 = 4
      // y: 0 + 3 = 3
      // d: 1 + floor(19.5) = 1 + 19 = 20
      assert((datetime2 == DateTime { 3, 4, 20, 12, 0, 0}));
    }
    // add_months()
    {
      DateTime datetime { 0, 1, 1, 0, 0, 0 };
      datetime.add_months(39.65);
      assert((datetime == DateTime { 3, 4, 20, 12, 0, 0 }));
    }
    // add_days_ret()
    {
      DateTime datetime { 1789, 5, 13, 7, 15, 54 };
      DateTime datetime2 = datetime.add_days_ret(299.123);
      // d: (1 + 12) + 299 = 1 + (12 + 299) = 1 + 311
      // d: 1 + (311 - 10*30) = 1 + 11 = 12
      // m: (1 + 4) + 10 = 1 + 14
      // m: 1 + (14 - 1*12) = 1 + 2 = 3
      // y: 1789 + 1 = 1790
      // h: 0.123 * 24 = 2.952. 2 + 7 = 9. 9 + (+1) = 10
      // min: 0.952 * 60 = 57.12. 57 + 15 = 72. 72 - 60 + (+1) = 13 : +1
      // s: .12 * 60 = 7.2. 54 + 7 = 61. 1 : +1
      assert((datetime2 == DateTime { 1790, 3, 12, 10, 13, 1 }));
    }
    // add_days()
    {
      DateTime datetime { 1789, 5, 13, 7, 15, 54 };
      datetime.add_days(299.123);
      assert((datetime == DateTime { 1790, 3, 12, 10, 13, 1 }));
    }
    // add_hours_ret();
    {
      DateTime datetime { 1789, 5, 13, 7, 15, 54 };
      auto datetime2 = datetime.add_hours_ret(43.874);
      // h: 7 + 43.874 = 50.874 = 50 + 0.874 = 2 + 0.874 : +2
      // m: 15 + 0.874*60 = 15 + 52.44 = 67.44 = 7 + 0.44 : +1
      // s: 54 + .44*60 = 54 + 26.4 = 80.4 = 20 + 0.4 : + 1
      // s = 20
      // m = 7 + 1
      // h = 2 + 1
      // d = 13 + 2
      assert((datetime2 == DateTime { 1789, 5, 15, 3, 8, 20 }));
    }
    // add_hours();
    {
      DateTime datetime { 1789, 5, 13, 7, 15, 54 };
      datetime.add_hours(43.874);
      assert((datetime == DateTime { 1789, 5, 15, 3, 8, 20 }));
    }
    // add_minutes_ret();
    {
      DateTime datetime { 1789, 5, 13, 7, 15, 54 };
      auto datetime2 = datetime.add_minutes_ret(111.111111);
      // m: 15 + 111.111111 = 126 + 0.111111 = 6 + 0.111111 + (+1) : +2
      // s: 54 + 0.111111*60 = 54 + 6.66666 = 0 + 0.66666 : +1
      // s = 0
      // m = 7
      // h = 7 + 2
      assert((datetime2 == DateTime { 1789, 5, 13, 9, 7, 0 }));
    }
    // add_minutes();
    {
      DateTime datetime { 1789, 5, 13, 7, 15, 54 };
      datetime.add_minutes(111.111111);
      assert((datetime == DateTime { 1789, 5, 13, 9, 7, 0 }));
    }
    // add_seconds_ret();
    {
      DateTime datetime { 1789, 5, 13, 7, 15, 54 };
      auto datetime2 = datetime.add_seconds_ret(345507721.533);
      assert((datetime2 == DateTime { 1800, 6, 22, 5, 37, 55 }));
    }
    // add_seconds();
    {
      DateTime datetime { 1789, 5, 13, 7, 15, 54 };
      datetime.add_seconds(345507721.533);
      assert((datetime == DateTime { 1800, 6, 22, 5, 37, 55 }));
    }
    // in_range()
    {
      DateTime start { 1945, 3, 21, 40, 38, 70 };
      DateTime val { 1945, 4, 1, 17, 18, 32 };
      DateTime end { 1946, 3, 12, 13, 19, 44 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      DateTime start { -2, 3, 14, 2, 3, 4 };
      DateTime val { 0, 50, 7, 7, 12, 34 };
      DateTime end { 3, 17, 35, 23, 18, 47 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      DateTime start { 590, 1, 28, 18, 19, 54 };
      DateTime val { 708, 7, 30, 13, 27, 88 };
      DateTime end { 595, 1, 4, 51, 133, 20 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      DateTime start { 590, 1, 27, 7, 15, 9 };
      DateTime val { 590, 1, 27, 7, 15, 8 };
      DateTime end { 595, 1, 4, 16, 16, 31 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }
    {
      DateTime start { 590, 1, 27, 7, 15, 9 };
      DateTime val { 590, 1, 27, 7, 15, 10 };
      DateTime end { 595, 1, 4, 16, 16, 31 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      DateTime start { 590, 1, 27, 7, 15, 9 };
      DateTime val { 595, 1, 4, 16, 16, 30 };
      DateTime end { 595, 1, 4, 16, 16, 31 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(in_range);
    }
    {
      DateTime start { 590, 1, 27, 7, 15, 9 };
      DateTime val { 595, 1, 4, 16, 16, 32 };
      DateTime end { 595, 1, 4, 16, 16, 31 };
      bool in_range = val.in_range(start, end, Range::Closed);
      assert(!in_range);
    }

    // ////////////////////////
    //   Utility Functions   //
    // ////////////////////////
    
    // update_date_time()
    {
      DateTime datetime0 = { 2000, 1, 1, 0, 0, 0 };
      DateTime datetime;
      const double dt = 0.1;
      double time = 0;
      for (int i = 0; i < 1000; ++i)
      {
        // #FIXME: update_date_time() -> add_seconds() should be responsible for the rounding.
        update_date_time(datetime, datetime0, std::round(time));
        time += dt;
      }
      assert((datetime == DateTime { 2000, 1, 1, 0, 1, 40 }));
    }
    
    rnd::srand_time();
    
    // rand_date()
    {
      auto start = Date { -11'800, 1, 1 };
      auto end = Date { 2030, 10, 4 };
      auto date = rand_date(start, end);
      assert(date.in_range(start, end, Range::Closed));
      assert(date.month > 0);
      assert(date.day > 0);
    }
    {
      auto start = Date { 2019, 12, 30 };
      auto end = Date { 2022, 5, 30 };
      auto date = rand_date(start, end);
      assert(date.in_range(start, end, Range::Closed));
      assert(date.month > 0);
      assert(date.day > 0);
    }
    
    // rand_time()
    {
      auto start = Time { 1, 20, 30 };
      auto end = Time { 21, 40, 51 };
      auto time = rand_time(start, end);
      assert(time.in_range(start, end, Range::Closed));
    }
    {
      auto start = Time { 21, 40, 51 };
      auto end = Time { 3, 20, 30 };
      auto time = rand_time(start, end);
      assert(time.in_range(start, end, Range::Closed));
    }
    
    // rand_datetime()
    {
      auto start = DateTime { -6000, 1, 1, 20, 30, 10 };
      auto end = DateTime { 2022, 11, 18, 21, 15, 30 }; // When I wrote this line.
      auto datetime = rand_datetime(start, end);
      assert(datetime.in_range(start, end, Range::Closed));
      assert(datetime.date.month > 0);
      assert(datetime.date.day > 0);
    }
    
    // randn_date()
    {
      auto start = Date { -11'800, 1, 1 };
      auto end = Date { 2030, 10, 4 };
      auto mu = Date { -4'000, 1, 1 };
      auto date = randn_date(mu, 10'000, start, end);
      assert(date.in_range(start, end, Range::Closed));
      assert(date.month > 0);
      assert(date.day > 0);
    }
    {
      auto start = Date { 2019, 12, 30 };
      auto end = Date { 2022, 5, 30 };
      auto mu = Date { 2020, 1, 1 };
      auto date = randn_date(mu, 100, start, end);
      assert(date.in_range(start, end, Range::Closed));
      assert(date.month > 0);
      assert(date.day > 0);
    }
    
    // randn_time()
    {
      auto start = Time { 1, 20, 30 };
      auto end = Time { 21, 40, 51 };
      auto mu = Time { 8, 1, 17 };
      auto time = randn_time(mu, 10'000, start, end);
      assert(time.in_range(start, end, Range::Closed));
    }
    {
      auto start = Time { 21, 40, 51 };
      auto end = Time { 3, 20, 30 };
      auto mu = Time { 0, 7, 53 };
      auto time = randn_time(mu, 4'000, start, end);
      assert(time.in_range(start, end, Range::Closed));
    }
    
  }

}
