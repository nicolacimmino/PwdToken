package commands

import (
	"../manifest"
	"../secret"
	"bufio"
	"fmt"
	"os"
	"strings"
)

func GenerateTokenData() error {
	secretReader := secret.NewSecretReader()

	theSecret, _ := secretReader.ReadSecret()

	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Label: ")
	label, err := reader.ReadString('\n')

	if err != nil {
		return fmt.Errorf("cannot read label: %s", err)
	}

	label = strings.ReplaceAll(label, "\n", "")

	theManifest := manifest.Manifest{
		Label:  label,
		Cbo:    0,
		Cre:    0,
		Secret: theSecret,
	}

	manifestWriter := manifest.NewManifestWriter()

	err = manifestWriter.WriteManifestToHFile(theManifest)

	if err != nil {
		return fmt.Errorf("cannot write header file: %s", err)
	}

	err = manifestWriter.WriteManifest(theManifest)

	if err != nil {
		return fmt.Errorf("cannot write manifest: %s", err)
	}

	return nil
}
