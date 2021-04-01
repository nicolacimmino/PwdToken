package manifest

import (
	"encoding/base64"
	"encoding/json"
	"fmt"
	"github.com/atotto/clipboard"
)

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

	_ = clipboard.WriteAll("")

	for len(manifestReader.manifest.Secret) == 0 {
		for encodedManifest == "" {
			encodedManifest, _ = clipboard.ReadAll()
		}

		jsonManifest, _ = base64.StdEncoding.DecodeString(encodedManifest)

		err := json.Unmarshal(jsonManifest, &manifestReader.manifest)

		if err != nil {
			fmt.Println("Bad manifest, ignoring.")
		}
	}

	_ = clipboard.WriteAll("")

	return manifestReader.manifest
}
