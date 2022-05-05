#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=141,133
AudioAnalyzeToneDetect   tone1;          //xy=383,330
AudioAmplifier           amp1;           //xy=389.00004959106445,255.00000762939453
AudioMixer4              mixer1;         //xy=413.00001525878906,127.00000381469727
AudioOutputI2S           i2s1;           //xy=553.0000152587891,249.00000619888306
AudioAnalyzeToneDetect   tone2;          //xy=579.0000190734863,126.00000381469727
AudioConnection          patchCord1(sine1, amp1);
AudioConnection          patchCord2(sine1, tone1);
AudioConnection          patchCord3(sine1, 0, mixer1, 2);
AudioConnection          patchCord4(amp1, 0, i2s1, 0);
AudioConnection          patchCord5(amp1, 0, i2s1, 1);
AudioConnection          patchCord6(amp1, 0, mixer1, 3);
AudioConnection          patchCord7(mixer1, tone2);
AudioControlSGTL5000     sgtl5000_1;     //xy=125,359
// GUItool: end automatically generated code


float freq;
float period;
float samplePeriod;
float mixedVolume;

void setup() {
  Serial.begin(9600);
  AudioMemory(30);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  delay(1000);

  freq = 440;
  tone1.frequency(freq, 4);
  //set initial frequency to A440 for testing purposes
  sine1.frequency(freq);
  sine1.amplitude(0.5);

  Serial.println("hello world");

  amp1.gain(-1.0);
  

}

//global vars


void loop() {
  // put your main code here, to run repeatedly:
  //PHASE ALIGNMENT
    if (tone2.available()) {
      mixedVolume = tone2.read();
      
      Serial.println(mixedVolume);
    }
}
