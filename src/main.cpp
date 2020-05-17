/*
 * Keyboard emulator for USB volume control
 *
 * Uses the HID-Project library from NicoHood
 * (see https://github.com/NicoHood/HID)
 * to emulate a keyboard with esoteric key values.
 *
 */
#include "Arduino.h"
#include <HID-Project.h>
#include <HID-Settings.h>
#include <Button.h>

// Rotary Encoder interrupt pins (0, 1, 2, 3, 7) on Leonardo
#define pinA 2
#define pinB 3

// Use the click as a Mute/Unmute
#define playPausePin 11
Button playPause(playPausePin,PULLUP);

void setup()
{
  // Rotary encoder setup
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  // Use the library to communicate with Windows
  Consumer.begin();
}

void loop()
{
  // -1 = Long press
  // 0 = not pressed
  // 1 = short press
  int buttonPressed = playPause.checkPress() ;
  if (buttonPressed == 1)
  {
    Consumer.write(MEDIA_PLAY_PAUSE );
  } 



  // Did the Rotary Encode get turned?
  // (Pin A goes LOW before going HIGH at next detent)
  if (digitalRead(pinA) == LOW)
  {

    // Clockwise?
    if (digitalRead(pinB) == LOW)
    {
      Consumer.write(MEDIA_VOL_DOWN);
    } else {
      Consumer.write(MEDIA_VOL_UP);
    }

    // Wait until rotation to next detent is complete
    while (digitalRead(pinA) != HIGH)
    {
      // Debounce delay
      delay(5);
    }
  }


}