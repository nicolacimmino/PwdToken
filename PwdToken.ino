
#include <DigiKeyboard.h>
#include <EEPROM.h>
#include "config.h"

// Uncomment to build the label and seal app. If commented the password typing app is built.
#define BUILD_LABEL_AND_SEAL

#define MAX_STRING_SIZE 32
#define EEPROM_LABEL 0
#define EEPROM_SEAL 32
#define EEPROM_SEALED_AT 64

#define BUTTON_SENSE 0
#define BUTTON_GND 2

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

void printBanner()
{
  char buffer[MAX_STRING_SIZE];

  DigiKeyboard.print("LABEL: ");
  DigiKeyboard.println(readStringFromEEPROM(EEPROM_LABEL, MAX_STRING_SIZE, buffer));

  DigiKeyboard.print("SEAL: ");
  DigiKeyboard.println(readStringFromEEPROM(EEPROM_SEAL, MAX_STRING_SIZE, buffer));

  DigiKeyboard.print("TS: ");
  DigiKeyboard.println(readStringFromEEPROM(EEPROM_SEALED_AT, MAX_STRING_SIZE, buffer));

  DigiKeyboard.println("Kayboard Layout: US");
  DigiKeyboard.println("Hash: #");
  DigiKeyboard.println("Backslash: \\");
}

void setup()
{
  pinMode(BUTTON_GND, OUTPUT);
  digitalWrite(BUTTON_GND, LOW);

  pinMode(BUTTON_SENSE, INPUT_PULLUP);

  if (digitalRead(BUTTON_SENSE) == LOW)
  {
    printBanner();
    while (digitalRead(BUTTON_SENSE) == LOW)
    {
      DigiKeyboard.delay(100);
    }
    DigiKeyboard.delay(100);
  }
}

char *readStringFromEEPROM(uint8_t address, uint8_t len, char *buffer)
{
  memset(buffer, 0, len);
  for (uint8_t ix = 0; ix < len; ix++)
  {
    buffer[ix] = EEPROM.read(address + ix);
  }

  return buffer;
}

void writeStringToEEPROM(uint8_t address, uint8_t len, char *buffer)
{
  for (uint8_t ix = 0; ix < len; ix++)
  {
    EEPROM.write(address + ix, buffer[ix]);
  }
}

void loop()
{
#ifdef BUILD_LABEL_AND_SEAL
  writeStringToEEPROM(EEPROM_LABEL, MAX_STRING_SIZE, PWD_TOKEN_LABEL);
  writeStringToEEPROM(EEPROM_SEAL, MAX_STRING_SIZE, PWD_TOKEN_SEAL);
  writeStringToEEPROM(EEPROM_SEALED_AT, MAX_STRING_SIZE, PWD_TOKEN_SEALED_AT);
#else
  DigiKeyboard.sendKeyStroke(0);

  while (digitalRead(BUTTON_SENSE) == HIGH)
  {
    DigiKeyboard.delay(100);
  }
  writeStringToEEPROM(EEPROM_SEAL, MAX_STRING_SIZE, "void void void void");
  DigiKeyboard.print(PWD_TOKEN_PASSWORD);
#endif

  while (1)
  {
    DigiKeyboard.delay(5000);
  }
}
