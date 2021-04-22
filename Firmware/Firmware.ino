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
 *  Copy  the contents of secrets_example.h into a new file secrets.h (this reduces the risk to push passwords to git as secrets.h is .gitignore:d
 */

#include <DigiKeyboard.h>
#include <EEPROM.h>
#include "options.h"
#include "src/config.h"
#include "secrets.h"
#include "src/secretGlobals.h"
#include "src/nbFlash.h"
#include "src/counters.h"
#include "src/banner.h"
#if UNLOCK_MODE == UNLOCK_MORSE_KEYBOARD
#include "src/morseKeyboard.h"
#elif UNLOCK_MODE == UNLOCK_BINARY_KEYBOARD
#include "src/binaryKeyboard.h"
#endif

uint8_t selectedPasswordIx = 0;

void setup()
{
  pinMode(PIN_LED_A, OUTPUT);
  digitalWrite(PIN_LED_A, LOW);

  pinMode(PIN_BUTTON_B, INPUT_PULLUP);
  pinMode(PIN_BUTTON_A, INPUT_PULLUP);

  DigiKeyboard.sendKeyStroke(0);

  // Press and hold Button B before reset to see the banner.
  if (digitalRead(PIN_BUTTON_A) == LOW)
  {
    DigiKeyboard.delay(500);

    Banner::print();

    while (true)
    {
      DigiKeyboard.delay(100);
    }
  }
}

void waitUnlockPassword()
{
#if UNLOCK_MODE == UNLOCK_NONE
  return;
#elif UNLOCK_MODE == UNLOCK_MORSE_KEYBOARD
  MorseKeyboard::waitForPassword();
#elif UNLOCK_MODE == UNLOCK_BINARY_KEYBOARD
  BinaryKeyboard::waitForPin();
#endif
}

void selectPassword()
{
  while (1)
  {
    while (digitalRead(PIN_BUTTON_B) == HIGH)
    {
      DigiKeyboard.delay(10);
      digitalWrite(PIN_LED_A, NBFlasher::flashCount(selectedPasswordIx, false));
    }

    digitalWrite(PIN_LED_A, LOW);

    DigiKeyboard.delay(100);

    unsigned long pressStart = millis();
    while (digitalRead(PIN_BUTTON_B) == LOW)
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

void typeSelectedPassword()
{
  Counters::incrementCounter(EEPROM_RETRIEVAL_COUNT);

  // Retrieve the password.
  char buffer[MAX_PWD_LEN];
  strcpy_P(buffer, (char *)pgm_read_word(&(passwords[selectedPasswordIx])));

  // Spit out the password.
  DigiKeyboard.print(buffer);

  // Wipe it from memory.
  memset(buffer, 0, MAX_PWD_LEN);
}

void loop()
{
  Counters::incrementCounter(EEPROM_BOOT_COUNT);

  waitUnlockPassword();

  while (1)
  {
    selectPassword();

    typeSelectedPassword();

    if (digitalRead(PIN_BUTTON_B) == LOW || digitalRead(PIN_BUTTON_A) == LOW)
    {
      DigiKeyboard.delay(100);
    }
  }
}

/*
 ****************************************************************************************************************************************************************/
