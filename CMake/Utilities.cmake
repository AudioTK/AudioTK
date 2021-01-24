#
# CMake utilities for ATK
#
include(CMakeParseArguments)

function(stagedebug target)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(APPLE)
      add_custom_command(TARGET ${target}
        POST_BUILD
        COMMAND dsymutil $<CONFIG>/$<TARGET_FILE_NAME:${target}>
        MAIN_DEPENDENCY ${target}
        COMMENT "Staging dSYM for ${target}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM)
    endif(APPLE)
  endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endfunction(stagedebug)

function(SOURCE_GROUP_BY_FOLDER target)
  SET(SOURCE_GROUP_DELIMITER "/")

  SET(last_dir "")
  SET(files "")
  FOREACH(file ${${target}_SRC} ${${target}_HEADERS})
    file(RELATIVE_PATH relative_file "${CMAKE_CURRENT_SOURCE_DIR}" ${file})
    GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
    IF (NOT "${dir}" STREQUAL "${last_dir}")
      IF (files)
        SOURCE_GROUP("${last_dir}" FILES ${files})
      ENDIF (files)
      SET(files "")
    ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
    SET(files ${files} ${file})
    SET(last_dir "${dir}")
  ENDFOREACH(file)
  IF (files)
    SOURCE_GROUP("${last_dir}" FILES ${files})
  ENDIF (files)
endfunction(SOURCE_GROUP_BY_FOLDER)

function(ATK_add_library PREFIX)

set(FLAGS )
set(SINGLEVALUES NAME FOLDER)
set(MULTIVALUES SRC HEADERS DEFINITIONS INCLUDE LIBRARIES)

cmake_parse_arguments(${PREFIX}
                 "${FLAGS}"
                 "${SINGLEVALUES}"
                 "${MULTIVALUES}"
                ${ARGN})

SOURCE_GROUP_BY_FOLDER(${PREFIX})

if(NOT ${PREFIX}_NAME)
  message(ERROR "No name set for ${PREFIX}")
endif(NOT ${PREFIX}_NAME)

if(ENABLE_STATIC_LIBRARIES)
  add_library(${${PREFIX}_NAME}_static
    STATIC
      ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE}
  )

  target_compile_definitions(${${PREFIX}_NAME}_static PRIVATE ${${PREFIX}_DEFINITIONS})
  target_include_directories(${${PREFIX}_NAME}_static PRIVATE ${${PREFIX}_INCLUDE})
  target_include_directories(${${PREFIX}_NAME}_static BEFORE PRIVATE ${PROJECT_SOURCE_DIR})
  target_include_directories(${${PREFIX}_NAME}_static INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${${PREFIX}_NAME}_static PUBLIC ${${PREFIX}_LIBRARIES})

  set_target_properties(${${PREFIX}_NAME}_static PROPERTIES
    FOLDER C++/${${PREFIX}_FOLDER}/static
  )
  INSTALL(TARGETS ${${PREFIX}_NAME}_static
    EXPORT ATK
    RUNTIME COMPONENT libraries
    LIBRARY COMPONENT libraries
    ARCHIVE COMPONENT libraries
  )
endif(ENABLE_STATIC_LIBRARIES)

if(ENABLE_SHARED_LIBRARIES)
  add_library(${${PREFIX}_NAME}
    SHARED
    ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE} ${${PREFIX}_ARCH_GEN_SRC}
  )

  target_compile_definitions(${${PREFIX}_NAME} PRIVATE ${${PREFIX}_DEFINITIONS} -DBUILD_${PREFIX} -DATK_SHARED)
  target_include_directories(${${PREFIX}_NAME} PRIVATE ${${PREFIX}_INCLUDE})
  target_include_directories(${${PREFIX}_NAME} BEFORE PRIVATE ${PROJECT_SOURCE_DIR})
  target_include_directories(${${PREFIX}_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${${PREFIX}_NAME} PUBLIC ${${PREFIX}_LIBRARIES})

  set_target_properties (${${PREFIX}_NAME} PROPERTIES
    FOLDER C++/${${PREFIX}_FOLDER}/shared
  )

  stagedebug(${${PREFIX}_NAME})

  INSTALL(TARGETS ${${PREFIX}_NAME}
    EXPORT ATK
    RUNTIME COMPONENT libraries
    LIBRARY COMPONENT libraries
    ARCHIVE COMPONENT libraries
  )

endif(ENABLE_SHARED_LIBRARIES)

INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ATK/
    FILES_MATCHING PATTERN *.h
)
endfunction()

function(ATK_add_executable PREFIX)

set(FLAGS INSTALL)
set(SINGLEVALUES NAME FOLDER)
set(MULTIVALUES SRC HEADERS DEFINITIONS INCLUDE LIBRARIES)

