GLIB_COMPILE_RESOURCES(USE_CASE DEST resource 
    SOURCE use_case_plugin.resource.xml
    MANUAL_REGISTER)

aux_source_directory(. USE_CASE_SOURCE)

find_package (GTK3 REQUIRED)


add_library (use_case_plugin MODULE ${USE_CASE_SOURCE} ${USE_CASE_RESOURCE})

target_include_directories(use_case_plugin
    PRIVATE ${GTK3_INCLUDE_DIRS})

target_link_libraries(use_case_plugin
    ${GTK3_LIBRARIES}
    umlmeow)

add_custom_command(TARGET use_case_plugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy $<TARGET_FILE:use_case_plugin> ${BINARY_PLUGINS_DIR})

