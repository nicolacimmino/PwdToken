package commands

import (
	"../banner"
	"../manifest"
	"../otp"
	"fmt"
)

func ValidatePad() error {
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
