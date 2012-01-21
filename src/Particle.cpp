#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "Particle.h"

using namespace ci;

Particle::Particle(Vec2f location)
{
  this->location = location;

  //GLfloat *verts = new float[(SEGMENTS+2)*2];
}

Particle::Particle(Vec2f location, int x, int y)
{
  this->location = location;
  this->x = x;
  this->y = y;
  //GLfloat *verts = new float[(SEGMENTS+2)*2];
}

Particle::~Particle() {
    //delete [] verts;
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
        
        //this->drawSolidCircle(location, radius);
        gl::drawSolidCircle(location, radius);
    }	
}

void Particle::drawSolidCircle( const Vec2f &center, int radius )
{
    verts[0] = center.x;
    verts[1] = center.y;
    for( int s = 0; s <= SEGMENTS; s++ ) {
        float t = s / (float)SEGMENTS * 2.0f * 3.14159f;
        verts[(s+1)*2+0] = center.x + math<float>::cos( t ) * radius;
        verts[(s+1)*2+1] = center.y + math<float>::sin( t ) * radius;
    }
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, verts );
    glDrawArrays( GL_TRIANGLE_FAN, 0, SEGMENTS + 2 );
    glDisableClientState( GL_VERTEX_ARRAY );
}