GLIB_COMPILE_RESOURCES(CLASS DEST resource 
    SOURCE class_plugin.resource.xml
    MANUAL_REGISTER)

aux_source_directory(. CLASS_SOURCE)

find_package (GTK3 REQUIRED)


add_library (class_plugin MODULE ${CLASS_SOURCE} ${CLASS_RESOURCE})

target_include_directories(class_plugin
    PRIVATE ${GTK3_INCLUDE_DIRS})

target_link_libraries(class_plugin
    ${GTK3_LIBRARIES}
    umlmeow)

add_custom_command(TARGET class_plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy $<TARGET_FILE:class_plugin> ${BINARY_PLUGINS_DIR})

