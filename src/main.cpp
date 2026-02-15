#include <iostream>
#include <ostream>
#include <print>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <yoga/Yoga.h>
#include "xamlimporter.hpp"
#include "nodecontext.hpp"
#include "resource.hpp"
#include "debugoutput.hpp"
#include "playgroundoutput.hpp"
#include "resourcescriptoutput.hpp"

int main(int argc, char** argv) {
  try {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string input_file;
    std::string output_file;
    std::string output_format = "resource-script";

    for (size_t i = 0; i < args.size(); ++i) {
      const auto& arg = args[i];
      if (arg == "--output-format") {
        if (i + 1 < args.size()) {
          output_format = args[++i];
        } else {
          std::cerr << "Error: --output-format requires an argument." << std::endl;
          return EXIT_FAILURE;
        }
      } else if (input_file.empty()) {
        input_file = arg;
      } else if (output_file.empty()) {
        output_file = arg;
      }
    }

    if (input_file.empty()) {
      std::cerr << "No input file specified." << std::endl;
      return EXIT_FAILURE;
    }

    xamlimporter importer;
    auto root = importer.import(input_file.c_str());

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    std::unique_ptr<class output_format> of;
    if (output_format == "debug")
      of = std::make_unique<debug_output>();
    else if (output_format == "playground")
      of = std::make_unique<playground_output>();
    else if (output_format == "resource-script")
      of = std::make_unique<resource_script_output>();
    else {
      std::cerr << "Unknown output format: " << output_format << std::endl;
      return EXIT_FAILURE;
    }

    std::ostream* out{};
    std::ofstream file_out;
    if (!output_file.empty()) {
      file_out.exceptions(std::ifstream::failbit);
      file_out.open(output_file);
      out = &file_out;
    } else {
      out = &std::cout;
    }

    of->output(root, *out);

    return EXIT_SUCCESS;

  } catch (const std::exception& e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }
}
