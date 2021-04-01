package bannerReader

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type bannerReader struct {
	bannerData map[string]string
}

/**
 * Constructor.
 */
func NewBanner() *bannerReader {
	bannerReader := bannerReader{bannerData: make(map[string]string)}

	bannerReader.readBanner()

	return &bannerReader
}

func (bannerReader *bannerReader) GetKeyboardLayout() string {
	return bannerReader.bannerData["Layout"]
}

func (bannerReader *bannerReader) IsKeyboardLayoutCorrect() bool {
	return bannerReader.bannerData["Hash"] == "#" && bannerReader.bannerData["Backslash"] == "\\"
}

func (bannerReader *bannerReader) GetOTP1() (uint32, error) {
	return bannerReader.getOTP("OTP1")
}

func (bannerReader *bannerReader) GetOTP2() (uint32, error) {
	return bannerReader.getOTP("OTP2")
}

func (bannerReader *bannerReader) GetLabel() string {
	return bannerReader.bannerData["LBL"]
}

func (bannerReader *bannerReader) getOTP(otpName string) (uint32, error) {
	otp, err := strconv.Atoi(bannerReader.bannerData[otpName])

	if err != nil {
		return 0, errors.New(fmt.Sprintf("invalid value for %s", otpName))
	}

	return uint32(otp), nil
}

func (bannerReader *bannerReader) readBanner() {
	fmt.Println("Insert token and hold key...")

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		bannerLine := scanner.Text()

		if strings.Contains(bannerLine, "-- end --") {
			break
		}

		label, value, err := parseBannerLine(bannerLine)

		if err == nil {
			bannerReader.bannerData[label] = value
		}
	}
}

func parseBannerLine(bannerLine string) (string, string, error) {
	tokens := strings.Split(bannerLine, ":")

	if len(tokens) != 2 {
		return "", "", errors.New("no label")
	}

	return strings.Trim(tokens[0], " "), strings.Trim(tokens[1], " "), nil
}
