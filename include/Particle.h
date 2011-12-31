#pragma once
#include "cinder/Vector.h"
#include "cinder/Color.h"

using namespace ci;

class Particle
{
public:
    Particle(ci::Vec2f location);
     void draw(bool PartShape);
    
    inline void setLocation(Vec2f value) { location = value; }
    inline void setRadius(float value) { radius = value; }
    inline void setColor(Color value) { color = value; }
    
    inline Vec2f getLocation() { return location; }
    inline float getRadius() { return radius; }
    inline Color getColor() { return color; }
    
private:
    Vec2f location;
    float radius;
    Color color;
};
