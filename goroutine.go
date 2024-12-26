package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// main function is the entry point of the program.
func main() {
	fmt.Println("Starting the program...")

	// Example 1: Basic Goroutines
	go printNumbers("Basic Goroutine")

	// Example 2: Using sync.WaitGroup to wait for goroutines to finish
	var wg sync.WaitGroup
	wg.Add(2) // We are adding two goroutines to wait for

	go func() {
		defer wg.Done() // Decrements the counter when this goroutine completes
		processTasks("Worker 1")
	}()

	go func() {
		defer wg.Done()
		processTasks("Worker 2")
	}()

	// Example 3: Communication Between Goroutines Using Channels
	results := make(chan string, 2) // Buffered channel to hold results

	go calculateSum(10, results)
	go calculateSum(20, results)

	// Read results from the channel
	for i := 0; i < 2; i++ {
		fmt.Println("Result from channel:", <-results)
	}

	// Example 4: Select Statement to Handle Multiple Channels
	dataChannel := make(chan int, 5)
	stopChannel := make(chan struct{})

	go generateData(dataChannel, stopChannel)
	go consumeData(dataChannel, stopChannel)

	// Close the stop channel after 3 seconds to signal all goroutines to stop
	time.Sleep(3 * time.Second)
	close(stopChannel)

	// Wait for the WaitGroup to finish
	wg.Wait()

	// Example 5: Fan-Out, Fan-In Pattern
	fmt.Println("Starting Fan-Out, Fan-In example...")
	jobs := make(chan int, 10)
	resultsChannel := make(chan int, 10)

	// Launch multiple workers (Fan-Out)
	for i := 0; i < 3; i++ {
		go worker(jobs, resultsChannel)
	}

	// Send jobs
	for i := 1; i <= 10; i++ {
		jobs <- i
	}
	close(jobs)

	// Collect results (Fan-In)
	for i := 1; i <= 10; i++ {
		fmt.Printf("Result from job %d: %d\n", i, <-resultsChannel)
	}
	close(resultsChannel)

	fmt.Println("Program completed!")
}

// printNumbers demonstrates a basic goroutine.
func printNumbers(name string) {
	for i := 1; i <= 5; i++ {
		fmt.Printf("%s: %d\n", name, i)
		time.Sleep(500 * time.Millisecond) // Simulate work
	}
}

// processTasks simulates task processing for a worker.
func processTasks(workerName string) {
	for i := 1; i <= 3; i++ {
		fmt.Printf("%s is processing task %d\n", workerName, i)
		time.Sleep(800 * time.Millisecond)
	}
}

// calculateSum demonstrates communication between goroutines using channels.
func calculateSum(n int, results chan string) {
	sum := 0
	for i := 1; i <= n; i++ {
		sum += i
	}
	results <- fmt.Sprintf("Sum of 1 to %d is %d", n, sum)
}

// generateData produces data for a consumer until stopped.
func generateData(dataChannel chan int, stopChannel chan struct{}) {
	for {
		select {
		case <-stopChannel:
			fmt.Println("Stopping data generation...")
			return
		default:
			data := rand.Intn(100)
			dataChannel <- data
			time.Sleep(500 * time.Millisecond)
		}
	}
}

// consumeData consumes data from a channel until stopped.
func consumeData(dataChannel chan int, stopChannel chan struct{}) {
	for {
		select {
		case <-stopChannel:
			fmt.Println("Stopping data consumption...")
			return
		case data := <-dataChannel:
			fmt.Printf("Consumed data: %d\n", data)
		}
	}
}

// worker processes jobs from the jobs channel and sends results to the results channel.
func worker(jobs <-chan int, results chan<- int) {
	for job := range jobs {
		fmt.Printf("Worker processing job %d\n", job)
		results <- job * job // Example work: squaring the job number
		time.Sleep(1 * time.Second) // Simulate work
	}
}
