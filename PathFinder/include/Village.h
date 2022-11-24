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

        void setVillagers();
        void update();
        void render() const;

        size_t numVillagers() const;

    private:
        float m_BoundWidth;
        float m_BoundHeight; 
        std::vector<Villager> m_Villagers;
        size_t m_numVillagers;

        std::unique_ptr<NavMesh> m_navMesh;
        std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif // !VILLAGE_H_