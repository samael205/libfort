project(libfort)

# Required cmake version
cmake_minimum_required(VERSION 2.8)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Built options
option(FORT_CXX_BUILD "Compile with c++ compiler instead of c" OFF)
option(FORT_ENABLE_ASTYLE "Enable astyle" OFF)
set(FORT_BUILD_TYPE "common" CACHE STRING "Build types(common, asan, ubsan, coveralls)")


# Determine compiler (pos. values Clang, GNU, Intel, MSVC, AppleClang...
# (https://cmake.org/cmake/help/v3.0/variable/CMAKE_LANG_COMPILER_ID.html)
if(FORT_CXX_BUILD)
    set(FORT_COMPILER ${CMAKE_CXX_COMPILER_ID})
else(FORT_CXX_BUILD)
    set(FORT_COMPILER ${CMAKE_C_COMPILER_ID})
endif(FORT_CXX_BUILD)



set(CMAKE_VERBOSE_MAKEFILE ON)


# ------------------------------------------------------------------------------
# Add WChar support for the build
# ------------------------------------------------------------------------------
add_definitions(-DFT_CONGIG_HAVE_WCHAR)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------

include_directories(lib)
include_directories(src)
include_directories(tests)





# ------------------------------------------------------------------------------
# Warnings
# ------------------------------------------------------------------------------

if("${FORT_COMPILER}" STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W4")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4")
else("${FORT_COMPILER}" STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -Wextra -std=c99 -Wpedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -Wextra")
endif("${FORT_COMPILER}" STREQUAL "MSVC")




# ------------------------------------------------------------------------------
# Sources and executables
# ------------------------------------------------------------------------------

FILE(GLOB_RECURSE FortHeaders "lib/*.h" "lib/*.hpp" "tests/*.h" "src/*.h")
add_custom_target(headers SOURCES ${FortHeaders})


set(FORT_DEV_SOURCES
    src/fort_impl.c
    src/vector.c
    src/string_buffer.c
    src/options.c
    src/cell.c
    src/row.c
    src/table.c
    src/fort_utils.c
    src/wcwidth.c)




set(EXAMPLE_SOURCES
    example/main.c)
add_executable(${PROJECT_NAME}_example
    ${EXAMPLE_SOURCES}
    lib/fort.c)

set(EXAMPLE_CPP_SOURCES
    example/main.cpp)
add_executable(${PROJECT_NAME}_example_cpp
    ${EXAMPLE_CPP_SOURCES}
    lib/fort.c)

set(TEST_SOURCES_DEV
    tests/main_test.c
    tests/wb_tests/test_vector.c
    tests/wb_tests/test_string_buffer.c
    tests/wb_tests/test_table_geometry.c
    tests/bb_tests/test_table_basic.c
    tests/bb_tests/test_table_border_style.c
    tests/bb_tests/test_table_options.c
    tests/bb_tests/test_memory_errors.c
    tests/test_utils.c)
add_executable(${PROJECT_NAME}_test_dev
    ${FORT_DEV_SOURCES}
    ${TEST_SOURCES_DEV})

target_compile_definitions(${PROJECT_NAME}_test_dev
    PUBLIC FORT_WB_TESTING_ENABLED=1)

set(TEST_SOURCES
    tests/main_test.c
    tests/bb_tests/test_table_basic.c
    tests/bb_tests/test_table_border_style.c
    tests/bb_tests/test_table_options.c
    tests/bb_tests/test_memory_errors.c
    tests/test_utils.c)
add_executable(${PROJECT_NAME}_test
    lib/fort.c
    ${TEST_SOURCES})


set(TEST_SOURCES_CPP
    tests/main_test_cpp.cpp
    tests/bb_tests_cpp/test_table_basic.cpp
    tests/test_utils.c)
add_executable(${PROJECT_NAME}_test_cpp
    lib/fort.c
    ${TEST_SOURCES_CPP})

if(FORT_CXX_BUILD)
    SET_SOURCE_FILES_PROPERTIES( ${FORT_DEV_SOURCES} PROPERTIES LANGUAGE CXX)
    SET_SOURCE_FILES_PROPERTIES( ${EXAMPLE_SOURCES} PROPERTIES LANGUAGE CXX)
    SET_SOURCE_FILES_PROPERTIES( ${TEST_SOURCES} PROPERTIES LANGUAGE CXX)
endif(FORT_CXX_BUILD)



# ------------------------------------------------------------------------------
# Sanitizers
# ------------------------------------------------------------------------------

if("${FORT_COMPILER}" STREQUAL "GNU" OR "${FORT_COMPILER}" STREQUAL "Clang")
    # asan case
    if(FORT_BUILD_TYPE STREQUAL "asan")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
        if("${FORT_COMPILER}" STREQUAL "GNU")
            target_link_libraries(${PROJECT_NAME}_example asan)
            target_link_libraries(${PROJECT_NAME}_test asan)
            target_link_libraries(${PROJECT_NAME}_example_cpp asan)
        endif("${FORT_COMPILER}" STREQUAL "GNU")
    endif(FORT_BUILD_TYPE STREQUAL "asan")

    #ubsan case
    if(FORT_BUILD_TYPE STREQUAL "ubsan")
        # -fno-sanitize-recover option is used to force faild
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined -fno-sanitize-recover")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fno-sanitize-recover")
        if("${FORT_COMPILER}" STREQUAL "GNU")
            target_link_libraries(${PROJECT_NAME}_example ubsan)
            target_link_libraries(${PROJECT_NAME}_example_cpp ubsan)
            target_link_libraries(${PROJECT_NAME}_test ubsan)
        endif("${FORT_COMPILER}" STREQUAL "GNU")
    endif("${FORT_COMPILER}" STREQUAL "ubsan")

    #coveralls case
    if(FORT_BUILD_TYPE STREQUAL "coveralls")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage")
        #target_link_libraries(${PROJECT_NAME}_example_cpp gcov)
    endif(FORT_BUILD_TYPE STREQUAL "coveralls")

