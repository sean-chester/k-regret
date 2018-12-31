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
using DataPointId = size_t;

template < size_t D >
  using Point = std::array< Value, D >;

template < size_t D >
  using DataPoint = std::pair< DataPointId, Point< D > >;

template < size_t D >
  using Dataset = std::vector< DataPoint< D > >;

} // namespace kregret


#endif // KREGRET_COMMON_DATA_POINT
