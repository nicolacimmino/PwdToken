package main

import (
	"bufio"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"github.com/atotto/clipboard"
	"os"
	"strconv"
	"strings"
)

type Manifest struct {
	Label    string
	Counter1 uint32
	Counter2 uint32
	Secret   []byte
}

func main() {

	fmt.Println("Copy manifest...")

	manifest := getManifest()

	fmt.Println("Insert token and hold key...")

	banner := readBanner()

	if manifest.Label != banner["LBL"] {
		fmt.Println("Banner/token mismatch.")
		os.Exit(1)
	}

	expectedOtp1, err := strconv.Atoi(banner["OTP1"])

	if err != nil {
		fmt.Println("Invalid OTP1")
		os.Exit(1)
	}

	newCounter1 := getNewOTPCounter("OTP1", manifest.Counter1, uint32(expectedOtp1), manifest.Secret)

	expectedOtp2, err := strconv.Atoi(banner["OTP2"])

	if err != nil {
		fmt.Println("Invalid OTP2")
		os.Exit(1)
	}

	newCounter2 := getNewOTPCounter("OTP2", manifest.Counter2, uint32(expectedOtp2), manifest.Secret)

	if newCounter1 != manifest.Counter1 || newCounter2 != manifest.Counter2 {
		manifest.Counter1 = newCounter1
		manifest.Counter2 = newCounter2

		jsonManifestString, _ := json.Marshal(manifest)

		clipboard.WriteAll(base64.StdEncoding.EncodeToString(jsonManifestString))

		fmt.Println("New manifest in clipboard.")
	}
}

func getNewOTPCounter(otpName string, expectedCounter uint32, expectedOTP uint32, secret []byte) uint32 {
	var offset uint32 = 0
	var otp uint32 = 0
	for {
		otp = calculateOTP(expectedCounter+offset, secret)
		if otp == expectedOTP {
			break
		}
		offset++
		if offset > 1000 {
			fmt.Println("Cannot match counter, offset over 1000")
			os.Exit(1)
		}
	}

	if offset > 0 {
		fmt.Printf("%s advanced to %d (+%d)\n", otpName, expectedCounter+offset, offset)
	} else {
		fmt.Printf("%s match.\n", otpName)
	}

	return expectedCounter + offset
}

func getManifest() Manifest {
	var encodedManifest string = ""
	var jsonManifest []byte
	var manifest Manifest

	clipboard.WriteAll("")

	for len(manifest.Secret) == 0 {
		for encodedManifest == "" {
			encodedManifest, _ = clipboard.ReadAll()
		}

		jsonManifest, _ = base64.StdEncoding.DecodeString(encodedManifest)

		json.Unmarshal(jsonManifest, &manifest)
	}

	clipboard.WriteAll("")

	return manifest
}

/*
 * This uses an implementation of CRC32 to match the polynomial
 * used in this Arduino library: https://github.com/bakercp/CRC32
 * This is necessary because go CRC32 tables are all 256 values
 * while the Arduino one, out of necessity, is based on a table
 * with 16 values.
 */
func calculateOTP(counter uint32, data []byte) uint32 {

	ix := 0
	for ix < 4 {
		data = append(data, byte((counter>>(ix*8))&0xFF))
		ix++
	}

	var crc32Table = [16]uint32{
		0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
		0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
		0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
		0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c}

	var state uint32 = 0xFFFFFFFF
	var tableIndex uint8 = 0
	var dataIndex int = 0

	for dataIndex < len(data) {
		tableIndex = uint8(state ^ uint32(data[dataIndex]))
		state = crc32Table[tableIndex&0xF] ^ (state >> 4)
		tableIndex = uint8(state ^ uint32(data[dataIndex]>>4))
		state = crc32Table[tableIndex&0xF] ^ (state >> 4)

		dataIndex++
	}

	return ^state
}

func parseBannerLine(bannerLine string) (string, string, string) {
	tokens := strings.Split(bannerLine, ":")

	if len(tokens) != 2 {
		return "", "", "NO_LABEL"
	}

	return strings.Trim(tokens[0], " "), strings.Trim(tokens[1], " "), ""
}

func readBanner() map[string]string {

	bannerValues := make(map[string]string)

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		bannerLine := scanner.Text()

		if strings.Contains(bannerLine, "-- end --") {
			break
		}

		label, value, err := parseBannerLine(bannerLine)

		if err == "" {
			bannerValues[label] = value
		}
	}

	return bannerValues
}
