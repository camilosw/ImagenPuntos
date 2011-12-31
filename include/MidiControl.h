#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "portmidi.h"
#include "porttime.h"

#define INPUT_BUFFER_SIZE 100
#define OUTPUT_BUFFER_SIZE 0
#define TIME_PROC ((int32_t (*)(void *)) Pt_Time)

void MidiInit();
int GetMidiDevice();
void OpenMidiIn(int in);
void CloseMidiIn();
void MidiEnd();
void ReadMidiControl(int MsgData1, int &CtlBuff);
void ReadMidiControl(int StatusData, int &CtlBuff1, int &CtlBuff2);