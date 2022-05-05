// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 3-1: Peak Detection
 

///////////////////////////////////
// copy the Design Tool code here
///////////////////////////////////
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=314,265.1999969482422
AudioSynthWaveformSine   sine1;          //xy=351.4000015258789,159
AudioOutputI2S           i2s1;           //xy=564.000129699707,162.2000026702881
AudioAnalyzePeak         peak1;          //xy=567,300
AudioAnalyzePeak         peak2;          //xy=612,373.1999969482422
AudioConnection          patchCord1(i2s2, 0, peak1, 0);
AudioConnection          patchCord2(i2s2, 0, peak2, 0);
AudioConnection          patchCord3(sine1, 0, i2s1, 0);
AudioConnection          patchCord4(sine1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=308.00000762939453,370.0000057220459
AudioAnalyzeNoteFrequency notefreq;
// GUItool: end automatically generated code

// GUItool: end automatically generated code




// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

int phasedel;

int del = 0;
void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(36);
  delay(1000);

  // Get initial potentiometer reading
  phasedel = analogRead(A1)*2.3;

  //--
  sine1.frequency(440);
  sine1.amplitude(0.1);
}

// for best effect make your terminal/monitor a minimum of 62 chars wide and as high as you can.

elapsedMillis msecs;

void loop() { 
  // Change phase if potentiometer value is changed
  int phasetemp = analogRead(A1)*2.3;
  
  if (phasetemp > phasedel + 5 || phasetemp < phasedel - 5){
    phasedel = phasetemp;
    sine1.phase(phasedel);
  }
  Serial.println(phasedel);

  if (msecs > 40) {
    if (peak1.available() && peak2.available()) {
      msecs = 0;
      float leftNumber = peak1.read();
      float rightNumber = peak2.read();
      //--match tone output to peak
      sine1.amplitude(leftNumber);
      //--
    }
  }

  delay(100);
  
}
