#include "secrets.h"

#define MAX_STRING_SIZE 32
#define EEPROM_LABEL 0
#define EEPROM_SEAL 32
#define EEPROM_SEALED_AT 64

#define BUTTON_SENSE 0
#define PIN_GND 2
#define LED_A 1

#define BROKEN_SEAL "void void void void"

#ifdef BUILD_LABEL_AND_SEAL
#define PWD_TOKEN_SEALED_AT __DATE__ " " __TIME__
#ifndef PWD_TOKEN_LABEL
#pragma GCC error "Missing PWD_TOKEN_LABEL in config.h"
#endif
#ifndef PWD_TOKEN_SEAL
#pragma GCC error "Missing PWD_TOKEN_SEAL in config.h"
#endif
#else
#ifndef PWD_TOKEN_PASSWORD
#pragma GCC error "Missing PWD_TOKEN_PASSWORD in config.h"
#endif
#endif

