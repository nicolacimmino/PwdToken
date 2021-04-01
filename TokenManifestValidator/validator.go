package main

import (
	"./banner"
	"./manifest"
	"./otp"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"github.com/atotto/clipboard"
	"os"
)

func main() {

	manifestReader := manifest.NewManifestReader()
	bannerReader := banner.NewBannerReader()

	readManifest := manifestReader.ReadManifest()
	readBanner := bannerReader.ReadBanner()

	fmt.Println(readManifest)
	fmt.Println(readBanner)

	if readManifest.Label != readBanner.Label {
		fmt.Println("Banner/token mismatch.")
		os.Exit(1)
	}

	otpGenerator := otp.NewOtpGenerator(readBanner, readManifest)

	newCounter1 := otpGenerator.FindNewOTP1Counter()

	newCounter2 := otpGenerator.FindNewOTP2Counter()

	if newCounter1 != readManifest.Counter1 || newCounter2 != readManifest.Counter2 {
		readManifest.Counter1 = newCounter1
		readManifest.Counter2 = newCounter2

		jsonManifestString, _ := json.Marshal(readManifest)

		clipboard.WriteAll(base64.StdEncoding.EncodeToString(jsonManifestString))

		fmt.Println("New manifestData in clipboard.")
	}
}
