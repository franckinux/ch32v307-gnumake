add_subdirectory(bmsis)
add_subdirectory(ch32v307_hal)
add_subdirectory(cocoos)

target_include_directories(${TARGET_ELF} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/application/inc)
target_include_directories(${TARGET_ELF} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/drivers/inc)
target_include_directories(${TARGET_ELF} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/inc)

target_sources(${TARGET_ELF} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/application/src/app_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/application/src/led.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/fifo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/fifos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/printf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/systick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/config/startup_main.c
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/ld/link.ld)
target_link_options(${TARGET_ELF} PUBLIC -T${LINKER_SCRIPT})
target_link_options(${TARGET_ELF} PUBLIC -Wl,-Map=$<TARGET_FILE:${TARGET_ELF}>.map)
