#include "Village.h"

#include <iostream>
#include <ngl/Util.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOFactory.h>
#include <fstream>

#include "Random.h"

Village::Village(size_t _numVillagers, const float _BoundWidth, const float _BoundHeight)
{
  m_BoundWidth = _BoundWidth;
  m_BoundHeight = _BoundHeight;

  // Setup Villagers
  changeNumVillagers(_numVillagers);
  // Setup NavMesh
  m_navMesh = std::make_unique<NavMesh>(10, 10);
  m_navMesh->initialiseTestWaypoints();
  // Setup VAO
  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);

  // Initialising the Python Interpreter
  Py_Initialize();
  // Get the main from python
  m_main = PyImport_ImportModule("__main__");
  // ..And get the Dictionary from main for reading & writing data
  m_dict = PyModule_GetDict(m_main);

  // Load Villager Update Script
  setNewScriptPath("python/villager.py");
  reloadScript();
  PyRun_SimpleString(m_script->c_str());

  setNewScriptPath("python/TestPython.py");
  reloadScript();

  // Set Var Initial Values
  for(auto i = 0; i < _numVillagers; ++i)
  {
    m_destination.push_back(ngl::Vec3(0.0f, 0.0f, 0.0f));

    m_pyDestination.push_back(PyList_New(3));

    m_pyNeeds.push_back(PyList_New(8));
  }
}

size_t Village::numVillagers() const
{
  return m_numVillagers;
}

void Village::changeNumVillagers(size_t _numVillagers)
{
  m_numVillagers = _numVillagers;
  m_Villagers.resize(m_numVillagers);
}

void Village::updateVillagers(float _dt)
{
  for(auto &v : m_Villagers)
  {
    if(!(v.timerTick(_dt)))
    {
      v.Update(_dt);
      if(v.m_isIdle)
      {
        v.timerReset(10);

        v.SetWaypoints(m_navMesh->FindWaypointPathDijkstra(v.m_position, Random::randomVec3(m_BoundWidth, 10, m_BoundHeight)));

        //v.AddRandomWaypoint(m_BoundWidth, m_BoundHeight);

        // Debug, going to random point then nearest node, to check it is correctly finding the closest node.
        //ngl::Vec3 pos = ngl::Vec3(Random::randomVec3XZ(10,10));
        //v.AddWaypoint(pos);
        //v.AddWaypoint(m_navMesh->getClosestWaypointPosition(pos));
      }
    }
  }
}

void Village::update(float _dt)
{
  // PYTHON TESTING

  for(auto i = 0; i < m_destination.size(); ++i)
  {
      // Set values for Python to use
      PyList_SetItem(m_pyDestination[i], 0,PyFloat_FromDouble(m_destination[i].m_x));
      PyList_SetItem(m_pyDestination[i], 1,PyFloat_FromDouble(m_destination[i].m_y));
      PyList_SetItem(m_pyDestination[i], 2,PyFloat_FromDouble(m_destination[i].m_z));
      // this passes it to the main dictionary of the python script
      PyDict_SetItemString(m_dict, "destination", m_pyDestination[i]);

      PyDict_SetItemString(m_dict, "needs", m_pyNeeds[i]);

      // Run the script
      PyRun_SimpleString(m_script->c_str());

      // Retrieve the values from python code
      m_pyDestination[i] = PyMapping_GetItemString(m_dict,"destination");
      m_destination[i].m_x=PyFloat_AsDouble(PyList_GetItem(m_pyDestination[i],0));
      m_destination[i].m_y=PyFloat_AsDouble(PyList_GetItem(m_pyDestination[i],1));
      m_destination[i].m_z=PyFloat_AsDouble(PyList_GetItem(m_pyDestination[i],2));
      // now we are done reduce the reference count of the object
      Py_XDECREF(m_pyDestination[i]);

      m_pyNeeds[i] = PyMapping_GetItemString(m_dict,"needs");
      // now we are done reduce the reference count of the object
      Py_XDECREF(m_pyNeeds[i]);

      std::cout<<"Python Value Test: "<<m_destination[i].m_x<<' '<<m_destination[i].m_y<<' '<<m_destination[i].m_z<<'\n';
  }

  // \PYTHON TESTING

  updateVillagers(_dt);

  extractVillagerInfo();
}

void Village::extractVillagerInfo()
{
  m_villagerColours.clear();
  m_villagerPositions.clear();

  for(auto v : m_Villagers)
  {
    m_villagerColours.push_back(v.m_colour);
    m_villagerPositions.push_back(v.m_position);
  }
}

void Village::render() const
{
  glPointSize(5);

  m_vao->bind();

  m_vao->setData(ngl::SimpleVAO::VertexData(m_Villagers.size() * sizeof(Villager), m_Villagers[0].m_position.m_x));
  m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(Villager), 0);
  //m_vao->setData(ngl::SimpleVAO::VertexData(m_villagerColours.size() * sizeof(ngl::Vec3), m_villagerColours[0].m_x));
  //m_vao->setVertexAttributePointer(1, 3, GL_FLOAT, 0, 0);
  m_vao->setVertexAttributePointer(1, 3, GL_FLOAT, sizeof(Villager), 3);
  m_vao->setNumIndices(m_villagerPositions.size());

  //glEnable(GL_PROGRAM_POINT_SIZE);
  m_vao->draw();
  //glDisable(GL_PROGRAM_POINT_SIZE);
  m_vao->unbind();

  // Draw NavMesh
  m_navMesh->render();
}

// \/ copied from ngl Embed Python
void Village::setNewScriptPath(const std::string &_p)
{
  m_filename=_p;
  reloadScript();
}

void Village::reloadScript()
{
  if(m_script !=0)
  {
    m_script.release();
  }
  std::ifstream script(m_filename.c_str());
  if (!script.is_open())
  {
    std::cerr<<"File not found "<<m_filename.c_str()<<"\n";
    exit(EXIT_FAILURE);
  }
  // now read in the data
  m_script.reset(  new std::string((std::istreambuf_iterator<char>(script)), std::istreambuf_iterator<char>()));
  script.close();
}

