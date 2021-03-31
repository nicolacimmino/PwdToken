package otp

import (
	"fmt"
	"os"
)

func GetNewOTPCounter(otpName string, expectedCounter uint32, expectedOTP uint32, secret []byte) uint32 {
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
