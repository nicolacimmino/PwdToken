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

func (manifestReader *manifestReader) ReadManifest() (Manifest, error) {
	var encodedManifest = ""

	fmt.Println("Copy manifestData...")

	err := clipboard.WriteAll("")

	if err != nil {
		return manifestReader.manifest, fmt.Errorf("failed to clear the clipboard: %s", err)
	}

	for true {
		for encodedManifest == "" {
			encodedManifest, err = clipboard.ReadAll()

			if err != nil {
				return manifestReader.manifest, fmt.Errorf("failed to read clipboard: %s", err)
			}
		}

		// We expect the manifest to be base64 encoded.
		jsonManifest, err := base64.StdEncoding.DecodeString(encodedManifest)

		// If it's not it might be it's just plain JSON, try that.
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

	err = clipboard.WriteAll("")

	if err != nil {
		return manifestReader.manifest, fmt.Errorf("got a valid manifest but failed to clear the clipboard: %s", err)
	}

	return manifestReader.manifest, nil
}
