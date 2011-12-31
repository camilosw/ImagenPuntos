#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "MidiControl.h"
#include "ParticleController.h"
#include <vector>
#include <iostream>

int nullCtl1=NULL;
int nullCtl2=NULL;
int nullCtl3=NULL;

bool rndPosCtl=false;
bool rndRadiusCtl=false;
bool CircleCtl=false;

int imageNumber = 1;
int valueCtl;
int valueCtl2;
int resolution = 5;
int ResController;
int xResolution; 
int yResolution;
int DotControl =64;
int DotControlBuffer=0;
int ResControl=0;
int xControl=0;
int yControl=0;
int rControl=127;
int gControl=127;
int bControl=127;
using namespace ci;
using namespace ci::app;
using namespace std;

class ImagenPuntosApp : public AppBasic {
public:
    void prepareSettings(Settings *settings);
    void setup();
    void mouseDown( MouseEvent event );	
    void update();
    void draw();
    
    ParticleController particleController;
    vector<Surface> surfaces;
    //Surface surface;
    //Channel32f channel;
};

void ImagenPuntosApp::prepareSettings(Settings *settings)
{
    settings->setWindowSize(843,600);
    settings->setFrameRate(30);
}

void ImagenPuntosApp::setup()
{
    surfaces.push_back(loadImage("/PROYECTOS/programacion/cinder/ImagenPuntosGit/resources/greco01.jpg"));
    surfaces.push_back(loadImage("/PROYECTOS/programacion/cinder/ImagenPuntosGit/resources/greco02.jpg"));

    //surface = loadImage("/PROYECTOS/programacion/cinder/ImagenPuntosGit/resources/elgreco01.jpg");
    //channel = Channel32f(loadImage("/PROYECTOS/programacion/cinder/ImagenPuntosGit/resources/elgreco02.jpg"));
    MidiInit();
    
    
    OpenMidiIn(GetMidiDevice());
    
    //OpenMidiIn(1);
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
    if (valueCtl==0x41)rndPosCtl=false;
    if (valueCtl==0x43)rndRadiusCtl=true;
    if (valueCtl==0x45)rndRadiusCtl=false;
    if (valueCtl==0x47)CircleCtl=true;
    if (valueCtl==0x48)CircleCtl=false;
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
        ResController=(resolution+((ResControl/resolution)));
        particleController = ParticleController(xResolution, yResolution,ResController) ;
     
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
      
    particleController.update(surfaces[imageNumber], DotControl, rControl, gControl, bControl, rndPosCtl, rndRadiusCtl);
}

void ImagenPuntosApp::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) ); 
    if (surfaces[imageNumber])
        particleController.draw(CircleCtl);
    //gl::draw(gl::Texture(surface));
   // if (surface && channel)
     //   particleController.draw();
}

CINDER_APP_BASIC( ImagenPuntosApp, RendererGl )
