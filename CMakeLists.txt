cmake_minimum_required(VERSION 3.10)
project(UMon)


add_executable(UMon Main.cc ProgramArgument.cc UART.cc)

target_compile_features(UMon PRIVATE cxx_std_20)
target_compile_features(UMon PRIVATE cxx_noexcept)

if (WIN32)
    target_compile_definitions(UMon PRIVATE HAS_WINAPI=1)
else()
    message(FATAL_ERROR "Non Windows platform not supported yet")
endif()
