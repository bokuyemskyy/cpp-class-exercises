file(GLOB_RECURSE MAIN_CANDIDATES
    "${SRC_DIR}/lab*/**/${EXEC_NAME_FINAL}"
)

foreach(MAIN_BIN ${MAIN_CANDIDATES})
    if(EXISTS "${MAIN_BIN}")
        file(REMOVE "${MAIN_BIN}")
    endif()
endforeach()
