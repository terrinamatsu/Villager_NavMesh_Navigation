#include "NavMesh.h"
#include <ngl/VAOFactory.h>

#include <iostream>

NavMesh::NavMesh(const float _BoundWidth, const float _BoundHeight)
{
  // Set Navigation Bounds
  m_BoundWidth = _BoundWidth;
  m_BoundHeight = _BoundHeight;

  // Initialise Waypoints
  //initialiseTestWaypoints();

  // Initialise VAO Factory
  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_TRIANGLES);

  m_vaoWaypoints = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_LINES);
}

void NavMesh::initialiseWaypointLines()
{
  for(auto i = 0; i < numWaypoints(); ++i)
  {
    for(auto j = 0; j < m_waypoints[i].m_connectedWaypoints.size(); ++j)
    {
      m_waypointPaths.push_back(m_waypoints[i].m_position);
      m_waypointPaths.push_back(m_waypoints[m_waypoints[i].m_connectedWaypoints[j]].m_position);
    }
  }
}

void NavMesh::connectWaypoints(size_t index1, size_t index2)
{
  m_waypoints[index1].connectWaypoint(index2);
  m_waypoints[index2].connectWaypoint(index1);
}

void NavMesh::initialiseTestWaypoints()
{
  // Initialise Navmesh Triangles
  // 1: Left Bay
  std::vector<NavTriangle> poly1;
  ngl::Vec3 p1 = { -6.0f,  0.0f, -5.0f};
  ngl::Vec3 p2 = { -6.0f,  0.0f,  5.0f};
  ngl::Vec3 p3 = { -8.0f,  0.0f,  6.0f};
  ngl::Vec3 p4 = { -8.0f,  0.0f, -6.0f};
  ngl::Vec3 p5 = {-15.0f,  0.0f,  6.0f};
  ngl::Vec3 p6 = {-15.0f,  0.0f,  -6.0f};
  poly1.push_back(NavTriangle(p1, p2 , p3));
  poly1.push_back(NavTriangle(p3, p1 , p4));
  poly1.push_back(NavTriangle(p4, p3 , p5));
  poly1.push_back(NavTriangle(p5, p4 , p6));
  // 2: Left Bay Exit North
  std::vector<NavTriangle> poly2;
  ngl::Vec3 p7 = { -4.0f,  0.0f,  7.0f};
  ngl::Vec3 p8 = { -4.0f,  0.0f,  10.0f};
  poly2.push_back(NavTriangle(p2, p3 , p7));
  poly2.push_back(NavTriangle(p7, p3 , p8));
  // 3: Left Bay Exit South
  std::vector<NavTriangle> poly3;
  ngl::Vec3 p9  = { -4.0f,  0.0f, -7.0f};
  ngl::Vec3 p10 = { -4.0f,  0.0f, -10.0f};
  poly3.push_back(NavTriangle(p1, p4 , p9));
  poly3.push_back(NavTriangle(p4, p10, p9));
  // 4: Centre Oct
  std::vector<NavTriangle> poly4;
  ngl::Vec3 p11 = {-4.0f,  4.0f,  3.0f};
  ngl::Vec3 p12 = {-4.0f,  4.0f, -3.0f};
  ngl::Vec3 p13 = {-3.0f,  4.0f,  4.0f};
  ngl::Vec3 p14 = {-3.0f,  4.0f, -4.0f};
  ngl::Vec3 p15 = { 3.0f,  4.0f,  4.0f};
  ngl::Vec3 p16 = { 3.0f,  4.0f, -4.0f};
  ngl::Vec3 p17 = { 4.0f,  4.0f,  3.0f};
  ngl::Vec3 p18 = { 4.0f,  4.0f, -3.0f};
  poly4.push_back(NavTriangle(p16, p18 , p17));
  poly4.push_back(NavTriangle(p17, p15 , p16));
  poly4.push_back(NavTriangle(p16, p15 , p14));
  poly4.push_back(NavTriangle(p14, p15 , p13));
  poly4.push_back(NavTriangle(p14, p13 , p11));
  poly4.push_back(NavTriangle(p14, p11 , p12));
  // 5: Containment Room North East
  std::vector<NavTriangle> poly5;
  ngl::Vec3 p19 = { 4.0f, -3.0f,  8.0f};
  ngl::Vec3 p20 = { 4.0f, -3.0f,  6.0f};
  ngl::Vec3 p21 = { 6.0f, -3.0f,  4.0f};
  ngl::Vec3 p22 = { 8.0f, -3.0f,  4.0f};
  poly5.push_back(NavTriangle(p21, p19 , p20));
  poly5.push_back(NavTriangle(p22, p19 , p21));
  // 6: Containment Room South East
  std::vector<NavTriangle> poly6;
  ngl::Vec3 p23 = { 6.0f, 5.0f, -4.0f};
  ngl::Vec3 p24 = { 8.0f, 5.0f, -4.0f};
  ngl::Vec3 p25 = { 4.0f, 5.0f, -6.0f};
  ngl::Vec3 p26 = { 4.0f, 5.0f, -8.0f};
  poly6.push_back(NavTriangle(p23, p26 , p24));
  poly6.push_back(NavTriangle(p23, p25 , p26));
  // 7: Secret Room Fart East
  std::vector<NavTriangle> poly7;
  ngl::Vec3 p27 = {12.0f, -4.0f,  -8.0f};
  ngl::Vec3 p28 = {12.0f, -4.0f, -11.0f};
  ngl::Vec3 p29 = {15.0f, -4.0f,  -8.0f};
  ngl::Vec3 p30 = {15.0f, -4.0f, -11.0f};
  poly7.push_back(NavTriangle(p27, p28 , p30));
  poly7.push_back(NavTriangle(p29, p27 , p30));

  // HALLWAYS
  // 8: 2-5
  std::vector<NavTriangle> poly8;
  poly8.push_back(NavTriangle(p7, p19 , p20));
  poly8.push_back(NavTriangle(p7, p8 , p19));
  // 9: 2-4
  std::vector<NavTriangle> poly9;
  poly9.push_back(NavTriangle(p11, p13 , p7));
  poly9.push_back(NavTriangle(p11, p7 , p2));
  //10: 4-5
  std::vector<NavTriangle> poly10;
  poly10.push_back(NavTriangle(p17, p21 , p20));
  poly10.push_back(NavTriangle(p17, p20 , p15));
  //11: 5-6
  std::vector<NavTriangle> poly11;
  poly11.push_back(NavTriangle(p23, p24 , p21));
  poly11.push_back(NavTriangle(p24, p22 , p21));
  //12: 3-4
  std::vector<NavTriangle> poly12;
  poly12.push_back(NavTriangle(p9, p14 , p12));
  poly12.push_back(NavTriangle(p1, p9 , p12));
  //13: 4-6
  std::vector<NavTriangle> poly13;
  poly13.push_back(NavTriangle(p16, p25 , p18));
  poly13.push_back(NavTriangle(p25, p23 , p18));
  //14: 3-6
  std::vector<NavTriangle> poly14;
  poly14.push_back(NavTriangle(p10, p25 , p9));
  poly14.push_back(NavTriangle(p10, p26 , p25));
  //15: 6-7
  std::vector<NavTriangle> poly15;
  poly15.push_back(NavTriangle(p24, p26 , p28));
  poly15.push_back(NavTriangle(p24, p28 , p27));

  //m_triangles.push_back(NavTriangle({-10,0,-10}, {10,0,-10}, {10,0,10}));
  //m_triangles.push_back(NavTriangle({-10,0,-10}, {10,0,10}, {-10,0,10}));



  Waypoint w1((NavPoly(poly1)));
  w1.m_polygon.m_colour = {1.0f, 0.0f, 0.0f};
  Waypoint w2((NavPoly(poly2)));
  w2.m_polygon.m_colour = {1.0f, 1.0f, 0.0f};
  Waypoint w3((NavPoly(poly3)));
  w3.m_polygon.m_colour = {1.0f, 0.0f, 1.0f};
  Waypoint w4((NavPoly(poly4)));
  w4.m_polygon.m_colour = {1.0f, 1.0f, 1.0f};
  Waypoint w5((NavPoly(poly5)));
  w5.m_polygon.m_colour = {0.0f, 1.0f, 0.0f};
  Waypoint w6((NavPoly(poly6)));
  w6.m_polygon.m_colour = {0.0f, 0.0f, 1.0f};
  Waypoint w7((NavPoly(poly7)));
  w7.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};

  Waypoint w8((NavPoly(poly8)));
  w8.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};
  Waypoint w9((NavPoly(poly9)));
  w9.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};
  Waypoint w10((NavPoly(poly10)));
  w10.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};
  Waypoint w11((NavPoly(poly11)));
  w11.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};
  Waypoint w12((NavPoly(poly12)));
  w12.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};
  Waypoint w13((NavPoly(poly13)));
  w13.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};
  Waypoint w14((NavPoly(poly14)));
  w14.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};
  Waypoint w15((NavPoly(poly15)));
  w15.m_polygon.m_colour = {0.0f, 1.0f, 1.0f};

  m_waypoints.push_back(w1);
  m_waypoints.push_back(w2);
  m_waypoints.push_back(w3);
  m_waypoints.push_back(w4);
  m_waypoints.push_back(w5);
  m_waypoints.push_back(w6);
  //m_waypoints.push_back(w7);

  m_waypoints.push_back(w8);
  m_waypoints.push_back(w9);
  m_waypoints.push_back(w10);
  m_waypoints.push_back(w11);
  m_waypoints.push_back(w12);
  m_waypoints.push_back(w13);
  m_waypoints.push_back(w14);
  //m_waypoints.push_back(w15);

  connectWaypoints(0, 1);
  connectWaypoints(0, 2);
  connectWaypoints(1, 6);
  connectWaypoints(1, 7);
  connectWaypoints(2, 10);
  connectWaypoints(2, 12);
  connectWaypoints(3, 7);
  connectWaypoints(3, 10);
  connectWaypoints(3, 8);
  connectWaypoints(3, 11);
  connectWaypoints(4, 6);
  connectWaypoints(4, 8);
  connectWaypoints(4, 9);
  connectWaypoints(5, 9);
  connectWaypoints(5, 11);
  connectWaypoints(5, 12);
 // connectWaypoints(5, 14);
 // connectWaypoints(6, 14);

  // Extract Waypoint Lines
  initialiseWaypointLines();
  // Extract Mesh Info
  extractNavMeshTrianglePoints();
}

