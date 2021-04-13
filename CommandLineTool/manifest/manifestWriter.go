package manifest

import (
	_ "embed"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"github.com/atotto/clipboard"
	"os"
	"path/filepath"
	"text/template"
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

	fmt.Println("New manifestData in clipboard. Copy it to a safe place.")

	return nil
}

//go:embed secretsHeaderTemplate.txt
var headerContent string

type headerData struct {
	Label      string
	Secret     string
	SecretSize uint8
}

func (manifestWriter *manifestWriter) WriteManifestToHFile(manifest Manifest) error {

	headerFilePath := filepath.Join("..", "Firmware", "secrets.h")

	t := template.Must(template.New("test").Parse(headerContent))

	headerData := headerData{
		Label:      manifest.Label,
		Secret:     manifest.getSecretCSV(),
		SecretSize: uint8(len(manifest.Secret)),
	}

	fileHandler, err := os.Create(headerFilePath)

	if err != nil {
		return fmt.Errorf("cannot write header file: %s", err)
	}

	defer func(f *os.File) {
		_ = f.Close()
	}(fileHandler)

	err = t.Execute(fileHandler, headerData)

	if err != nil {
		return fmt.Errorf("template error: %s", err)
	}

	fmt.Println("done")

	return nil
}
