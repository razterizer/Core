#pragma once

class OneShot
{
  bool val = true;
  
public:
  
  OneShot() = default;
  OneShot(bool preset) : val(preset) {}
  
  bool once()
  {
    bool curr = val;
    val = false;
    return curr;
  }
  
  void reset()
  {
    val = true;
  }
  
};
