execute_process(
  COMMAND ${exe} ${input}
  OUTPUT_VARIABLE actual_output
  RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
  message(FATAL_ERROR "program failed with code ${result}")
endif()

file(READ "${expected}" expected_output)

if(NOT actual_output STREQUAL expected_output)
  message(FATAL_ERROR
    "output mismatch\n\n=== expected ===\n${expected_output}\n\n=== actual ===\n${actual_output}"
  )
endif()
