#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "MidiControl.h"
#include "ParticleController.h"
#include <vector>
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

class ImagenPuntosApp : public AppBasic {
public:
    void setup();
    void mouseDown( MouseEvent event );	
    void update();
    void draw();
    
    ParticleController particleController;
    vector<Surface> surfaces;
    bool midiDetected;

    int nullCtl1, nullCtl2, nullCtl3;
    bool rndPosCtl, rndRadiusCtl, CircleCtl;

    int imageNumber;
    int profile;      // Identificador de la configuración según el dispositivo físico que se usará
    int valueCtl;
    int valueCtl2;
    int resolution;
    int ResController;
    int xResolution; 
    int yResolution;
    int DotControl;
    int DotControlBuffer;
    int ResControl;
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

    midiDetected = false;

    int nullCtl1, nullCtl2, nullCtl3 = NULL;
    bool rndPosCtl,rndRadiusCtl, CircleCtl;

    rndPosCtl=false;
    rndRadiusCtl=false;
    CircleCtl=false;
    imageNumber = 1;
    profile = 0;
    resolution = 5;
    DotControl = 64;
    DotControlBuffer = 0;
    ResControl = 0;
    xControl, yControl = 0;
    rControl, gControl, bControl = 127;

    
    //surfaces.push_back(loadImage("../resources/greco01.jpg"));
    //surfaces.push_back(loadImage("../resources/greco02.jpg"));

    
    surfaces.push_back(loadImage("/PROYECTOS/programacion/cinder/ImagenPuntosGit/resources/greco01.jpg"));
    surfaces.push_back(loadImage("/PROYECTOS/programacion/cinder/ImagenPuntosGit/resources/greco02.jpg"));

    MidiInit();
       
    //OpenMidiIn(GetMidiDevice());
    
    OpenMidiIn(1);
    particleController = ParticleController(getWindowWidth(), getWindowHeight(), resolution);
}

void ImagenPuntosApp::mouseDown( MouseEvent event )
{
    quit();
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
                
            // Verifica si el mensaje midi corresponde a una perilla o un control deslizable
            if (type == PitchBend) 
                {
                if (channel == 0x00)
                    {
                    DotControl = value;
                    }
                else if (channel== 0x09) 
                    {
                        ResControl = value;
                    }
                }
                
                // Verifica si corresponde a una nota
                if (type == NoteOn) 
                {
                    if (id == 0x57) imageNumber = 1;        // <-
                    if (id == 0x58) imageNumber = 0;        // ->
                    if (id == 0x2b) rndPosCtl = true;       // Plugin
                    if (id == 0x4a) rndPosCtl = false;      // auto
                    if (id == 0x2a) rndRadiusCtl = true;    // pan
                    if (id == 0x29) rndRadiusCtl = false;   // send
                    if (id == 0x56) CircleCtl = true;       // loop
                    if (id == 0x32) CircleCtl = false;      // flip
                }
            }
            
    break;
    case 1:
    //Mapping para teclado MIDI standard

    // Lee todos los mensajes midi que estén pendientes en el buffer
    while (ReadMidiMessage(type, channel, id, value)) {
      
      // Verifica si el mensaje midi corresponde a una perilla o un control deslizable
      if (type == ControllerChange) {
        if (id == 0x4A) {
          DotControl = value;
        }
        else if (id == 0x47) {
          ResControl = value;
        }
      }

      // Verifica si corresponde a una nota
      if (type == NoteOn) {
        if (id == 0x3c) imageNumber = 1;        // C4 (DO)
        if (id == 0x3e) imageNumber = 0;        // D4 (RE)
        if (id == 0x40) rndPosCtl = true;       // E4 (MI)
        if (id == 0x41) rndPosCtl = false;      // F4 (FA)
        if (id == 0x43) rndRadiusCtl = true;    // G4 (SOL)
        if (id == 0x45) rndRadiusCtl = false;   // A4 (LA)
        if (id == 0x47) CircleCtl = true;       // B4 (SI)
        if (id == 0x48) CircleCtl = false;      // C5 (DO)
      }
    }
    
    break;
  }

  //if(nullCtl1==10)
  //{
  //    if(DotControl>=41) 
  //        {
  //            cout<<"41!"<<endl;
  //        if (DotControlBuffer>0) DotControlBuffer-=2;
  //        }
  //
  //if (DotControl<=6) DotControlBuffer+=2;
  //} 
    
  //if (surfaces[imageNumber])
      
      /*if(DotControl==65)
      {
          DotControlBuffer--; 
          if (DotControlBuffer<0) DotControlBuffer=0;
          DotControl=0;
      }
      if(DotControl==1)
      {
          DotControlBuffer ++;
          if (DotControlBuffer>127) DotControlBuffer=127;
          DotControl=0;    
      }*/
    
  Shapes shape = CircleCtl == true ? Square : Circle;
  
  ResController = (resolution + ((ResControl / resolution)));
  particleController.setResolution(ResController);
  particleController.update(surfaces[imageNumber], DotControl, rControl, gControl, bControl, 
    rndPosCtl, rndRadiusCtl, shape);
}

void ImagenPuntosApp::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) ); 
    if (surfaces[imageNumber])
        particleController.draw();
}

CINDER_APP_BASIC( ImagenPuntosApp, RendererGl )
