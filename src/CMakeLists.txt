add_subdirectory(ch32v307)

target_include_directories(${MY_TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/application/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/os/inc
)

target_sources(${MY_TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/application/src/app_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/application/src/led.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/fifo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/fifos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/printf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/src/systick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/src/os_assert.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/src/os_cbk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/src/os_event.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/src/os_kernel.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/src/os_msgqueue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/src/os_sem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cocoos/src/os_task.c
)

target_link_options(${MY_TARGET} PRIVATE -T${LINKER_SCRIPT})
target_link_options(${MY_TARGET} PRIVATE -Wl,-Map=$<TARGET_FILE:${MY_TARGET}>.map)
target_link_libraries(${MY_TARGET} ${EXTERNAL_LIBRARIES})
