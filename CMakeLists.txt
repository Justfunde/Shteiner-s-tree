cmake_minimum_required(VERSION 3.19)

project(SHTEINER_TREE LANGUAGES CXX)

#enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Initialization of common build parameters
set(BUILD_TYPE_LIST "Debug" "Release")
set(OUTPUT_DIR "${CMAKE_CURRENT_LIST_DIR}/Output")

set(OUTPUT_DEBUG_DIR "{CMAKE_CURRENT_LIST_DIR}/Debug")
set(OUTPUT_RELEASE_DIR "{CMAKE_CURRENT_LIST_DIR}/Release")

set(CMAKE_MODULE_PATH "{CMAKE_CURRENT_LIST_DIR}/cmake")

# Окружение


find_package(Qt5 COMPONENTS Core Gui Widgets  REQUIRED)

set(SHARED_DIRS "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(ShteinerTree)
add_subdirectory(Libs)