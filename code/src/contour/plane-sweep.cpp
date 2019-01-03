#include "k-regret/contour/plane-sweep.h"

#include <algorithm> // std::sort

namespace kregret {
namespace Contour {
namespace // anonymous
{

struct compare_points_by_angle
{
  template < typename Point >
  bool
    operator() ( Point const& p, Point const& q ) const
    {
      auto const angle_p = geom::arctan_angle( p.coords );
      auto const angle_q = geom::arctan_angle( q.coords );

      if( angle_p.has_value() && angle_q.has_value() ) { return angle_p.value() < angle_q.value(); }
      else if( angle_p.has_value() ) { return true; } /* q is vertical: last possible event point */
      else { return false; } /* p is vertical: last possible event point */
    }
};

template < typename PointList >
void
  sort_points( PointList & points )
  {
    std::sort( points.begin(), points.end(), compare_points_by_angle{} );
  }

template < typename Map >
void
  set_pointer( Map & pointers, DataPointId const point_id, PointIndex const index )
  {
    assert( point_id < pointers.size() );
    pointers[ point_id ] = index;
  }

template < typename Queue >
void
  push_on_queue( Queue & q, geom::Angle const angle, Intersection const point_ids )
  {
    q.push_back( { angle, point_ids } );
  }


template < typename Order, typename Map, typename Queue >
void
  set_point_indexes_and_populate_q( Order const& sort_order, Map & point_to_index, Queue & event_q )
  {
    auto const n = sort_order.size();
    if( n == 0 ) { return; }

    // Note: Two responsibilities for this loop:
    // a) iterate all sorted points and set the pointer from their id to their index in sort_order
    // b) populate the event queue with the intersection points of all adjacent points
    for( PointIndex i = 0; i < n - 1; ++i )
    {
      auto const& point_i = sort_order[ i ];
      auto const& point_j = sort_order[ i + 1 ];

      set_pointer( point_to_index, point_i.id, i ); // responsibility (a)

      auto const intersection_point = geom::dual_line_intersection( point_i.coords, point_j.coords );
      if( intersection_point.has_value() )
      {
        auto const intersection_angle = geom::arctan_angle( intersection_point.value() );
        if( intersection_angle.has_value() )
        {
          push_on_queue( event_q, intersection_angle.value(), { point_i.id, point_j.id } ); // responsibility (b)
        }
        //else intersection point is on y-axis: event point not used
      }
      // else lines were parallel or coincident: did not create an event point
    }
    set_pointer( point_to_index, sort_order[ n - 1 ].id, n - 1 ); // handle last pointer (a): no corresponding event (b)
  }


} // namespace anonymous



Intersection
  RadialPlaneSweep::advance()
  {
    return { 0, 0 };
  }

bool
  RadialPlaneSweep::is_done() const
  {
    return event_q.empty();
  }

void
  RadialPlaneSweep::initialise()
  {
    sort_points( sorted_points );
    set_point_indexes_and_populate_q( sorted_points, unsorted_points, event_q );
  }

} // namespace Contour
} // namespace kregret
