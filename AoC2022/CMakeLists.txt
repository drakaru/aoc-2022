cmake_minimum_required (VERSION 3.21)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(COMMON_SOURCE
        common/aoc.h
        common/aoc_time.h
        common/aoc_time.cpp
        )

function(add_day name)
    add_executable(${name} ${name}.cpp ${COMMON_SOURCE})
    set_property(TARGET ${name} PROPERTY CXX_STANDARD 23)

    target_compile_options(${name} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Wconversion>
    )

    add_custom_command(
        TARGET ${name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/${name}.txt
        ${CMAKE_CURRENT_BINARY_DIR}/${name}.txt
    )
endfunction()

add_day ("day01")
add_day ("day02")
add_day ("day03")
add_day ("day04")
add_day ("day05")
add_day ("day06")
add_day ("day07")
add_day ("day08")
add_day ("day09")
add_day ("day10")
#add_day ("day11")
#add_day ("day12")
#add_day ("day13")
#add_day ("day14")
#add_day ("day15")
#add_day ("day16")
#add_day ("day17")
#add_day ("day18")
#add_day ("day19")
#add_day ("day20")
#add_day ("day21")
#add_day ("day22")
#add_day ("day23")
#add_day ("day24")
#add_day ("day25")
