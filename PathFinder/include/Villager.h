#ifndef VILLAGER_H_
#define VILLAGER_H_

#if defined(__APPLE__)
    #include <Python/Python.h>
#else
    #include <Python.h>
#endif

#include <ngl/Vec3.h>
#include <memory>

#include <iostream>
#include "Random.h"

class Villager
{
public:
    Villager();
    ~Villager() = default;

    void AddWaypoint(ngl::Vec3 position);
    void AddRandomWaypoint(float width, float height);
    void SetWaypoints(std::vector<ngl::Vec3> _positions);
    void RemoveLastWaypoint();
    void RemoveNextWaypoint();

    void timerReset(float _waitTime);
    bool timerTick(float _dt);

    void Move();

    ngl::Vec3 m_position = ngl::Vec3(0.0f, 0.0f, 0.0f);
    ngl::Vec3 m_colour = ngl::Vec3(1.0f, 1.0f, 1.0f); 
    std::vector<ngl::Vec3> m_waypoints;
    size_t m_numWaypoints = 0;
    float m_speed = 0.1f;
    float m_waitTimer = 0.0f;
    bool m_isIdle = true;
};

#endif // !VILLAGER_H_