/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Options.
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

#ifndef __OPTIONS_H__
#define __OPTIONS_H__

/****************************************************************************
 * Unlock mode.
 * Set the mode of unlocking the token after boot.
 * 
 *  NONE            Token is not locked and can be used immediately at boot.
 *  MORSE_KEYBOARD  User needs to enter a passphrase in morse code.
 *  BINARY_KEYBOARD User needs to enter a passphrase on a binary keyboard.
 */

#define UNLOCK_NONE 0
#define UNLOCK_MORSE_KEYBOARD 1
#define UNLOCK_BINARY_KEYBOARD 2

#define UNLOCK_MODE UNLOCK_MORSE_KEYBOARD

/*
 ****************************************************************************/

#define UNLOCK_MAX_ATTEMPTS 3

#endif

/*
 ****************************************************************************************************************************************************************/