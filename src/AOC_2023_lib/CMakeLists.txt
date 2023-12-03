set(CMAKE_CXX_STANDARD 23)

set(SOURCES days.hpp
        day1/part1.c
        day1/part2.c
        day2/part2.c
        day2/part1.c
        day2/line_process.asm
        day3/part1.c)
add_library(AOC_2023_lib STATIC ${SOURCES})

target_include_directories(AOC_2023_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(AOC_2023_lib PROPERTIES VERSION 1.0 SOVERSION 1)