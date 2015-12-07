cmake_minimum_required(VERSION 3.0)

project(UMLMeow)

set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=implicit")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=implicit")
include (GResource)

find_package (GTK3 REQUIRED)
find_package (Cairo REQUIRED)
find_package (PANGOCAIRO REQUIRED)


set (PLUGIN_DIR "plugins/")
add_definitions (${GTK3_CFLAGS_OTHER})
add_definitions (-DPLUGIN_DIR="${PLUGIN_DIR}")

if (UNIX)
    link_libraries (m)
endif (UNIX)

add_subdirectory (basic_type)

#aux_source_directory (. TOTAL_SOURCE)

set (umlmeow_dirs 
    PRIVATE ${GTK3_INCLUDE_DIRS}
    PRIVATE ${CAIRO_INCLUDE_DIRS}
    PRIVATE ${PANGOCAIRO_INCLUDE_DIRS})
set (umlmeow_libs 
    ${GTK3_LIBRARIES}
    ${CAIRO_LIBRARIES}
    ${PANGOCAIRO_LIBRARIES})

set (umlmeow_objs
    component.c component.h
        line.c line.h line-protected.h
        line_factory.c line_factory.h
        object.c object.h
            port_object.c port_object.h
            line_decorate.c line_decorate.h
            composite_object.c composite_object.h
            basic_object.c basic_object.h basic_object-protected.h
        region.c region.h
    general_object.c general_object.h general_object-type.h
    general_object_pool.c general_object_pool.h)


add_library (umlmeow SHARED 
    utils.c utils.h
    basic_types.h
    canvas.h
    common.h
    double_list-template.h
    single_list-template.h
    ${umlmeow_objs}
    tool_plugin.h
    $<TARGET_OBJECTS:basic_type>)

target_include_directories(umlmeow ${umlmeow_dirs})
target_link_libraries(umlmeow ${umlmeow_libs})


GLIB_COMPILE_RESOURCES(main_resource DEST resource SOURCE umlmeow.resource.xml)

add_subdirectory (plugins)

set (uml_meow_src 
    application.c
    main.c
    canvas.c
    plugin_manager.c)


add_executable (uml_meow ${uml_meow_src} ${main_resource_RESOURCE})

target_include_directories(uml_meow 
    PRIVATE ${GTK3_INCLUDE_DIRS}
    PRIVATE ${CAIRO_INCLUDE_DIRS}
    PRIVATE ${PANGOCAIRO_INCLUDE_DIRS})
target_link_libraries(uml_meow 
    ${GTK3_LIBRARIES} 
    ${CAIRO_LIBRARIES}
    ${PANGOCAIRO_LIBRARIES}
    ${CMAKE_DL_LIBS} 
    umlmeow)


