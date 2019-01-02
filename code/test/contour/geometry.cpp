#include "catch2/catch.hpp"

#include "k-regret/contour/geometry.h"

SCENARIO( "The intersection of dual lines is computed", "[contour][geometry][2d]")
{
  using namespace kregret;

  GIVEN( "Two two-dimensional points" )
  {
    Point< 2 > a, b;

    WHEN( "The points are identical" )
    {
      a = { 0.25f, 0.75f };
      b = a;

      /* For the purpose of this code, infinite and no intersection points are equivalent */
      THEN( "The intersection point does not exist" )
      {
        REQUIRE( ! geom::dual_line_intersection( a, b ).has_value() );
      }
    }

    WHEN( "The points are unique but the dual lines are parallel" )
    {
      a = { 0.25f, 0.125f };
      b = { 0.5f, 0.25f };

      THEN( "The intersection point does not exist" )
      {
        REQUIRE( ! geom::dual_line_intersection( a, b ).has_value() );
      }
    }

    WHEN( "The dual lines have a unique intersection point" )
    {
      a = { 0.25f, 0.75f };
      b = { 0.75f, 0.25f };

      THEN( "The intersection point is correctly computed" )
      {
        Point< 2 > const solution{ 1.0f, 1.0f };
        auto const result = geom::dual_line_intersection( a, b );

        REQUIRE( result.has_value() );
        CHECK( result.value() == solution );
      }
    }

    WHEN( "(Only) The first dual line is vertical (at x = 0.75)" )
    {
      a = { 0.75f, 0.0f };
      b = { 0.75f, 0.5f };

      THEN( "The intersection point is where the second line takes value x = 0.75" )
      {
        Point< 2 > const solution{ 0.75f, 0.875f };
        auto const result = geom::dual_line_intersection( a, b );

        REQUIRE( result.has_value() );
        CHECK( result.value() == solution );
      }
    }

    WHEN( "(Only) The second dual line is vertical (at x = 0.25)" )
    {
      a = { 0.875f, 0.625f };
      b = { 0.25f, 0.0f };

      THEN( "The intersection point is where the first line takes value x = 0.25" )
      {
        Point< 2 > const solution{ 0.25f, 1.25f };
        auto const result = geom::dual_line_intersection( a, b );

        REQUIRE( result.has_value() );
        CHECK( result.value() == solution );
      }
    }
  }
}
