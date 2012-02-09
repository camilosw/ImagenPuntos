#pragma once
#include "Particle.h"
#include "cinder/Channel.h"
#include "cinder/Surface.h"
#include <list>

class ParticleController
{
public:
  ParticleController();
  ParticleController(int width, int height, int resolution);
  // TODO: convertir los par�metros en m�todos set
  void update(ci::Surface surface);
  void draw();

  void setResolution(int value);
  void setRadius(float value) { radius = value; }
  void setPosition(float value) { position = value; }
  void setShape(Shapes value) { shape = value; }  
  void setRandomRadius(bool value) { randomRadius = value; }
  void setRandomPosition(bool value) { randomPosition = value; }
  void setR(int value) { r = value; }
  void setG(int value) { g = value; }
  void setB(int value) { b = value; }

  Shapes getShape() { return shape; }
  bool getRandomRadius() { return randomRadius; }
  bool getRandomPosition() { return randomPosition; }


private:
  std::list<Particle> particles;
  int width;
  int height;

  int resolution;           // Distancia entre las part�culas
  float radius;             // Radio de las part�culas
  float position;           // Posici�n en x de la imagen
  Shapes shape;             // Forma de las part�culas (c�rculo o cuadrado)
  bool randomRadius;        // Determina si el tama�o es est�tico o var�a de forma aleatoria
  bool randomPosition;      // Determina si la posici�n es est�tica o var�a de forma aleatoria
  int r;
  int g;
  int b;
};

