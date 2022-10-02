set(TARGET_NAME GraphView)

set(SOURCES_LIST GraphView.cpp)

add_library(${TARGET_NAME} STATIC ${SOURCES_LIST})

target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_DIRS})
target_link_libraries(${TARGET_NAME} PUBLIC Qt5::Core  Qt5::Gui Qt5::Widgets GraphModel)