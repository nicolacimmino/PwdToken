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

type manifestReader struct {
	manifest Manifest
}

func NewManifestReader() *manifestReader {
	manifestReader := manifestReader{}

	return &manifestReader
}

func (manifestReader *manifestReader) ReadManifest() Manifest {
	var encodedManifest = ""
	var jsonManifest []byte

	fmt.Println("Copy manifestData...")

	clipboard.WriteAll("")

	for len(manifestReader.manifest.Secret) == 0 {
		for encodedManifest == "" {
			encodedManifest, _ = clipboard.ReadAll()
		}

		jsonManifest, _ = base64.StdEncoding.DecodeString(encodedManifest)

		json.Unmarshal(jsonManifest, &manifestReader.manifest)
	}

	clipboard.WriteAll("")

	return manifestReader.manifest
}
