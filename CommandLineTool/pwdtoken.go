/****************************************************************************************************************************************************************
 *  PwdToken.
 *  Command line utility for the pwdToken.
 *
 *  Copyright (C) 2021 Nicola Cimmino
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see http:*www.gnu.org/licenses/.
 */

package main

import (
	. "./commands"
	"fmt"
	"os"
	"path/filepath"
)

func printUsage() {
	fmt.Println("Usage:")
	fmt.Printf("%s [command]\n", filepath.Base(os.Args[0]))
	fmt.Println("  ver verify a token banner against its manifest.")
	fmt.Println("  gen generate a token manifest and secrets header.")
}

func main() {
	var err error

	if len(os.Args) < 2 {
		printUsage()
		os.Exit(1)
	}

	switch os.Args[1] {
	case "ver":
		err = VerifyToken()

		if err != nil {
			err = fmt.Errorf("failed to verify token: %s", err)
		}
	case "gen":
		err = GenerateTokenData()

		if err != nil {
			err = fmt.Errorf("failed to generate token data: %s", err)
		}
	default:
		printUsage()
	}

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

/*
 ****************************************************************************************************************************************************************/
