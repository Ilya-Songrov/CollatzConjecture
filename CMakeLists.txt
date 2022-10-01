cmake_minimum_required(VERSION 3.5)

project(CollatzConjecture LANGUAGES CXX)

add_definitions(-DAPPLICATION_NAME="${CMAKE_PROJECT_NAME}")
add_definitions(-DAPPLICATION_VERSION="2.0.0")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE "x86_64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(ARCHITECTURE "x86")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS_DEBUG} -DBUILD_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS_RELEASE} -DBUILD_RELEASE")
set(ROOT_FOLDER                     "${CMAKE_CURRENT_SOURCE_DIR}")
set(BIN_FOLDER                      "${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}_${ARCHITECTURE}")
set(BIN_DIR                         "${ROOT_FOLDER}/build/bin/${BIN_FOLDER}")
set(LIBS_DIR                        ${BIN_DIR})
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.71.0 REQUIRED COMPONENTS
    system
    program_options
    filesystem
    date_time
    context
    chrono
)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    ArgumentParser.hpp
    CollatzSequences/CollatzSequenceMath.hpp
    CollatzSequences/CollatzSequenceMath.cpp
)

message(STATUS "PROJECT_NAME:               ${PROJECT_NAME}")
message(STATUS "CMAKE_BUILD_TYPE:           ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_SOURCE_DIR:           ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_SYSTEM_NAME:          ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR:   ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "PROJECT_BINARY_DIR:         ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR:         ${PROJECT_SOURCE_DIR}")
message(STATUS "ARCHITECTURE:               ${ARCHITECTURE}")
message(STATUS "Boost_INCLUDE_DIRS:         ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES:            ${Boost_LIBRARIES}")
message(STATUS "ROOT_FOLDER:                ${ROOT_FOLDER}")
message(STATUS "BIN_FOLDER:                 ${BIN_FOLDER}")
message(STATUS "BIN_DIR:                    ${BIN_DIR}")
message(STATUS "LIBS_DIR:                   ${LIBS_DIR}")

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIBS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${LIBS_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    DEBUG_POSTFIX "_d"
)

link_directories(${LIBS_DIR})

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" AND "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    target_link_libraries(
        ${PROJECT_NAME}
        -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -Wl,-Bdynamic
        ${Boost_LIBRARIES}
    )
else()
    target_link_libraries(
        ${PROJECT_NAME}
        -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -Wl,-Bdynamic
        ${Boost_LIBRARIES}
    )
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstrict-aliasing -Wall -Wextra -Wno-comment -Wdouble-promotion -Wswitch-default -Wswitch-enum -Wuninitialized -Wstrict-aliasing -Wfloat-equal -Wshadow -Wplacement-new -Wcast-align -Wconversion -Wlogical-op")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wduplicated-branches -Wrestrict -Wnull-dereference -Wno-terminate")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_VERBOSE_MAKEFILE ON)
