#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "MidiControl.h"
#include "ParticleController.h"
#include <vector>
#include <iostream>
//#include "SimpleGUI.h"

using namespace ci;
using namespace ci::app;
using namespace std;
//using namespace mowa::sgui;

class ImagenPuntosApp : public AppBasic {
public:
    void setup();
    void keyDown( KeyEvent event );
    void update();
    void draw();
    
private:
    //SimpleGUI* gui;
    ParticleController particleController;
    vector<Surface> surfaces;
    bool midiDetected;

    int nullCtl1, nullCtl2, nullCtl3;
    bool randomPositionControl, randomRadiusControl;
    Shapes shapeControl;

    int imageNumber;
    int profile;      // Identificador de la configuración según el dispositivo físico que se usará
    int valueCtl;
    int valueCtl2;
    int resolution;
    int resolutionController;
    int xResolution; 
    int yResolution;
    float radiusControl;
    float resolutionControl;
    int xControl;
    int yControl;
    int rControl;
    int gControl;
    int bControl;
};

void ImagenPuntosApp::setup()
{
    setWindowSize(843,600);
    setFrameRate(30);

    //gui = new SimpleGUI(this);
    //gui->lightColor = ColorA(1, 1, 0, 1);	
    //gui->addLabel("Dispositivos MIDI");

    midiDetected = false;

    randomPositionControl = false;
    randomRadiusControl = false;
    shapeControl = Circle;
    imageNumber = 1;
    profile = 1;
    resolution = 5;
    radiusControl = 1;
    resolutionControl = 1;
    xControl, yControl = 0;
    rControl, gControl, bControl = 127;
        
    surfaces.push_back(loadImage("../resources/greco01.jpg"));
    surfaces.push_back(loadImage("../resources/greco02.jpg"));

    //surfaces.push_back(loadImage("/PROYECTOS/programacion/cinder/ImagenPuntosGit/resources/greco01.jpg"));
    //surfaces.push_back(loadImage("/PROYECTOS/programacion/cinder/ImagenPuntosGit/resources/greco02.jpg"));

    MidiInit();
       
    //OpenMidiIn(GetMidiDevice());
    
    OpenMidiIn(1);
    particleController = ParticleController(getWindowWidth(), getWindowHeight(), resolution);
}

void ImagenPuntosApp::keyDown( KeyEvent event ) 
{
  switch(event.getCode())
  {
  case KeyEvent::KEY_ESCAPE:
    quit();
    break;
  }
}

void ImagenPuntosApp::update()
{
    Messages type;
    int channel, id, value;
    
    switch (profile) 
    {
    //Alphatrack map
    case 0:
        while (ReadMidiMessage(type, channel, id, value)) {
          float valueF = lmap((float)value, 0.0f, 127.0f, 0.0f, 1.0f);
                
            // Verifica si el mensaje midi corresponde a una perilla o un control deslizable
            if (type == PitchBend) 
                {
                if (channel == 0x00)
                    {
                    radiusControl = valueF;
                    }
                else if (channel== 0x09) 
                    {
                        resolutionControl = valueF;
                    }
                }
                
                // Verifica si corresponde a una nota
                if (type == NoteOn) 
                {
                    if (id == 0x57) imageNumber = 1;        // <-
                    if (id == 0x58) imageNumber = 0;        // ->
                    if (id == 0x2b) randomPositionControl = true;       // Plugin
                    if (id == 0x4a) randomPositionControl = false;      // auto
                    if (id == 0x2a) randomRadiusControl = true;    // pan
                    if (id == 0x29) randomRadiusControl = false;   // send
                    if (id == 0x56) shapeControl = Circle;       // loop
                    if (id == 0x32) shapeControl = Square;      // flip
                    if (id == 0x36) randomPositionControl = !particleController.getRandomPosition();    // Plugin
                    if (id == 0x37)randomRadiusControl = !particleController.getRandomRadius();       // auto
                    if (id == 0x38) shapeControl = particleController.getShape() == Circle ? Square : Circle;  // flip
                
                                   }
            }
            
    break;
    case 1:
    //Mapping para teclado MIDI standard

    // Lee todos los mensajes midi que estén pendientes en el buffer
    while (ReadMidiMessage(type, channel, id, value)) {
      float valueF = lmap((float)value, 0.0f, 127.0f, 0.0f, 1.0f);

      // Verifica si el mensaje midi corresponde a una perilla o un control deslizable
      if (type == ControllerChange) {
        if (id == 0x4A) {
          radiusControl = valueF; 
        }
        else if (id == 0x47) {
          resolutionControl = valueF;
        }
      }

      // Verifica si corresponde a una nota
      if (type == NoteOn) {
        if (id == 0x3c) imageNumber = 1;                                                // C4 (DO)
        if (id == 0x3e) imageNumber = 0;                                                // D4 (RE)
        if (id == 0x40)                                                                 // E4 (MI)
            randomPositionControl = !particleController.getRandomPosition();   
        if (id == 0x41)                                                                 // F4 (FA)
            randomRadiusControl = !particleController.getRandomRadius();     
        if (id == 0x43)                                                                 // G4 (SOL)
            shapeControl = particleController.getShape() == Circle ? Square : Circle;          
      }
    }
    
    break;
  }

  particleController.setResolution(resolutionControl * 25 + resolution);
  particleController.setRadius(radiusControl);
  particleController.setShape(shapeControl);
  particleController.setRandomRadius(randomRadiusControl);
  particleController.setRandomPosition(randomPositionControl);
  particleController.update(surfaces[imageNumber]);
}

void ImagenPuntosApp::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) ); 

    if (surfaces[imageNumber])
        particleController.draw();
    //gui->draw();
}

CINDER_APP_BASIC( ImagenPuntosApp, RendererGl )
