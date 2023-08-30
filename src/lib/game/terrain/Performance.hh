
#pragma once

#include <chrono>

namespace pge::terrain {

struct Performance
{
  int64_t heightDuration{0};
  int64_t atDuration{0};

  int64_t areaDuration{0};
  int64_t generateForDuration{0};
  int64_t interpolateDuration{0};
  int64_t normalizeDuration{0};

  int64_t modulusDuration{0};
  int64_t permDuration{0};
  int64_t gradDuration{0};

  int64_t steps{0};
};

} // namespace pge::terrain
