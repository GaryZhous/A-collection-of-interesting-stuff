package main
/* review of basics in golang*/
import (
	"fmt"
	"sync"
	"time"
)

// Go Fundamentals Review
func main() {
	// Variables and Constants
	var name string = "GoLang"
	age := 10 // Short declaration
	const pi float64 = 3.14159

	// Data Types
	var integer int = 42
	var floating float64 = 42.42
	var boolean bool = true
	var character rune = 'G' // Rune for single characters
	var text string = "Hello, Go!"

	// Arrays and Slices
	var arr [3]int = [3]int{1, 2, 3} // Fixed size
	slice := []int{1, 2, 3, 4, 5} // Dynamic size
	slice = append(slice, 6)

	// Maps (Dictionaries)
	myMap := map[string]int{"one": 1, "two": 2}
	myMap["three"] = 3

	// Conditionals
	if age > 5 {
		fmt.Println("Age is greater than 5")
	} else {
		fmt.Println("Age is 5 or less")
	}

	// Loops
	for i := 0; i < 5; i++ {
		fmt.Println("Loop iteration", i)
	}

	// Range-based Loop
	for index, value := range slice {
		fmt.Println("Index", index, "Value", value)
	}

	// Functions
	fmt.Println(add(5, 3))

	// Structs
	type Person struct {
		Name string
		Age  int
	}

	person := Person{Name: "Alice", Age: 30}
	fmt.Println("Person:", person.Name, "Age:", person.Age)

	// Pointers
	num := 10
	ptr := &num
	fmt.Println("Pointer Address:", ptr, "Value:", *ptr)

	// Goroutines (Concurrency)
	go printMessage("Hello from Goroutine")

	var wg sync.WaitGroup
	wg.Add(2)
	go func() {
		defer wg.Done()
		fmt.Println("Goroutine 1")
	}()
	go func() {
		defer wg.Done()
		fmt.Println("Goroutine 2")
	}()
	wg.Wait()

	// Channels for communication between Goroutines
	ch := make(chan string)
	go func() {
		ch <- "Message from channel"
	}()
	fmt.Println(<-ch)

	// Simulating time delay
	time.Sleep(time.Second)

	// Inheritance using Interfaces
	type Animal interface {
		Speak() string
	}
	type Dog struct{}

	func (d Dog) Speak() string {
		return "Woof!"
	}
	type Cat struct{}

	func (c Cat) Speak() string {
		return "Meow!"
	}

	var animals []Animal = []Animal{Dog{}, Cat{}}
	for _, animal := range animals {
		fmt.Println(animal.Speak())
	}

	go func() {
		// Defer go routine will run anyways when a program exits, following Last In, First Out rule
		defer func() {
			if r := recover(); r != nil {
				fmt.Println("Goroutine recovered from panic:", r)
			}
		}()
	
		// This panic won't crash the whole program
		panic("Oops in goroutine")
	}() //recover from panic, like try and catch in C++/Java/Python
}

// Function Example
func add(a int, b int) int {
	return a + b
}

// Goroutine Example
func printMessage(message string) {
	fmt.Println(message)
}
