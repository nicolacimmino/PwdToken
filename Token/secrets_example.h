// Copy the content of this file into a new secrets.h file and edit with your
// defisred information.
// secrets.h is gitignored, make sure you don't commit it in case you make changes!

#ifndef __SECRETS_H__
#define __SECRETS_H__

#define PWD_TOKEN_LABEL "TST002"

#define PWD_TOKEN_SEAL_SECRET_SIZE 16

uint8_t sealSecret[] = {
    0x26, 0x25, 0x24, 0x23, 0x26, 0x25, 0x24, 0x23, 0x26, 0x25, 0x24, 0x23, 0x26, 0x25, 0x24, 0x23};

#define PWD_TOKEN_PASSWORD "MySuperSecretPassword"

#endif