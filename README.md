# hnc
Our HNC (Hyperactive Noise Cancellation) technology can be implemented on any pair of headphones and will be able to selectively cancel out sine waves of different frequencies.

Final Code: HNC_Final.ino

Hardware/Electronics Requirements:
- Teensy 4.0
- Audio Shield for Teensy 4.0
- Potentiometer (to select an audio file to play and cancel out its corresponding frequency)
- Headphones

Software Requirements:
- Arduino 
- Teensyduino: https://www.pjrc.com/teensy/teensyduino.html
- SD card to store audio files of sine waves/noise to be cancelled out
  - Code references the names of audio files in the stateChange function

Instructions:
1. Solder Teensy onto Audio Shield
2. Connect Potentiometer to Teensy (GND, VCC, A0/Pin14)
3. Plug headphones into Audio Shield
4. Upload code onto Teensy
