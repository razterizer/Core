#!/bin/bash

function build_linux_macos()
{
  #g++ pilot_episode.cpp -lSDL2 -o pilot_episode
  #g++ pilot_episode.cpp -lncurses -o pilot_episode
  #export XDG_RUNTIME_DIR=/tmp
  echo "Building for Linux / MacOS target..."
  mkdir -p bin_linux
  g++ $1.cpp -o ./bin_linux/$1 -std=c++2a -O3
  echo "Done."
  #./pilot_episode
}

function build_windows()
{
  echo "Building for Windows target via mingw..."
  mkdir -p bin_windows
  x86_64-w64-mingw32-g++ -Wl,--stack,10000000 $1.cpp -o ./bin_windows/$1.exe -std=c++2a -O3
  echo "Done."

  echo "Copying Windows/mingw related dlls..."
  # Paths to the found DLLs
  #DLL_PATH_1="/System/Volumes/Data/opt/homebrew/Cellar/mingw-w64/11.0.1/toolchain-x86_64/x86_64-w64-mingw32/lib/libstdc++-6.dll"
  #DLL_PATH_2="/System/Volumes/Data/opt/homebrew/Cellar/mingw-w64/11.0.1/toolchain-x86_64/x86_64-w64-mingw32/lib/libgcc_s_seh-1.dll"
  #/opt/homebrew/Cellar/mingw-w64/11.0.1/toolchain-i686/i686-w64-mingw32/bin/libwinpthread-1.dll
  #/opt/homebrew/Cellar/mingw-w64/11.0.1/toolchain-x86_64/x86_64-w64-mingw32/bin/libwinpthread-1.dll
  DLL_PATH_1="/opt/homebrew/Cellar/mingw-w64/11.0.1/toolchain-x86_64/x86_64-w64-mingw32/lib/libstdc++-6.dll"
  DLL_PATH_2="/opt/homebrew/Cellar/mingw-w64/11.0.1/toolchain-x86_64/x86_64-w64-mingw32/lib/libgcc_s_seh-1.dll"
  DLL_PATH_3="/opt/homebrew/Cellar/mingw-w64/11.0.1/toolchain-x86_64/x86_64-w64-mingw32/bin/libwinpthread-1.dll"

  if [ -f "$DLL_PATH_1" ] && [ -f "$DLL_PATH_2" ] && [ -f "$DLL_PATH_3" ]; then
    cp "$DLL_PATH_1" ./bin_windows
    cp "$DLL_PATH_2" ./bin_windows
    cp "$DLL_PATH_3" ./bin_windows
  else
    echo "DLLs not found. Please provide correct paths."
  fi
  echo "Done."
}

function show_help() {
    echo "Usage: ./build [output_name] [option]"
    echo "Options:"
    echo "  all          : Builds for Linux/MacOS and Windows"
    echo "  a            : Same as 'all'"
    echo "  linmac       : Builds for Linux/MacOS only"
    echo "  l            : Same as 'linmac'"
    echo "  windows      : Builds for Windows only"
    echo "  w            : Same as 'windows'"
    echo "  help         : Shows help explaining command line arguments"
    echo "  h            : Same as 'help'"
}

# Check the number of arguments provided
if [ "$#" -lt 1 ]; then
    echo "Insufficient arguments. Usage: ./build [output_name] [option]"
    exit 1
fi

option=${2:-help}

case "$option" in
    'all' | 'a')
        build_linux_macos "$1"
        build_windows "$1"
        ;;
    'linmac' | 'l')
        build_linux_macos "$1"
        ;;
    'windows' | 'w')
        build_windows "$1"
        ;;
    'help' | 'h')
        show_help
        ;;
    *)
        echo "Invalid option. Use './build help' to see available options."
        ;;
esac
