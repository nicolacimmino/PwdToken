
//  PwdTooken.
//  A hardware implementation of a piece of paper with your password, use with judgment!
//
//  
//  Copyright (C) 2019 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//
//
//  Copy  the contents of `secrets_example.h` into a new file `secrets.h` (this reduces the risk to push passwords to git as `secrets.h` is `.gitignore`d
//
//  * Edit the password needed
//  * Edit the label to something that means something to you (I would avoid the username!)
//  * Edit the seal to something you recognize, pretty much anything you can remember and is not sensitive will do
//  * **un**comment the line `#define BUILD_LABEL_AND_SEAL`
//  * Build and program you Digispaspark board
//
// This writes the seal. You can now program the actual password:
//
//  * **comment** the line `#define BUILD_LABEL_AND_SEAL`
//  * Build and program you Digispaspark board
//  * Verify that the LED is lit, this confirms that software loaded is the one capable of typing the password

// Uncomment to build the label and seal app. If commented the password typing app is built.
// #define BUILD_LABEL_AND_SEAL

#include <DigiKeyboard.h>
#include <EEPROM.h>
#include "secrets.h"
#include "config.h"

char *readStringFromEEPROM(uint8_t address, uint8_t len, char *buffer)
{
  memset(buffer, 0, len);
  for (uint8_t ix = 0; ix < len; ix++)
  {
    buffer[ix] = EEPROM.read(address + ix);
  }

  return buffer;
}

void writeStringToEEPROM(uint8_t address, uint8_t len, char *buffer)
{
  for (uint8_t ix = 0; ix < len; ix++)
  {
    EEPROM.write(address + ix, buffer[ix]);
  }
}

void printBanner()
{
  char buffer[MAX_STRING_SIZE];

  // A user defined label identifying this device.
  DigiKeyboard.print("LABEL: ");
  DigiKeyboard.println(readStringFromEEPROM(EEPROM_LABEL, MAX_STRING_SIZE, buffer));

  // A user defined seal proving the password has never been typed.
  DigiKeyboard.print("SEAL: ");
  DigiKeyboard.println(readStringFromEEPROM(EEPROM_SEAL, MAX_STRING_SIZE, buffer));

  // Date and time of the seal.
  DigiKeyboard.print("TS: ");
  DigiKeyboard.println(readStringFromEEPROM(EEPROM_SEALED_AT, MAX_STRING_SIZE, buffer));

  // A guide to ensure they current keyboard layout is US.
  DigiKeyboard.println("Kayboard Layout: US");
  DigiKeyboard.println("Hash: #");
  DigiKeyboard.println("Backslash: \\");
}

void setup()
{
  // To simplify HW assembly we use a pin as the ground so
  // the LED and the button can be soldered directly to the 
  // board without the need of additional boards or flimsy
  // wire-wrapping.
  pinMode(PIN_GND, OUTPUT);
  digitalWrite(PIN_GND, LOW);

  pinMode(LED_A, OUTPUT);
  digitalWrite(LED_A, LOW);

  pinMode(BUTTON_SENSE, INPUT_PULLUP);

  // Press an hold before reset to see the banner.
  if (digitalRead(BUTTON_SENSE) == LOW)
  {
    printBanner();
    while (digitalRead(BUTTON_SENSE) == LOW)
    {
      DigiKeyboard.delay(100);
    }

    // Debounce.
    DigiKeyboard.delay(100);
  }
}

void loop()
{
#ifdef BUILD_LABEL_AND_SEAL
  writeStringToEEPROM(EEPROM_LABEL, MAX_STRING_SIZE, PWD_TOKEN_LABEL);
  writeStringToEEPROM(EEPROM_SEAL, MAX_STRING_SIZE, PWD_TOKEN_SEAL);
  writeStringToEEPROM(EEPROM_SEALED_AT, MAX_STRING_SIZE, PWD_TOKEN_SEALED_AT);
#else
  DigiKeyboard.sendKeyStroke(0);

  analogWrite(LED_A, 10);
  while (digitalRead(BUTTON_SENSE) == HIGH)
  {
    DigiKeyboard.delay(100);
  }

  // Break the seal.
  writeStringToEEPROM(EEPROM_SEAL, MAX_STRING_SIZE, BROKEN_SEAL);
  
  // Spit out the password.
  DigiKeyboard.print(PWD_TOKEN_PASSWORD);
  
  digitalWrite(LED_A, LOW);
#endif

  while (1)
  {
    DigiKeyboard.delay(5000);
  }
}
