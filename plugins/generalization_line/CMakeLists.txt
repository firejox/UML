GLIB_COMPILE_RESOURCES(GENERALIZATION_LINE DEST resource 
    SOURCE generalization_line_plugin.resource.xml
    MANUAL_REGISTER)

aux_source_directory(. GENERALIZATION_LINE_SOURCE)

find_package (GTK3 REQUIRED)


add_library (generalization_line_plugin MODULE
    ${GENERALIZATION_LINE_SOURCE} ${GENERALIZATION_LINE_RESOURCE})

target_include_directories(generalization_line_plugin
    PRIVATE ${GTK3_INCLUDE_DIRS})

target_link_libraries(generalization_line_plugin
    ${GTK3_LIBRARIES}
    umlmeow)

add_custom_command(TARGET generalization_line_plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy $<TARGET_FILE:generalization_line_plugin> ${BINARY_PLUGINS_DIR})

