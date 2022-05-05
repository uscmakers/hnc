///////////////////////////////////
// copy the Design Tool code here
///////////////////////////////////
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=390.00000762939453,130.00000190734863
AudioInputI2S            i2s2;           //xy=391.00000381469727,323.00000381469727
AudioAnalyzeToneDetect   tone1;          //xy=632.0000076293945,377.0000057220459
AudioOutputI2S           i2s1;           //xy=647.0000076293945,125.00000190734863
AudioMixer4              mixer1;         //xy=648.0000076293945,201.00000381469727
AudioAnalyzeToneDetect   tone2;          //xy=861,198
AudioConnection          patchCord1(sine1, 0, i2s1, 0);
AudioConnection          patchCord2(sine1, 0, i2s1, 1);
AudioConnection          patchCord3(sine1, 0, mixer1, 0);
AudioConnection          patchCord4(i2s2, 0, mixer1, 1);
AudioConnection          patchCord5(i2s2, 1, tone1, 0);
AudioConnection          patchCord6(mixer1, tone2);
AudioControlSGTL5000     sgtl5000_1;     //xy=374.00000762939453,406.00000381469727
// GUItool: end automatically generated code

//global vars
elapsedMillis msecs;
float inputVolume = 0;
float mixedVolume;
float amptemp;
float amp;
float freq;
float period;
float samplePeriod;

void setup() {
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
  //set initial frequency to A440 for testing purposes
  sine1.frequency(freq);
  sine1.amplitude(0.5);

   Serial.println("hello world");
    period = 1/(freq/1000);
  Serial.print("period: ");
  Serial.println(period);

  amp = analogRead(A1);
}


void loop() { 
  samplePeriod = period/2;
  if (msecs > samplePeriod) {   //IMPORTANT - what sampling rate is needed/possible? order of microseconds?
    //VOLUME ALIGNMENT
    if (tone1.available()) {
      msecs = 0;
      inputVolume = tone1.read();
    
      //match output volume to input volume
      //sine1.amplitude(inputVolume);
      amptemp = analogRead(A1)*0.00185;
  
    if (amptemp > amp + 0.05 || amptemp < amp - 0.05){
      amp = amptemp;
      sine1.amplitude(amp);
    }
     //Serial.println(amp);


      Serial.print(inputVolume); //test1
      Serial.print("  ");
    }
    
    //PHASE ALIGNMENT
    if (tone2.available()) {
      mixedVolume = tone2.read();
      if (mixedVolume > 0.2*inputVolume) { //continuosly restart the sine wave until a cancelling phase is hit
        sine1.phase(0);
        Serial.print("Change  ");
      }
      Serial.println(mixedVolume);
    }
  }
}
