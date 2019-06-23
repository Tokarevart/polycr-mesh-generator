#pragma once
#include "polygon.h"

namespace spt {

template <std::size_t Dim = 3, typename ValueType = typename spt::vec<Dim>::value_type>
using face = polygon<Dim, ValueType>;

} // namespace spt
