#pragma once
#include "Particle.h"
#include "cinder/Channel.h"
#include "cinder/Surface.h"
#include <list>

class ParticleController
{
public:
  ParticleController();
  ParticleController(int width, int height, int resolution);
  void update(ci::Surface surface, float MidiCtler1, float MidiCtler2, float MidiCtler3, float MidiCtler4, 
              bool rndPosFlag , bool rndRadiusFlag, Shapes shape);
  void draw();

  void setResolution(int value);

private:
  std::list<Particle> particles;
  int width;
  int height;
  int resolution;
};

