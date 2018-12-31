#include "catch2/catch.hpp"

#include "k-regret/brute-force/regret-solver-2d.h"
#include "k-regret/common/solution.h"

SCENARIO( "The brute-force algorithm is black-box tested on a 2d toy example", "[brute-force][toy][black-box][2d]")
{
  using namespace kregret;

  GIVEN( "A toy input of 5 2d points" )
  {
    BruteForce::Solver2d solver(
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
      Solution const response1 = solver.representative_set(  5, 1 );
      Solution const response2 = solver.representative_set( 10, 1 );

      THEN( "All points (and extra zero-padding, if necessary) are returned" )
      {
        Solution const actual1 = { 1, 2, 3, 4, 5 };
        Solution const actual2 = { 1, 2, 3, 4, 5, 0, 0, 0, 0, 0 };

        CHECK( response1 == actual1 );
        CHECK( response2 == actual2 );
      }
    }

    WHEN( "Only 3 points should minimise regret with respect to top-1 choices" )
    {
      Solution const response = solver.representative_set( 3, 1 );
      THEN( "The brute force method retrieves the three extreme points" )
      {
        Solution const actual = { 1, 2, 3 };

        CHECK( response == actual );
      }
    }
  }

  // GIVEN( "The toy database example from Table 1 of Chester et al. (2014)" )
}
