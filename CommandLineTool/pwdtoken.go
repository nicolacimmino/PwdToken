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
	fmt.Println("  ver verify a password pad banner against its manifest.")
	fmt.Println("  gen generate a password pad manifest and secrets header.")
}

func main() {
	var err error

	if len(os.Args) < 2 {
		printUsage()
		os.Exit(1)
	}

	switch os.Args[1] {
	case "ver":
		err = ValidatePad()
	case "gen":
		err = GeneratePadData()
	default:
		printUsage()
	}

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
