/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Banner.
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

#ifndef __BANNER_H__
#define __BANNER_H__

#include <CRC32.h>
#include "config.h"
#include "../secrets.h"

#define VERSION_MAJOR "0"
#define VERSION_MINOR "01"

#if UNLOCK_MODE == UNLOCK_NONE
#define VARIANT_A "N"
#elif UNLOCK_MODE == UNLOCK_MORSE_KEYBOARD
#define VARIANT_A "M"
#elif UNLOCK_MODE == UNLOCK_BINARY_KEYBOARD
#define VARIANT_A "B"
#endif

#define VERSION_ID VERSION_MAJOR "." VERSION_MINOR "-" VARIANT_A

namespace Banner
{

CRC32 crc;

uint32_t getOTP(uint32_t cbo, uint32_t cre)
{
    crc.reset();

    for (uint8_t ix = 0; ix < OTP_SECRET_SIZE; ix++)
    {
        crc.update(otpSecret[ix]);
    }

    for (uint8_t ix = 0; ix < 4; ix++)
    {
        crc.update((uint8_t)((cbo >> (ix * 8)) & 0xFF));
    }

    for (uint8_t ix = 0; ix < 4; ix++)
    {
        crc.update((uint8_t)((cre >> (ix * 8)) & 0xFF));
    }

    for (uint8_t ix = 0; ix < OTP_SECRET_SIZE; ix++)
    {
        crc.update(otpSecret[ix]);
    }

    uint32_t otp = crc.finalize();

    return otp;
}

void print()
{
    DigiKeyboard.println("----------- begin -----------");
    DigiKeyboard.println(" ");

    DigiKeyboard.println("; PwdToken " VERSION_ID);
    DigiKeyboard.println("; Built " __DATE__ " " __TIME__);

    // A guide to ensure the current keyboard layout is US.
    DigiKeyboard.println("; Keyboard Layout US");
    DigiKeyboard.println("; Hash Backslash: # \\");

    DigiKeyboard.println("LBL: " PWD_TOKEN_LABEL);

    DigiKeyboard.print("CBO: ");
    DigiKeyboard.println(Counters::getCounter(EEPROM_BOOT_COUNT));

    DigiKeyboard.print("CRE: ");
    DigiKeyboard.println(Counters::getCounter(EEPROM_RETRIEVAL_COUNT));

    DigiKeyboard.print("OTP: ");
    DigiKeyboard.println(getOTP(Counters::getCounter(EEPROM_BOOT_COUNT), Counters::getCounter(EEPROM_RETRIEVAL_COUNT)));

    DigiKeyboard.println(" ");
    DigiKeyboard.println("------------ end ------------");
}

} // namespace Banner

#endif

/*
 ****************************************************************************************************************************************************************/