size_t NavMesh::numWaypoints()
{
  return m_waypoints.size();
}

size_t NavMesh::numTriangles()
{
  return m_triangles.size();
}

void NavMesh::printWaypoints()
{
  for(auto way : m_waypoints)
  {
    way.print();
  }
}

void NavMesh::printWaypoints(std::vector<ngl::Vec3> _waypoints)
{
  for(auto way : _waypoints)
  {
    std::cout<<way.m_x<<' '<<way.m_y<<' '<<way.m_z<<'\n';
  }
}

void NavMesh::waypointVisit(size_t toVisitIndex)
{
  m_waypoints[toVisitIndex].m_isVisited = true;

  for(auto way : m_waypoints[toVisitIndex].m_connectedWaypoints)
  {
    float newDist = m_waypoints[toVisitIndex].m_pathDistance + fabs((m_waypoints[way].m_position - m_waypoints[toVisitIndex].m_position).length());
    if(m_waypoints[way].m_pathDistance > newDist && !(m_waypoints[way].m_isVisited))
    {
      m_waypoints[way].m_pathDistance = newDist;
      m_waypoints[way].m_pathWaypoints = m_waypoints[toVisitIndex].m_pathWaypoints;
      m_waypoints[way].m_pathWaypoints.push_back(m_waypoints[toVisitIndex].m_position);
    }
  }
}

