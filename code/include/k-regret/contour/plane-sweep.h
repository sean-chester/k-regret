/**
 * @file
 * Conducts a radial plane sweep over a collection of (dual) lines
 */

#ifndef KREGRET_COMMON_PLANE_SWEEP
#define KREGRET_COMMON_PLANE_SWEEP

#include "k-regret/common/data-point.h"
#include "k-regret/contour/geometry.h"

namespace kregret {
namespace Contour{


using PointIndex = uint32_t;
using PointIndexMap = std::vector< PointIndex >;
using Intersection = std::pair< DataPointId, DataPointId >;

class RadialPlaneSweep
{
  struct EventPoint
  {
    geom::Angle angle;
    Intersection point_ids;
  };
  using EventPointQ = std::vector< EventPoint >;


  Dataset< 2 > sorted_points;
  PointIndexMap unsorted_points;
  EventPointQ event_q;

  Intersection advance();

public:
  RadialPlaneSweep( Dataset< 2 > const& input, PointIndex const max_point_id )
    : sorted_points( input ), unsorted_points( max_point_id + 1 ) { event_q.reserve( input.size() ); }
  ~RadialPlaneSweep() {}

  template < typename EventAction >
    void process_next_event( EventAction && event_action )
    {
      event_action( advance() );
    }

  bool is_done() const;
  void initialise();
};

} // namespace Contour
} // namespace kregret


#endif // KREGRET_COMMON_PLANE_SWEEP
