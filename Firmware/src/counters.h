/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Counters.
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

#ifndef __COUNTERS_H__
#define __COUNTERS_H__

namespace Counters
{

    uint32_t getCounter(uint8_t baseAddress)
    {
        uint32_t counter;
        EEPROM.get(baseAddress, counter);

        return counter;
    }

    void setCounter(uint8_t baseAddress, uint32_t value)
    {
        EEPROM.put(baseAddress, value);
    }

    uint32_t incrementCounter(uint8_t baseAddress)
    {
        uint32_t value = getCounter(baseAddress) + 1;

        setCounter(baseAddress, value);

        return value;
    }

} // namespace Counters

#endif

/*
 ****************************************************************************************************************************************************************/