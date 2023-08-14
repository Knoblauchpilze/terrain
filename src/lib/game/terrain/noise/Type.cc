
#include "Type.hh"

namespace pge::noise {

auto str(const Type &type) noexcept -> std::string
{
  switch (type)
  {
    case Type::White:
      return "white";
    case Type::Value:
      return "value";
    default:
      return "unknown(" + std::to_string(static_cast<int>(type)) + ")";
  }
}

} // namespace pge::noise
