target_sources(${TARGET_ELF} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ch32v30x_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core_riscv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/startup_ch32v30x.S
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interrupt_dispatch.S
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system_ch32v30x.c
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/ch32v30x_conf.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/ch32v30x_it.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/core_riscv.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/system_ch32v30x.h
)

target_include_directories(${TARGET_ELF} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

