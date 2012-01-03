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

void ParticleController::update(Surface surface, float MidiCtler1, float MidiCtler2, float MidiCtler3, 
                                float MidiCtler4, bool rndPosFlag, bool rndRadiusFlag, Shapes shape)
{
    MidiCtler1 = (MidiCtler1/127);
    for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {

      // Modifica la posición de la partícula según la resolución;
      float xPos = (p->getX() + 0.5f) * resolution;
      float yPos = (p->getY() + 0.5f) * resolution;
      p->setLocation(Vec2f(xPos, yPos));

      // Determina si la partícula es visible. Si no lo es, continúa con la siguiente
      if ( (p->getLocation().x - resolution) > width ||
           (p->getLocation().y - resolution) > height) {
        continue;
      }

      // Obtiene el color de un pixel de la imagen
      ColorA8u color = surface.getPixel(p->getLocation());
      // Obtiene el nivel de gris
      float gray = (color.r / 255.0f + color.g / 255.0f + color.b / 255.0f) / 3.0f;
      //float radius = (gray);//+(MidiCtler1*4.5f);
      if (rndRadiusFlag==true) {
        p->setRadius(MidiCtler1*Rand::randFloat( 1.0f, 10.0f));
      }        
      else {
        p->setRadius(MidiCtler1*7.0f);
      }
      p->setColor(Color(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f));    
      
      if (rndPosFlag) {
        Vec2f location = p->getLocation() + Rand::randVec2f();
        p->setLocation(location);
      }                    
      p->setShape(shape);
    }    
    
    //for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {
    //  float radius = (channel.getValue(p->location)* MidiCtler1*4.5f);
       
    //ColorA8u color = surface.getPixel(p->location);
    //p->update(radius, Color(color.r / (MidiCtler2*2.0f)+0.1, color.g / (MidiCtler3*2.0f)+0.1, color.b / (MidiCtler4*2.0f)+0.1));
  //}
}

void ParticleController::draw()
{
  for(list<Particle>::iterator p = particles.begin(); p != particles.end(); p++) {
    // Determina si la partícula es visible. Si no lo es, la ignora y continúa con la siguiente
    if ( (p->getLocation().x - resolution) > width ||
          (p->getLocation().y - resolution) > height) {
      continue;
    }
    p->draw();
  }
}