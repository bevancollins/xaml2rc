#pragma once

#include <filesystem>
#include <memory>
#include <vector>
#include <pugixml.hpp>
#include "nodecontext.hpp"

class xamlimporter {
public:
  std::tuple<YGNodeRef, std::vector<std::unique_ptr<nodecontext>>> import(const std::filesystem::path& path);

private:
  bool process_xaml(const pugi::xml_node& xaml, YGNodeRef node, std::vector<std::unique_ptr<nodecontext>>& contexts);
  void finalise_layout(YGNodeRef node);
};
