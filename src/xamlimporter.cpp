#include "xamlimporter.hpp"
#include <string_view>
#include <yoga/Yoga.h>
#include "dialogex.hpp"
#include "flexibox.hpp"
#include "pushbutton.hpp"

using namespace std::string_view_literals;

std::tuple<YGNodeRef, std::vector<std::unique_ptr<control>>> xamlimporter::import(const std::filesystem::path& path) {
  pugi::xml_document doc;
  auto result = doc.load_file(path.c_str());
  if (!result)
    throw std::runtime_error(result.description());

  std::vector<std::unique_ptr<control>> controls;
  auto root_node = parse_xaml(doc.document_element(), {}, controls);

  return std::make_tuple(root_node, std::move(controls));
}

YGNodeRef xamlimporter::parse_xaml(const pugi::xml_node& xaml, std::optional<YGNodeRef> parent, std::vector<std::unique_ptr<control>>& controls) {
  YGNodeRef node{};

  std::string_view name{ xaml.name() };
  if (name == "Window"sv)
    node = parse_control<dialogex>(xaml, parent, controls);
  else if (name == "StackPanel"sv)
    node = parse_control<flexibox>(xaml, parent, controls);
  else if (name == "Button"sv)
    node = parse_control<pushbutton>(xaml, parent, controls);
  else
    return {};

  for (auto& xml_node_child : xaml.children())
    parse_xaml(xml_node_child, node, controls);

  return node;
}
