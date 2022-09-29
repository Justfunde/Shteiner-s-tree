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
set(QT_DIR "C:/Tools/Qt/Qt5.13.1/5.13.1/msvc2017_64" CACHE STRING "Specify Qt MSVC 2017 installation path")
set(QT_BIN_DIR "{QT_DIR}/bin")

#set(QT_IFW_DIR "C:/Tools/Qt/QtIFW-3.2.2" CACHE STRING "Specify QtIFW installation path")

set(CMAKE_PREFIX_PATH "${QT_DIR}")

find_package(Qt5 COMPONENTS Core Gui Widgets Network Xml Sql Help REQUIRED)

set(INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/Include")

add_subdirectory(ShteinerTree)