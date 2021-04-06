package banner

import (
	"../manifest"
	"fmt"
)

func ValidateBanner(banner Banner, manifest manifest.Manifest) error {
	if manifest.Label != banner.Label {
		return fmt.Errorf("invalid banner: label mismatch")
	}

	return nil
}
