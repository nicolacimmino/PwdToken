package manifest

import (
	"encoding/base64"
	"encoding/json"
	"fmt"
	"github.com/atotto/clipboard"
)

type Manifest struct {
	Label    string
	Counter1 uint32
	Counter2 uint32
	Secret   []byte
}

func GetManifestData() Manifest {
	var encodedManifest string = ""
	var jsonManifest []byte
	var manifest Manifest

	fmt.Println("Copy manifestData...")

	clipboard.WriteAll("")

	for len(manifest.Secret) == 0 {
		for encodedManifest == "" {
			encodedManifest, _ = clipboard.ReadAll()
		}

		jsonManifest, _ = base64.StdEncoding.DecodeString(encodedManifest)

		json.Unmarshal(jsonManifest, &manifest)
	}

	clipboard.WriteAll("")

	return manifest
}
