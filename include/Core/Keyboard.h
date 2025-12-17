//
//  Keyboard.h
//  Core
//
//  Created by Rasmus Anthin on 2025-12-17.
//

#pragma once

#ifdef _WIN32
  #include <conio.h>
#else
  #include <termios.h>
  #include <unistd.h>
  #include <cstdio>
#endif


namespace keyboard
{

  inline int getch()
  {
    #ifdef _WIN32
    return _getch();
#else
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    int ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
  }
  
  inline void press_any_key()
  {
    std::cout << "Press any key to continue ...\n";
    keyboard::getch();
  }
  
}
