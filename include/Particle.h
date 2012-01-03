#pragma once
#include "cinder/Vector.h"
#include "cinder/Color.h"

#define CIRCLE 0
#define SQUARE 1

enum Shapes { Circle, Square };

using namespace ci;

class Particle
{
public:
    Particle(ci::Vec2f location);
    Particle(ci::Vec2f location, int x, int y);
    void draw();
    
    inline void setLocation(Vec2f value) { location = value; }
    inline void setRadius(float value) { radius = value; }
    inline void setColor(Color value) { color = value; }
    inline void setShape(Shapes value) { shape = value; }
    
    inline Vec2f getLocation() { return location; }
    inline float getRadius() { return radius; }
    inline Color getColor() { return color; }
    inline Shapes getShape() { return shape; }    
    inline int getX() { return x; }
    inline int getY() { return y; }
    
private:
    int x, y;
    Vec2f location;
    float radius;
    Color color;
    Shapes shape;
};
