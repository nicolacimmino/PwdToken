package banner

import (
	"../manifest"
)

func IsBannerValid(banner Banner, manifest manifest.Manifest) bool {
	if manifest.Label != banner.Label {
		return false
	}

	return true
}
