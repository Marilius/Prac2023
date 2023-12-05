cmake_minimum_required(VERSION 3.16)
project(zadanie3)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        # last version
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Function lib/Factory.hpp lib/Function.hpp lib/Function.cpp lib/Root.hpp lib/Root.cpp)

set(SOURCE_EXE main.cpp)

add_library(zadanie3 ${Function})

add_executable(test lib/test/Factory_test.cpp lib/test/Functions_test.cpp lib/test/Operations_test.cpp lib/test/Root_test.cpp)
target_link_libraries(test zadanie3)
target_link_libraries(test gtest_main)
add_test(NAME test COMMAND test)

add_executable(main ${SOURCE_EXE})
target_link_libraries(main zadanie3) # Линковка программы с библиотекой
