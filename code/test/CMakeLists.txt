add_executable(
  unit_tests
    unitTests.cpp
    contour/black-box.cpp
    contour/geometry.cpp
    contour/plane-sweep.cpp
)

target_link_libraries( 
  unit_tests
    contour
    gcov
)

target_compile_options(
  unit_tests
    PRIVATE --coverage
)
