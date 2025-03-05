cmake_minimum_required(VERSION 3.25.2)
project(Steno)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1

)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(SFML)


add_executable(Steno main.cpp BMP.cpp PNG.cpp share.cpp)
target_link_libraries(Steno fmt)
target_link_libraries(Steno sfml-graphics)