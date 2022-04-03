#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=115.00000762939453,215.00000953674316
AudioSynthWaveformSine   sine1;          //xy=130,69
AudioMixer4              mixer1;         //xy=317,141
//AudioAnalyzeToneDetect   tone2;          //xy=330.00001525878906,253.00000762939453
AudioAnalyzeToneDetect   tone1;          //xy=524,134
AudioOutputI2S           i2s1;           //xy=609,210
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 3);
//AudioConnection          patchCord2(playSdWav1, 0, tone2, 0);
AudioConnection          patchCord3(sine1, 0, mixer1, 0);
AudioConnection          patchCord4(mixer1, tone1);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=265,453
// GUItool: end automatically generated code

float freq;
float period;
float amp = -10;
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
  sine1.amplitude(0);
 
  period = 1/(freq/1000);
  //Serial.println("period: ");
  //Serial.print(period);

  if(!(SD.begin(10))){
    while(1){
      Serial.println("SD error");
      delay(500);
    }
  }
  
}

//global vars
elapsedMillis msecs;

void loop() {
  // put your main code here, to run repeatedly:
    //Serial.println("sampelPeriod: ");
    if(playSdWav1.isPlaying() == false){
      Serial.println("Start playing 1");
      playSdWav1.play("440.WAV");
      sine1.amplitude(0);
      while(tone1.available() == false){
        
      }
      delay(500);
      amp = tone1.read();
      Serial.print("SD amp: ");
      Serial.println(amp);
      sine1.amplitude(amp);
      delay(10); 
    }
    
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
