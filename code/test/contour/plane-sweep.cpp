#include "catch2/catch.hpp"

#include "k-regret/contour/plane-sweep.h"

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
}
