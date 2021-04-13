package manifest

import (
	"strconv"
	"strings"
)

type Manifest struct {
	Label  string
	Cbo    uint32
	Cre    uint32
	Secret []byte
}

func (manifest *Manifest) getSecretCSV() string {

	secretCsv := ""

	for _, secretByte := range manifest.Secret {
		secretCsv += strconv.Itoa(int(secretByte)) + ", "
	}

	secretCsv = strings.TrimRight(secretCsv, ", ")

	return secretCsv
}
