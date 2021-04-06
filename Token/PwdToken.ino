
/****************************************************************************************************************************************************************
*  PwdToken.
*
*  A hardware implementation of a piece of paper with your password, use with judgment!
*
*
*  Copyright (C) 2021 Nicola Cimmino
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see http:*www.gnu.org/licenses/.
*
*
*  Copy  the contents of `secrets_example.h` into a new file `secrets.h` (this reduces the risk to push passwords to git as `secrets.h` is `.gitignore`d
*
****************************************************************************************************************************************************************/

#include <DigiKeyboard.h>
#include <EEPROM.h>
#include <CRC32.h>
#include "utils.h"
#include "secrets.h"
#include "config.h"
#include "nbFlash.h"

CRC32 crc;

uint8_t otpSecret[] = {OTP_SECRET};

const char password1[] PROGMEM = PASSWORD_1;
const char password2[] PROGMEM = PASSWORD_2;
const char password3[] PROGMEM = PASSWORD_3;
const char password4[] PROGMEM = PASSWORD_4;

const char *const passwords[] PROGMEM = {password1, password2, password3, password4};

uint32_t getOTP(uint32_t counter)
{
  crc.reset();

  for (uint8_t ix = 0; ix < OTP_SECRET_SIZE; ix++)
  {
    crc.update(otpSecret[ix]);
  }

  for (uint8_t ix = 0; ix < 4; ix++)
  {
    crc.update((uint8_t)((counter >> (ix * 8)) & 0xFF));
  }

  for (uint8_t ix = 0; ix < OTP_SECRET_SIZE; ix++)
  {
    crc.update(otpSecret[ix]);
  }

  uint32_t otp = crc.finalize();

  return otp;
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

uint32_t getRetrievalCounter()
{
  uint32_t retrievalCounter;
  EEPROM.get(EEPROM_RETRIEVAL_COUNT, retrievalCounter);

  return retrievalCounter;
}

void incrementRetrievalCounter()
{
  EEPROM.put(EEPROM_RETRIEVAL_COUNT, getRetrievalCounter() + 1);
}

void printBanner()
{
  DigiKeyboard.println("----- begin -----");
  DigiKeyboard.println("LBL: " PWD_TOKEN_LABEL);

  DigiKeyboard.print("OTP1: ");
  DigiKeyboard.println(getOTP(getBootCounter()));

  DigiKeyboard.print("OTP2: ");
  DigiKeyboard.println(getOTP(getRetrievalCounter()));

  // A guide to ensure the current keyboard layout is US.
  DigiKeyboard.println("Layout: US");
  DigiKeyboard.println("Hash: #");
  DigiKeyboard.println("Backslash: \\");
  DigiKeyboard.println("----- end -----");
}

void setup()
{
  incrementBootCounter();

  // To simplify HW assembly we use a pin as the ground so
  // the button can be soldered directly to the
  // board without the need of additional boards or flimsy
  // wire-wrapping.
  pinMode(PIN_GND, OUTPUT);
  digitalWrite(PIN_GND, LOW);

  pinMode(LED_A, OUTPUT);
  digitalWrite(LED_A, LOW);

  pinMode(BUTTON_SENSE, INPUT_PULLUP);

  DigiKeyboard.sendKeyStroke(0);

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

uint8_t selectedPasswordIx = 0;

void selectPassword()
{
  while (1)
  {
    while (digitalRead(BUTTON_SENSE) == HIGH)
    {
      DigiKeyboard.delay(10);
      digitalWrite(LED_A, nbFlash(selectedPasswordIx, false));
    }

    digitalWrite(LED_A, LOW);

    DigiKeyboard.delay(100);

    unsigned long pressStart = millis();
    while (digitalRead(BUTTON_SENSE) == LOW)
    {
      DigiKeyboard.delay(100);
      if (millis() - pressStart > 2000)
      {
        return;
      }
    }

    selectedPasswordIx = (selectedPasswordIx + 1) % PASWWORDS_COUNT;

    DigiKeyboard.delay(100);
  }
}

void loop()
{
  selectPassword();

  incrementRetrievalCounter();

  // Retrieve the password.
  char buffer[MAX_STRING_SIZE];
  strcpy_P(buffer, (char *)pgm_read_word(&(passwords[selectedPasswordIx])));

  // Spit out the password.
  DigiKeyboard.print(buffer);

  // Wipe it from memory.
  memset(buffer, 0, MAX_STRING_SIZE);
}
