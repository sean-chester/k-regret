#include "k-regret/contour/regret-solver-2d.h"


namespace kregret {
namespace // anonymous
{

Solution pad_with_zeroes( Dataset< 2 > const& data, size_t const result_size )
{
  Solution s( result_size, 0.0f );
  std::transform(
    data.cbegin(),
    data.cend(),
    s.begin(),
    []( auto const& p ){ return p.id; }
  );

  return s;
}

} // namespace anonymous

namespace Contour {

Solution Solver2d::operator () ( size_t const r, size_t const k ) const
{
  if( r >= data.size() ) { return pad_with_zeroes( data, r ); }

  return {};
}

} // namespace Contour
} // namespace kregret
