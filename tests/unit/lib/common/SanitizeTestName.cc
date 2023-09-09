
#include "SanitizeTestName.hh"

namespace pge::terrain {

auto sanitizeTestName(const std::string &in) -> std::string
{
  std::string out(in);

  std::replace(out.begin(), out.end(), '.', 'p');
  std::replace(out.begin(), out.end(), '-', 'm');

  return out;
}

} // namespace pge::terrain
