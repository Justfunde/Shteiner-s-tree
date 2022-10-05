set(TARGET_NAME ShteinerTree)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES_FILES
   MainWindow.cpp
   GraphWidget/GraphWidget.cpp
   main.cpp)


set(HEADER_FILES
   MainWindow.hpp
   GraphWidget/GraphWidget.hpp)

set(RESOURCES_FILES 
   Resources/resource.qrc)



source_group("Sources Files" FILES ${SOURCES_FILES})
source_group("Headers Files" FILES ${HEADERS_FILES})
source_group("Resources Files" FILES ${RESOURCES_FILES})

add_executable(${TARGET_NAME} WIN32  ${SOURCES_FILES} ${HEADERS_FILES}  ${RESOURCES_FILES})
target_link_libraries(${TARGET_NAME} Qt5::Core  Qt5::Gui Qt5::Widgets GraphModel GraphView ShteinerTreeAlgh)



target_include_directories(${TARGET_NAME} 
   PUBLIC ${SHARED_DIRS}
           ${CMAKE_CURRENT_LIST_DIR})  