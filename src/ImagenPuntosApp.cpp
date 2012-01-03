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
    bool rndPosCtl, rndRadiusCtl, CircleCtl = false;

    imageNumber = 1;
    profile = 1;
    resolution = 5;
    DotControl = 64;
    DotControlBuffer = 0;
    ResControl = 0;
    xControl, yControl = 0;
    rControl, gControl, bControl = 127;

    surfaces.push_back(loadImage("../resources/greco01.jpg"));
    surfaces.push_back(loadImage("../resources/greco02.jpg"));

    MidiInit();
       
    //OpenMidiIn(GetMidiDevice());
    
    OpenMidiIn(9);
    xResolution = getWindowWidth() / resolution;
    yResolution = getWindowHeight() / resolution;
    particleController = ParticleController(xResolution, yResolution, resolution);
}

void ImagenPuntosApp::mouseDown( MouseEvent event )
{
    quit();
}
//Mapping para teclado MIDI standar

void ImagenPuntosApp::update()
{
  switch (profile) {
  case 0:
    ReadMidiControl(0x01,DotControl);
    //ReadMidiControl(0xb0,nullCtl1,DotControl);
    
    //ReadMidiControl(0x01,ResControl);
   // ReadMidiControl(0xe9,nullCtl2,DotControl);
    ReadMidiControl(0x07,ResControl);
    //DotControl=((DotControl*127)+DotControl)+(nullCtl2);
    //ReadMidiControl(0x15,ResControl);
    
    ReadMidiControl(0x90,valueCtl,nullCtl3);
    //if(valueCtl==0x68 ||valueCtl==0x70 ||valueCtl==0x78 ||valueCtl==0x70||valueCtl==0x7a) valueCtl=0;
    //ReadMidiControl(0x10,valueCtl2);
    
    //ReadMidiControl(0x58,imageNumberCtl);
    //ReadMidiControl(0x19,rControl);
    //ReadMidiControl(0x1a,gControl);
    //ReadMidiControl(0x1b,bControl);
    if (valueCtl==0x3c) imageNumber=1;
    if (valueCtl==0x3e) imageNumber=0;
    if (valueCtl==0x40) rndPosCtl=true;
    if (valueCtl==0x41) rndPosCtl=false;
    if (valueCtl==0x43) rndRadiusCtl=true;
    if (valueCtl==0x45) rndRadiusCtl=false;
    if (valueCtl==0x47) CircleCtl=true;
    if (valueCtl==0x48) CircleCtl=false;
    break;
  
  case 1:
    // Lee todos los mensajes midi que estén pendientes en el buffer
    Messages type;
    int id, value;
    while (ReadMidiMessage(type, id, value)) {
      
      // Verifica si el mensaje midi corresponde a una perilla o un control deslizable
      if (type == ControllerChange) {
        if (id == 0x4A) {
          DotControl = value;
        }
        else if (id == 0x07) {
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
    
  if (surfaces[imageNumber])
      ResController = (resolution + ((ResControl / resolution)));
  particleController = ParticleController(xResolution, yResolution, ResController) ;
     
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
