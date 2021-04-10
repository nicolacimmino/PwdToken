package commands

import (
	"../manifest"
	"../secret"
	"bufio"
	"fmt"
	"os"
)

func GeneratePadData() error {
	secretReader := secret.NewSecretReader()

	theSecret, _ := secretReader.ReadSecret()

	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Label: ")

	label, err := reader.ReadString('\n')

	if err != nil {
		return fmt.Errorf("cannot read label: %s", err)
	}

	theManifest := manifest.Manifest{
		Label:    label,
		Counter1: 0,
		Counter2: 0,
		Secret:   theSecret,
	}

	manifestWriter := manifest.NewManifestWriter()

	err = manifestWriter.WriteManifest(theManifest)

	if err != nil {
		return fmt.Errorf("cannot write manifest: %s", err)
	}

	err = manifestWriter.WriteManifestToHFile(theManifest)

	if err != nil {
		return fmt.Errorf("cannot write header file: %s", err)
	}

	return nil
}
