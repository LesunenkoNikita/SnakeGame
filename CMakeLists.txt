cmake_minimum_required(VERSION 3.30)
project(SnakeGame)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0)
FetchContent_MakeAvailable(SFML)
add_executable(SnakeGame main.cpp
        IState.h
        StateManage.cpp
        StateManage.h
        SpriteManage.cpp
        SpriteManage.h
        Game.cpp
        Game.h
        Menu.cpp
        Menu.h
        Gameplay.cpp
        Gameplay.h
        Snake.cpp
        Snake.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE  sfml-window sfml-system sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
install(TARGETS ${PROJECT_NAME})