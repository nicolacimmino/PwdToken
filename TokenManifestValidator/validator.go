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
	"strconv"
)

func main() {

	fmt.Println("Copy manifestData...")

	manifestData := manifest.GetManifest()

	fmt.Println("Insert token and hold key...")

	bannerData := banner.ReadBanner()

	if manifestData.Label != bannerData["LBL"] {
		fmt.Println("Banner/token mismatch.")
		os.Exit(1)
	}

	expectedOtp1, err := strconv.Atoi(bannerData["OTP1"])

	if err != nil {
		fmt.Println("Invalid OTP1")
		os.Exit(1)
	}

	newCounter1 := otp.GetNewOTPCounter("OTP1", manifestData.Counter1, uint32(expectedOtp1), manifestData.Secret)

	expectedOtp2, err := strconv.Atoi(bannerData["OTP2"])

	if err != nil {
		fmt.Println("Invalid OTP2")
		os.Exit(1)
	}

	newCounter2 := otp.GetNewOTPCounter("OTP2", manifestData.Counter2, uint32(expectedOtp2), manifestData.Secret)

	if newCounter1 != manifestData.Counter1 || newCounter2 != manifestData.Counter2 {
		manifestData.Counter1 = newCounter1
		manifestData.Counter2 = newCounter2

		jsonManifestString, _ := json.Marshal(manifestData)

		clipboard.WriteAll(base64.StdEncoding.EncodeToString(jsonManifestString))

		fmt.Println("New manifestData in clipboard.")
	}
}
