#pragma once
#include <vector>
#include "indexed_mesh-base.h"
#include "polyhedron.h"


namespace spt {

template <std::size_t Dim, typename ValueType>
struct indexed_mesh<spt::dion<Dim, ValueType>, spt::elem_shape::polytope> {
    using polytope_type = spt::dion<Dim, ValueType>;
    using value_type = ValueType;
    using index_type = std::size_t;
    using vertex_type = spt::vec<Dim, value_type>;
    using edge_type = std::array<index_type, 2>;

    std::vector<vertex_type> vertices;
    std::vector<edge_type> edges;
};


template <std::size_t Dim, typename ValueType>
struct indexed_mesh<spt::polygon<Dim, ValueType>, spt::elem_shape::polytope> {
    using polytope_type = spt::polygon<Dim, ValueType>;
    using value_type = ValueType;
    using index_type = std::size_t;
    using vertex_type = spt::vec<Dim, value_type>;
    using edge_type = std::array<index_type, 2>;
    using face_type = std::vector<index_type>;

    std::vector<vertex_type> vertices;
    std::vector<edge_type> edges;
    std::vector<face_type> faces;
};


template <std::size_t Dim, typename ValueType>
struct indexed_mesh<spt::polyhedron<Dim, ValueType>, spt::elem_shape::polytope> {
    using polytope_type = spt::polyhedron<Dim, ValueType>;
    using value_type = ValueType;
    using index_type = std::size_t;
    using vertex_type = spt::vec<Dim, ValueType>;
    using edge_type = std::array<index_type, 2>;
    using face_type = std::vector<index_type>;
    using cell_type = std::vector<index_type>;

    std::vector<vertex_type> vertices;
    std::vector<edge_type> edges;
    std::vector<face_type> faces;
    std::vector<cell_type> cells;
};

} // namespace pmg
