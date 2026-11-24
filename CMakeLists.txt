#Tell Cmake how to build the project

cmake_minimum_required(VERSION 3.20)

project(chess_console
    VERSION 0.1.0
    LANGUAGES CXX
)
include(CTest)
enable_testing()

set(CHESS_SOURCES
    src/board.cpp
    src/knight.cpp
    src/king.cpp
    src/rook.cpp
    src/queen.cpp
    src/bishop.cpp
    src/pawn.cpp
    src/chess_game.cpp
)
add_executable(chess_console
    src/main.cpp
    ${CHESS_SOURCES}
)

set_property(TARGET chess_console PROPERTY CXX_STANDARD 20)
target_include_directories(chess_console PRIVATE include)

# Unit tests
if(BUILD_TESTING)

    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.16.1
    )

    FetchContent_MakeAvailable(Catch2)

    add_executable(chess_tests
        tests/position_tests.cpp
        tests/board_tests.cpp
        tests/chess_game_tests.cpp
        ${CHESS_SOURCES}
    )

    set_property(TARGET chess_tests PROPERTY CXX_STANDARD 20)

    target_include_directories(chess_tests PRIVATE include)

    target_link_libraries(chess_tests PRIVATE Catch2::Catch2WithMain)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(chess_tests)

endif()
