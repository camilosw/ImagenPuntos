#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <vector>
#include "MidiControl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

int resolution = 5;
int xResolution; 
int yResolution;
int DotControl = 64;
int ResControl = 0;
int xControl = 0;
int yControl = 0;
int rControl = 127;
int gControl = 127;
int bControl = 127;

class ImagenPuntosApp : public AppBasic {
  public:
  void prepareSettings(Settings *settings);
  void setup();
  void mouseDown( MouseEvent event );	
  void update();
  void draw();

  ParticleController particleController;
  vector<Surface> surfaces;
};

void ImagenPuntosApp::prepareSettings(Settings *settings)
{
  settings->setWindowSize(600, 400);
  settings->setFrameRate(30);
}

void ImagenPuntosApp::setup()
{
  surfaces.push_back(loadImage("../resources/prueba2.jpg"));
  surfaces.push_back(loadImage("../resources/prueba4.jpg"));

  MidiInit();
  OpenMidiIn();

  resolution = 5;
  xResolution = getWindowWidth() / resolution;
  yResolution = getWindowHeight() / resolution;
  particleController = ParticleController(xResolution, yResolution, resolution);
}

void ImagenPuntosApp::mouseDown( MouseEvent event )
{
  exit(1);
}

void ImagenPuntosApp::update()
{  
  ReadMidiControl(0x4a, DotControl);
  ReadMidiControl(0x16, ResControl);
  ReadMidiControl(0x17, xControl);
  ReadMidiControl(0x18, yControl);
  ReadMidiControl(0x19, rControl);
  ReadMidiControl(0x1a, gControl);
  ReadMidiControl(0x1b, bControl);

  float ResControler = (resolution + ((ResControl / resolution)));
  //particleController = ParticleController(xResolution-xControl, yResolution-yControl, ResControler);
  particleController = ParticleController(xResolution-xControl, yResolution-yControl, ResControler);

  int i = 0;
  if (surfaces[i])
    particleController.update(surfaces[i]);
}

void ImagenPuntosApp::draw()
{
  // clear out the window with black
  gl::clear( Color( 0, 0, 0 ) ); 
  //gl::draw(gl::Texture(surface));
  int i = 0;
  if (surfaces[i])
    particleController.draw();
}

CINDER_APP_BASIC( ImagenPuntosApp, RendererGl )