endif("${FORT_COMPILER}" STREQUAL "GNU" OR "${FORT_COMPILER}" STREQUAL "Clang")


# Hack for some gcc versions
if("${FORT_COMPILER}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
endif("${FORT_COMPILER}" STREQUAL "GNU")



# ------------------------------------------------------------------------------
# Astyle
# ------------------------------------------------------------------------------

if(FORT_ENABLE_ASTYLE)
    list(APPEND ASTYLE_CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
    )

    ExternalProject_Add(
        astyle
        GIT_REPOSITORY      https://github.com/Bareflank/astyle.git
        GIT_TAG             v1.2
        GIT_SHALLOW         1
        CMAKE_ARGS          ${ASTYLE_CMAKE_ARGS}
        PREFIX              ${CMAKE_BINARY_DIR}/external/astyle/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/external/astyle/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/external/astyle/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/astyle/download
        SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/astyle/src
        BINARY_DIR          ${CMAKE_BINARY_DIR}/external/astyle/build
    )

    list(APPEND ASTYLE_ARGS
        --style=kr
        --lineend=linux
        --suffix=none
        --pad-oper
        --unpad-paren
        --align-pointer=name
        --align-reference=name
        --indent-switches
        --keep-one-line-statements
        --keep-one-line-blocks
        --pad-header
        --convert-tabs
        --min-conditional-indent=0
        --indent=spaces=4
        ${CMAKE_SOURCE_DIR}/lib/*.h
        ${CMAKE_SOURCE_DIR}/lib/*.c
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/tests/*.c
        ${CMAKE_SOURCE_DIR}/tests/*.h
        ${CMAKE_SOURCE_DIR}/tests/bb_tests/*.c
        ${CMAKE_SOURCE_DIR}/tests/wb_tests/*.c
        ${CMAKE_SOURCE_DIR}/tests/bb_tests_cpp/*.cpp
    )

    if(NOT WIN32 STREQUAL "1")
        add_custom_target(
            format
            COMMAND ${CMAKE_BINARY_DIR}/bin/astyle ${ASTYLE_ARGS}
            COMMENT "running astyle"
        )
    else()
        add_custom_target(
            format
            COMMAND ${CMAKE_BINARY_DIR}/bin/astyle.exe ${ASTYLE_ARGS}
            COMMENT "running astyle"
        )
    endif()

endif()
