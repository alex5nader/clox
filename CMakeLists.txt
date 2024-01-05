cmake_minimum_required(VERSION 3.26.4)

project(THE_PROJECT C)


set(SOURCES
  src/main.c
)

add_executable(project ${SOURCES})

target_include_directories(project
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_property(TARGET project  PROPERTY C_STANDARD 99)
target_compile_options(project
  PRIVATE
    -Wall
    -Werror
    -Wextra
)

