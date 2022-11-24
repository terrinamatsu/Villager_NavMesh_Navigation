#ifndef NAVTRIANGLE_H_
#define NAVTRIANGLE_H_

#include <ngl/Vec3.h>
#include "Random.h"
#include <iostream>

struct NavPoint
{
  NavPoint()
  {

  }
  NavPoint(ngl::Vec3 _position)
  {
    m_pos = _position;
  }
  NavPoint(ngl::Vec3 _position, ngl::Vec3 _colour)
  {
    m_pos = _position;
    m_colour = _colour;
  }
  ngl::Vec3 m_pos;
  ngl::Vec3 m_colour = ngl::Vec3(0.0f, 0.0f, 0.0f);
};

struct NavEdge
{
  NavEdge() = default;
  NavEdge(ngl::Vec3 _pos1, ngl::Vec3 _pos2)
  {
    m_pos1 = NavPoint(_pos1);
    m_pos2 = NavPoint(_pos2);
  }
  NavEdge(ngl::Vec3 _pos1, ngl::Vec3 _pos2, bool _isConstrained)
  {
    m_pos1 = NavPoint(_pos1);
    m_pos2 = NavPoint(_pos2);
    m_isConstrained = _isConstrained;
  }

  NavPoint m_pos1;
  NavPoint m_pos2;
  bool m_isConstrained = true;
};

struct NavTriangle
{
  NavTriangle() = default;
  NavTriangle(ngl::Vec3 _pos1, ngl::Vec3 _pos2, ngl::Vec3 _pos3)
  {
    m_edge1 = NavEdge(_pos1, _pos2);
    m_edge2 = NavEdge(_pos2, _pos3);
    m_edge3 = NavEdge(_pos3, _pos1);

    //m_colour1 = Random::randomPositiveVec3();
    //m_colour2 = Random::randomPositiveVec3();
    //m_colour3 = Random::randomPositiveVec3();
  }

  std::vector<ngl::Vec3> toPointPos()
  {
    std::vector<ngl::Vec3> points;

    points.push_back(m_edge1.m_pos1.m_pos);
    points.push_back(m_edge1.m_pos2.m_pos);
    points.push_back(m_edge2.m_pos1.m_pos);
    points.push_back(m_edge2.m_pos2.m_pos);
    points.push_back(m_edge3.m_pos1.m_pos);
    points.push_back(m_edge3.m_pos2.m_pos);

    return points;
  }

  std::vector<ngl::Vec3> toTriPointPos()
  {
    std::vector<ngl::Vec3> points;

    points.push_back(m_edge1.m_pos1.m_pos);
    points.push_back(m_edge2.m_pos1.m_pos);
    points.push_back(m_edge3.m_pos1.m_pos);

    return points;
  }

  NavEdge m_edge1;
  NavEdge m_edge2;
  NavEdge m_edge3;
  //ngl::Vec3 m_colour1 = ngl::Vec3(1.0f, 1.0f, 1.0f);
  //ngl::Vec3 m_colour2 = ngl::Vec3(1.0f, 1.0f, 1.0f);
  //ngl::Vec3 m_colour3 = ngl::Vec3(1.0f, 1.0f, 1.0f);
};

struct NavPoly
{
  NavPoly() = default;
  NavPoly(std::vector<NavTriangle> _polygon)
  {
    m_polygon = _polygon;
  }
  NavPoly(std::vector<ngl::Vec3> _polygon)
  {
    if(_polygon.size() < 3)
    {
      return;
    }
    for(auto i = 0; i < _polygon.size(); i += 3)
    {
      m_polygon.push_back(NavTriangle(_polygon[i], _polygon[i + 1], _polygon[i + 2]));
    }
  }

  // Function to return the positions of each of the points of the lines in the polygon
  std::vector<ngl::Vec3> toPointPos()
  {
    std::vector<ngl::Vec3> points;

    for(auto tri : m_polygon)
    {
      std::vector<ngl::Vec3> triPoints  = tri.toPointPos();
      for(auto p : triPoints)
      {
        points.push_back(p);
      }
    }

    return points;
  }

  // Function to return the positions of each of the points in the polygon
  std::vector<ngl::Vec3> toTriPointPos()
  {
    std::vector<ngl::Vec3> points;

    for(auto tri : m_polygon)
    {
      std::vector<ngl::Vec3> triPoints  = tri.toTriPointPos();
      for(auto p : triPoints)
      {
        points.push_back(p);
      }
    }

    return points;
  }

  // Function to verify that this is one polygon, with each triangle sharing an edge with at least one other.
  // Could also check if it is a convex hull?
  bool isValid()
  {
    return true;
  }

