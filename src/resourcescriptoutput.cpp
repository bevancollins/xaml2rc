#include "resourcescriptoutput.hpp"
#include "nodecontext.hpp"

void resource_script_output::output(YGNodeRef root, std::ostream& out) {
  auto context = reinterpret_cast<nodecontext*>(YGNodeGetContext(root));
  if (context)
    context->output(out);
}

