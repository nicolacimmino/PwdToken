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

		if err == nil {
			switch label {
			case "OTP":
				bannerReader.banner.Otp = numericValue
			case "LBL":
				bannerReader.banner.Lbl = value
			case "CRE":
				bannerReader.banner.Cre = numericValue
			case "CBO":
				bannerReader.banner.Cbo = numericValue
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
