file(GLOB_RECURSE BINARIES
    "${SRC_DIR}/lab*/**/*"
)

foreach(BIN IN LISTS BINARIES)
    get_filename_component(EXT "${BIN}" EXT)

    if(EXT STREQUAL ".cpp" OR EXT STREQUAL ".hpp")
        list(REMOVE_ITEM BINARIES ${BIN})
    endif()
endforeach()

foreach(BIN ${BINARIES})
    if(EXISTS "${BIN}" AND IS_EXECUTABLE "${BIN}")
        file(REMOVE "${BIN}")
    endif()
endforeach()

#file(REMOVE "${BIN}")