  ngl::Vec3 pointPlaneProjection(ngl::Vec3 _triPoint1, ngl::Vec3 _triPoint2, ngl::Vec3 _triPoint3, ngl::Vec3 _point)
  {
    ngl::Vec3 normal = _triPoint1.cross(_triPoint2);
    ngl::Vec3 d = _point - _triPoint1;
    float dist = d.dot(normal);

    return _point - (normal * dist);
  }

  bool ptSameSide(ngl::Vec3 _point1, ngl::Vec3 _point2, ngl::Vec3 _triPoint1, ngl::Vec3 _triPoint2)
  {
    auto cp1 = (_triPoint2 - _triPoint1).cross(_point1 - _triPoint1);
    auto cp2 = (_triPoint2 - _triPoint1).cross(_point2 - _triPoint1);
    if(cp1.dot(cp2) >= 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool isPointInTriangle(ngl::Vec3 _triPoint1, ngl::Vec3 _triPoint2, ngl::Vec3 _triPoint3, ngl::Vec3 _point)
  {
    if(ptSameSide(_point, _triPoint1, _triPoint2, _triPoint3) && ptSameSide(_point, _triPoint2, _triPoint1, _triPoint3) && ptSameSide(_point, _triPoint3, _triPoint1, _triPoint2))
    {
      return true;
    }
    return false;
  }

  ngl::Vec3 closestPointOnLineSeg(ngl::Vec3 _triPoint1, ngl::Vec3 _triPoint2, ngl::Vec3 _point)
  {
    // Incomplete Method One
//    float AB_BP = (_triPoint2 - _triPoint1).dot(_point - _triPoint2);
//    float AB_AP = (_triPoint2 - _triPoint1).dot(_point - _triPoint1);
//    if(AB_BP > 0)
//    {
//      return _triPoint2;
//    }
//    else if(AB_AP < 0)
//    {
//      return _triPoint1;
//    }
//    return

    // Method 2
    ngl::Vec3 t1p1 = _point - _triPoint1;
    ngl::Vec3 t1t2 = _triPoint2 - _triPoint1;

    float magT1T2 = t1t2.lengthSquared();
    float dot = t1p1.dot(t1t2);
    float distance = dot / magT1T2;

    if(distance < 0)
    {
      return _triPoint1;
    }
    else if(distance > 1)
    {
      return _triPoint2;
    }
    else
    {
      return _triPoint1 + t1t2 * distance;
    }
  }

  // Function to return the closest point on the polygon to a given position
  ngl::Vec3 getClosestPoint(ngl::Vec3 _position)
  {
    float closestDistance = 10'000'000.0f;
    ngl::Vec3 closestPoint;
    for(auto tri : m_polygon)
    {
      ngl::Vec3 pointOnTriPlane = pointPlaneProjection(tri.m_edge1.m_pos1.m_pos, tri.m_edge2.m_pos1.m_pos, tri.m_edge3.m_pos1.m_pos, _position);
      //std::cout<<pointOnTriPlane.m_x<<' '<<pointOnTriPlane.m_y<<' '<<pointOnTriPlane.m_z<<'\n';
      // Return point if it is on the triangle
      if(isPointInTriangle(tri.m_edge1.m_pos1.m_pos, tri.m_edge2.m_pos1.m_pos, tri.m_edge3.m_pos1.m_pos, pointOnTriPlane))
      {
        return pointOnTriPlane;
      }
      // Else find closest point on edge
      ngl::Vec3 p1 = closestPointOnLineSeg(tri.m_edge1.m_pos1.m_pos, tri.m_edge1.m_pos2.m_pos, _position);
      ngl::Vec3 p2 = closestPointOnLineSeg(tri.m_edge2.m_pos1.m_pos, tri.m_edge2.m_pos2.m_pos, _position);
      ngl::Vec3 p3 = closestPointOnLineSeg(tri.m_edge3.m_pos1.m_pos, tri.m_edge3.m_pos2.m_pos, _position);
      if((_position - p1).length() < closestDistance)
      {
        closestDistance = (_position - p1).length();
        closestPoint = p1;
      }
      if((_position - p2).length() < closestDistance)
      {
        closestDistance = (_position - p2).length();
        closestPoint = p2;
      }
      if((_position - p3).length() < closestDistance)
      {
        closestDistance = (_position - p3).length();
        closestPoint = p3;
      }
    }
    return closestPoint;
  }

  std::vector<NavTriangle> m_polygon;
  ngl::Vec3 m_colour;
};

#endif // !NAVTRIANGLE_H_
