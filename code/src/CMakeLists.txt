add_subdirectory( contour )
# add_subdirectory( common )

add_executable(
  k-regret
    main.cpp
)

set_target_properties(
  k-regret
    PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY "../lib/"
      LIBRARY_OUTPUT_DIRECTORY "../lib/"
      RUNTIME_OUTPUT_DIRECTORY "../"
)

target_link_libraries(
  k-regret
    ${Boost_LIBRARIES}
    contour
#    common
)
