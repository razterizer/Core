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
  
  bool set(float t)
  {
    if (!started)
    {
      timestamp = t;
      started = true;
      return true;
    }
    return false;
  }
  
  bool wait(float t, bool reset = true)
  {
    if (started && (t - timestamp > delay))
    {
      if (reset)
        started = false;
      return true;
    }
    return false;
  }
  
  bool is_ticking(float t)
  {
    return started && (t - timestamp <= delay);
  }
  
  void reset()
  {
    started = false;
  }
};
