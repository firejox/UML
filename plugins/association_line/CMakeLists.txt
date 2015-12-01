GLIB_COMPILE_RESOURCES(ASSOCIATION_LINE DEST resource 
    SOURCE association_line_plugin.resource.xml
    MANUAL_REGISTER)

aux_source_directory(. ASSOCIATION_LINE_SOURCE)

find_package (GTK3 REQUIRED)


add_library (association_line_plugin MODULE
    ${ASSOCIATION_LINE_SOURCE} ${ASSOCIATION_LINE_RESOURCE})

target_include_directories(association_line_plugin
    PRIVATE ${GTK3_INCLUDE_DIRS})

target_link_libraries(association_line_plugin
    ${GTK3_LIBRARIES}
    umlmeow)

add_custom_command(TARGET association_line_plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy $<TARGET_FILE:association_line_plugin> ${BINARY_PLUGINS_DIR})

