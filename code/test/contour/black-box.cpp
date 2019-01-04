#include "catch2/catch.hpp"

#include "k-regret/contour/regret-solver-2d.hpp"
#include "k-regret/common/solution.hpp"

SCENARIO( "The contour algorithm is black-box tested on a 2d toy example", "[contour][toy][black-box][2d]")
{
  using namespace kregret;

  GIVEN( "A toy input of 5 2d points" )
  {
    Contour::Solver2d solve(
      {
        { 1, { 0.00f, 1.00f } },
        { 2, { 1.00f, 0.00f } },
        { 3, { 0.50f, 0.50f } },
        { 4, { 0.40f, 0.60f } },
        { 5, { 0.75f, 0.25f } }
      }
    );

    WHEN( "A of size solution >= 5 is requested" )
    {
      THEN( "All points (and extra zero-padding, if necessary) are returned" )
      {
        CHECK( solve(  5, 1 ) == Solution{ 1, 2, 3, 4, 5 } );
        CHECK( solve( 10, 1 ) == Solution{ 1, 2, 3, 4, 5, 0, 0, 0, 0, 0 } );
      }
    }

    WHEN( "Only 3 points should minimise regret with respect to top-1 choices" )
    {
      THEN( "The brute force method retrieves the three extreme points" )
      {
        CHECK( solve( 3, 1 ) == Solution{ 1, 2, 3 } );
      }
    }
  }

  // GIVEN( "The toy database example from Table 1 of Chester et al. (2014)" )
}
