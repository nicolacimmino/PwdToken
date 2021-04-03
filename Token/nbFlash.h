
/****************************************************************************************************************************************************************
 * Non Blocking Flash.
 * 
 * Copyright (C) 2021 Nicola Cimmino
 * 
 * This is a helper function to implement a flasher when you can't affor to idle sleep your loop.
 * You need to call this often in your loop and use the return value to set your LED on or OFF, for instance:
 * 
 *  digitalWrite(LED_A, nbFlash(selectedIndex));
 * 
 * Timing diagram for fixedTloop = true
 * 
 *   |--------------------------------------------------- TLOOP ---------------------------------------|----------------------------    ...
 *   |---------- TUNIT -----------|---------- TUNIT -----------|---------- TUNIT -----------|   ...    |---------- TUNIT -----------|   ...
 *   |---- TON ----|---- TOFF ----|---- TON ----|---- TOFF ----|---- TON ----|---- TOFF ----|   ...    |---- TON ----|---- TOFF ----|   ...
 *  1 *************                                                                                     *************                   ...
 *  2 *************                *************                                                        *************                   ...
 *  3 *************                *************                *************                           *************                   ...
 * 
 * Timing diagram for fixedTloop = false
 * 
 *   |---------- TUNIT -----------|---------- TUNIT -----------|---------- TUNIT -----------|---------- TUNIT -----------|---------- TUNIT -----------|  ...
 *   |---- TON ----|---- TOFF ----|---- TON ----|---- TOFF ----|---- TON ----|---- TOFF ----|---- TON ----|---- TOFF ----|---- TON ----|---- TOFF ----|  ...
 *  1 *************                                             *************                                             *************                  ...
 *  2 *************                *************                                             *************                *************                  ...
 *  3 *************                *************                *************                                             *************                  ...
 * 
 ****************************************************************************************************************************************************************/

#ifndef __NB_FLASH_H__
#define __NB_FLASH_H__

// All times in mS
#define TON 200
#define TOFF 300
#define TUNIT (TON + TOFF)
#define TLOOP 3000

bool nbFlash(uint8_t value, bool fixedTloop = true)
{
    uint32_t tloop = fixedTloop ? TLOOP : ((value + 1) * TUNIT);
    unsigned long relativeTime = millis() % TLOOP;
    uint8_t currentUnit = relativeTime / TUNIT;

    if (currentUnit > value)
    {
        return false;
    }

    if (relativeTime % TUNIT > TON)
    {
        return false;
    }

    return true;
}
#endif