target_sources(${TARGET_ELF} PUBLIC
    systick.c
)

target_include_directories(${TARGET_ELF} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
