
GLIB_COMPILE_RESOURCES(SELECT DEST resource 
    SOURCE select_plugin.resource.xml
    MANUAL_REGISTER)

aux_source_directory(. SELECT_SOURCE)

find_package (GTK3 REQUIRED)


add_library (select_plugin MODULE ${SELECT_SOURCE} ${SELECT_RESOURCE})

target_include_directories(select_plugin
    PRIVATE ${GTK3_INCLUDE_DIRS})

target_link_libraries(select_plugin
    ${GTK3_LIBRARIES}
    umlmeow)


add_custom_command(TARGET select_plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy $<TARGET_FILE:select_plugin> ${BINARY_PLUGINS_DIR})

