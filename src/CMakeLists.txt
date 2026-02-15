find_package(pugixml CONFIG REQUIRED)
find_package(wil CONFIG REQUIRED)
find_package(yoga CONFIG REQUIRED)

add_executable(xaml2rc
  checkbox.cpp
  checkbox.hpp
  combobox.cpp
  combobox.hpp
  debugoutput.cpp
  debugoutput.hpp
  dialogex.cpp
  dialogex.hpp
  edittext.cpp
  edittext.hpp
  fontmetrics.cpp
  fontmetrics.hpp
  groupbox.cpp
  groupbox.hpp
  listbox.cpp
  listbox.hpp
  ltext.cpp
  ltext.hpp
  main.cpp
  nodecontext.cpp
  nodecontext.hpp
  outputformat.hpp
  playgroundoutput.cpp
  playgroundoutput.hpp
  pushbutton.cpp
  pushbutton.hpp
  radiobutton.cpp
  radiobutton.hpp
  resource.cpp
  resource.hpp
  resourcescriptoutput.cpp
  resourcescriptoutput.hpp
  stackpanel.cpp
  stackpanel.hpp
  textwidget.cpp
  textwidget.hpp
  widget.cpp
  widget.hpp
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
