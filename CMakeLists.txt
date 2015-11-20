cmake_minimum_required(VERSION 3.0)

project(UMLMeow)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package (GTK3 REQUIRED)

add_definitions (${GTK3_CFLAGS_OTHER})

add_executable (umlmeow main.c)

target_include_directories(umlmeow PUBLIC ${GTK3_INCLUDE_DIRS})
target_link_libraries(umlmeow ${GTK3_LIBRARIES})
