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

	fmt.Println("Copy manifestData...")

	_ = clipboard.WriteAll("")

	for true {
		for encodedManifest == "" {
			encodedManifest, _ = clipboard.ReadAll()
		}

		// We expect the manifest to be base64 encoded.
		jsonManifest, err := base64.StdEncoding.DecodeString(encodedManifest)

		// If it's not it might be it's just plain JSON.
		if err != nil {
			jsonManifest = []byte(encodedManifest)
		}

		err = json.Unmarshal(jsonManifest, &manifestReader.manifest)

		// We got a valid manifest.
		if err == nil {
			break
		}

		encodedManifest = ""
	}

	_ = clipboard.WriteAll("")

	return manifestReader.manifest
}
