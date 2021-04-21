/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Configuration.
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

#ifndef __CONFIG_H__
#define __CONFIG_H__

//
// General
#define MAX_PWD_LEN 32 // Maximum password length (bytes)

//
// EEPROM Memory Map
#define EEPROM_BOOT_COUNT 0                                    //  Start offset of the boot counter (uint32_t).
#define EEPROM_RETRIEVAL_COUNT (EEPROM_BOOT_COUNT + 4)         //  Start offset of the retrieval counter (uint32_t).
#define EEPROM_FAILED_LOGIN_COUNT (EEPROM_RETRIEVAL_COUNT + 4) //  Start offset of the failed logins count counter (uint8_t).

//
// Hardware Configuration
#define PIN_BUTTON_A 2 // Button A (N/O).
#define PIN_BUTTON_B 0 // Button B (N/O).
#define PIN_LED_A 1    // LED Anode.

//
// Magic numbers busters
// Changes to these constants will require also code change, there are here just to make code more readable.
#define PASWWORDS_COUNT 4

#endif

/*
 ****************************************************************************************************************************************************************/