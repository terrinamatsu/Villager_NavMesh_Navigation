#include "Villager.h"

Villager::Villager()
{
  m_colour = Random::randomPositiveVec3();
  m_speed = Random::randomPositiveFloat(6.0f) + 2.0f;
}

void Villager::AddWaypoint(ngl::Vec3 position)
{
  m_waypoints.push_back(position);
  ++m_numWaypoints;
}

void Villager::SetWaypoints(std::vector<ngl::Vec3> _positions)
{
  //std::cout<<"-----\n";
  m_waypoints.clear();
  m_numWaypoints = 0;
  for(auto P : _positions)
  {
    //std::cout<<P.m_x<<' '<<P.m_y<<' '<<P.m_z<<'\n';
    AddWaypoint(ngl::Vec3(P.m_x, P.m_y, P.m_z));
  }
}

void Villager::AddRandomWaypoint(float width, float height)
{
  auto newWaypoint = Random::randomVec3XZ(width, height);
  //std::cout<<newWaypoint.m_x<<' '<<newWaypoint.m_y<<' '<<newWaypoint.m_z<<'\n';

  m_waypoints.push_back(newWaypoint);
  ++m_numWaypoints;
}

void Villager::RemoveLastWaypoint()
{
  m_waypoints.pop_back();
  --m_numWaypoints;
}

void Villager::RemoveNextWaypoint()
{
  m_waypoints.erase(m_waypoints.begin());
  --m_numWaypoints;
}

void Villager::timerReset(float _waitTime)
{
  m_waitTimer = _waitTime;
}

bool Villager::timerTick(float _dt)
{
  m_waitTimer -= _dt;
  if(m_waitTimer < 0.0f)
  {
    return false;
  }
  return true;
}

void Villager::Update(float _dt)
{

  Move(_dt);
}

void Villager::Move(float _dt)
{
  // Check there is another waypoint to move to 
  float dtSpeed = m_speed * _dt;

  auto currentPos = m_position;
  if(m_numWaypoints >= 1)
  {
    if((m_waypoints[0] -  m_position).length() > dtSpeed)
    {
      auto movement = (m_waypoints[0] - m_position);
      movement.normalize();
      m_position += movement * dtSpeed;

      //std::cout<<m_position.m_x<<'\n';
    }
    else
    {
      m_position = m_waypoints[0];
      RemoveNextWaypoint();
    }
  }

  // Is idle if hasn't moved this update
  if(currentPos == m_position && m_waypoints.size() == 0)
  {
    m_isIdle = true;
  }
  else
  {
    m_isIdle = false;
  }
}


