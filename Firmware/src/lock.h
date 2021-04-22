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

#include "counters.h"

namespace Lock
{
    void onFailedLogin()
    {
        if (Counters::incrementCounter(EEPROM_FAILED_LOGIN_COUNT) > UNLOCK_MAX_ATTEMPTS)
        {
            // wipe app
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