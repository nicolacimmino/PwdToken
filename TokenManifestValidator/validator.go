package main

import (
	"./bannerReader"
	"./manifest"
	"./otp"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"github.com/atotto/clipboard"
	"os"
)

func main() {
	manifestData := manifest.GetManifestData()

	banner := bannerReader.NewBanner()

	if manifestData.Label != banner.GetLabel() {
		fmt.Println("Banner/token mismatch.")
		os.Exit(1)
	}

	expectedOtp1, err := banner.GetOTP1()

	if err != nil {
		fmt.Println("Invalid OTP1")
		os.Exit(1)
	}

	expectedOtp2, err := banner.GetOTP2()

	if err != nil {
		fmt.Println("Invalid OTP2")
		os.Exit(1)
	}

	newCounter1 := otp.GetNewOTPCounter("OTP1", manifestData.Counter1, uint32(expectedOtp1), manifestData.Secret)

	newCounter2 := otp.GetNewOTPCounter("OTP2", manifestData.Counter2, uint32(expectedOtp2), manifestData.Secret)

	if newCounter1 != manifestData.Counter1 || newCounter2 != manifestData.Counter2 {
		manifestData.Counter1 = newCounter1
		manifestData.Counter2 = newCounter2

		jsonManifestString, _ := json.Marshal(manifestData)

		clipboard.WriteAll(base64.StdEncoding.EncodeToString(jsonManifestString))

		fmt.Println("New manifestData in clipboard.")
	}
}
