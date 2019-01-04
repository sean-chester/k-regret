/**
 * @file
 * Typedefs for common data types using across all the algorithm implementations.
 */

#ifndef KREGRET_COMMON_DATA_POINT
#define KREGRET_COMMON_DATA_POINT

#include <cstddef>  // uint32_t
#include <array>    // std::array
#include <vector>   // std::vector
#include <iostream> // std::ostream

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

inline
std::ostream &
  operator << ( std::ostream & stream, Point< 2 > const& p )
  {
    return stream << "«" << p[ 0 ] << " " << p[ 1 ] << "»";
  }

inline
std::ostream &
  operator << ( std::ostream & stream, DataPoint< 2 > const& p )
  {
    return stream << "(" << p.id << ", " << p.coords << ")";
  }

} // namespace kregret


#endif // KREGRET_COMMON_DATA_POINT
