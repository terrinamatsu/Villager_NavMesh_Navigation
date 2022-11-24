#include "Village.h"

#include <iostream>
#include <ngl/Util.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOFactory.h>

#include "Random.h"

Village::Village(size_t _numVillagers, const float _BoundWidth, const float _BoundHeight)
{
    m_numVillagers = _numVillagers;
    m_BoundWidth = _BoundWidth;
    m_BoundHeight = _BoundHeight;
    
    m_Villagers.resize(m_numVillagers);
    
    m_navMesh = std::make_unique<NavMesh>(10, 10);
    m_navMesh->initialiseTestWaypoints();

    m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);

    // Initialising the Python Interpreter
    Py_Initialize();
    PyObject *main;
    PyObject *dict;
    // Get the main from python
    main = PyImport_ImportModule("__main__");
    // ..And get the Dictionary from main for reading & writing data
    dict = PyModule_GetDict(main);
}

size_t Village::numVillagers() const
{
    return m_numVillagers;
}

void Village::setVillagers()
{
    for(auto &v : m_Villagers)
    {
        if(!(v.timerTick(1)))
        {
            v.Move();
            if(v.m_isIdle)
            {
                v.timerReset(100);
                
                v.SetWaypoints(m_navMesh->FindWaypointPathDijkstra(v.m_position, Random::randomVec3XZ(m_BoundWidth, m_BoundHeight)));
                
                //v.AddRandomWaypoint(m_BoundWidth, m_BoundHeight);
                
                // Debug, going to random point then nearest node, to check it is correctly finding the closest node.
                //ngl::Vec3 pos = ngl::Vec3(Random::randomVec3XZ(10,10));
                //v.AddWaypoint(pos);
                //v.AddWaypoint(m_navMesh->getClosestWaypointPosition(pos));
            }
        }
    }
}

void Village::update()
{
    setVillagers();
}

void Village::render() const
{
    glPointSize(5);

    m_vao->bind();

    m_vao->setData(ngl::SimpleVAO::VertexData(m_Villagers.size() * sizeof(Villager), m_Villagers[0].m_position.m_x));
    m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(Villager), 0);
    m_vao->setVertexAttributePointer(1, 3, GL_FLOAT, sizeof(Villager), 3);
    //m_vao->setVertexAttributePointer(2, 1, GL_FLOAT, sizeof(Villager), 9);
    m_vao->setNumIndices(m_Villagers.size());

    //glEnable(GL_PROGRAM_POINT_SIZE);
    m_vao->draw();
    //glDisable(GL_PROGRAM_POINT_SIZE);
    m_vao->unbind();

    // Draw NavMesh
    m_navMesh->render();
}