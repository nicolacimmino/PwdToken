/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Lock.
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

#ifndef __LOCK_H__
#define __LOCK_H__

#define BOOTLOADER_ADDRESS 0x1A00

#include <avr/boot.h>
#include "counters.h"

namespace Lock
{
    void selfDestruct()
    {
        uint16_t ptr = BOOTLOADER_ADDRESS;
        while (ptr)
        {
            ptr -= SPM_PAGESIZE;
            boot_page_erase(ptr);
        }

        // Write the reset vector.
        // This is a rjmp to the start of the bootloader.
        // It can be calculated as 0xC000 + (BOOTLOADER_ADDRESS / 2) - 1
        // See your bootloader Makefile.inc if you need to change this.
        // For the standard PWdToken t85_sec_boot the bootaloader address is 0x1A00
        // and the rjmp opcode is 0xCCFF.
        boot_page_fill(0, 0xCCFF);
        boot_page_write(0);
    }

    void onFailedLogin()
    {
        if (Counters::incrementCounter(EEPROM_FAILED_LOGIN_COUNT) > UNLOCK_MAX_ATTEMPTS)
        {
            selfDestruct();
        }
    }

    void onSuccessfulLogin()
    {
        Counters::setCounter(EEPROM_FAILED_LOGIN_COUNT, 0);
    }

} // namespace Lock

#endif

/*
 ****************************************************************************************************************************************************************/