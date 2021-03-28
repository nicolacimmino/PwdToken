
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
//#define BUILD_LABEL_AND_SEAL

#include <DigiKeyboard.h>
#include <EEPROM.h>
#include <CRC32.h>
#include "utils.h"
#include "secrets.h"
#include "config.h"

uint32_t getOTP(uint32_t counter)
{
  CRC32 crc;

  crc.update(counter);

  for (uint8_t ix = 0; ix < PWD_TOKEN_SEAL_SECRET_SIZE; ix++)
  {
    crc.update(sealSecret[ix]);
  }
  uint32_t otp = crc.finalize();

  return otp % 100000;
}

uint32_t getBootCounter()
{
  uint32_t bootCounter;
  EEPROM.get(EEPROM_BOOT_COUNT, bootCounter);

  return bootCounter;
}

void incrementBootCounter()
{
  EEPROM.put(EEPROM_BOOT_COUNT, getBootCounter() + 1);
}

uint32_t getTypeCounter()
{
  uint32_t typeCounter;
  EEPROM.get(EEPROM_TYPE_COUNT, typeCounter);

  return typeCounter;
}

void incrementTypeCounter()
{
  EEPROM.put(EEPROM_TYPE_COUNT, getTypeCounter() + 1);
}

void printBanner()
{
  DigiKeyboard.println("LBL: " PWD_TOKEN_LABEL);

  DigiKeyboard.print("OTP1: ");
  DigiKeyboard.println(getOTP(getBootCounter()));

  DigiKeyboard.print("OTP2: ");
  DigiKeyboard.println(getOTP(getTypeCounter()));

  // A guide to ensure they current keyboard layout is US.
  DigiKeyboard.println("Kayboard Layout: US");
  DigiKeyboard.println("Hash: #");
  DigiKeyboard.println("Backslash: \\");
}

void setup()
{
  incrementBootCounter();

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
  DigiKeyboard.sendKeyStroke(0);

  analogWrite(LED_A, 10);
  while (digitalRead(BUTTON_SENSE) == HIGH)
  {
    DigiKeyboard.delay(100);
  }

  incrementTypeCounter();

  // Spit out the password.
  DigiKeyboard.print(F(PWD_TOKEN_PASSWORD));

  digitalWrite(LED_A, LOW);

  while (1)
  {
    DigiKeyboard.delay(5000);
  }
}
