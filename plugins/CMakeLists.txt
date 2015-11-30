

file(GLOB_RECURSE plugin_dirs "*/CMakeLists.txt")

message ("plugin dirs :${plugin_dirs}")

set (BINARY_PLUGINS_DIR ${CMAKE_CURRENT_BINARY_DIR})

FOREACH(plugin_dir ${plugin_dirs})
    get_filename_component(dir_name "${plugin_dir}" DIRECTORY)
    message ( "Find plugin : ${dir_name}")
    add_subdirectory ("${dir_name}")
ENDFOREACH(plugin_dir)


