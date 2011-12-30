#pragma once
#include "Particle.h"
#include "cinder/Channel.h"
#include "cinder/Surface.h"
#include <list>

class ParticleController
{
public:
  ParticleController();
  ParticleController(int xParticles, int yParticles, int resolution);
  void update(ci::Surface surface);
  void draw();

  std::list<Particle> particles;
};

