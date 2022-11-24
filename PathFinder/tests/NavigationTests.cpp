#include <gtest/gtest.h>
#include "NavMesh.h"
#include "Waypoint.h"
#include <iostream>

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

    nav.printWaypoints();

    size_t index = nav.getClosestWaypoint({0,0,0});

    ASSERT_EQ(index, 3);
}

TEST(NavMesh, WaypointPath)
{
    NavMesh nav(10,10);
    nav.initialiseTestWaypoints();

    nav.printWaypoints();

    std::vector<ngl::Vec3> waypath = nav.FindWaypointPathDijkstra({ 15, -2,  0}, {-11,  0,  0});

    ASSERT_GT(waypath.size(), 0);

    std::cout<<"----------------------------------------------\n";
    for(auto way : waypath)
    {
        std::cout<<way.m_x<<' '<<way.m_y<<' '<<way.m_z<<'\n';
    }
}