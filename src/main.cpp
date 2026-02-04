#include <cstdlib>
#include <iostream>
#include <ostream>
#include <yoga/Yoga.h>
#include "xamlimporter.hpp"
#include "resource.hpp"
#include "dialogex.hpp"
#include "fontmetrics.hpp"

void output_nodes(YGNodeRef node, std::ostream& os) {
  auto c = reinterpret_cast<resource*>(YGNodeGetContext(node));
  if (c)
    c->output(node, os);

  auto child_count = YGNodeGetChildCount(node);
  if (child_count > 1)
    os << "BEGIN\n";

  for (size_t i = 0; i < child_count; i++)
    output_nodes(YGNodeGetChild(node, i), os);

  if (child_count > 1)
    os << "END\n";
}

void init_font_metrics(YGNodeRef root) {
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

  font_metrics::instance().initialise(dialog->font_face().c_str(), dialog->font_size(), dialog->font_weight(), dialog->font_italic(), dialog->font_char_set());
}

int main(int argc, char** argv) {
  try {
    xamlimporter importer;
    auto [root, resources] = importer.import(argv[1]);

    init_font_metrics(root);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    output_nodes(root, std::cout);

    return EXIT_SUCCESS;

  } catch (const std::exception& e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }
}
