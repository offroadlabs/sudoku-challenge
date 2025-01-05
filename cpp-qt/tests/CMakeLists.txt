enable_testing()

add_executable(sudoku_tests
    sudoku_test.cpp
    ${CMAKE_SOURCE_DIR}/src/core/sudoku.cpp
)

target_include_directories(sudoku_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(sudoku_tests
    PRIVATE
    GTest::gtest_main
    Qt6::Core
)

target_compile_options(sudoku_tests PRIVATE -g)

include(GoogleTest)
gtest_discover_tests(sudoku_tests) 