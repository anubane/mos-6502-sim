add_library(mos_tech_6502 architecture.cpp
                          assembler.cpp
                          instructions.cpp
                          loader.cpp
                          memory.cpp
                          mos6502_exceptions.cpp
                          registers.cpp
)


target_include_directories(mos_tech_6502 PUBLIC ${PROJECT_SOURCE_DIR}/include)