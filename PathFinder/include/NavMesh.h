#ifndef NAVMESH_H_
#define NAVMESH_H_

#include <ngl/SimpleVAO.h>
#include <memory>
#include "NavTriangle.h"
#include "Waypoint.h"


class NavMesh
{
    public:
        NavMesh() = default;
        NavMesh(const float _BoundWidth, const float _BoundHeight);
        ~NavMesh() = default;

        void render() const;
 
        void connectWaypoints(size_t index1, size_t index2);
        void initialiseTestWaypoints();
        void initialiseWaypointLines();
        size_t numWaypoints();
        void printWaypoints();
        void printWaypoints(std::vector<ngl::Vec3> _waypoints);
        void waypointVisit(size_t toVisitIndex);
        size_t getClosestWaypoint(ngl::Vec3 _point);
        ngl::Vec3 getClosestWaypointPosition(ngl::Vec3 _point);

        size_t numTriangles();

        std::vector<ngl::Vec3> FindWaypointPathDijkstra(ngl::Vec3 _start, ngl::Vec3 _end);
        std::vector<ngl::Vec3> FindWaypointPathAStar(ngl::Vec3 _start, ngl::Vec3 _end);

    private:
        float m_BoundWidth;
        float m_BoundHeight;

        std::vector<Waypoint> m_waypoints;
        std::vector<ngl::Vec3> m_waypointPaths;

        std::vector<NavTriangle> m_triangles;

        std::unique_ptr<ngl::AbstractVAO> m_vao;
        std::unique_ptr<ngl::AbstractVAO> m_vaoWaypoints;
};

#endif // !NAVMESH_H_