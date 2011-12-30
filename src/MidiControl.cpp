//#include <stdlib.h>
//#include <string.h>
//#include <assert.h>
//#include <stdio.h>
//#include <math.h>

#include "MidiControl.h"
 
PmStream *midiIn, *midiOut;
PmTimestamp timestamp;
PmEvent buffer[128];
PmError status;

void MidiInit()
    {
        Pm_Initialize();
        /*
        status=Pm_Initialize();
        if (status!=pmNoError) 
        {
        printf("01PortMidi error:%s\n",Pm_GetErrorText(status));
        exit(1);
        }*/
        TIME_START;
    }


void OpenMidiIn(int in)
    {
        Pm_OpenInput(&midiIn, in,
                     DRIVER_INFO, 
                     INPUT_BUFFER_SIZE, 
                     TIME_PROC, 
                     TIME_INFO);
    
        Pm_SetFilter(midiIn, PM_FILT_REALTIME | PM_FILT_CLOCK  );
    
        while (Pm_Poll(midiIn)) 
        {
            Pm_Read(midiIn, buffer, 1);
        }
    }

void ReadMidiControl(int MsgData1,int &CtlBuff)
{
    
    
    status = Pm_Poll(midiIn);
    if (status == TRUE) 
    {
        Pm_Read(midiIn,buffer,1);
        
    }
    if((Pm_MessageData1(buffer[0].message)==MsgData1))
    {    
        CtlBuff=Pm_MessageData2(buffer[0].message);
    }
    
}   

void ReadMidiControl(int StatusData,int &CtlBuff1,int &CtlBuff2)
{
    
    
    status = Pm_Poll(midiIn);
    if (status == TRUE) 
    {
        Pm_Read(midiIn,buffer,1);
        
    }
    if((Pm_MessageStatus(buffer[0].message)==StatusData))
    {    
        CtlBuff1=Pm_MessageData1(buffer[0].message);
        CtlBuff2=Pm_MessageData2(buffer[0].message);
    }
    
}   




void CloseMidiIn()
    {
        Pm_Close(midiIn);
    }

void MidiEnd()
    {
        Pm_Terminate();
    }
    

//void OpenMidiOut();
//void CloseMidiOut();


