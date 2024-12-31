package main

import (
	"fmt"
	"os"
)

func main() {
	// Example 1: Get environment variables
	fmt.Println("Environment Variables:")
	for _, env := range os.Environ() {
		fmt.Println(env)
	}

	// Example 2: Get the current working directory
	cwd, err := os.Getwd()
	if err != nil {
		fmt.Println("Error getting current directory:", err)
	} else {
		fmt.Println("Current Working Directory:", cwd)
	}

	// Example 3: Create and remove a file
	fileName := "example.txt"
	file, err := os.Create(fileName)
	if err != nil {
		fmt.Println("Error creating file:", err)
	} else {
		fmt.Println("File created:", fileName)
		file.Close()
	}

	err = os.Remove(fileName)
	if err != nil {
		fmt.Println("Error removing file:", err)
	} else {
		fmt.Println("File removed:", fileName)
	}

	// Example 4: Read command-line arguments
	fmt.Println("Command-line Arguments:")
	for i, arg := range os.Args {
		fmt.Printf("Arg %d: %s\n", i, arg)
	}

	// Example 5: Get the hostname of the machine
	hostname, err := os.Hostname()
	if err != nil {
		fmt.Println("Error getting hostname:", err)
	} else {
		fmt.Println("Hostname:", hostname)
	}
}
