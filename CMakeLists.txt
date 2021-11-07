cmake_minimum_required(VERSION 3.16)
project(pg_valid)
set(CMAKE_C_STANDARD 99)

find_package(ICU REQUIRED uc io)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -m64 -mfpmath=sse -march=native -ftree-vectorize -msse2 -msse3 -msse4 -msse4.1 -msse4.2 -mavx -mavx2")

set(C_FILES
        ${PROJECT_SOURCE_DIR}/src/alpha_case.c
        ${PROJECT_SOURCE_DIR}/src/alpha.c
        ${PROJECT_SOURCE_DIR}/src/email.c
        ${PROJECT_SOURCE_DIR}/src/html.c
        ${PROJECT_SOURCE_DIR}/src/ws.c
)

file(GLOB C_TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.c)

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/test ${ICU_INCLUDE_DIRS})
link_directories(${ICU_LIBRARY_DIRS})

add_executable(pg_valid_test ${C_FILES} ${C_TEST_FILES})
target_link_libraries(pg_valid_test ${ICU_LIBRARIES})
