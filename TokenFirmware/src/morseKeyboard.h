/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Morse Keyboard.
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
 */

#ifndef __MORSE_KEYBOARD_H__
#define __MORSE_KEYBOARD_H__

#include "config.h"

namespace MorseKeyboard
{

#define LOOKUP_TABLE_LEN 64
#define INTER_LETTER_DELAY_MS 1000
#define WORD_END_MARKER '.' // .-.-.-

char *lookupTable = ".EISH54V.3UF....2ARL.....WP..J.1TNDB6.X..KC..Y..MGZ7.Q..O.8..90.";

uint8_t currentDecoderIndex = 0;
uint8_t currentDashJump = 64;

void advanceLookup(bool dot)
{
    currentDashJump = currentDashJump >> 1;
    currentDecoderIndex += (dot) ? 1 : currentDashJump;

    if (currentDecoderIndex >= LOOKUP_TABLE_LEN)
    {
        currentDecoderIndex = 0;
    }
}

void resetLookup()
{
    currentDecoderIndex = 0;
    currentDashJump = 64;
}

void getWord(char *buffer, uint8_t bufferSize)
{
    unsigned long lastUserInputTime = 0;
    uint8_t bufferIx = 0;

    memset(buffer, 0, bufferSize);

    digitalWrite(PIN_LED_A, HIGH);

    while (1)
    {
        if (digitalRead(PIN_BUTTON_A) == LOW || digitalRead(PIN_BUTTON_B) == LOW)
        {
            advanceLookup(digitalRead(PIN_BUTTON_B) == LOW);
            lastUserInputTime = millis();
        }

        while (digitalRead(PIN_BUTTON_A) == LOW || digitalRead(PIN_BUTTON_B) == LOW)
        {
            DigiKeyboard.delay(10);
        }

        DigiKeyboard.delay(100);

        if (lastUserInputTime != 0 && millis() - lastUserInputTime > INTER_LETTER_DELAY_MS)
        {
            if (lookupTable[currentDecoderIndex] == WORD_END_MARKER)
            {
                break;
            }

            buffer[bufferIx++] = lookupTable[currentDecoderIndex];

            if (bufferIx == (bufferSize - 1))
            {
                break;
            }

            lastUserInputTime = 0;
            resetLookup();
        }
    }

    digitalWrite(PIN_LED_A, LOW);
}

} // namespace MorseKeyboard

#endif

/*
 ****************************************************************************************************************************************************************/