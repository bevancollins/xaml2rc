#include <cstdlib>
#include <iostream>
#include <ostream>
#include <fstream>
#include <yoga/Yoga.h>
#include "xamlimporter.hpp"
#include "resource.hpp"

void to_rc(YGNodeRef node, std::ostream& os) {
  auto c = reinterpret_cast<resource*>(YGNodeGetContext(node));
  if (c)
    c->to_rc(node, os);

  auto child_count = YGNodeGetChildCount(node);
  if (child_count > 1)
    os << "BEGIN\n";

  for (size_t i = 0; i < child_count; i++)
    to_rc(YGNodeGetChild(node, i), os);

  if (child_count > 1)
    os << "END\n";
}

int main(int argc, char** argv) {
  try {
    xamlimporter importer;
    auto [root, resources] = importer.import(argv[1]);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    std::ostream* out{};
    std::ofstream file_out;
    if (argc >= 3) {
      file_out.exceptions(std::ifstream::failbit);
      file_out.open(argv[2]);
      out = &file_out;
    } else {
      out = &std::cout;
    }
    to_rc(root, *out);

    return EXIT_SUCCESS;

  } catch (const std::exception& e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }
}
