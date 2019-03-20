// Copyright © 2018-2019 Tokarev Artem Alekseevich. All rights reserved.
// Licensed under the MIT License.

#include "spatial-objs/vert.h"




const Vec& pmg::Vert::pos() const
{
    return *m_pos;
}


void pmg::Vert::setPos(const Vec& newPos)
{
    *m_pos = newPos;
}


void pmg::Vert::setPos(real_t coor0, real_t coor1, real_t coor2)
{
    m_pos->coors[0] = coor0;
    m_pos->coors[1] = coor1;
    m_pos->coors[2] = coor2;
}




real_t& pmg::Vert::operator[](short axis)
{
    return m_pos->coors[axis];
}


const real_t& pmg::Vert::operator[](short axis) const
{
    return m_pos->coors[axis];
}


Vec pmg::Vert::operator-(const pmg::Vert& other) const
{
    return *m_pos - *other.m_pos;
}


Vec pmg::Vert::operator-(const shell::Vert& other) const
{
    return *m_pos - other.pos();
}


pmg::Vert& pmg::Vert::operator+=(const Vec& other)
{
    if (belongsToShellVert)
    {
        return *this;
    }
    else if (belongsToShellEdge)
    {
        (*m_pos) += Vec(other).project(*belongsToShellEdge->verts[0] - *belongsToShellEdge->verts[1]);
        return *this;
    }
    else if (belongsToShellFace)
    {
        (*m_pos) += Vec(other).project(
            *belongsToShellFace->edges[0]->verts[1] - *belongsToShellFace->edges[0]->verts[0],
            *belongsToShellFace->edges[1]->verts[1] - *belongsToShellFace->edges[1]->verts[0]);
        return *this;
    }
    else
    {
        return *this;
    }
}


pmg::Vert& pmg::Vert::operator-=(const Vec& other)
{
    if (belongsToShellVert)
    {
        return *this;
    }
    else if (belongsToShellEdge)
    {
        (*m_pos) -= Vec(other).project(*belongsToShellEdge->verts[0] - *belongsToShellEdge->verts[1]);
        return *this;
    }
    else
    {
        (*m_pos) -= other;
        return *this;
    }
}




pmg::Vert::Vert()
{
    m_pos.reset(new Vec());
}


pmg::Vert::Vert(real_t coor0, real_t coor1, real_t coor2)
{
    m_pos.reset(new Vec(coor0, coor1, coor2));
}


pmg::Vert::Vert(const Vec& position)
{
    m_pos.reset(new Vec(position));
}