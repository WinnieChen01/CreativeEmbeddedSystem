# Interacti Dog
## Additional Links
- blog: https://billowy-mailman-a67.notion.site/Interacti-Dog-6df013629201431cb6ed641ed122a393
- YouTube: https://youtu.be/BLaokN1lC_E

## Description
Interacti Dog is my final project for the Creative Embedded System course in Spring 2023. The material I used included ESP32 TTGO T-display, a distance sensor, a stepper motor, and a LED strip. An ESP32 program is written to collect distance information and to control the movement of the stepper motor as well as the light pattern for the LED strip.
![overview](https://user-images.githubusercontent.com/104162702/236983443-83eeaba8-d7e4-4cdb-8713-f4d01f41f864.jpeg)

## Materials
- ESP32 TTGO T-display 
- a distance sensor
- a stepper motor
- a LED strip (WS2812B)
- jumper wires
- 1/4 basswood, clipboard

## Steps
- Use jumper wires to connect all components 
<img src="https://user-images.githubusercontent.com/104162702/236983418-ccc2481b-3b0f-486d-8dfe-c3669a172502.jpeg" width="400" height="600">

- Laser cut all the enclosures: dog house uses clipboard, boxes inside the house use basswood 
<img src="https://user-images.githubusercontent.com/104162702/236983477-3d7bf4a2-4696-41e8-9c67-52d152fc13eb.jpeg" width="400" height="400">

- Use a hot glue gun to glue the wooden boxes and the stepper motor
<img src="https://user-images.githubusercontent.com/104162702/236983496-54358a64-c30e-4bcf-8dd4-941a4a5c2e2b.jpeg" width="600" height="400">

- After fixing the wooden stick onto the stepper motor tip, put the stick into the stuffed dog 
<img src="https://user-images.githubusercontent.com/104162702/236983536-d1aa55bb-4ff2-4860-8013-1a18840e3ac2.jpeg" width="600" height="400">

- Add the LED lights to the ceiling and walls of the dog house

## Arduino program 
- Open file `FinalProject.ino` on Arduino
- Select `Tools -> Port -> /dev/cu.wchusbserialXXXXXXXX`
- Select `Boards > Boards Manager` under `Tools`, find and install `esp32`
- Select `Upload`

