package main

import (
	"./banner"
	"./manifest"
	"./otp"
	"./secret"
	"bufio"
	"fmt"
	"os"
	"path/filepath"
)

func main() {
	var err error

	switch os.Args[1] {
	case "-v":
		err = validate()
	case "-g":
		err = generate()
	default:
		fmt.Println("Usage:")
		fmt.Printf("%s -v|-g", filepath.Base(os.Args[0]))
	}

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

func generate() error {
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

func validate() error {
	manifestReader := manifest.NewManifestReader()
	theManifest, err := manifestReader.ReadManifest()

	if err != nil {
		return fmt.Errorf("cannot read mainfest: %s", err)
	}

	bannerReader := banner.NewBannerReader()
	theBanner := bannerReader.ReadBanner()

	err = banner.ValidateBanner(theBanner, theManifest)

	if err != nil {
		return fmt.Errorf("banner validation error: %s", err)
	}

	otpGenerator := otp.NewOtpGenerator(theBanner, theManifest)

	newCounter1, newCounter2, err := otpGenerator.GetNewCounters()

	if err != nil {
		return fmt.Errorf("cannot get new counters: %s", err)
	}

	if newCounter1 != theManifest.Counter1 || newCounter2 != theManifest.Counter2 {
		theManifest.Counter1 = newCounter1
		theManifest.Counter2 = newCounter2

		manifestWriter := manifest.NewManifestWriter()

		err = manifestWriter.WriteManifest(theManifest)

		if err != nil {
			return fmt.Errorf("cannot write mainfest: %s", err)
		}
	}

	return nil
}
