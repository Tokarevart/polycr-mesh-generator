#pragma once
#include <cstddef>
#include <stdexcept>
#include <array>
#include <vector>
#include "vec.h"


namespace spt {

template <std::size_t N, std::size_t Dim = 3, typename Real = typename spt::vec<Dim>::real_type>
struct polytope;

template <typename Polytope>
struct aggregate;


template <std::size_t N, std::size_t Dim, typename Real>
struct polytope
{
    static constexpr auto n = N;
    static constexpr auto dim = Dim;
    using real_type = Real;
    using facet_type = polytope<N - 1, Dim, Real>;

    const std::vector<facet_type*> facets;

    template <typename SubPolytope>
    std::vector<SubPolytope*> all_of() const;

    template <typename SubPolytope>
    bool contains(const SubPolytope* subpt) const
    {
        if constexpr (SubPolytope::n >= n)
            return false;
        else if constexpr (std::is_same<polytope<N - 1, Dim, Real>, SubPolytope>())
            return std::find(facets.begin(), facets.end(), subpt) != facets.end();
        else
        {
            for (const auto& facet : facets)
                if (facet->contains(subpt))
                    return true;

            return false;
        }
    }

    polytope() = delete;
    polytope(const std::vector<facet_type*>& facets)
        : facets(facets) {}
    polytope(std::vector<facet_type*>&& facets) noexcept
        : facets(std::move(facets)) {}
    template <std::size_t NFacets>
    polytope(const std::array<facet_type*, NFacets>& facets)
        : facets(facets.begin(), facets.end()) {}
    template <typename... Facets>
    polytope(Facets... facets)
        : facets({ facets... }) {}
};


template <typename Polytope>
struct aggregate
{
    using polytope_type = Polytope;
    aggregate() = delete;
};

} // namespace spt