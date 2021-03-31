package banner

import (
	"bufio"
	"os"
	"strings"
)

func parseBannerLine(bannerLine string) (string, string, string) {
	tokens := strings.Split(bannerLine, ":")

	if len(tokens) != 2 {
		return "", "", "NO_LABEL"
	}

	return strings.Trim(tokens[0], " "), strings.Trim(tokens[1], " "), ""
}

func ReadBanner() map[string]string {

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
