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
	jsonManifestString, _ := json.Marshal(manifest)

	err := clipboard.WriteAll(base64.StdEncoding.EncodeToString(jsonManifestString))

	if err != nil {
		return err
	}

	fmt.Println("New manifestData in clipboard.")

	return nil
}
