
IF (GTK3_INCLUDE_DIRS AND GTK3_LIBRARIES)
    SET(GTK3_FOUND TRUE)
ELSE (GTK3_INCLUDE_DIRS AND GTK3_LIBRARIES)
    IF (NOT WIN32)
        FIND_PACKAGE (PkgConfig QUIET)
        IF (PKG_CONFIG_FOUND)
            pkg_check_modules(_GTK3_PC QUIET gtk+-3.0)
        ENDIF (PKG_CONFIG_FOUND)
    ENDIF (NOT WIN32)


    #FIND_PATH (GTK3_INCLUDE_DIRS gtk-3.0
    #    HINTS ${_GTK3_PC_INCLUDE_DIR} ${_GTK3_PC_INCLUDE_DIRS})


    #    FIND_LIBRARY (GTK3_LIBRARIES NAMES 
    #   pangocairo-1.0 libpangocairo-1.0
    #    HINTS ${_GTK3_PC_LIBDIR} ${_GTK3_PC_LIBDIRS})
    
    set (GTK3_INCLUDE_DIRS ${_GTK3_PC_INCLUDE_DIRS})
    set (GTK3_LIBRARIES ${_GTK3_PC_LIBRARIES})
    set (GTK3_CFLAGS_OTHER ${_GTK3_PC_CFLAGS_OTHER})

    #message ("GTK3 : ${_GTK3_PC_LIBRARIES}")

    IF (GTK3_INCLUDE_DIRS AND GTK3_LIBRARIES)
        SET(GTK3_FOUND TRUE)
    ENDIF (GTK3_INCLUDE_DIRS AND GTK3_LIBRARIES)

    IF (GTK3_FOUND)
        IF (NOT GTK3_FIND_QUIETLY)
            MESSAGE (STATUS "Found gtk3 include dir: ${GTK3_INCLUDE_DIRS}")
            MESSAGE (STATUS "      gtk3 lib: ${GTK3_LIBRARIES}")
        ENDIF (NOT GTK3_FIND_QUIETLY)
    ELSE (GTK3_FOUND)
        IF (NOT GTK3_FIND_QUIETLY)
            MESSAGE (SEND_ERROR "Could NOT find gtk3")
        ENDIF (NOT GTK3_FIND_QUIETLY)
    ENDIF (GTK3_FOUND)

    MARK_AS_ADVANCED(GTK3_INCLUDE_DIRS GTK3_LIBRARIES GTK3_CFLAGS_OTHER)

ENDIF (GTK3_INCLUDE_DIRS AND GTK3_LIBRARIES)