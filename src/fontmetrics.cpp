#include "fontmetrics.hpp"
#include <windows.h>
#include <cmath>
#include <system_error>
#include <wil/resource.h>

font_metrics& font_metrics::instance() {
  static font_metrics fm;
  return fm;
}

void font_metrics::initialise(const char* face, int size, int weight, bool italic, int char_set) {
  wil::unique_hdc hdc { CreateCompatibleDC(nullptr) };
  if (!hdc)
    throw std::system_error(GetLastError(), std::system_category());

  auto dpi_y = GetDeviceCaps(hdc.get(), LOGPIXELSY);
  auto height = -MulDiv(size, dpi_y, 72); // negative = character height

  wil::unique_hfont font { CreateFontA(
      height,
      0, 0, 0,
      weight,
      italic ? TRUE : FALSE,
      FALSE, FALSE, char_set,
      OUT_DEFAULT_PRECIS,
      CLIP_DEFAULT_PRECIS,
      CLEARTYPE_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE,
      face) };
  if (!font)
    throw std::system_error(GetLastError(), std::system_category());

  auto old = wil::SelectObject(hdc.get(), font.get());

  TEXTMETRICA tm{};
  if (!GetTextMetricsA(hdc.get(), &tm))
    throw std::system_error(GetLastError(), std::system_category());

  base_unit_x_ = tm.tmAveCharWidth;
  base_unit_y_ = tm.tmHeight;
}

int font_metrics::dip_to_dlu_x(float x) const {
  return std::lround((x * 4.0f) / base_unit_x_);
}

int font_metrics::dip_to_dlu_y(float y) const {
  return std::lround((y * 8.0f) / base_unit_y_);
}
