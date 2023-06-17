cmake_minimum_required(VERSION 3.26.3)
set (CMAKE_CXX_STANDARD 14)

project(mos_tech_6502)
set(mos_tech_6502_MAJOR_VERSION 0)
set(mos_tech_6502_MINOR_VERSION 1)
set(mos_tech_6502_PATCH_VERSION 0.dev)
set(mos_tech_6502_VERSION "${mos_tech_6502_MAJOR_VERSION}
                                .${mos_tech_6502_MINOR_VERSION}
                                .${mos_tech_6502_PATCH_VERSION}")

#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/dist)
#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(examples)

#option(TEST "Run testing suite" ON)

#if(TEST)
#    add_subdirectory(testing)
#endif()