size_t NavMesh::getClosestWaypoint(ngl::Vec3 _point)
{
  float closestDistStart = 10'000'000.0f;
  size_t EndpointIndex = -1;

  // Reset all nodes && Find nodes closest to start and end points
  for(auto i = 0; i < numWaypoints(); ++i)
  {
    float distToStart = fabs((_point - m_waypoints[i].m_position).length());
    if(closestDistStart > distToStart)
    {
      closestDistStart = distToStart;
      EndpointIndex = i;
    }
  }

  //m_waypoints[EndpointIndex].print();

  return EndpointIndex;
}

ngl::Vec3 NavMesh::getClosestWaypointPosition(ngl::Vec3 _point)
{
  float closestDistStart = 10'000'000.0f;
  size_t EndpointIndex = -1;

  // Reset all nodes && Find nodes closest to start and end points
  for(auto i = 0; i < numWaypoints(); ++i)
  {
    float distToStart = fabs((_point - m_waypoints[i].m_position).length());
    if(closestDistStart > distToStart)
    {
      closestDistStart = distToStart;
      EndpointIndex = i;
    }
  }

  //m_waypoints[EndpointIndex].print();

  return m_waypoints[EndpointIndex].m_position;
}

ngl::Vec3 NavMesh::getClosestNavMeshPosition(ngl::Vec3 _point)
{
  float closestDistStart = 10'000'000.0f;
  size_t EndpointIndex = -1;
  ngl::Vec3 closestPoint;

  for(auto i = 0; i < numWaypoints(); ++i)
  {
    ngl::Vec3 newPoint = m_waypoints[i].m_polygon.getClosestPoint(_point);
    if((_point - newPoint).length() < closestDistStart)
    {
      closestDistStart = (_point - newPoint).length();
      EndpointIndex = i;
      closestPoint = newPoint;
    }
  }

  return closestPoint;//m_waypoints[EndpointIndex].m_position;
}

size_t NavMesh::getClosestNavMeshWayIndex(ngl::Vec3 _point)
{
  float closestDistStart = 10'000'000.0f;
  size_t EndpointIndex = -1;
  ngl::Vec3 closestPoint;

  for(auto i = 0; i < numWaypoints(); ++i)
  {
    ngl::Vec3 newPoint = m_waypoints[i].m_polygon.getClosestPoint(_point);
    if((_point - newPoint).length() < closestDistStart)
    {
      closestDistStart = (_point - newPoint).length();
      EndpointIndex = i;
      closestPoint = newPoint;
    }
  }

  return EndpointIndex;
}

