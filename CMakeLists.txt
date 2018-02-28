cmake_minimum_required(VERSION 3.9)
project(NoRecoil)

FIND_PACKAGE(Boost REQUIRED)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

set(GCC_CXX_FLAGS ${GCC_CXX_FLAGS} "-m32 -lboost_thread-mt -lboost_system")

set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_CXX_STANDARD 14)

add_executable(NoRecoil.exe main.cpp MouseAndKeyboardInput.h DialogCreator.h NoRecoilConfig.h AsyncKeyEventListener.h NoRecoil.h)