set(TARGET_NAME ShteinerTree)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES_FILES
   MainWindow.cpp
   MatrixWidget/MatrixWidget.cpp
   main.cpp)


set(HEADER_FILES
   MainWindow.hpp
   MatrixWidget/MatrixWidget.hpp)

set(RESOURCES_FILES)



source_group("Sources Files" FILES ${SOURCES_FILES})
source_group("Headers Files" FILES ${HEADERS_FILES})
source_group("Resources Files" FILES ${RESOURCES_FILES})

add_executable(${TARGET_NAME} WIN32  ${SOURCES_FILES} ${HEADERS_FILES}  ${RESOURCES_FILES} ${INSTALLER_FILES})
target_link_libraries(${TARGET_NAME} Qt5::Core  Qt5::Gui Qt5::Widgets)



target_include_directories(${TARGET_NAME} 
   PRIVATE ${INCLUDE_DIRECTORIES}
           ${CMAKE_CURRENT_LIST_DIR})  