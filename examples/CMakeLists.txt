add_executable(dummy_run dummy.cpp)
target_link_libraries(dummy_run mos_tech_6502)
target_include_directories(dummy_run PUBLIC ${PROJECT_SOURCE_DIR}/include)