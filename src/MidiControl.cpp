#include "MidiControl.h"

PmStream *midiIn, *midiOut;
PmTimestamp timestamp;
PmEvent buffer[128];
PmError status;

void MidiInit() {
  Pm_Initialize();
  TIME_START;
}

void OpenMidiIn() {
  // Obtiene el id del dispositivo midi por defecto
  PmDeviceID deviceId = Pm_GetDefaultInputDeviceID();  
  Pm_OpenInput(&midiIn, deviceId,
                  DRIVER_INFO, 
                  INPUT_BUFFER_SIZE, 
                  TIME_PROC, 
                  TIME_INFO);
    
    Pm_SetFilter(midiIn, PM_FILT_REALTIME | PM_FILT_NOTE | PM_FILT_CLOCK);
    
    while (Pm_Poll(midiIn)) 
    {
        Pm_Read(midiIn, buffer, 1);
    }
}

void ReadMidiControl(int MsgData1, int &CtlBuff) {
  status = Pm_Poll(midiIn);
  if (status == TRUE) 
  {
      Pm_Read(midiIn, buffer, 1);
  }
  if ((Pm_MessageData1(buffer[0].message) == MsgData1))
  {    
      CtlBuff = Pm_MessageData2(buffer[0].message);
  }
}


void CloseMidiIn() {
  Pm_Close(midiIn);
}

void MidiEnd() {
  Pm_Terminate();
}