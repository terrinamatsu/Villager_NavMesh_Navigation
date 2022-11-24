#include "Random.h"

std::mt19937 Random::m_generator;

auto randomFloatDistribution = std::uniform_real_distribution<float>(-1.0f, 1.0f);
auto randomPositiveFloatDistribution = std::uniform_real_distribution<float>(0,1.0f);

ngl::Vec3 Random::randomVec3(float _XRange, float _YRange, float _ZRange)
{
  return ngl::Vec3(randomFloatDistribution(m_generator) * _XRange, randomFloatDistribution(m_generator) * _YRange, randomFloatDistribution(m_generator) * _ZRange);
}

ngl::Vec3 Random::randomVec3XZ(float _XRange, float _ZRange)
{
  return ngl::Vec3(randomFloatDistribution(m_generator) * _XRange, 0, randomFloatDistribution(m_generator) * _XRange);
}

ngl::Vec3 Random::randomPositiveVec3(float _multiplier)
{
  return ngl::Vec3(randomPositiveFloatDistribution(m_generator)*_multiplier, randomPositiveFloatDistribution(m_generator)*_multiplier, randomPositiveFloatDistribution(m_generator)*_multiplier);
}

float Random::randomFloat(float _multiplier)
{
  return randomFloatDistribution(m_generator) * _multiplier;
}

float Random::randomPositiveFloat(float _multiplier)
{
  return randomPositiveFloatDistribution(m_generator) * _multiplier;
}
