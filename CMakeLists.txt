cmake_minimum_required(VERSION 3.9)
project(NoRecoil)

FIND_PACKAGE(Boost REQUIRED)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_CXX_STANDARD 14)

add_executable(NoRecoil.exe main.cpp MouseInput.h DialogCreator.h Config.h)