package commands

import (
	"../banner"
	"../manifest"
	"../otp"
	"fmt"
)

func ValidateToken() error {
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

	if !otpGenerator.ValidateOtp(theBanner.Otp, theBanner.Cre, theBanner.Cbo) {
		return fmt.Errorf("failed to validate otp: token might have been tampered with")
	}

	if theManifest.Cre != theBanner.Cre || theManifest.Cbo != theBanner.Cbo {
		fmt.Println("Counters mismatch:")
		fmt.Printf("CRE: %d => %d\n", theManifest.Cre, theBanner.Cre)
		fmt.Printf("CBO: %d => %d\n", theManifest.Cbo, theBanner.Cbo)

		theManifest.Cre = theBanner.Cre
		theManifest.Cbo = theBanner.Cbo

		manifestWriter := manifest.NewManifestWriter()

		err = manifestWriter.WriteManifest(theManifest)

		if err != nil {
			return fmt.Errorf("cannot write mainfest: %s", err)
		}
	}

	fmt.Println("Token valid")

	return nil
}
