/**
 * @file
 * An exact plane-sweep method to solve 2d k-regret queries.
 * @see Section 4 and Algorithm 1 of:
 * Chester et al. (2014) "Computing k-regret minimizing sets." PVLDB: (7)5.
 */

#ifndef KREGRET_CONTOUR_2D
#define KREGRET_CONTOUR_2D


#include "k-regret/common/solution.h"
#include "k-regret/common/data-point.h"


namespace kregret {
namespace Contour {

class Solver2d
{
  Dataset< 2 > data;

public:
  explicit Solver2d( Dataset< 2 > const& input ) : data( input ) {}
  ~Solver2d() {}

  /** Retrieve the k-regret minimising set of size _r_ with respect to top-k preferences */
  Solution operator () ( size_t const r, size_t const k ) const;
};

} // namespace Contour
} // namespace kregret


#endif // KREGRET_CONTOUR_2D
