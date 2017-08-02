cmake_minimum_required(VERSION 2.8.12)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
    if(POLICY CMP0020)
        cmake_policy(SET CMP0020 NEW)
    endif(POLICY CMP0020)
endif(COMMAND cmake_policy)

if(CMAKE_COMPILER_IS_GNUC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif()

project(OpenSIFT)
enable_language(C)
find_package(Doxygen)
find_package(OpenCV)
find_package(GTK2)
find_package(Threads)

if(DOXYGEN_FOUND)
    add_custom_target(docs ALL
        ${DOXYGEN_EXECUTABLE} Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    install(DIRECTORY docs/html DESTINATION share/opensift/docs
        FILES_MATCHING PATTERN "*")
endif()

add_subdirectory(src)
