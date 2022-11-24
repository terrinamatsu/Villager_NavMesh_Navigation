#ifndef NAVTRIANGLE_H_
#define NAVTRIANGLE_H_

#include <ngl/Vec3.h>
#include "Random.h"

struct NavTriangle
{
    NavTriangle() = default;
    NavTriangle(ngl::Vec3 _pos1, ngl::Vec3 _pos2, ngl::Vec3 _pos3)
    {
        m_pos1 = _pos1;
        m_pos2 = _pos2;
        m_pos3 = _pos3;

        //m_colour1 = Random::randomPositiveVec3();
        //m_colour2 = Random::randomPositiveVec3();
        //m_colour3 = Random::randomPositiveVec3();
    }

    ngl::Vec3 m_pos1 = ngl::Vec3(0.0f, 0.0f, 0.0f);
    ngl::Vec3 m_pos2 = ngl::Vec3(0.0f, 0.0f, 0.0f);
    ngl::Vec3 m_pos3 = ngl::Vec3(0.0f, 0.0f, 0.0f);
    //ngl::Vec3 m_colour1 = ngl::Vec3(1.0f, 1.0f, 1.0f);
    //ngl::Vec3 m_colour2 = ngl::Vec3(1.0f, 1.0f, 1.0f);
    //ngl::Vec3 m_colour3 = ngl::Vec3(1.0f, 1.0f, 1.0f);
};

#endif // !NAVTRIANGLE_H_