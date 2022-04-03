#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=142,276
AudioAnalyzeToneDetect   tone1;          //xy=383,330
AudioAmplifier           amp1;           //xy=389.00004959106445,255.00000762939453
AudioMixer4              mixer1;         //xy=413.00001525878906,127.00000381469727
AudioOutputI2S           i2s1;           //xy=553.0000152587891,249.00000619888306
AudioAnalyzeToneDetect   tone2;          //xy=579.0000190734863,126.00000381469727
AudioConnection          patchCord1(i2s2, 0, amp1, 0);
AudioConnection          patchCord2(i2s2, 0, mixer1, 2);
AudioConnection          patchCord3(i2s2, 1, tone1, 0);
AudioConnection          patchCord4(amp1, 0, i2s1, 0);
AudioConnection          patchCord5(amp1, 0, i2s1, 1);
AudioConnection          patchCord6(amp1, 0, mixer1, 3);
AudioConnection          patchCord7(mixer1, tone2);
AudioControlSGTL5000     sgtl5000_1;     //xy=125,359
// GUItool: end automatically generated code


//global vars
float freq;
float mixedVolume;


void setup(){
  Serial.begin(9600);
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(40);
  delay(1000);

  freq = 440;
  tone1.frequency(freq, 4);
  tone2.frequency(freq, 4);

  Serial.println("hello world");

  amp1.gain(-1.0);
}

void loop(){
  //PHASE ALIGNMENT
    if (tone2.available()) {
      mixedVolume = tone2.read();
      
      Serial.println(mixedVolume);
    }
}
