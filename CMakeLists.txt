cmake_minimum_required(VERSION 3.16.3)

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

set(MOVE_SEMANTICS_SOURCE src/con_logger.cpp
                   src/func_logger.cpp
                   src/ilogger.cpp
                   src/log_int.cpp
                   src/log_initer.cpp
                   src/html_logger.cpp
                   src/gv_logger.cpp
                   src/move_semantics.cpp)

add_executable(MoveSemantics ${MOVE_SEMANTICS_SOURCE} src/main.cpp)
target_include_directories(MoveSemantics PUBLIC include/)
