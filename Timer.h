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
  
  bool wait(float t)
  {
    if (started && (t - timestamp > delay))
    {
      started = false;
      return true;
    }
    return false;
  }
  
  void reset()
  {
    started = false;
  }
};
