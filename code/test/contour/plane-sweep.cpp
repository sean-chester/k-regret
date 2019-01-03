#include "catch2/catch.hpp"

#include "k-regret/contour/plane-sweep.h"

namespace { // anonymous

template < typename T >
std::ostream &
  operator << ( std::ostream & stream, std::vector< T > const& vec )
  {
    stream << "«";
    for( T const& element : vec ) stream << element << " ";
    return stream << "»";
  }

} // namespace anonymous

SCENARIO( "The plane sweep processes its event points", "[contour][geometry][2d][plane-sweep]")
{
  using namespace kregret::Contour;

  GIVEN( "A set of two 2d points with coincident dual lines" )
  {
    kregret::Dataset< 2 > data{
      { 1, { 0.25f, 0.75f } },
      { 2, { 0.25f, 0.75f } }
    };

    WHEN( "The plane sweep algorithm processes those points" )
    {
      RadialPlaneSweep sweep( data, 2 );
      sweep.initialise();

      THEN( "The sweep has no events to process" )
      {
        REQUIRE( sweep.is_done() == true );
      }
    }
  }

  GIVEN( "A set of three 2d points with non-parallel, non-coincident dual lines and non-contiguous ids" )
  {
    kregret::Dataset< 2 > basketball_players{
      { 1, { 1.00f, 0.66f } },
      { 3, { 0.77f, 0.77f } },
      { 5, { 0.68f, 1.00f } },
    };

    WHEN( "The plane sweep algorithm processes those points" )
    {
      RadialPlaneSweep sweep( basketball_players, 5 );
      sweep.initialise();
      REQUIRE( sweep.is_done() == false );

      THEN( "The sweep processes the three correct intersection points in the correct order" )
      {
        std::vector< Intersection > result;
        std::vector< Intersection > solution{
          Intersection{ 3, 5 }, // @ (0.72f, 0.28f)
          Intersection{ 1, 5 }, // @ (0.52f, 0.48f)
          Intersection{ 1, 3 }  // @ (0.32f, 0.68f)
        };

        while( ! sweep.is_done() )
        {
          sweep.process_next_event( [ &result ]( auto const& event ){ result.push_back( event ); } );
        }
        CHECK( result == solution );
      }
    }
  }
}
