cmake_minimum_required(VERSION 3.10)
project(SanitizerExample C)

# Compiler settings
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# Optional sanitizer flags
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=memory -fsanitize-memory-track-origins -fno-omit-frame-pointer")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

# Include directories
include_directories(include)

# Find PCRE and PCRE2 libraries
find_library(PCRE_LIBRARY NAMES pcre)
find_library(PCRE2_LIBRARY NAMES pcre2-8)

# Executables
add_executable(hello.exe src/hello.c)
target_link_libraries(hello.exe ${PCRE_LIBRARY} ${PCRE2_LIBRARY})

add_executable(leak-free.exe src/leak-free.c)
add_executable(leaky1.exe src/leaky1.c)
add_executable(leaky2.exe src/leaky2.c)
add_executable(leaky3.exe src/leaky3.c)

add_executable(pcre1-regex.exe src/pcre1-regex.c)
target_link_libraries(pcre1-regex.exe ${PCRE_LIBRARY})

add_executable(pcre2-regex.exe src/pcre2-regex.c)
target_link_libraries(pcre2-regex.exe ${PCRE2_LIBRARY})

# Clean target
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E rm -f *.o *.exe *.out
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning all generated files"
)