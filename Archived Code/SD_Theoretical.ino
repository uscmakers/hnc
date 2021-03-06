#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=115.00000762939453,215.00000953674316
AudioSynthWaveformSine   sine1;          //xy=130,69
AudioMixer4              mixer1;         //xy=317,141
AudioAnalyzeToneDetect   tone2;          //xy=330.00001525878906,253.00000762939453
AudioAnalyzeToneDetect   tone1;          //xy=524,134
AudioOutputI2S           i2s1;           //xy=609,210
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 3);
AudioConnection          patchCord2(playSdWav1, 0, tone2, 0);
AudioConnection          patchCord3(sine1, 0, mixer1, 0);
AudioConnection          patchCord4(mixer1, tone1);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=265,453
// GUItool: end automatically generated code

float freq;
float amp;
const int pMax = 1023;
int phasedel;
int state;

void setup() {
  Serial.begin(9600);
  AudioMemory(30);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  delay(1000);

  // Get initial potentiometer reading
  phasedel = analogRead(A0);
  state = phasedel/(pMax/3);

  Serial.print("Initial potentiometer reading: ");
  Serial.println(phasedel);
  Serial.println("Iniital state: ");
  Serial.println(state);



  if(!(SD.begin(10))){
    while(1){
      Serial.println("SD error");
      delay(500);
    }
  }

  // set the frequency to be detected
  stateChange(state); 
}

// global vars
elapsedMicros microsecs;

void loop() {  
    int tempState = analogRead(A0)/(pMax/3); 

    if (tempState != state)
    {
      state = tempState;
      Serial.print("Set state to ");
      Serial.println(state);

      stateChange(state); // change the frequency and WAV file being played
    }



   /* 
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
    */

    if (microsecs > 1) {   // sampling rate
      //VOLUME & PHASE ALIGNMENT
      if (tone1.available()) {
        microsecs = 0;
        float mixedVolume = tone1.read();

        if (mixedVolume > 0.05) { //continuosly restart the sine wave until a cancelling phase is hit
          sine1.phase(0);
          Serial.print("Change  ");
        }

        Serial.println(mixedVolume);
      }
   }
}

// readjust frequency and start playing new WAV file
void stateChange (int state) {
  if (state == 0) {
    freq = 440;
    playSdWav1.play("440.WAV");
  }
  else if (state == 1) {
    freq = 1000;
    playSdWav1.play("1000Hz.WAV");
  }
  else if (state == 2) {
    freq = 2000;
    playSdWav1.play("2000Hz.WAV");
  }
  tone1.frequency(freq, 4);
  tone2.frequency(freq, 4);
  while(tone2.available() == false){}
  amp = tone2.read();
  sine1.amplitude(amp);
  sine1.frequency(freq);
}
