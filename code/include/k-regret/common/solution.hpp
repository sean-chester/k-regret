#ifndef KREGRET_COMMON_SOLUTION
#define KREGRET_COMMON_SOLUTION


#include <vector>    // std::vector
#include <algorithm> // std::is_permutation


#include "k-regret/common/data-point.hpp"

namespace kregret {

using Solution = std::vector< DataPointId >;

inline bool operator == ( Solution const& s1, Solution const& s2 )
{
  if( s1.size() != s2.size() ) { return false; }
  return std::is_permutation( s1.cbegin(), s1.cend(), s2.cbegin() );
}

} // namespace kregret


#endif // KREGRET_COMMON_SOLUTION
