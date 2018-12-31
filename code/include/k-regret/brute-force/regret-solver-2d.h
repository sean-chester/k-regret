/**
 * @file
 * A slow, brute-force method to solve 2d k-regret queries.
 * Principally used for verifying the correctness of other implementations.
 */

#ifndef KREGRET_BF_2D
#define KREGRET_BF_2D


#include "k-regret/common/solution.h"
#include "k-regret/common/data-point.h"


namespace kregret {
namespace BruteForce {

/**
 * A slow, brute-force method to solve 2d k-regret queries.
 *
 * This algorithm iterates all subsets of size _r_ and computes the regret ratio.
 * The subset that minimises the regret ratio is returned. *Choose _r_ carefully!*
 */
class Solver2d
{
  Dataset< 2 > data;

public:
  explicit Solver2d( Dataset< 2 > const& input ) : data( input ) {}
  ~Solver2d() {}

  /** Retrieve the k-regret minimising set of size _r_ with respect to top-k preferences */
  Solution operator () ( size_t const r, size_t const k ) const;
};

} // namespace BruteForce
} // namespace kregret


#endif // KREGRET_BF_2D
