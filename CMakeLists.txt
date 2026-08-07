cmake_minimum_required(VERSION 3.24)

project(Core LANGUAGES CXX)

add_library(Core INTERFACE)
add_library(Core::Core ALIAS Core)

target_compile_features(Core INTERFACE cxx_std_20)
target_include_directories(Core INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

