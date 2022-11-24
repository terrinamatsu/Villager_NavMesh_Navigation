#include <gtest/gtest.h>
#include "NavMesh.h"
#include "Waypoint.h"
#include "NavTriangle.h"
#include <iostream>

TEST(NavPoint, ctor)
{
  NavPoint p;

  ASSERT_EQ(p.m_pos, ngl::Vec3(0.0f, 0.0f, 0.0f));

  ASSERT_EQ(p.m_colour, ngl::Vec3(0.0f, 0.0f, 0.0f));
}

TEST(NavPoint, usrctor)
{
  // Position Ctor
  NavPoint p({30.0f, 20.0f, 10.0f});

  ASSERT_EQ(p.m_pos, ngl::Vec3(30.0f, 20.0f, 10.0f));
  ASSERT_EQ(p.m_colour, ngl::Vec3(0.0f, 0.0f, 0.0f));

  // Position Colour Ctor
  NavPoint p2({30.0f, 20.0f, 10.0f}, {1.0f, 1.0f, 0.0f});

  ASSERT_EQ(p2.m_pos, ngl::Vec3(30.0f, 20.0f, 10.0f));
  ASSERT_EQ(p2.m_colour, ngl::Vec3(1.0f, 1.0f, 0.0f));
}

TEST(NavEdge, usrctor)
{
  NavEdge e({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  ASSERT_EQ(e.m_pos1.m_pos, ngl::Vec3(0.0f, 0.0f, 0.0f));
  ASSERT_EQ(e.m_pos2.m_pos, ngl::Vec3(1.0f, 1.0f, 1.0f));
  ASSERT_TRUE(e.m_isConstrained);


  NavEdge e2({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, false);
  ASSERT_FALSE(e2.m_isConstrained);
}

TEST(NavTriangle, usrctor)
{
  NavTriangle t({0.0f, 0.0f, 0.0f}, {5.0f, 0.0f, 0.0f}, {0.0f, 10.0f, 0.0f});

  ASSERT_EQ(t.m_edge1.m_pos1.m_pos, ngl::Vec3(0.0f, 0.0f, 0.0f));
  ASSERT_EQ(t.m_edge1.m_pos2.m_pos, ngl::Vec3(5.0f, 0.0f, 0.0f));

  ASSERT_EQ(t.m_edge2.m_pos1.m_pos, ngl::Vec3(5.0f, 0.0f, 0.0f));
  ASSERT_EQ(t.m_edge2.m_pos2.m_pos, ngl::Vec3(0.0f, 10.0f, 0.0f));

  ASSERT_EQ(t.m_edge3.m_pos1.m_pos, ngl::Vec3(0.0f, 10.0f, 0.0f));
  ASSERT_EQ(t.m_edge3.m_pos2.m_pos, ngl::Vec3(0.0f, 0.0f, 0.0f));
}

TEST(NavPoly, ctor)
{
  ngl::Vec3 p1(0.0f, 0.0f, 0.0f);
  ngl::Vec3 p2(5.0f, 0.0f, 0.0f);
  ngl::Vec3 p3(0.0f, 10.0f, 0.0f);
  ngl::Vec3 p4(5.0f, 10.0f, 0.0f);

  NavTriangle t1(p1, p2, p3);
  NavTriangle t2(p2, p4, p3);

  std::vector<NavTriangle> tris;
  tris.push_back(t1);
  tris.push_back(t2);

  NavPoly poly1(tris);

  std::vector<ngl::Vec3> tris2;
  tris2.push_back(p1);
  tris2.push_back(p2);
  tris2.push_back(p3);
  tris2.push_back(p2);
  tris2.push_back(p4);
  tris2.push_back(p3);
  NavPoly poly2(tris2);

  ASSERT_EQ(poly1.m_polygon.size(), 2);
  ASSERT_EQ(poly2.m_polygon.size(), 2);

  for(auto i = 0; i < poly1.m_polygon.size(); ++i)
  {
    ASSERT_EQ(poly1.m_polygon[i].m_edge1.m_pos1.m_pos, poly2.m_polygon[i].m_edge1.m_pos1.m_pos);
    ASSERT_EQ(poly1.m_polygon[i].m_edge1.m_pos2.m_pos, poly2.m_polygon[i].m_edge1.m_pos2.m_pos);

    ASSERT_EQ(poly1.m_polygon[i].m_edge2.m_pos1.m_pos, poly2.m_polygon[i].m_edge2.m_pos1.m_pos);
    ASSERT_EQ(poly1.m_polygon[i].m_edge2.m_pos2.m_pos, poly2.m_polygon[i].m_edge2.m_pos2.m_pos);

    ASSERT_EQ(poly1.m_polygon[i].m_edge3.m_pos1.m_pos, poly2.m_polygon[i].m_edge3.m_pos1.m_pos);
    ASSERT_EQ(poly1.m_polygon[i].m_edge3.m_pos2.m_pos, poly2.m_polygon[i].m_edge3.m_pos2.m_pos);
  }
}

TEST(NavPoly, toPoints)
{
  ngl::Vec3 p1(0.0f, 0.0f, 0.0f);
  ngl::Vec3 p2(5.0f, 0.0f, 0.0f);
  ngl::Vec3 p3(0.0f, 10.0f, 0.0f);
  ngl::Vec3 p4(5.0f, 10.0f, 0.0f);

  NavTriangle t1(p1, p2, p3);
  NavTriangle t2(p2, p4, p3);

  std::vector<NavTriangle> tris;
  tris.push_back(t1);
  tris.push_back(t2);

  NavPoly poly1(tris);

  std::vector<ngl::Vec3> newPoints = poly1.toPointPos();

  ASSERT_EQ(newPoints.size(), 12);

  ASSERT_EQ(newPoints[0], p1);
  ASSERT_EQ(newPoints[1], p2);
  ASSERT_EQ(newPoints[2], p2);
  ASSERT_EQ(newPoints[3], p3);
  ASSERT_EQ(newPoints[4], p3);
  ASSERT_EQ(newPoints[5], p1);
  ASSERT_EQ(newPoints[6], p2);
  ASSERT_EQ(newPoints[7], p4);
  ASSERT_EQ(newPoints[8], p4);
  ASSERT_EQ(newPoints[9], p3);
  ASSERT_EQ(newPoints[10], p3);
  ASSERT_EQ(newPoints[11], p2);
}

TEST(NavPoly, isValid)
{
  // Valid Poly
  ngl::Vec3 p1(0.0f, 0.0f, 0.0f);
  ngl::Vec3 p2(5.0f, 0.0f, 0.0f);
  ngl::Vec3 p3(0.0f, 10.0f, 0.0f);
  ngl::Vec3 p4(5.0f, 10.0f, 0.0f);

  NavTriangle t1(p1, p2, p3);
  NavTriangle t2(p2, p4, p3);

  std::vector<NavTriangle> tris;
  tris.push_back(t1);
  tris.push_back(t2);

  NavPoly poly1(tris);

  ASSERT_TRUE(poly1.isValid());

  // Invalid Poly (triangles dont share edges)
  ngl::Vec3 p5(10.0f, 0.0f, 0.0f);
  NavTriangle t3(p2, p5, p4);
  std::vector<NavTriangle> tris2;
  tris2.push_back(t1);
  tris2.push_back(t3);
  NavPoly poly2(tris2);

  //ASSERT_FALSE(poly2.isValid());
}

TEST(NavPoly, pointProjection)
{
  // Valid Poly
  ngl::Vec3 p1(0.0f, 0.0f, 0.0f);
  ngl::Vec3 p2(5.0f, 0.0f, 0.0f);
  ngl::Vec3 p3(0.0f, 0.0f, 10.0f);
  ngl::Vec3 p4(5.0f, 0.0f, 10.0f);

  NavTriangle t1(p1, p3, p2);
  NavTriangle t2(p2, p3, p4);

  std::vector<NavTriangle> tris;
  tris.push_back(t1);
  tris.push_back(t2);

  NavPoly poly1(tris);

  ngl::Vec3 closestP = poly1.getClosestPoint({1.0f, 3.0f, 2.0f});

  ASSERT_EQ(closestP.m_x, 1.0f);
  ASSERT_EQ(closestP.m_y, 0.0f);
  ASSERT_EQ(closestP.m_z, 2.0f);
}




/*
 *
 * WAYPOINT & NAVMESH TESTS
 *
 */

TEST(Waypoint, ctor)
{
  Waypoint w({10.0f,0.0f,10.0f});
  ASSERT_EQ(w.m_position, ngl::Vec3(10.0f, 0.0f, 10.0f));
  ASSERT_EQ(w.m_isVisited, false);
}

TEST(Waypoint, addConnection)
{
  Waypoint w1({5,5,5});
  Waypoint w2({6,6,6});

  w1.connectWaypoint(1);
  w2.connectWaypoint(0);

  ASSERT_EQ(w1.m_connectedWaypoints.back(), 1);
  //ASSERT_EQ(w1.m_connectedWaypoints.back()->m_position, w2.m_position);

  ASSERT_EQ(w2.m_connectedWaypoints.back(), 0);
  //ASSERT_EQ(w2.m_connectedWaypoints.back()->m_position, w1.m_position);


  ASSERT_EQ(w1.m_connectedWaypoints.size(), 1);
  ASSERT_EQ(w2.m_connectedWaypoints.size(), 1);
}

TEST(Waypoint, visitedCheck)
{
  Waypoint w1({5,5,5});
  Waypoint w2({6,6,6});

  w1.connectWaypoint(1);
  w2.connectWaypoint(0);

  ASSERT_GT(w2.m_pathDistance, 1'000'000.0f);
  ASSERT_EQ(w1.m_isVisited, false);
  // w1.visit();
  // ASSERT_EQ(w1.m_isVisited, true);
  // ASSERT_EQ(w2.m_pathDistance, ngl::Vec3(1,1,1).length());
  // ASSERT_EQ(w1.m_pathDistance, 0.0f);

  w1.resetVisit();
  ASSERT_EQ(w1.m_isVisited, false);
  ASSERT_GT(w1.m_pathDistance, 1'000'000.0f);
}

TEST(NavMesh, ctor)
{
  NavMesh nav(2,4);
  ASSERT_EQ(1,1);
}

TEST(NavMesh, ClosestWaypoint)
{
  NavMesh nav(10,10);
  ASSERT_EQ(nav.numWaypoints(),0);
  nav.initialiseTestWaypoints();
  ASSERT_GT(nav.numWaypoints(),5);

  //nav.printWaypoints();

  size_t index = nav.getClosestWaypoint({0,0,0});

  ASSERT_EQ(index, 3);
}

TEST(NavMesh, WaypointPath)
{
  NavMesh nav(10,10);
  nav.initialiseTestWaypoints();

  //nav.printWaypoints();

  std::vector<ngl::Vec3> waypath = nav.FindWaypointPathDijkstra({ 15, -2,  0}, {-11,  0,  0});

  ASSERT_GT(waypath.size(), 0);

  //std::cout<<"----------------------------------------------\n";
  for(auto way : waypath)
  {
    //std::cout<<way.m_x<<' '<<way.m_y<<' '<<way.m_z<<'\n';
  }
}
