package main

import (
	"./banner"
	"./manifest"
	"./otp"
	"fmt"
	"os"
)

func main() {

	manifestReader := manifest.NewManifestReader()
	theManifest, err := manifestReader.ReadManifest()

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	bannerReader := banner.NewBannerReader()
	theBanner := bannerReader.ReadBanner()

	if !banner.IsBannerValid(theBanner, theManifest) {
		fmt.Println("banner/token mismatch")
		os.Exit(1)
	}

	otpGenerator := otp.NewOtpGenerator(theBanner, theManifest)

	newCounter1, newCounter2, err := otpGenerator.GetNewCounters()

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	if newCounter1 != theManifest.Counter1 || newCounter2 != theManifest.Counter2 {
		theManifest.Counter1 = newCounter1
		theManifest.Counter2 = newCounter2

		manifestWriter := manifest.NewManifestWriter()

		err = manifestWriter.WriteManifest(theManifest)

		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
	}
}
