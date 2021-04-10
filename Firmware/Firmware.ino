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
#include "src/config.h"
#include "secrets.h"
#include "secretGlobals.h"
#include "src/nbFlash.h"
#include "src/counters.h"
#include "src/banner.h"
#include "src/morseKeyboard.h"

uint8_t selectedPasswordIx = 0;

void setup()
{
  Counters::incrementCounter(EEPROM_BOOT_COUNT);

  pinMode(PIN_LED_A, OUTPUT);
  digitalWrite(PIN_LED_A, LOW);

  pinMode(PIN_BUTTON_A, INPUT_PULLUP);
  pinMode(PIN_BUTTON_B, INPUT_PULLUP);

  DigiKeyboard.sendKeyStroke(0);

  // Press and hold Button B before reset to see the banner.
  if (digitalRead(PIN_BUTTON_B) == LOW)
  {
    Banner::print();
    while (digitalRead(PIN_BUTTON_A) == LOW)
    {
      DigiKeyboard.delay(100);
    }

    // Debounce.
    DigiKeyboard.delay(100);
  }
}

void waitUnlockPassword()
{
  while (1)
  {
    char buffer[MAX_PWD_LEN];
    MorseKeyboard::getWord(buffer, MAX_PWD_LEN);
    if (strcmp(buffer, UNLOCK_PASSWORD) == 0)
    {
      return;
    }
  }
}

void selectPassword()
{
  while (1)
  {
    while (digitalRead(PIN_BUTTON_A) == HIGH)
    {
      DigiKeyboard.delay(10);
      digitalWrite(PIN_LED_A, NBFlasher::flashCount(selectedPasswordIx, false));
    }

    digitalWrite(PIN_LED_A, LOW);

    DigiKeyboard.delay(100);

    unsigned long pressStart = millis();
    while (digitalRead(PIN_BUTTON_A) == LOW)
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
  waitUnlockPassword();

  while (1)
  {
    selectPassword();

    typeSelectedPassword();

    if (digitalRead(PIN_BUTTON_A) == LOW || digitalRead(PIN_BUTTON_B) == LOW)
    {
      DigiKeyboard.delay(100);
    }
  }
}

/*
 ****************************************************************************************************************************************************************/
