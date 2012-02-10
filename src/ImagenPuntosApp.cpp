#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/qtime/QuickTime.h"
#include "MidiControl.h"
#include "ParticleController.h"
#include <vector>
#include <iostream>
#include "Resources.h"
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
    gl::Texture background;
    bool midiDetected;
    qtime::MovieSurface	myMovie;
    bool	VideoPlay;

    int nullCtl1, nullCtl2, nullCtl3;
    bool randomPositionControl, randomRadiusControl;
    Shapes shapeControl;

    int imageNumber;
    int profile;      // Identificador de la configuración según el dispositivo físico que se usará
    int resolution;
    float radiusControl;
    float resolutionControl;
    float positionControl;
    int rControl;
    int gControl;
    int bControl;
};

void ImagenPuntosApp::setup()
{
    setWindowSize(720,480);
    setFrameRate(30);
    VideoPlay=false;
    myMovie = qtime::MovieSurface(loadResource("negfxh264.mov"));
    //myMovie = qtime::MovieSurface("Medea.mov");
    myMovie.setLoop( true, true );
    //gui = new SimpleGUI(this);
    //gui->lightColor = ColorA(1, 1, 0, 1);	
    //gui->addLabel("Dispositivos MIDI");

    midiDetected = false;

    imageNumber = 1;
    profile = 0;
    resolution = 5;
    radiusControl = 1;
    resolutionControl = 1;
    positionControl = 0;
    randomPositionControl = false;
    randomRadiusControl = false;
    shapeControl = Circle;
    rControl, gControl, bControl = 127;
        
    //surfaces.push_back(loadImage("../resources/greco01.jpg"));
    //surfaces.push_back(loadImage("../resources/greco02.jpg"));
    background=gl::Texture(loadImage(loadResource(FONDO)));
    surfaces.push_back(loadImage(loadResource("greco01.jpg")));
    surfaces.push_back(loadImage(loadResource("greco02.jpg")));
    surfaces.push_back(loadImage(loadResource("el_greco_pieta.jpg")));
    /*background = gl::Texture(loadImage("prueba2.JPG"));
    surfaces.push_back(loadImage("greco01.jpg"));
    surfaces.push_back(loadImage("greco02.jpg"));
    surfaces.push_back(loadImage("el_greco_pieta.jpg"));
    */
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
    case KeyEvent::KEY_v:
      {
      VideoPlay=!VideoPlay;
          
        if(VideoPlay==true)  // Play
              myMovie.play();
        else myMovie.stop();  
          
      }
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
           if (type == ControllerChange)
           {
               if (id == 0x10)
               {
                   if((value>=1)&&(value<=3)) radiusControl+=0.1;
                   else radiusControl-=0.1;
                   if(radiusControl<0) radiusControl=0;
                   if(radiusControl>2) radiusControl=2;
                   
                   
               }
               if (id == 0x11)
               {
                   if((value>=1)&&(value<=3)) resolutionControl+=0.1;
                   else resolutionControl-=0.1;
                   if(resolutionControl<0) resolutionControl=0;                   
               }
           }   
           if (type == PitchBend) 
                {
                //if (channel == 0x00)
                  //  {
                    //radiusControl = valueF;
                    //}
                //else 
                    if (channel== 0x09) 
                    {
                    //    resolutionControl = valueF;
                        positionControl = valueF;
                    }
                }
                
                // Verifica si corresponde a una nota
                if (type == NoteOn) 
                {
                    if ((id == 0x5b)&&(value==0x7f)) if(imageNumber >0)imageNumber--;        // <-
                    if ((id == 0x5c)&&(value==0x7f)) if(imageNumber <2) imageNumber++;        // ->
                    if (id == 0x36) randomPositionControl = !particleController.getRandomPosition();      // Plugin
                    if (id == 0x37) randomRadiusControl = !particleController.getRandomRadius();       // auto
                    if (id == 0x38) shapeControl = particleController.getShape() == Circle ? Square : Circle;  // pan
                   // if (id == 0x29) randomRadiusControl = false;   // send
                   // if (id == 0x56) shapeControl = Circle;       // loop
                   // if (id == 0x32) shapeControl = Square;      // flip
                    if ((id == 0x57)&&(value==0x7f)) randomPositionControl = !particleController.getRandomPosition();    // Plugin
                    if ((id == 0x58)&&(value==0x7f))randomRadiusControl = !particleController.getRandomRadius();       // auto
                    if ((id == 0x56)&&(value==0x7f)) shapeControl = particleController.getShape() == Circle ? Square : Circle;  // flip
                    if ((id == 0x5e) &&(value==0x7f))
                        {
                        if(VideoPlay!=true)
                            {
                            VideoPlay=true;  // Play
                            myMovie.play(); 
                            }
                        }
                    if ((id == 0x5d) &&(value==0x7f))
                        {
                        VideoPlay=false;  // Stop
                        myMovie.stop();
                        }               
                }
            }
            
    break;

    //Mapping para teclado MIDI standard
    case 1:   

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
        else if (id == 0x5b) {
          positionControl = valueF;
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
  particleController.setPosition(positionControl);
  particleController.setShape(shapeControl);
  particleController.setRandomRadius(randomRadiusControl);
  particleController.setRandomPosition(randomPositionControl);
    if(VideoPlay==true)
    { 
    Surface frame = myMovie.getSurface();
    particleController.update(frame);
    }
    else particleController.update(surfaces[imageNumber]);
}

void ImagenPuntosApp::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) ); 
    //gl::color color = Color(1.0, 1.0 1.0);
    //gl::color(color);
    gl::draw( background, getWindowBounds() );
    if (surfaces[imageNumber])
        particleController.draw();
    //gui->draw();
}

CINDER_APP_BASIC( ImagenPuntosApp, RendererGl )
