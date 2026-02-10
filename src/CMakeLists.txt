find_package(pugixml CONFIG REQUIRED)
find_package(wil CONFIG REQUIRED)
find_package(yoga CONFIG REQUIRED)

add_executable(xaml2rc
  checkbox.cpp
  checkbox.hpp
  common_text_control.cpp
  common_text_control.hpp
  dialogex.cpp
  dialogex.hpp
  edittext.cpp
  edittext.hpp
  fontmetrics.cpp
  fontmetrics.hpp
  ltext.cpp
  ltext.hpp
  main.cpp
  pushbutton.cpp
  pushbutton.hpp
  resource.cpp
  resource.hpp
  stackpanel.cpp
  stackpanel.hpp
  xamlimporter.cpp
  xamlimporter.hpp
)

target_compile_features(xaml2rc
  PRIVATE
    cxx_std_23
)

target_compile_definitions(xaml2rc
  PRIVATE
    NOMINMAX
)

target_link_libraries(xaml2rc
  PRIVATE
    pugixml::pugixml
    yoga::yogacore
    WIL::WIL
)
