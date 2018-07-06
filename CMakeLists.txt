cmake_minimum_required(VERSION 3.10)
project(Roguelike)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-lncurses -Wall")

include_directories(include)

add_executable(Roguelike source/main.cpp include/Game_manager.h source/Game_manager.cpp include/Screens.h source/Screens.cpp include/Actors.h source/Actors.cpp include/Map.h source/Map.cpp source/Config.cpp include/Config.h source/Statistics.cpp include/Statistics.h source/Point.cpp include/Point.h source/UserInterface.cpp include/UserInterface.h include/Enums.h)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries (Roguelike ${CURSES_LIBRARIES})
endif()