//
//  Timer.h
//  Core
//
//  Created by Rasmus Anthin on 2025-07-10.
//

#pragma once

class Timer
{
  float timestamp = 0.f;
  float delay = 0.f;
  bool started = false;
  
public:
  Timer(float d) : delay(d) {}
  
  // Old name : set(t).
  bool start_if_stopped(float t)
  {
    if (!started)
    {
      force_start(t);
      return true;
    }
    return false;
  }
  
  // Old name : set(t).
  void force_start(float t)
  {
    timestamp = t;
    started = true;
  }
  
  // Old name : wait(t, reset = false).
  // Returns true if timer has finished.
  bool finished(float t)
  {
    return started && (t - timestamp > delay);
  }
  
  // Old name : wait(t, reset = true).
  // Returns true and resets timer if timer has finished, otherwise returns false.
  bool wait_then_reset(float t)
  {
    if (finished(t))
    {
      reset();
      return true;
    }
    return false;
  }
  
  bool is_ticking(float t) const
  {
    return started && (t - timestamp <= delay);
  }
  
  void reset()
  {
    started = false;
  }
  
  bool is_active() const
  {
    return started;
  }
  
  void set_delay(float d)
  {
    delay = d;
  }
  
  float get_delay() const
  {
    return delay;
  }
};
