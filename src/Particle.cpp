#include "Particle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Particle::Particle(Vec2f location)
{
  this->location = location;
}

void Particle::draw()
{
  gl::color(color);
  gl::drawSolidCircle(location, radius);  
}