#include "xamlimporter.hpp"
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

using namespace std::string_view_literals;

std::tuple<YGNodeRef, std::vector<std::unique_ptr<resource>>> xamlimporter::import(const std::filesystem::path& path) {
  pugi::xml_document doc;
  auto result = doc.load_file(path.c_str());
  if (!result)
    throw std::runtime_error(result.description());

  std::vector<std::unique_ptr<resource>> resources;
  auto root_node = process_xaml(doc.document_element(), {}, resources);

  finalise_layout(root_node);

  return std::make_tuple(root_node, std::move(resources));
}

YGNodeRef xamlimporter::process_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent, std::vector<std::unique_ptr<resource>>& resources) {
  std::unique_ptr<resource> r;
  std::string_view name{ xaml.name() };
  if (name == "Window")
    r = std::make_unique<dialogex>();
  else if (name == "StackPanel")
    r = std::make_unique<stackpanel>();
  else if (name == "Button")
    r = std::make_unique<pushbutton>();
  else if (name == "CheckBox")
    r = std::make_unique<checkbox>();
  else if (name == "ComboBox")
    r = std::make_unique<combobox>();
  else if (name == "GroupBox")
    r = std::make_unique<groupbox>();
  else if (name == "ListBox")
    r = std::make_unique<listbox>();
  else if (name == "Label")
    r = std::make_unique<ltext>();
  else if (name == "RadioButton")
    r = std::make_unique<radiobutton>();
  else if (name == "TextBox")
    r = std::make_unique<edittext>();
  else
    return {};

  auto node = r->process_xaml(xaml, parent);
  resources.push_back(std::move(r));

  for (auto& xml_node_child : xaml.children())
    process_xaml(xml_node_child, node, resources);

  // nodes with children can't have a measure function
  auto child_count = YGNodeGetChildCount(node);
  if (!child_count) {
    YGNodeSetMeasureFunc(node, [](
          YGNodeConstRef node,
          float width,
          YGMeasureMode width_mode,
          float height,
          YGMeasureMode height_mode)->YGSize {
        auto r = reinterpret_cast<resource*>(YGNodeGetContext(node));
        if (r)
          r->measure(node, width, width_mode, height, height_mode);
        return {width, height};
      }
    );
  }

  return node;
}

void xamlimporter::finalise_layout(YGNodeRef node) {
  auto child_count = YGNodeGetChildCount(node);
  for (size_t i = 0; i < child_count; i++)
    finalise_layout(YGNodeGetChild(node, i));

  auto context = YGNodeGetContext(node);
  if (context)
    (reinterpret_cast<resource*>(context))->finalise_layout(node);
}
