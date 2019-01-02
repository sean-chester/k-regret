/**
 * @file
 * Geometric operations on points
 */

#ifndef KREGRET_COMMON_GEOMETRY
#define KREGRET_COMMON_GEOMETRY

#include <optional>

#include "k-regret/common/data-point.h"

namespace kregret {
namespace geom{

/**
 * Given two 2d points, calculates the intersection point of their dual lines. Returns
 * std::nullopt if the lines are parallel (or coincident); i.e., have no unique
 * intersection point.
 */
std::optional< Point< 2 > > dual_line_intersection( Point< 2 > const a, Point< 2 > const b )
{
  auto const y_diff = a[ 1 ] - b[ 1 ];
  auto const shift = b[ 0 ] * b[ 1 ] - a[ 0 ] * a[ 1 ];

  if( shift == 0 ) /* parallel or coincident */ 
  {
    return std::nullopt;
  }
  else if( a[ 1 ] == 0 ) /* easy case: dual line of a is vertical */
  {
    return Point< 2 >{ ( 1.0f - b[ 0 ] * a[ 0 ] ) / b [ 1 ], 0.0f };
  }

  auto const x = y_diff / shift;
  return Point< 2 >{
    x,
    ( 1.0f - a[ 0 ] * x ) / a [ 1 ]
  };
}

} // namespace geom
} // namespace kregret


#endif // KREGRET_COMMON_GEOMETRY