std::vector<ngl::Vec3> NavMesh::FindWaypointPathDijkstra(ngl::Vec3 _start, ngl::Vec3 _end)
{
  if(numWaypoints() <= 0)
  {
    std::vector<ngl::Vec3> empty;
    return empty;
  }

  std::vector<size_t> UnvisitedWaypoints;

  // Clamp start and end to the navmesh
  _start = getClosestNavMeshPosition(_start);
  _end = getClosestNavMeshPosition(_end);

  // Reset all nodes && Find nodes closest to start and end points
  for(auto i = 0; i < numWaypoints(); ++i)
  {
    m_waypoints[i].resetVisit();
    UnvisitedWaypoints.push_back(i);
  }

  // Find closest waypoints to the start and end
  size_t StartIndex = getClosestNavMeshWayIndex(_start);
  size_t EndIndex = getClosestNavMeshWayIndex(_end);

  // Dijkstra Pathfind Time!
  size_t CurrentIndex = StartIndex;
  size_t NextIndex = 0;
  float distance = 1'000'000.0f;

  m_waypoints[StartIndex].m_pathDistance = 0.0f;

  while(CurrentIndex != EndIndex)
  {
    //std::cout<<"Segmentation Fs in the Chat "<<CurrentIndex<<'\n';
    waypointVisit(CurrentIndex);
    distance = 1'000'000.0f;

    // Remove visited waypoints
    for(auto i = 0; i < UnvisitedWaypoints.size(); ++i)
    {

      if(m_waypoints[UnvisitedWaypoints[i]].m_isVisited)
      {
        // Remove unvisited nodes
        UnvisitedWaypoints.erase(UnvisitedWaypoints.begin() + i);
      }
    }
    // Find next waypoint with lowest distance from unvisited list
    for(auto i = 0; i < UnvisitedWaypoints.size(); ++i)
    {
      float heuristicDistance = fabs((m_waypoints[UnvisitedWaypoints[i]].m_position - m_waypoints[EndIndex].m_position).length()) ;
      if((m_waypoints[UnvisitedWaypoints[i]].m_pathDistance + heuristicDistance) < distance)
      {
        // Find node with lowest distance value
        distance = m_waypoints[UnvisitedWaypoints[i]].m_pathDistance;
        NextIndex = UnvisitedWaypoints[i] ;
      }
    }
    //m_waypoints[NextIndex].m_pathWaypoints.push_back(m_waypoints[CurrentIndex].m_position);
    CurrentIndex = NextIndex;
  }
  // Pushback end waypoint's position
  m_waypoints[EndIndex].m_pathWaypoints.push_back(m_waypoints[EndIndex].m_position);
  // Pushback end position on navmesh
  m_waypoints[EndIndex].m_pathWaypoints.push_back(_end);

  return m_waypoints[EndIndex].m_pathWaypoints;
}

void NavMesh::extractNavMeshTrianglePoints()
{
  m_meshPoints.clear();
  m_meshColours.clear();

  for(auto way : m_waypoints)
  {
    for(auto point : way.m_polygon.toTriPointPos())
    {
        m_meshPoints.push_back(point);
        m_meshPoints.push_back(way.m_polygon.m_colour);
    }
  }
}

void NavMesh::update()
{
  // Extract Mesh Info
  //extractNavMeshTrianglePoints();
}

void NavMesh::render() const
{
  //Render Navmesh
  m_vao->bind();

  m_vao->setData(ngl::SimpleVAO::VertexData(m_meshPoints.size() * sizeof(ngl::Vec3) * 2, m_meshPoints[0].m_x));
  m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(ngl::Vec3) * 2, 0);
  m_vao->setVertexAttributePointer(1, 3, GL_FLOAT, sizeof(ngl::Vec3) * 2, 3);
  m_vao->setNumIndices(m_meshPoints.size()/2);

  m_vao->draw();
  m_vao->unbind();

  // Render Waypoint Paths
  glPointSize(10);
  glLineWidth(10);
  m_vaoWaypoints->bind();

  m_vaoWaypoints->setData(ngl::SimpleVAO::VertexData(m_waypointPaths.size() * sizeof(ngl::Vec3), m_waypointPaths[0].m_x));
  m_vaoWaypoints->setVertexAttributePointer(0, 3, GL_FLOAT, 0, 0);
  m_vaoWaypoints->setVertexAttributePointer(1, 3, GL_FLOAT, 0, 0);
  m_vaoWaypoints->setNumIndices(m_waypointPaths.size());

  m_vaoWaypoints->draw();
  m_vaoWaypoints->unbind();
}