cmake_parse_arguments(${PREFIX}
                 "${FLAGS}"
                 "${SINGLEVALUES}"
                 "${MULTIVALUES}"
                ${ARGN})

SOURCE_GROUP_BY_FOLDER(${PREFIX})

if(NOT ${PREFIX}_NAME)
  message(ERROR "No name set for ${PREFIX}")
endif(NOT ${PREFIX}_NAME)

add_definitions(${${PREFIX}_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR} ${${PREFIX}_INCLUDE})

add_executable(${${PREFIX}_NAME}
  ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE}
)

if(${PREFIX}_FOLDER)
  set_target_properties (${${PREFIX}_NAME} PROPERTIES
    FOLDER C++/${${PREFIX}_FOLDER}
  )
endif(${PREFIX}_FOLDER)

target_link_libraries(${${PREFIX}_NAME} ${${PREFIX}_LIBRARIES})
if(${PREFIX}_INSTALL)
INSTALL(TARGETS ${${PREFIX}_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/ COMPONENT apps
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/ COMPONENT apps
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/ COMPONENT apps
)
endif()
endfunction()

function(ATK_add_test PREFIX)

set(FLAGS)
set(SINGLEVALUES NAME TESTNAME)
set(MULTIVALUES SRC HEADERS DEFINITIONS INCLUDE LIBRARIES)

cmake_parse_arguments(${PREFIX}
                 "${FLAGS}"
                 "${SINGLEVALUES}"
                 "${MULTIVALUES}"
                ${ARGN})

if(NOT ${PREFIX}_TESTNAME)
  message(ERROR "No test name set for ${PREFIX}")
endif(NOT ${PREFIX}_TESTNAME)

ATK_add_executable(${PREFIX}
  NAME ${${PREFIX}_NAME}
  FOLDER Tests
  SRC ${${PREFIX}_SRC}
  HEADERS ${${PREFIX}_HEADERS}
  DEFINITIONS ${${PREFIX}_DEFINITIONS}
  INCLUDE ${${PREFIX}_INCLUDE}
  LIBRARIES ${${PREFIX}_LIBRARIES}
)

add_test(NAME ${${PREFIX}_TESTNAME}
         COMMAND ${${PREFIX}_NAME} --log_level=message)

endfunction()

function(ATK_add_python_module PREFIX)

set(FLAGS INSTALL)
set(SINGLEVALUES NAME FOLDER)
set(MULTIVALUES SRC HEADERS DEFINITIONS INCLUDE LIBRARIES)

cmake_parse_arguments(${PREFIX}
                 "${FLAGS}"
                 "${SINGLEVALUES}"
                 "${MULTIVALUES}"
                ${ARGN})

if(NOT ${PREFIX}_NAME)
  message(ERROR "No name set for ${PREFIX}")
endif(NOT ${PREFIX}_NAME)

SOURCE_GROUP_BY_FOLDER(${PREFIX})

include_directories(${PROJECT_SOURCE_DIR} ${NUMPY_INCLUDE_DIRS} ${${PREFIX}_INCLUDE})

pybind11_add_module(${${PREFIX}_NAME} MODULE ${${PREFIX}_SRC} ${${PREFIX}_HEADERS} ${NATVIS_FILE})
target_link_libraries(${${PREFIX}_NAME} PRIVATE ${${PREFIX}_LIBRARIES})

SET(ATK_PYTHON_NAME "${${PREFIX}_NAME}")

configure_file (
  "${CMAKE_SOURCE_DIR}/Python/ATK/__init__.py.in"
  "${CMAKE_CURRENT_BINARY_DIR}/__init__.py" @ONLY
)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/__init__.py
  DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/${${PREFIX}_FOLDER}
)
INSTALL(TARGETS ${${PREFIX}_NAME}
  DESTINATION ${PYTHON_INSTALL_FOLDER}/site-packages/ATK/${${PREFIX}_FOLDER}
)

set_target_properties (${${PREFIX}_NAME} PROPERTIES
  FOLDER Python
)

endfunction()

INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/CMake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share
  FILES_MATCHING PATTERN "*.cmake"
)

include(CheckCXXCompilerFlag)

if(CMAKE_CXX_COMPILER_ID MATCHES "Apple")
  include(apple-clang)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  include(clang)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  include(gcc)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  if(MSVC)
    include(intel-msvc)
  else()
    include(intel-gcc)
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  include(msvc)
else()
  message(FATAL_ERROR "Compiler '${CMAKE_CXX_COMPILER_ID}' not recognized")
endif()

if(ATK_CURRENTLY_BUILDING)
  INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/3rdParty/gsl/include/gsl ${PROJECT_SOURCE_DIR}/3rdParty/eigen/Eigen
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    )
endif(ATK_CURRENTLY_BUILDING)

