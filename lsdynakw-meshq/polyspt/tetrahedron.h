#pragma once
#include "simplex/simplex-3.h"

namespace spt {

template <std::size_t Dim, typename Real>
using tetrahedron = spt::simplex<3, Dim, Real>;

template <std::size_t Dim, typename Real>
using tetrahedron_v = spt::simplex_v<3, Dim, Real>;

} // namespace spt
