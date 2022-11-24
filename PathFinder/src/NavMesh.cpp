#include "NavMesh.h"
#include <ngl/VAOFactory.h>

#include <iostream>

NavMesh::NavMesh(const float _BoundWidth, const float _BoundHeight)
{
    // Set Navigation Bounds
    m_BoundWidth = _BoundWidth;
    m_BoundHeight = _BoundHeight;
    
    // Initialise Navmesh Triangles
    m_triangles.push_back(NavTriangle({-10,0,-10}, {10,0,-10}, {10,0,10}));
    m_triangles.push_back(NavTriangle({-10,0,-10}, {10,0,10}, {-10,0,10}));

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
    Waypoint w1({-10,  0,  0});
    Waypoint w2({ -5, -2,  6});
    Waypoint w3({ -5,  5, -7});
    Waypoint w4({  0,  4,  0});
    Waypoint w5({  5,  1,  6});
    Waypoint w6({  5,  1, -7});
    Waypoint w7({ 10, -2,  0});

    m_waypoints.push_back(w1);
    m_waypoints.push_back(w2);
    m_waypoints.push_back(w3);
    m_waypoints.push_back(w4);
    m_waypoints.push_back(w5);
    m_waypoints.push_back(w6);
    m_waypoints.push_back(w7);

    connectWaypoints(0, 1);
    connectWaypoints(0, 2);
    connectWaypoints(2, 3);
    connectWaypoints(1, 3);
    connectWaypoints(1, 4);
    connectWaypoints(3, 4);
    connectWaypoints(3, 5);
    connectWaypoints(4, 5);
    connectWaypoints(5, 6);

    initialiseWaypointLines();
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
        float newDist = m_waypoints[toVisitIndex].m_pathDistance + abs((m_waypoints[way].m_position - m_waypoints[toVisitIndex].m_position).length());
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
    size_t EndpointIndex;

    // Reset all nodes && Find nodes closest to start and end points
    for(auto i = 0; i < numWaypoints(); ++i)
    {
        float distToStart = abs((_point - m_waypoints[i].m_position).length());
        if(closestDistStart > distToStart)
        {
            closestDistStart = distToStart;
            EndpointIndex = i;
        }
    }

    m_waypoints[EndpointIndex].print();

    return EndpointIndex;
}

ngl::Vec3 NavMesh::getClosestWaypointPosition(ngl::Vec3 _point)
{
    float closestDistStart = 10'000'000.0f;
    size_t EndpointIndex;

    // Reset all nodes && Find nodes closest to start and end points
    for(auto i = 0; i < numWaypoints(); ++i)
    {
        float distToStart = abs((_point - m_waypoints[i].m_position).length());
        if(closestDistStart > distToStart)
        {
            closestDistStart = distToStart;
            EndpointIndex = i;
        }
    }

    m_waypoints[EndpointIndex].print();

    return m_waypoints[EndpointIndex].m_position;
}

std::vector<ngl::Vec3> NavMesh::FindWaypointPathDijkstra(ngl::Vec3 _start, ngl::Vec3 _end)
{
    if(numWaypoints() <= 0)
    {
        std::vector<ngl::Vec3> empty;
        return empty;
    }

    std::vector<size_t> UnvisitedWaypoints;

    // Reset all nodes && Find nodes closest to start and end points
    for(auto i = 0; i < numWaypoints(); ++i)
    {
        m_waypoints[i].resetVisit();
        UnvisitedWaypoints.push_back(i);
    }

    // Find closest waypoints to the start and end
    size_t StartIndex = getClosestWaypoint(_start);
    size_t EndIndex = getClosestWaypoint(_end);
    //std::cout<<"THE START END INDEX: "<<StartIndex<<' '<<EndIndex<<'\n';

    // Dijkstra Pathfind Time!
    size_t CurrentIndex = StartIndex;
    size_t NextIndex;
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
            //std::cout<<"SF no good "<<m_waypoints[UnvisitedWaypoints[i]].m_pathDistance<<'\n';
                  
            if(m_waypoints[UnvisitedWaypoints[i]].m_isVisited)
            {
                // Remove unvisited nodes
                //std::cout<<"S visit "<<m_waypoints[UnvisitedWaypoints[i]].m_isVisited<<'\n';
                UnvisitedWaypoints.erase(UnvisitedWaypoints.begin() + i);    
            }
        }
        // Find next waypoint with lowest distance from unvisited list
        for(auto i = 0; i < UnvisitedWaypoints.size(); ++i)
        {   
            float heuristicDistance = abs((m_waypoints[UnvisitedWaypoints[i]].m_position - m_waypoints[EndIndex].m_position).length()) ;
            if((m_waypoints[UnvisitedWaypoints[i]].m_pathDistance + heuristicDistance) < distance)
            {
                // Find node with lowest distance value
                distance = m_waypoints[UnvisitedWaypoints[i]].m_pathDistance;
                NextIndex = UnvisitedWaypoints[i] ;
            }
            //std::cout<<"S hurty "<<distance<<' '<<m_waypoints[UnvisitedWaypoints[i]].m_pathDistance<<'\n';
        }
        //m_waypoints[NextIndex].m_pathWaypoints.push_back(m_waypoints[CurrentIndex].m_position);
        CurrentIndex = NextIndex;

        //std::cout<<"----------------------------------------------\n";
        //printWaypoints(m_waypoints[NextIndex].m_pathWaypoints);
    }

    //std::cout<<"Segmentation Faulty "<<StartIndex<<' '<<CurrentIndex<<' '<<EndIndex<<'\n';

    // Pushback end waypoint's position
    m_waypoints[EndIndex].m_pathWaypoints.push_back(m_waypoints[EndIndex].m_position);
    // Pushback end position on navmesh
    m_waypoints[EndIndex].m_pathWaypoints.push_back(_end);
    
    //std::cout<<"----------------------------------------------\n";
    //printWaypoints(m_waypoints[EndIndex].m_pathWaypoints); 

    return m_waypoints[EndIndex].m_pathWaypoints;
}


void NavMesh::render() const
{
    //Render Navmesh
    m_vao->bind();

    m_vao->setData(ngl::SimpleVAO::VertexData(m_triangles.size() * sizeof(NavTriangle), m_triangles[0].m_pos1.m_x));
    m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, 0, 0);
    //m_vao->setVertexAttributePointer(1, 3, GL_FLOAT, sizeof(NavTriangle), 9);
    m_vao->setNumIndices(m_triangles.size() * 3);

    m_vao->draw();
    m_vao->unbind();

    // Render Waypoint Paths
    glPointSize(10);
    m_vaoWaypoints->bind();

    m_vaoWaypoints->setData(ngl::SimpleVAO::VertexData(m_waypointPaths.size() * sizeof(ngl::Vec3), m_waypointPaths[0].m_x));
    m_vaoWaypoints->setVertexAttributePointer(0, 3, GL_FLOAT, 0, 0);
    m_vaoWaypoints->setVertexAttributePointer(1, 3, GL_FLOAT, 0, 0);
    m_vaoWaypoints->setNumIndices(m_waypointPaths.size());

    m_vaoWaypoints->draw();
    m_vaoWaypoints->unbind();
}