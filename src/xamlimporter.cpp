#include "xamlimporter.hpp"
#include <string_view>
#include <yoga/Yoga.h>
#include "checkbox.hpp"
#include "dialogex.hpp"
#include "edittext.hpp"
#include "flexibox.hpp"
#include "ltext.hpp"
#include "pushbutton.hpp"

using namespace std::string_view_literals;

std::tuple<YGNodeRef, std::vector<std::unique_ptr<resource>>> xamlimporter::import(const std::filesystem::path& path) {
  pugi::xml_document doc;
  auto result = doc.load_file(path.c_str());
  if (!result)
    throw std::runtime_error(result.description());

  std::vector<std::unique_ptr<resource>> resources;
  auto root_node = parse_xaml(doc.document_element(), {}, resources);

  return std::make_tuple(root_node, std::move(resources));
}

YGNodeRef xamlimporter::parse_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent, std::vector<std::unique_ptr<resource>>& resources) {
  YGNodeRef node{};

  std::string_view name{ xaml.name() };
  if (name == "Window")
    node = parse_resource<dialogex>(xaml, parent, resources);
  else if (name == "StackPanel")
    node = parse_resource<flexibox>(xaml, parent, resources);
  else if (name == "Button")
    node = parse_resource<pushbutton>(xaml, parent, resources);
  else if (name == "CheckBox")
    node = parse_resource<checkbox>(xaml, parent, resources);
  else if (name == "Label")
    node = parse_resource<ltext>(xaml, parent, resources);
  else if (name == "TextBox")
    node = parse_resource<edittext>(xaml, parent, resources);
  else
    return {};

  for (auto& xml_node_child : xaml.children())
    parse_xaml(xml_node_child, node, resources);

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
          return r->measure(width, width_mode, height, height_mode);
        else
          return {width, height};
      }
    );
  }

  return node;
}
