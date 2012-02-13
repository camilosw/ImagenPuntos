#include "cinder/Vector.h"
#include "ParticleController.h"
#include "cinder/Rand.h"

using namespace ci;
using std::list;

ParticleController::ParticleController()
{
}
ParticleController::ParticleController(int width, int height, int resolution)
{
  this->width = width;
  this->height = height;
  this->resolution = resolution;
  int xParticles = width / resolution;
  int yParticles = height / resolution;
    
  for (int y = 0; y < yParticles; y++) {
    for (int x = 0; x < xParticles; x++) {
      float xPos = (x + 0.5f) * resolution;
      float yPos = (y + 0.5f) * resolution;
        particles.push_back(Particle(Vec2f(xPos, yPos), x, y));
    }
  }
}

void ParticleController::setResolution(int value)
{
  resolution = value;

  for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {
    // Modifica la posición de la partícula según la resolución;
    float xPos = (p->getX() + 0.5f) * resolution;
    float yPos = (p->getY() + 0.5f) * resolution;
    p->setLocation(Vec2f(xPos, yPos));
  }
}

void ParticleController::update(Surface surface)
{
  float offset = lmap(position, 0.0f, 1.0f, -(float)width, (float)width);
  Vec2f offsetVector = Vec2f(offset, 0.0);
  for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {

    // Determina si la partícula es visible. Si no lo es, continúa con la siguiente
    if ( (p->getLocation().x + offset - resolution) > width ||
         (p->getLocation().x + offset - resolution) < 0 ||
         (p->getLocation().y - resolution) > height) {
      continue;
    }

    // Obtiene el color de un pixel de la imagen
    ColorA8u color = surface.getPixel(p->getLocation() + offsetVector);
    // Obtiene el nivel de gris
    //float gray = (color.r / 255.0f + color.g / 255.0f + color.b / 255.0f) / 3.0f;
    //float radius = (gray);//+(radius*4.5f);
    p->setColor(ColorA(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255));    
            
    if (randomRadius) {
      p->setRadius(radius * Rand::randFloat( 1.0f, 10.0f));
    }        
    else {
      p->setRadius(radius * 7.0f);
    }
      
    if (randomPosition) {
      Vec2f location = p->getLocation() + Rand::randVec2f();
      p->setLocation(location);
    }                    
      
    p->setShape(shape);
  }    
    
    //for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {
    //  float radius = (channel.getValue(p->location)* radius*4.5f);
       
    //ColorA8u color = surface.getPixel(p->location);
    //p->update(radius, Color(color.r / (MidiCtler2*2.0f)+0.1, color.g / (MidiCtler3*2.0f)+0.1, color.b / (MidiCtler4*2.0f)+0.1));
  //}
}

void ParticleController::draw()
{
  float offset = lmap(position, 0.0f, 1.0f, -(float)width, (float)width);
  for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {
    // Determina si la partícula es visible. Si no lo es, la ignora y continúa con la siguiente
    if ( (p->getLocation().x + offset - resolution) > width ||
         (p->getLocation().x + offset - resolution) < 0 ||
         (p->getLocation().y - resolution) > height) {
      continue;
    }
    p->draw();
  }
}