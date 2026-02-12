#include <cstdlib>
#include <iostream>
#include <ostream>
#include <fstream>
#include <yoga/Yoga.h>
#include "xamlimporter.hpp"
#include "nodecontext.hpp"

void output(YGNodeRef node, std::ostream& os) {
  auto c = reinterpret_cast<nodecontext*>(YGNodeGetContext(node));
  if (c)
    c->output(os);
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
    output(root, *out);

    return EXIT_SUCCESS;

  } catch (const std::exception& e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }
}
