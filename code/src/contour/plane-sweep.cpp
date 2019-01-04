#include "k-regret/contour/plane-sweep.hpp"

#include <algorithm> // std::sort

namespace kregret {
namespace Contour {
namespace { // anonymous

struct
  compare_points_by_xcoord
  {
    template < typename Point >
    bool
      operator() ( Point const& p, Point const& q ) const
      {
        return p.coords[ 0 ] > q.coords[ 0 ];
      }
  };

template < typename PointList >
void
  sort_points( PointList & points )
  {
    std::sort( points.begin(), points.end(), compare_points_by_xcoord() );
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
    q.insert( { angle, point_ids } );
  }


template < typename EventList >
void
  add_single_event( EventList & event_q, DataPoint< 2 > const p, DataPoint< 2 > const q, geom::Angle const cur_pos )
  {
    auto const intersection_point = geom::dual_line_intersection( p.coords, q.coords );
    if( intersection_point.has_value() )
    {
      auto const intersection_angle = geom::arctan_angle( intersection_point.value() );
      if( intersection_angle.has_value() )
      {
        if( intersection_angle.value() > cur_pos )
        {
          push_on_queue( event_q, intersection_angle.value(), { p.id, q.id } );
        }
        // else intersection is stuck in the past, maaaannnn....
      }
      //else intersection point is on y-axis: event point not used
    }
    // else lines were parallel or coincident: did not create an event point
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
      add_single_event( event_q, point_i, point_j, 0.0f ); // responsibility (b)
    }
    set_pointer( point_to_index, sort_order[ n - 1 ].id, n - 1 ); // handle last pointer (a): no corresponding event (b)
  }

template < typename Event, template< typename > typename EventContainer >
Event
  pop_front_off_queue( EventContainer< Event > & event_queue )
  {
    auto next_event = *event_queue.begin();
    event_queue.erase( event_queue.begin() );
    return next_event;
  }

/** Swaps the position in the sort order of the specified point ids, then updates their pointers */
template < typename Order, typename Map >
void
  swap( Order & sort_order, Map & pointers, Intersection const& point_ids )
  {
    std::swap( sort_order[ pointers[ point_ids.i ] ], sort_order[ pointers[ point_ids.j ] ] );
    std::swap( pointers[ point_ids.i ], pointers[ point_ids.j ] );
  }


template < typename Order, typename Map, typename Event, template< typename > typename EventContainer  >
void
  add_events( EventContainer< Event > & event_q, Order const& sorted_points, Map const& pointers, Event const& prev_event )
  {
    auto const point_i = std::next( sorted_points.cbegin(), pointers[ prev_event.point_ids.i ] );
    auto const point_j = std::next( sorted_points.cbegin(), pointers[ prev_event.point_ids.j ] );

    if( point_i < sorted_points.cend() - 1 )
    {
      add_single_event( event_q, *point_i, *( point_i + 1 ), prev_event.angle );
    }
    if( point_j > sorted_points.cbegin() )
    {
      add_single_event( event_q, *( point_j - 1 ), *point_j, prev_event.angle );
    }
  }

} // namespace anonymous



Intersection
  RadialPlaneSweep::advance()
  {
    auto const event = pop_front_off_queue( event_q );
    swap( sorted_points, unsorted_points, event.point_ids );
    add_events( event_q, sorted_points, unsorted_points, event );
    return event.point_ids;
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
