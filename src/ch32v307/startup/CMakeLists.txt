target_sources(${MY_TARGET} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ch32v30x_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core_riscv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/startup_ch32v30x.S
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interrupt_dispatch.S
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system_ch32v30x.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/startup_main.c
)

target_include_directories(${MY_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

