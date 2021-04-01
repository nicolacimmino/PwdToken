package banner

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type bannerReader struct {
	banner Banner
}

/**
 * Constructor.
 */
func NewBannerReader() *bannerReader {
	bannerReader := bannerReader{banner: Banner{}}

	return &bannerReader
}

func (bannerReader *bannerReader) ReadBanner() Banner {

	fmt.Println("Insert token and hold key...")

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		bannerLine := scanner.Text()

		if strings.Contains(bannerLine, "-- end --") {
			break
		}

		label, value, numericValue, err := bannerReader.parseBannerLine(bannerLine)
		fmt.Println(label, value, numericValue, err)

		if err == nil {
			switch label {
			case "OTP1":
				bannerReader.banner.Otp1 = numericValue
				break
			case "OTP2":
				bannerReader.banner.Otp2 = numericValue
				break
			case "LBL":
				bannerReader.banner.Label = value
				break
			}
		}
	}

	return bannerReader.banner
}

func (bannerReader *bannerReader) parseBannerLine(wkt string) (string, string, uint32, error) {
	tokens := strings.Split(wkt, ":")

	if len(tokens) != 2 {
		return "", "", 0, errors.New("no label")
	}

	numericValue, err := strconv.Atoi(strings.Trim(tokens[1], " "))

	if err == nil {
		return strings.Trim(tokens[0], " "), "", uint32(numericValue), nil
	}

	return strings.Trim(tokens[0], " "), strings.Trim(tokens[1], " "), 0, nil
}
