add_executable(
  unit_tests
    unitTests.cpp
    brute-force/black-box.cpp
)

target_link_libraries( 
  unit_tests
    brute-force
    gcov
)

target_compile_options(
  unit_tests
    PRIVATE --coverage
)
