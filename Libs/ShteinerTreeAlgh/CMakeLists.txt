set(TARGET_NAME ShteinerTreeAlgh)

set(SOURCES_LIST ShteinerTreeAlgh.cpp)

add_library(${TARGET_NAME} STATIC ${SOURCES_LIST})

target_include_directories(${TARGET_NAME} PUBLIC ${SHARED_DIRS})
target_link_libraries(${TARGET_NAME} PUBLIC GraphModel)