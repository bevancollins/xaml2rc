#pragma once

#include <string_view>
#include <string>
#include <vector>
#include "nodecontext.hpp"

class resource : public nodecontext {
public:
  using nodecontext::nodecontext;
  virtual ~resource() = default;

  void process_xaml(const pugi::xml_node& xaml) override;
  void output(std::ostream& os) const override;

  virtual std::string_view resource_class() const = 0;
  virtual void measure(float& width, YGMeasureMode& width_mode, float& height, YGMeasureMode& height_mode);

protected:
  std::string x() const;
  std::string y() const;
  std::string width() const;
  std::string height() const;
  std::string style() const;
  std::string extended_style() const;
  std::string join_strings(const std::vector<std::string>& strings) const;

  std::string id_{"-1"};
  std::vector<std::string> style_;
  std::vector<std::string> extended_style_;
};
