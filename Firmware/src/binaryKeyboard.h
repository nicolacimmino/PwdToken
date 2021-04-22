/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Binary Keyboard.
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

#ifndef __BINARY_KEYBOARD_H__
#define __BINARY_KEYBOARD_H__

#include "config.h"
#include "lock.h"

namespace BinaryKeyboard
{

    void waitForPin()
    {
        uint16_t pinCode = 0;
        uint16_t digitIndex = 1;

        digitalWrite(PIN_LED_A, HIGH);

        while (1)
        {
            if (digitalRead(PIN_BUTTON_B) == LOW || digitalRead(PIN_BUTTON_A) == LOW)
            {
                pinCode = (pinCode >> 1) | ((digitalRead(PIN_BUTTON_B) == LOW) ? 0b1000000000000000 : 0);
                digitIndex = digitIndex << 1;

                if (digitIndex == 0)
                {
                    Lock::onFailedLogin();
                    digitIndex = 1;
                    pinCode = 0;
                }
            }

            while (digitalRead(PIN_BUTTON_B) == LOW || digitalRead(PIN_BUTTON_A) == LOW)
            {
                DigiKeyboard.delay(10);
            }

            DigiKeyboard.delay(100);

            if (pinCode == UNLOCK_PIN)
            {
                break;
            }
        }

        Lock::onSuccessfulLogin();

        digitalWrite(PIN_LED_A, LOW);
    }

} // namespace BinaryKeyboard

#endif

/*
 ****************************************************************************************************************************************************************/