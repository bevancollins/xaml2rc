#pragma once

#include <array>
#include <ostream>
#include <string_view>
#include <string>
#include <vector>
#include <yoga/Yoga.h>
#include <pugixml.hpp>

class resource {
public:
  resource(YGNodeRef node);
  virtual ~resource() = default;

  virtual std::string_view resource_class() const = 0;
  virtual void process_xaml(const pugi::xml_node& xaml);
  virtual void output(std::ostream& os) const;
  virtual void measure(float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode);
  virtual void finalise_layout();

protected:
  void output_children(std::ostream& os) const;
  std::string x() const;
  std::string y() const;
  std::string width() const;
  std::string height() const;
  std::string style() const;
  std::string extended_style() const;
  std::string join_strings(const std::vector<std::string>& strings) const;
  std::array<int, 4> parse_quad(std::string_view input);
  YGJustify parse_justify(std::string_view alignment) const;
  YGAlign parse_align(std::string_view alignment) const;

  YGNodeRef node_{};
  std::string id_{"-1"};
  std::vector<std::string> style_;
  std::vector<std::string> extended_style_;
};
