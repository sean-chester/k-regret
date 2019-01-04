/**
 * @file
 * Conducts a radial plane sweep over a collection of (dual) lines
 */

#ifndef KREGRET_COMMON_PLANE_SWEEP
#define KREGRET_COMMON_PLANE_SWEEP

#include <iostream> // std::ostream
#include <set>      // std::set

#include "k-regret/common/data-point.hpp"
#include "k-regret/contour/geometry.hpp"

namespace kregret {
namespace Contour{


using PointIndex = uint32_t;
using PointIndexMap = std::vector< PointIndex >;

struct Intersection
{
  DataPointId i;
  DataPointId j;

  bool operator == ( Intersection const& other ) const
  {
    return ( i == other.i && j == other.j )
        || ( j == other.i && i == other.j );
  }
  bool operator < ( Intersection const& other ) const
  {
    if( std::min( i, j ) == std::min( other.i, other.j ) )
    {
      return std::max( i, j ) < std::max( other.i, other.j );
    }
    else
    {
      return std::min( i, j ) < std::min( other.i, other.j );
    }
  }
};

class RadialPlaneSweep
{
  struct EventPoint
  {
    geom::Angle angle;
    Intersection point_ids;

    bool operator < ( EventPoint const& other ) const
    {
      if( angle == other.angle ) { return point_ids < other.point_ids; }
      return angle < other.angle;
    }
    bool operator == ( EventPoint const& other ) const
    {
      return angle == other.angle && point_ids == other.point_ids;
    }
  };

  // using an ordered set instead of a vector/heap because we need to check whether a given
  // event has already been inserted (don't want duplicate events), which is quite inefficient
  // in a non-sorted (e.g., "heapified") vector.
  using EventPointQ = std::set< EventPoint >;


  Dataset< 2 > sorted_points;
  PointIndexMap unsorted_points;
  EventPointQ event_q;

  Intersection advance();

public:
  RadialPlaneSweep( Dataset< 2 > const& input, PointIndex const max_point_id )
    : sorted_points( input ), unsorted_points( max_point_id + 1 ) {}
  ~RadialPlaneSweep() {}

  template < typename EventAction >
    void process_next_event( EventAction && event_action )
    {
      event_action( advance() );
    }

  bool is_done() const;
  void initialise();
};

inline
std::ostream &
  operator << ( std::ostream & stream, Intersection const& inter )
  {
    return stream << "(" << inter.i << ", " << inter.j << ")";
  }

} // namespace Contour
} // namespace kregret


#endif // KREGRET_COMMON_PLANE_SWEEP
