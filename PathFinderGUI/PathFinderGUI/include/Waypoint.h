#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include "NavTriangle.h"
#include <ngl/Vec3.h>
#include <iostream>

struct Waypoint
{
  Waypoint(ngl::Vec3 _position)
  {
    m_position = _position;
    m_isVisited = false;
    m_pathDistance = 10'000'000.0f;
  }

  Waypoint(ngl::Vec3 _position, NavPoly _polygon)
  {
    m_position = _position;
    m_isVisited = false;
    m_pathDistance = 10'000'000.0f;
    m_polygon = _polygon;
  }

  Waypoint(NavPoly _polygon)
  {
    ngl::Vec3 point;
    for(auto p : _polygon.toPointPos())
    {
      point += p;
    }
    point/=_polygon.toPointPos().size();
    m_position = point;
    m_isVisited = false;
    m_pathDistance = 10'000'000.0f;
    m_polygon = _polygon;
  }

  void connectWaypoint(size_t _connectedWaypoint)
  {
    m_connectedWaypoints.push_back(_connectedWaypoint);
  }

  void resetVisit()
  {
    m_isVisited = false;
    m_pathDistance = 10'000'000.0f;
    m_pathWaypoints.clear();
  }

  void print()
  {
    std::cout<<m_position.m_x<<' '<<m_position.m_y<<' '<<m_position.m_z<<'\n';
  }

  // Waypoint Position
  ngl::Vec3 m_position;
  std::vector<size_t> m_connectedWaypoints;
  std::vector<ngl::Vec3> m_pathWaypoints;
  bool m_isVisited;
  float m_pathDistance;

  // Polygon Informatin
  NavPoly m_polygon;
};

#endif // !WAYPOINT_H_
