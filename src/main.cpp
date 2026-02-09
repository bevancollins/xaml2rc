#include <cstdlib>
#include <iostream>
#include <ostream>
#include <yoga/Yoga.h>
#include "xamlimporter.hpp"
#include "resource.hpp"

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

int main(int argc, char** argv) {
  try {
    xamlimporter importer;
    auto [root, resources] = importer.import(argv[1]);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    output_nodes(root, std::cout);

    return EXIT_SUCCESS;

  } catch (const std::exception& e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }
}
