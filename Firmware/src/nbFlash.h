/****************************************************************************************************************************************************************
 * Non Blocking Flash.
 * 
 * Copyright (C) 2021 Nicola Cimmino
 * 
 * Helper functions to implement a flasher when you can't affor to idle sleep your loop.
 */

#ifndef __NB_FLASH_H__
#define __NB_FLASH_H__

namespace NBFlasher
{

// All times in mS
#define TON 200
#define TOFF 300
#define TUNIT (TON + TOFF)
#define TLOOP 3000

/*
 * flashCount flashes a given amount of times with a pause. It can be used to communicate the value of a variable.
 * You need to call this often in your loop and use the return value to set your LED on or OFF, for instance:
 * 
 *  digitalWrite(PIN_LED_A, NBFlasher::flashCount(selectedIndex));
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
 */
bool flashCount(uint8_t count, bool fixedTloop = true)
{
    uint32_t tloop = fixedTloop ? TLOOP : ((count + 1) * TUNIT);
    unsigned long relativeTime = millis() % TLOOP;
    uint8_t currentUnit = relativeTime / TUNIT;

    if (currentUnit > count)
    {
        return false;
    }

    if (relativeTime % TUNIT > TON)
    {
        return false;
    }

    return true;
}

} // namespace nbFlash
#endif

/*
 ****************************************************************************************************************************************************************/