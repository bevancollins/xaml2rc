#include <windows.h>
#include <iostream>
#include <ostream>
#include <yoga/Yoga.h>
#include <wil/resource.h>
#include "xamlimporter.hpp"
#include "resource.hpp"
#include "dialogex.hpp"

void output_nodes(YGNodeRef node, const resource::font_metrics& fm, std::ostream& os) {
  auto c = reinterpret_cast<resource*>(YGNodeGetContext(node));
  if (c)
    c->output(node, fm, os);

  auto child_count = YGNodeGetChildCount(node);
  if (child_count > 1)
    os << "BEGIN\n";

  for (size_t i = 0; i < child_count; i++)
    output_nodes(YGNodeGetChild(node, i), fm, os);

  if (child_count > 1)
    os << "END\n";
}

resource::font_metrics get_font_metrics(YGNodeRef root) {
  // the root node should be for the dialogex
  dialogex* dialog{};
  auto root_context = YGNodeGetContext(root);
  if (root_context) {
    auto r = reinterpret_cast<resource*>(root_context);
    if (r->resource_class() == "DIALOGEX")
      dialog = reinterpret_cast<dialogex*>(r);
  }
  if (!dialog)
    throw std::runtime_error("unable to locate DIALOGEX");

  wil::unique_hdc hdc { CreateCompatibleDC(nullptr) };
  if (!hdc)
    throw std::system_error(GetLastError(), std::system_category());

  auto dpi_y = GetDeviceCaps(hdc.get(), LOGPIXELSY);
  auto height = -MulDiv(dialog->font_size(), dpi_y, 72); // negative = character height

  wil::unique_hfont font { CreateFontA(
      height,
      0, 0, 0,
      dialog->font_weight(),
      dialog->font_italic() ? TRUE : FALSE,
      FALSE, FALSE, dialog->font_char_set(),
      OUT_DEFAULT_PRECIS,
      CLIP_DEFAULT_PRECIS,
      CLEARTYPE_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE,
      dialog->font_face().c_str()) };
  if (!font)
    throw std::system_error(GetLastError(), std::system_category());

  auto old = wil::SelectObject(hdc.get(), font.get());

  TEXTMETRICA tm{};
  if (!GetTextMetricsA(hdc.get(), &tm))
    throw std::system_error(GetLastError(), std::system_category());

  return {tm.tmAveCharWidth, tm.tmHeight};
}

int main(int argc, char** argv) {
  try {
    xamlimporter importer;
    auto [root, resources] = importer.import(argv[1]);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    auto fm = get_font_metrics(root);
    output_nodes(root, fm, std::cout);

    return EXIT_SUCCESS;

  } catch (const std::exception& e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }
}
