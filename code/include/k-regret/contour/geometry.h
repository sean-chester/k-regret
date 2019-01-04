/**
 * @file
 * Geometric operations on points
 */

#ifndef KREGRET_COMMON_GEOMETRY
#define KREGRET_COMMON_GEOMETRY

#include <optional>
#include <cassert>

#include "k-regret/common/data-point.h"

namespace kregret {
namespace geom{

using Angle = float;

/** Calculates the arctan of the angle given by vector p */
inline
std::optional< Angle >
  arctan_angle( Point< 2 > const p )
  {
    if( p[ 0 ] == 0.0f ) { return std::nullopt; }
    return p[ 1 ] / p[ 0 ];
  }

/**
 * Given two 2d points, calculates the intersection point of their dual lines. Returns
 * std::nullopt if the lines are parallel (or coincident); i.e., have no unique
 * intersection point.
 */
inline
std::optional< Point< 2 > >
  dual_line_intersection( Point< 2 > const a, Point< 2 > const b )
  {
    auto const shift = a[ 0 ] * b[ 1 ] - b[ 0 ] * a[ 1 ];

    if( shift == 0 ) /* parallel or coincident */ 
    {
      return std::nullopt;
    }
    else if( a[ 1 ] == 0 ) /* easy case: dual line of a is vertical */
    {
      assert( b[ 1 ] != 0.0f );
      return Point< 2 >{ a[ 0 ], ( 1.0f - b[ 0 ] * a[ 0 ] ) / b [ 1 ] };
    }
    else if( b[ 1 ] == 0 ) /* another easy case: dual line of b is vertical */
    {
      assert( a[ 1 ] != 0.0f );
      return Point< 2 >{ b[ 0 ], ( 1.0f - a[ 0 ] * b[ 0 ] ) / a [ 1 ] };
    }
    else
    {
      auto const y_diff = b[ 1 ] - a[ 1 ];
      auto const x = y_diff / shift;
      auto const y = ( 1.0f - a[ 0 ] * x ) / a [ 1 ];

      return Point< 2 >{ x, y };
    }
  }

} // namespace geom
} // namespace kregret


#endif // KREGRET_COMMON_GEOMETRY
