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
#include "lock.h"

namespace MorseKeyboard
{

#define LOOKUP_TABLE_LEN 64
#define INTER_LETTER_DELAY_MS 1000
#define WORD_END_MARKER '.' // .-.-.-

    char *lookupTable = ".EISH54V.3UF....2ARL.....WP..J.1TNDB6.X..KC..Y..MGZ7.Q..O.8..90.";

    uint8_t lookupIx = 0;
    uint8_t dashOffset = 64;

    void advanceLookup(bool dot)
    {
        dashOffset = dashOffset >> 1;
        lookupIx += (dot) ? 1 : dashOffset;

        if (lookupIx >= LOOKUP_TABLE_LEN)
        {
            lookupIx = 0;
        }
    }

    void resetLookup()
    {
        lookupIx = 0;
        dashOffset = 64;
    }

    void waitForPassword()
    {
        char buffer[MAX_PWD_LEN];
        unsigned long lastUserInputTime = 0;
        uint8_t bufferIx = 0;

        memset(buffer, 0, MAX_PWD_LEN);

        digitalWrite(PIN_LED_A, HIGH);

        while (1)
        {
            if (digitalRead(PIN_BUTTON_B) == LOW || digitalRead(PIN_BUTTON_A) == LOW)
            {
                advanceLookup(digitalRead(PIN_BUTTON_A) == LOW);
                lastUserInputTime = millis();
            }

            while (digitalRead(PIN_BUTTON_B) == LOW || digitalRead(PIN_BUTTON_A) == LOW)
            {
                DigiKeyboard.delay(10);
            }

            DigiKeyboard.delay(100);

            if (lastUserInputTime != 0 && millis() - lastUserInputTime > INTER_LETTER_DELAY_MS)
            {
                if (lookupTable[lookupIx] == WORD_END_MARKER)
                {
                    if (strcmp(buffer, UNLOCK_PASSWORD) == 0)
                    {
                        // Unlock.
                        break;
                    }

                    Lock::onFailedLogin();

                    memset(buffer, 0, MAX_PWD_LEN);
                    bufferIx = 0;
                }

                buffer[bufferIx++] = lookupTable[lookupIx];

                if (bufferIx == (MAX_PWD_LEN - 1))
                {
                    bufferIx = 0;
                }

                lastUserInputTime = 0;
                resetLookup();
            }
        }

        Lock::onSuccessfulLogin();

        digitalWrite(PIN_LED_A, LOW);
    }

} // namespace MorseKeyboard

#endif

/*
 ****************************************************************************************************************************************************************/