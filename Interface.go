package main

import "fmt"
//declare an interface with methods
type OGInterface interface {
	FuncOne() int
	FuncTwo() float64
	FuncThree() string
}
//a struct that implements all three methods of the OG interface
type StructAll struct{}

func (s StructAll) FuncOne() int {
	return 100
}
func (s StructAll) FuncTwo() float64 {
	return 10.0
}
func (s StructAll) FuncThree() string {
	return "hello"
}

type Handler struct{}

func (handler *Handler) handling() {
	fmt.Printf("Handling!")
}
//embed the Handler struct
type MockHandler struct{
	Handler 
}

func (handler *MockHandler) handling() {
	fmt.Printf("Mock-handling!")
}

func main() {
  //an interface can bind with any struct that implements all the methods listed in it
	var OG OGInterface = StructAll{} 
	fmt.Println(OG.FuncOne())
	fmt.Println(OG.FuncTwo())
	fmt.Println(OG.FuncThree())
	mockhandler := &MockHandler{Handler{}}
	mockhandler.handling() //this will call MockHandler's handling()
	mockhandler.Handler.handling() //this will call the embedded Hanlder's handling()
}
