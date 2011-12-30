#include "ParticleController.h"
#include "cinder/Vector.h"
#include "cinder/Rand.h"

using namespace ci;
using std::list;

ParticleController::ParticleController()
{
}
ParticleController::ParticleController(int xParticles, int yParticles, int resolution)
{
  for (int y = 0; y < yParticles; y++) {
    for (int x = 0; x < xParticles; x++) {
      float xPos = (x + 0.5f) * resolution;
      float yPos = (y + 0.5f) * resolution;
      particles.push_back(Particle(Vec2f(xPos, yPos)));
    }
  }
}

void ParticleController::update(Surface surface)
{
  for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {
    // Obtiene el color de un pixel de la imagen
    ColorA8u color = surface.getPixel(p->getLocation());
    // Obtiene el nivel de gris
    float gray = (color.r / 255.0f + color.g / 255.0f + color.b / 255.0f) / 3.0f;
    float radius = gray * 1.5f;

    p->setRadius(radius);
    p->setColor(Color(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f));    
    Vec2f location = p->getLocation() + Rand::randVec2f();
    //p->setLocation(location);
  }
}

void ParticleController::draw()
{
  for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {
    p->draw();
  }
}