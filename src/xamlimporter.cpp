#include "xamlimporter.hpp"
#include <iostream>
#include <string_view>
#include <yoga/Yoga.h>
#include "checkbox.hpp"
#include "combobox.hpp"
#include "dialogex.hpp"
#include "edittext.hpp"
#include "groupbox.hpp"
#include "listbox.hpp"
#include "ltext.hpp"
#include "pushbutton.hpp"
#include "radiobutton.hpp"
#include "stackpanel.hpp"

YGNodeRef xamlimporter::import(const std::filesystem::path& path) {
  pugi::xml_document doc;
  auto result = doc.load_file(path.c_str());
  if (!result)
    throw std::runtime_error(result.description());

  auto root_node = YGNodeNew();
  if (!process_xaml(doc.document_element(), root_node)) {
    YGNodeFree(root_node);
    throw std::runtime_error("xaml parsing failed");
  }
  
  return root_node;
}

bool xamlimporter::process_xaml(const pugi::xml_node& xaml, YGNodeRef node) {
  std::unique_ptr<nodecontext> context;
  std::string_view name{ xaml.name() };
  if (name == "Window")
    context = std::make_unique<dialogex>(node);
  else if (name == "StackPanel")
    context = std::make_unique<stackpanel>(node);
  else if (name == "Button")
    context = std::make_unique<pushbutton>(node);
  else if (name == "CheckBox")
    context = std::make_unique<checkbox>(node);
  else if (name == "ComboBox")
    context = std::make_unique<combobox>(node);
  else if (name == "GroupBox")
    context = std::make_unique<groupbox>(node);
  else if (name == "ListBox")
    context = std::make_unique<listbox>(node);
  else if (name == "Label")
    context = std::make_unique<ltext>(node);
  else if (name == "RadioButton")
    context = std::make_unique<radiobutton>(node);
  else if (name == "TextBox")
    context = std::make_unique<edittext>(node);
  else {
    std::cerr << std::format("unrecognised tag: {}\n", name);
    return false;
  }

  context->process_xaml(xaml);
  contexts_.push_back(std::move(context));

  for (auto& xml_node_child : xaml.children()) {
    auto child = YGNodeNew();

    if (process_xaml(xml_node_child, child)) {
      auto child_index = YGNodeGetChildCount(node);
      YGNodeInsertChild(node, child, child_index);
    } else {
      YGNodeFree(child);
    }
  }

  return true;
}
