find_package(yoga CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

add_executable(xaml2rc
  control.cpp
  control.hpp
  dialogex.cpp
  dialogex.hpp
  flexibox.cpp
  flexibox.hpp
  main.cpp
  pushbutton.cpp
  pushbutton.hpp
  xamlimporter.cpp
  xamlimporter.hpp
)

target_compile_features(xaml2rc
  PRIVATE
    cxx_std_20
)

target_link_libraries(xaml2rc
  PRIVATE
    yoga::yogacore
    pugixml::pugixml
)
