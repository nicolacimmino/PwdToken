#ifndef __UTILS_H__
#define __UTILS_H__

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

void typeHex(uint32_t value)
{
    for (uint8_t ix = 0; ix < 8; ix += 2)
    {
        DigiKeyboard.print((value >> ((ix + 1) * 4)) & 0xF, HEX);
        DigiKeyboard.print((value >> (ix * 4)) & 0xF, HEX);
        if (ix < 6)
        {
            DigiKeyboard.print(".");
        }
    }
}

#endif
