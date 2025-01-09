package main

import (
	"fmt"
)

// Golang doesn't support traditional OOP inheritance but provides features like structs, methods, and interfaces
// to achieve object-oriented design. Below are examples demonstrating Go's OOP capabilities in detail.

// 1. Structs: Used to define custom types (similar to classes in OOP)
type Person struct {
	Name string
	Age  int
}

// 2. Methods: Functions with a receiver (can be a value or pointer receiver)
// Method with a value receiver (does not modify the original struct)
func (p Person) Greet() {
	fmt.Printf("Hello, my name is %s and I am %d years old.\n", p.Name, p.Age)
}

// Method with a pointer receiver (modifies the original struct)
func (p *Person) HaveBirthday() {
	p.Age++
}

// 3. Composition: Go uses composition instead of inheritance
// Employee "inherits" properties and methods of Person via embedding
type Employee struct {
	Person
	JobTitle string
}

// Employee-specific method
func (e Employee) Work() {
	fmt.Printf("%s is working as a %s.\n", e.Name, e.JobTitle)
}

// 4. Interfaces: Define behavior that types can implement
type Greeter interface {
	Greet()
}

type Worker interface {
	Work()
}

// 5. Polymorphism: A type can implement multiple interfaces
// Example with polymorphism
func PerformDuties(g Greeter, w Worker) {
	g.Greet()
	w.Work()
}

// 6. Anonymous Structs: Used for temporary data structures without defining a named type
func DemoAnonymousStruct() {
	student := struct {
		Name  string
		Grade int
	}{
		Name:  "Alice",
		Grade: 90,
	}
	fmt.Printf("Student: %s, Grade: %d\n", student.Name, student.Grade)
}

// 7. Inner Structs: Structs within structs to organize data hierarchically
type Address struct {
	Street string
	City   string
}

type Company struct {
	Name    string
	Address Address
}

// Demonstrating inner struct usage
func (c Company) PrintDetails() {
	fmt.Printf("Company: %s, Located at: %s, %s\n", c.Name, c.Address.Street, c.Address.City)
}

// 8. Type Assertions: Used to access the underlying type of an interface value
func TypeAssertionDemo(i interface{}) {
	if v, ok := i.(Greeter); ok {
		v.Greet()
	} else {
		fmt.Println("Provided value does not implement Greeter interface")
	}
}

func main() {
	// Creating an instance of Person
	john := Person{Name: "John", Age: 30}

	// Accessing methods of Person
	john.Greet()
	john.HaveBirthday()
	john.Greet() // Age should be incremented

	// Creating an instance of Employee
	jane := Employee{
		Person:   Person{Name: "Jane", Age: 25},
		JobTitle: "Software Engineer",
	}

	// Accessing methods from Person (embedded in Employee)
	jane.Greet()

	// Accessing Employee-specific method
	jane.Work()

	// Using interfaces and polymorphism
	PerformDuties(jane, jane)

	// Demonstrating anonymous struct
	DemoAnonymousStruct()

	// Demonstrating inner structs
	company := Company{
		Name: "Tech Corp",
		Address: Address{
			Street: "123 Innovation Drive",
			City:   "Toronto",
		},
	}
	company.PrintDetails()

	// Demonstrating type assertions
	TypeAssertionDemo(john)
	TypeAssertionDemo("random string")
}
