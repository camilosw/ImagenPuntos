#pragma once
#include "cinder/Vector.h"
#include "cinder/Color.h"

#if defined( CINDER_MAC )
	#include <OpenGL/gl.h>
	#include <OpenGL/glext.h>
#elif defined( CINDER_MSW )
	#include "cinder/gl/GLee.h"
#else
	#define CINDER_GLES
	#define CINDER_GLES1
#endif

#define CIRCLE 0
#define SQUARE 1
#define SEGMENTS 10

enum Shapes { Circle, Square };

using namespace ci;

class Particle
{
public:
    Particle(ci::Vec2f location);
    Particle(ci::Vec2f location, int x, int y);
	~Particle();
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
	void drawSolidCircle( const Vec2f &center, int radius );

	GLfloat *verts;

    int x, y;
    Vec2f location;
    float radius;
    ColorA color;
    Shapes shape;
};
