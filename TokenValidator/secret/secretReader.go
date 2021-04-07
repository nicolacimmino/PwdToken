package secret

import (
	"encoding/base64"
	"fmt"
	"github.com/atotto/clipboard"
)

type secretReader struct {
	secret Secret
}

func NewSecretReader() *secretReader {
	secretReader := secretReader{}

	return &secretReader
}

func (secretReader *secretReader) ReadSecret() (Secret, error) {
	var encodedSecret = ""

	fmt.Println("Copy base64 encoded secret...")

	err := clipboard.WriteAll("")

	if err != nil {
		return nil, fmt.Errorf("failed to clear the clipboard: %s", err)
	}

	for encodedSecret == "" {
		encodedSecret, err = clipboard.ReadAll()

		if err != nil {
			return nil, fmt.Errorf("failed to read clipboard: %s", err)
		}
	}

	// We expect the secret to be base64 encoded.
	secretReader.secret, err = base64.StdEncoding.DecodeString(encodedSecret)

	if err != nil {
		return nil, err
	}

	err = clipboard.WriteAll("")

	if err != nil {
		return nil, fmt.Errorf("got a valid secret but failed to clear the clipboard: %s", err)
	}

	return secretReader.secret, nil
}
