# Digital Overdrive Pedal Plugin

This basic audio effect plugin simulates an overdrive guitar pedal. 

The DSP chain is as follows:
Gain (Drive) -> Waveshaping -> IIR Low-Pass Filter (Tone) -> Gain (Level)

This matches the fundamental Op-Amp -> Low-Pass -> Voltage Divider architecture of an overdrive pedal.

---
### Build Instructions

A Windows or Mac device is required to build this plugin.

To build, perform the following:
- Install the Juce framework (with the Projucer) at [https://juce.com/get-juce/]
- Clone the repo and load the .jucer file in the Projucer
- Create an exporter to open the project your local IDE and execute the build.

