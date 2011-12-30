#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "Particle.h"

using namespace ci;

Particle::Particle(Vec2f location)
{
  this->location = location;
}

void Particle::draw()
{
  gl::color(color);
  //gl::drawSolidCircle(location, radius);
  float x1 = location.x - radius;
  float y1 = location.y - radius;
  float x2 = location.x + radius;
  float y2 = location.y + radius;
  gl::drawSolidRect(Rectf(x1, y1, x2, y2));
}