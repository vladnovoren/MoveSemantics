cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic

    -fno-elide-constructors

    -fsanitize=address
)

add_link_options(
    -fno-elide-constructors

    -fsanitize=address
)

project(MoveSemantics)

set(UTILITY_SOURCE src/con_logger.cpp
                   src/func_logger.cpp
                   src/ilogger.cpp
                   src/log_int.cpp
                   src/log_initer.cpp
                   src/html_logger.cpp
                   src/gv_logger.cpp
                   src/move_semantics.cpp)

add_library(utility STATIC ${UTILITY_SOURCE})

add_executable(move_overload src/move/overload.cpp)
target_link_libraries(move_overload PUBLIC utility)

add_executable(move_universal src/move/universal.cpp)
target_link_libraries(move_universal PUBLIC utility)

target_include_directories(utility PUBLIC include include/move)
