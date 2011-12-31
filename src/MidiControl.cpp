
#include "MidiControl.h"
#define STRING_MAX 80
const PmDeviceInfo *devInfo;

PmStream *midiIn, *midiOut;
PmTimestamp timestamp;
PmEvent buffer[128];
PmError status;

int get_number(char *prompt)
{
    char line[STRING_MAX];
    int n = 0, i;
    printf(prompt);
    while (n != 1) {
        n = scanf("%d", &i);
        fgets(line, STRING_MAX, stdin);
        
    }
    return i;
}


void MidiInit()
{
  Pm_Initialize();
  Pt_Start(1, 0, 0);
}

int GetMidiDevice()
{
   
    int nDev =Pm_CountDevices();
    int i;
    for(i=0; i<(nDev/2); i++)
    {
    devInfo=Pm_GetDeviceInfo(i);
    const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
    if(info!=NULL)
        {
        printf("(%i) %s\n", i, info->name);
        //printf("(%i) %s\n", i, info->interf); //This parameter shows who is the midi system
        }
    } 
// The user can chose a midi in and a midi out port

int in = get_number("Type input number: ");
return in;
}
void OpenMidiIn(int in)
{
  Pm_OpenInput(&midiIn, in, NULL, INPUT_BUFFER_SIZE, TIME_PROC, NULL);
    
  Pm_SetFilter(midiIn, PM_FILT_REALTIME | PM_FILT_CLOCK );
    
  while (Pm_Poll(midiIn)) {
    Pm_Read(midiIn, buffer, 1);
  }
}

void ReadMidiControl(int MsgData1,int &CtlBuff)
{
  status = Pm_Poll(midiIn);
  if (status == TRUE) {
    Pm_Read(midiIn,buffer,1);
  }
  if((Pm_MessageData1(buffer[0].message)==MsgData1)) {    
    CtlBuff=Pm_MessageData2(buffer[0].message);
  }
}   

void ReadMidiControl(int StatusData,int &CtlBuff1,int &CtlBuff2)
{
  status = Pm_Poll(midiIn);
  if (status == TRUE) {
    Pm_Read(midiIn,buffer,1);
  }
  if((Pm_MessageStatus(buffer[0].message)==StatusData)) {    
    CtlBuff1 = Pm_MessageData1(buffer[0].message);
    CtlBuff2 = Pm_MessageData2(buffer[0].message);
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