#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "Particle.h"

using namespace ci;

Particle::Particle(Vec2f location)
{
  this->location = location;
}

Particle::Particle(Vec2f location, int x, int y)
{
  this->location = location;
  this->x = x;
  this->y = y;
}

void Particle::draw()
{
    gl::color(color);
    
    if (shape == Square)
    {
        float x1 = location.x - radius;
        float y1 = location.y - radius;
        float x2 = location.x + radius;
        float y2 = location.y + radius;
        gl::drawSolidRect(Rectf(x1, y1, x2, y2));    
    }    
    else 
    {
        //radius = cos( location.y * 0.1f ) + sin( location.x * 0.1f ) + 2.0f;
        //radius = (sin( location.y * location.x  ) + 1.0f)*2.0f;
        //float xyOffset = sin( cos( sin( location.y * 0.3183f ) + cos( location.x * 0.3183f ) ) ) + 1.0f;
        //radius = xyOffset * xyOffset * 1.8f;
        
        gl::drawSolidCircle(location, radius);
    }	
}