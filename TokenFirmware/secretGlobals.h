/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Secret Globals.
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

#ifndef __SECRET_GLOBALS_H__
#define __SECRET_GLOBALS_H__

uint8_t otpSecret[] = {OTP_SECRET};

const char password1[] PROGMEM = PASSWORD_1;
const char password2[] PROGMEM = PASSWORD_2;
const char password3[] PROGMEM = PASSWORD_3;
const char password4[] PROGMEM = PASSWORD_4;

const char *const passwords[] PROGMEM = {password1, password2, password3, password4};

#endif

/*
 ****************************************************************************************************************************************************************/