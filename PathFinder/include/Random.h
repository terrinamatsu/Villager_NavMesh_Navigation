#ifndef RANDOM_H_
#define RANDOM_H_

#include <ngl/Vec3.h>
#include <random>

class Random
{
    public:
        static ngl::Vec3 randomVec3(float _multiplier = 1.0f);
        static ngl::Vec3 randomVec3XZ(float _XRange = 1.0f, float _ZRange = 1.0f);
        static ngl::Vec3 randomPositiveVec3(float _multiplier = 1.0f);

        static float randomFloat(float _multiplier = 1.0f);
        static float randomPositiveFloat(float _multiplier = 1.0f);

    private:
        static std::mt19937 m_generator;
};

#endif // !RANDOM_H_