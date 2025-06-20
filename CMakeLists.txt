cmake_minimum_required(VERSION 3.25)
project(AllLabs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()



set(EXEC_NAME_FINAL "main")


file(GLOB LABS RELATIVE ${CMAKE_SOURCE_DIR} lab*)

foreach(lab ${LABS})
  set(LAB_DIR ${CMAKE_SOURCE_DIR}/${lab})
  file(GLOB TASKS RELATIVE ${LAB_DIR} "${LAB_DIR}/*")

  foreach(task ${TASKS})
    set(TASK_DIR ${LAB_DIR}/${task})
    if(IS_DIRECTORY ${TASK_DIR} AND EXISTS ${TASK_DIR}/main.cpp)
      string(TOLOWER "${lab}_${task}" EXEC_NAME)
      set(SOURCES "${TASK_DIR}/main.cpp")
      set(SOURCE_DIR "${TASK_DIR}/source")
      if(EXISTS ${SOURCE_DIR})
        file(GLOB ADDITIONAL_SOURCES "${SOURCE_DIR}/*.cpp")
        list(APPEND SOURCES ${ADDITIONAL_SOURCES})
      endif()
      set(INCLUDE_DIRS "")
      set(INCLUDE_DIR "${TASK_DIR}/include")
      if(EXISTS ${INCLUDE_DIR})
        list(APPEND INCLUDE_DIRS "${INCLUDE_DIR}")
      endif()
      add_executable(${EXEC_NAME} ${SOURCES})
      if(INCLUDE_DIRS)
        target_include_directories(${EXEC_NAME} PRIVATE "${INCLUDE_DIRS}")
      endif()
      set_target_properties(${EXEC_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TASK_DIR}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TASK_DIR}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TASK_DIR}
      )
      if(EXEC_NAME_FINAL)
        set_target_properties(${EXEC_NAME} PROPERTIES
          OUTPUT_NAME ${EXEC_NAME_FINAL}
        )
      endif()
    endif()
  endforeach()
endforeach()


set(HUB_DIR "${CMAKE_SOURCE_DIR}/hub")
if(EXISTS "${HUB_DIR}/main.cpp")
  add_executable(main "${HUB_DIR}/main.cpp")
  set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${HUB_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${HUB_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${HUB_DIR}"
  )
endif()


add_custom_target(clear_bins
  COMMAND ${CMAKE_COMMAND} -DSRC_DIR=${CMAKE_SOURCE_DIR} -DEXEC_NAME_FINAL=${EXEC_NAME_FINAL} -P ${CMAKE_SOURCE_DIR}/ClearBins.cmake
  COMMENT "Deleting all built binaries from bin/"
)


