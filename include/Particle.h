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
    
    void setLocation(Vec2f value) { location = value; }
    void setRadius(float value) { radius = value; }
    void setColor(Color value) { color = value; }
    void setShape(Shapes value) { shape = value; }
    
    Vec2f getLocation() { return location; }
    float getRadius() { return radius; }
    Color getColor() { return color; }
    Shapes getShape() { return shape; }    
    int getX() { return x; }
    int getY() { return y; }
    
private:
    int x, y;
    Vec2f location;
    float radius;
    Color color;
    Shapes shape;
};
