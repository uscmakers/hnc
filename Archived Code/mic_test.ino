// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 3-1: Peak Detection


///////////////////////////////////
// copy the Design Tool code here
///////////////////////////////////
// Declare directories, libraries, files you're referring to
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=314,265.1999969482422
AudioOutputI2S           i2s1;           //xy=555,226.1999969482422
// Two peaks for left and right
AudioAnalyzePeak         peak1;          //xy=567,300
AudioAnalyzePeak         peak2;          //xy=612,373.1999969482422
AudioConnection          patchCord1(i2s2, 0, i2s1, 0);
AudioConnection          patchCord2(i2s2, 0, i2s1, 1);
AudioConnection          patchCord3(i2s2, 0, peak1, 0);
AudioConnection          patchCord4(i2s2, 0, peak2, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=308.00000762939453,370.0000057220459
// GUItool: end automatically generated code




// Use these with the Teensy Audio Shield
// Declare constants
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

void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  // Setting mic sensitivity
  sgtl5000_1.micGain(36);
  delay(1000);
}

// for best effect make your terminal/monitor a minimum of 62 chars wide and as high as you can.

// Declare variable of type elaspedMillis, that automatically increases
elapsedMillis msecs;

void loop() {
  // Tutorial was playing music from the SD card. We want the input to be the microphone
//  if (playSdWav1.isPlaying() == false) {
//    Serial.println("Start playing");
//    //playSdWav1.play("SDTEST1.WAV");
//    playSdWav1.play("SDTEST2.WAV");
//    //playSdWav1.play("SDTEST3.WAV");
//    //playSdWav1.play("SDTEST4.WAV");
//    delay(10); // wait for library to parse WAV info
//  }
  
  // 40 for sampling rate, every 40 milliseconds
  if (msecs > 40) {
    if (peak1.available() && peak2.available()) {
      // Resets stopwatch
      msecs = 0;
      float leftNumber = peak1.read();
      float rightNumber = peak2.read();
      // Scales peak by 30 for width of monitor
      int leftPeak = leftNumber * 30.0;
      int rightPeak = rightNumber * 30.0;
      int count;
      for (count=0; count < 30-leftPeak; count++) {
        Serial.print(" ");
      }
      while (count++ < 30) {
        Serial.print("<");
      }
      Serial.print("||");
      for (count=0; count < rightPeak; count++) {
        Serial.print(">");
      }
      while (count++ < 30) {
        Serial.print(" ");
      }
      Serial.print(leftNumber);
      Serial.print(", ");
      Serial.print(rightNumber);
      Serial.println();
    }
  }
}
