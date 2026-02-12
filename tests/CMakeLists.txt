function(add_output_test name input expected)
  add_test(
    NAME ${name}
    COMMAND ${CMAKE_COMMAND}
      -D exe=$<TARGET_FILE:xaml2rc>
      -D input=${input}
      -D expected=${expected}
      -P compare_output.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  )
endfunction()

add_output_test(
  AlignmentTest
    alignment_test.xaml
    alignment_expected.rc
)

add_output_test(
  GridTest
    grid_test.xaml
    grid_expected.rc
)
