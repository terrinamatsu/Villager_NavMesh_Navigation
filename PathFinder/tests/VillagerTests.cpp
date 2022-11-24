#include <gtest/gtest.h>
#include <Villager.h>

TEST(Villager, ctor)
{
    Villager v;
    ASSERT_EQ(v.m_speed,0.1f);
    ASSERT_EQ(v.m_numWaypoints,0);
    ASSERT_EQ(v.m_position,ngl::Vec3(0,0,0));
    ASSERT_TRUE(v.m_isIdle);
    ASSERT_EQ(v.m_waypoints.size(), 0);
}

TEST(Villager, AddWaypoint)
{
    Villager v;
    v.AddWaypoint(ngl::Vec3(1,1,1));

    ASSERT_EQ(v.m_waypoints.size(), 1);
    ASSERT_EQ(v.m_numWaypoints, 1);
    ASSERT_EQ(v.m_waypoints[0], ngl::Vec3(1,1,1));
}

TEST(Villager, RemoveLastWaypoint)
{
    Villager v;
    v.AddWaypoint(ngl::Vec3(5,5,5));
    ASSERT_EQ(v.m_waypoints.size(), 1);
    ASSERT_EQ(v.m_numWaypoints, 1);
    v.RemoveLastWaypoint();
    ASSERT_EQ(v.m_waypoints.size(), 0);
    ASSERT_EQ(v.m_numWaypoints, 0);
}

TEST(Villager, RemoveNextWaypoint)
{
    Villager v;
    
    v.AddWaypoint(ngl::Vec3(10,10,10));
    ASSERT_EQ(v.m_waypoints.size(), 1);
    ASSERT_EQ(v.m_numWaypoints, 1);
    
    v.AddWaypoint(ngl::Vec3(3,3,3));
    ASSERT_EQ(v.m_waypoints.size(), 2);
    ASSERT_EQ(v.m_numWaypoints, 2);

    v.RemoveNextWaypoint();
    ASSERT_EQ(v.m_waypoints.size(), 1);
    ASSERT_EQ(v.m_numWaypoints, 1);
    ASSERT_EQ(v.m_waypoints[0].m_x, 3);
    ASSERT_EQ(v.m_waypoints[0].m_y, 3);
    ASSERT_EQ(v.m_waypoints[0].m_z, 3);
}

TEST(Villager, AddRandomWaypoint)
{
    Villager v;
    
    // Test a bunch of points to see if they are all in the correct range. 
    for(auto i=0; i < 100; ++i)
    {
        v.AddRandomWaypoint(10,50);
    
        ASSERT_TRUE(v.m_waypoints[0].m_x >= -10);
        ASSERT_TRUE(v.m_waypoints[0].m_x <= 10);

        ASSERT_TRUE(v.m_waypoints[0].m_y > -50);
        ASSERT_TRUE(v.m_waypoints[0].m_y <= 50);

        ASSERT_EQ(v.m_waypoints[0].m_z, 0);

        v.RemoveLastWaypoint();
    }
}

TEST(Villager, Move)
{
    Villager vX, vY, vZ, v0, vNone, vXY, vXZ, vYZ, vXYZ;
    vX.AddWaypoint(ngl::Vec3(1.0f, 0.0f, 0.0f));
    ASSERT_EQ(vX.m_waypoints.size(), 1);
    ASSERT_EQ(vX.m_numWaypoints, 1);
    vY.AddWaypoint(ngl::Vec3(0.0f, 1.0f, 0.0f));
    vZ.AddWaypoint(ngl::Vec3(0.0f, 0.0f, 1.0f));
    v0.AddWaypoint(ngl::Vec3(0.0f, 0.0f, 0.0f));

    vXY.AddWaypoint(ngl::Vec3(1.0f, 1.0f, 0.0f));
    vXZ.AddWaypoint(ngl::Vec3(1.0f, 0.0f, 1.0f));
    vYZ.AddWaypoint(ngl::Vec3(0.0f, 1.0f, 1.0f));
    vXYZ.AddWaypoint(ngl::Vec3(1.0f, 1.0f, 1.0f));

    vX.Move();
    ASSERT_FALSE(vX.m_isIdle);
    vY.Move();
    ASSERT_FALSE(vY.m_isIdle);
    vZ.Move();
    ASSERT_FALSE(vZ.m_isIdle);
    v0.Move();
    ASSERT_TRUE(v0.m_isIdle);
    vNone.Move();
    ASSERT_TRUE(vNone.m_isIdle);
    vXY.Move();
    ASSERT_FALSE(vXY.m_isIdle);
    vXZ.Move();
    ASSERT_FALSE(vXZ.m_isIdle);
    vYZ.Move();
    ASSERT_FALSE(vYZ.m_isIdle);
    vXYZ.Move();
    ASSERT_FALSE(vXYZ.m_isIdle);

    ASSERT_EQ(vX.m_position.m_x, 0.1f);
    ASSERT_EQ(vX.m_position.m_y, 0.0f);
    ASSERT_EQ(vX.m_position.m_z, 0.0f);
    ASSERT_EQ(vX.m_position, ngl::Vec3(0.1f, 0.0f, 0.0f));

    ASSERT_EQ(vY.m_position, ngl::Vec3(0.0f, 0.1f, 0.0f));
    ASSERT_EQ(vZ.m_position, ngl::Vec3(0.0f, 0.0f, 0.1f));
    ASSERT_EQ(v0.m_position, ngl::Vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(vNone.m_position, ngl::Vec3(0.0f, 0.0f, 0.0f));
    
    ASSERT_FLOAT_EQ(vXY.m_position.m_x, 0.1f);
    ASSERT_FLOAT_EQ(vXY.m_position.m_y, 0.0f);
    ASSERT_FLOAT_EQ(vXY.m_position.m_z, 0.0f);
    ASSERT_EQ(vXY.m_position, ngl::Vec3());
    
    ASSERT_EQ(vXZ.m_position, ngl::Vec3());
    ASSERT_EQ(vYZ.m_position, ngl::Vec3());
    ASSERT_EQ(vXYZ.m_position, ngl::Vec3());
}

TEST(Python, ctor)
{
    
}