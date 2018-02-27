cmake_minimum_required(VERSION 3.9)
project(NoRecoil)

set(GCC_CXX_FLAGS ${GCC_CXX_FLAGS} "-static-libgcc -static-libstdc++ -static")
set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_CXX_STANDARD 11)

add_executable(NoRecoil.exe main.cpp)