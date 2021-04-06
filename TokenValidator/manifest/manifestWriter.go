package manifest

import (
	"encoding/base64"
	"encoding/json"
	"fmt"
	"github.com/atotto/clipboard"
)

type manifestWriter struct {
}

func NewManifestWriter() *manifestWriter {
	manifestWriter := manifestWriter{}

	return &manifestWriter
}

func (manifestWriter *manifestWriter) WriteManifest(manifest Manifest) error {
	jsonManifestString, err := json.Marshal(manifest)

	if err != nil {
		return fmt.Errorf("failed to json encode manifest: %s", err)
	}

	err = clipboard.WriteAll(base64.StdEncoding.EncodeToString(jsonManifestString))

	if err != nil {
		return fmt.Errorf("failed to write manifest to clipboard: %s", err)
	}

	fmt.Println("New manifestData in clipboard.")

	return nil
}
