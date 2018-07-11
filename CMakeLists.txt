cmake_minimum_required(VERSION 3.10)
project(Roguelike)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-lncurses -Wall")

include_directories(include)

add_executable(Roguelike source/main.cpp include/GameManager.h source/GameManager.cpp include/Screens.h source/Screens.cpp include/Actors.h source/Actors.cpp include/Map.h source/Map.cpp source/Config.cpp include/Config.h source/Statistics.cpp include/Statistics.h source/Point.cpp include/Point.h source/UserInterface.cpp include/UserInterface.h include/Enums.h source/Hero.cpp include/Hero.h source/Zombie.cpp include/Zombie.h source/Dragon.cpp include/Dragon.h source/Princess.cpp include/Princess.h source/Fireball.cpp include/Fireball.h source/Floor.cpp include/Floor.h source/Wall.cpp include/Wall.h source/HealthPotion.cpp include/HealthPotion.h source/ManaPotion.cpp include/ManaPotion.h source/ActorFactory.cpp include/ActorFactory.h source/MainMenu.cpp include/MainMenu.h source/Loading.cpp include/Loading.h source/GameField.cpp include/GameField.h)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries (Roguelike ${CURSES_LIBRARIES})
endif()