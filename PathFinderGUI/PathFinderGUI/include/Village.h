#ifndef VILLAGE_H_
#define VILLAGE_H_

#include <ngl/SimpleVAO.h>

#include "Villager.h"
#include "NavMesh.h"

class Village
{
  public:
    Village() = default;
    Village(size_t _numVillagersl, const float _BoundWidth, const float _BoundHeight);
    ~Village() = default;

    void updateVillagers(float _dt);
    void update(float _dt);
    void render() const;

    size_t numVillagers() const;

    void changeNumVillagers(size_t _numVillagers);
    void extractVillagerInfo();

  private:
    float m_BoundWidth;
    float m_BoundHeight;
    std::vector<Villager> m_Villagers;
    size_t m_numVillagers;

    std::vector<ngl::Vec3> m_villagerPositions;
    std::vector<ngl::Vec3> m_villagerColours;

    std::unique_ptr<NavMesh> m_navMesh;
    std::unique_ptr<ngl::AbstractVAO> m_vao;


    void reloadScript();
    void setNewScriptPath(  const std::string &_p );

    std::unique_ptr <std::string> m_script;
    std::string m_filename;

    PyObject *m_main;
    PyObject *m_dict;

    PyObject *m_pyVillager;

    std::vector<ngl::Vec3> m_destination;
    std::vector<PyObject *> m_pyDestination;

    std::vector<PyObject *> m_pyNeeds;
};

#endif // !VILLAGE_H_
