// Copy the content of this file into a new secrets.h file and edit with your
// defisred information.
// secrets.h is gitignored, make sure you don't commit it in case you make changes!

#ifndef __SECRETS_H__
#define __SECRETS_H__

#define PWD_TOKEN_LABEL "TST002"

#define PWD_TOKEN_SEAL_SECRET_SIZE 16

uint8_t sealSecret[] = {26, 25, 24, 23, 26, 25, 24, 23, 26, 25, 24, 23, 26, 25, 24, 23};

#define PASWWORDS_COUNT 4

#define PWD_TOKEN_PASSWORD_0 "MySuperSecretPassword1"
#define PWD_TOKEN_PASSWORD_1 "MySuperSecretPassword2"
#define PWD_TOKEN_PASSWORD_2 "MySuperSecretPassword3"
#define PWD_TOKEN_PASSWORD_3 "MySuperSecretPassword4"

#endif