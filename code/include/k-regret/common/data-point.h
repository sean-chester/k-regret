/**
 * @file
 * Typedefs for common data types using across all the algorithm implementations.
 */

#ifndef KREGRET_COMMON_DATA_POINT
#define KREGRET_COMMON_DATA_POINT

#include <cstddef>
#include <array>
#include <vector>

namespace kregret {

using Value = float;
using RegretRatio = float;
using DataPointId = uint32_t;

template < size_t D >
  using Point = std::array< Value, D >;

template < size_t D >
  struct DataPoint
  {
    DataPointId id;
    Point< D > coords;
  };

template < size_t D >
  using Dataset = std::vector< DataPoint< D > >;

} // namespace kregret


#endif // KREGRET_COMMON_DATA_POINT
