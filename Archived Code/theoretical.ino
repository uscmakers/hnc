#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine2;          //xy=111,265.00000381469727
AudioSynthWaveformSine   sine1;          //xy=153.00000381469727,73.00005531311035
AudioMixer4              mixer1;         //xy=340,145
AudioAnalyzeToneDetect   tone1;          //xy=547,138
AudioOutputI2S           i2s1;           //xy=632,214.00000476837158
AudioConnection          patchCord1(sine2, 0, mixer1, 1);
AudioConnection          patchCord2(sine1, 0, mixer1, 0);
AudioConnection          patchCord3(mixer1, tone1);
AudioConnection          patchCord4(mixer1, 0, i2s1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=288,457
// GUItool: end automatically generated code

float freq;
float period;
float samplePeriod;

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
  sine2.frequency(freq);
  sine2.amplitude(0.5);

  period = 1/(freq/1000);
  //Serial.println("period: ");
  //Serial.print(period);
  
}

//global vars
elapsedMillis msecs;

void loop() {
  // put your main code here, to run repeatedly:
    //Serial.println("sampelPeriod: ");
    
    samplePeriod = period/2;
    //Serial.print(samplePeriod);
    if (msecs > samplePeriod) {   //IMPORTANT - what sampling rate is needed/possible? order of microseconds?
    //VOLUME & PHASE ALIGNMENT
    if (tone1.available()) {
      msecs = 0;
      float mixedVolume = tone1.read();
      
      if (mixedVolume > 0.05) { //continuosly restart the sine wave until a cancelling phase is hit
        sine1.phase(0);
        Serial.print("Change  ");
      }
      
      Serial.println(mixedVolume);
    }
  }
}
