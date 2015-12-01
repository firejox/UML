GLIB_COMPILE_RESOURCES(COMPOSITION_LINE DEST resource 
    SOURCE composition_line_plugin.resource.xml
    MANUAL_REGISTER)

aux_source_directory(. COMPOSITION_LINE_SOURCE)

find_package (GTK3 REQUIRED)


add_library (composition_line_plugin MODULE
    ${COMPOSITION_LINE_SOURCE} ${COMPOSITION_LINE_RESOURCE})

target_include_directories(composition_line_plugin
    PRIVATE ${GTK3_INCLUDE_DIRS})

target_link_libraries(composition_line_plugin
    ${GTK3_LIBRARIES}
    umlmeow)

add_custom_command(TARGET composition_line_plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy $<TARGET_FILE:composition_line_plugin> ${BINARY_PLUGINS_DIR})

