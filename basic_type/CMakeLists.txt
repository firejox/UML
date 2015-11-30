
file (GLOB BASIC_TYPE_HEADERS RELATIVE . "*.h")

aux_source_directory (. BASIC_TYPE_SRCS)

find_package(GTK3 REQUIRED)
find_package(Cairo REQUIRED)

add_library (basic_type OBJECT 
    ${BASIC_TYPE_SRCS} 
    ${BASIC_TYPE_HEADERS})

target_include_directories(basic_type
    PRIVATE ${GTK3_INCLUDE_DIRS}
    PRIVATE ${CAIRO_INCLUDE_DIRS})



