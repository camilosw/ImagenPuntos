#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "portmidi.h"
#include "porttime.h"

#define INPUT_BUFFER_SIZE 100
#define OUTPUT_BUFFER_SIZE 0
#define TIME_PROC ((int32_t (*)(void *)) Pt_Time)

enum Messages { NoteOff           = 0x80, 
                NoteOn            = 0x90, 
                PolyKeyPressure   = 0xA0, 
                ControllerChange  = 0xB0, 
                ProgramChange     = 0xC0, 
                ChannelPressure   = 0xD0, 
                PitchBend         = 0xE0 
};

void MidiInit();
int GetMidiDevice();
void OpenMidiIn(int in);
void CloseMidiIn();
void MidiEnd();
void ReadMidiControl(int MsgData1, int &CtlBuff);
void ReadMidiControl(int StatusData, int &CtlBuff1, int &CtlBuff2);
bool ReadMidiMessage(Messages &type, int &channel, int &id, int &value);