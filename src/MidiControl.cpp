#include "MidiControl.h"

#define STRING_MAX 80

const PmDeviceInfo *devInfo;

PmStream *midiIn, *midiOut;
PmTimestamp timestamp;
PmEvent buffer[128];
PmError status;
PmEvent *event;

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

  // Reserva memoria para el objeto que contendrá los mensajes midi
  event = (PmEvent *)malloc(sizeof(PmEvent));
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
    
  // Ignora todos los mensajes de tiempo real
  Pm_SetFilter(midiIn, PM_FILT_REALTIME | PM_FILT_CLOCK );
    
  // Limpia el buffer que contiene los mensajes midi
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

bool ReadMidiMessage(Messages &type, int &channel, int &id, int &value) {
  if (Pm_Read(midiIn, event, sizeof(long)) > 0) {
    long status = Pm_MessageStatus(event->message);
    long data1 = Pm_MessageData1(event->message);
    long data2 = Pm_MessageData2(event->message);
    
    // Obtiene el canal
    channel = status & 0x0F;

    // Verfica el tipo de mensaje, eliminando la información del canal
    switch (status & 0xF0) {
    case NoteOn:
      type = NoteOn;
      id = data1;
      value = data2;
      break;
    case ControllerChange:
      type = ControllerChange;
      id = data1;
      value = data2;
      break;
    case ProgramChange:
      type = ProgramChange;
      id = 0;
      value = data1;
      break;
    case PitchBend:
      type = PitchBend;
      id = 0;
      value = data2;
      break;
    }

    // TODO: agregar los demás tipos de mensajes
    return true;
  }
  return false;
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