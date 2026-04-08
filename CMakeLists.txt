cmake_minimum_required(VERSION 3.20)
project(
        RadarSignalProcessor
        VERSION 1.0
        DESCRIPTION "Library for radar signal processing"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(
        googlebenchmark
        URL https://github.com/google/benchmark/archive/refs/tags/v1.8.0.zip
)
FetchContent_Declare(
        spdlog
        URL https://github.com/gabime/spdlog/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest googlebenchmark spdlog)

add_library(radar_core
        src/FFT.cpp
        src/PeakDetector.cpp
        src/Processor.cpp
        src/SignalSource.cpp
        src/Validator.cpp
        src/DataExporter.cpp
)

target_include_directories(radar_core PUBLIC include)

if (MSVC)
    target_compile_options(radar_core PRIVATE /W4 /WX)
else()
    target_compile_options(radar_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(RadarSignalProcessor src/main.cpp)
target_link_libraries(radar_core PUBLIC spdlog::spdlog)
target_link_libraries(RadarSignalProcessor PRIVATE radar_core)

if(BUILD_TESTS)
    enable_testing()
    add_executable(RadarTests tests/radar_test.cpp)
    target_link_libraries(RadarTests PRIVATE radar_core gtest gmock gtest_main)
    include(GoogleTest)
    gtest_discover_tests(RadarTests)
endif()

if(BUILD_BENCHMARKS)
    add_executable(RadarBenchmark bench/benchmark_main.cpp)
    target_link_libraries(RadarBenchmark PRIVATE radar_core benchmark benchmark::benchmark_main)
endif()