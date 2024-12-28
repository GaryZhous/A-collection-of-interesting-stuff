// This file provides examples of how to use generics in Go.

package main

import "fmt"

// Generic function for summing slices of numeric types
func SumSlice[T int | float64](slice []T) T {
    var sum T
    for _, v := range slice {
        sum += v
    }
    return sum
}

// Generic function to find the maximum element in a slice
func Max[T comparable](slice []T) T {
    if len(slice) == 0 {
        panic("slice is empty")
    }
    max := slice[0]
    for _, v := range slice {
        if v > max {
            max = v
        }
    }
    return max
}

// Generic type Pair to hold two values of the same type
type Pair[T any] struct {
    First, Second T
}

func (p Pair[T]) Swap() Pair[T] {
    return Pair[T]{First: p.Second, Second: p.First}
}

// Generic function to filter a slice based on a predicate
func Filter[T any](slice []T, predicate func(T) bool) []T {
    var result []T
    for _, v := range slice {
        if predicate(v) {
            result = append(result, v)
        }
    }
    return result
}

// Example of a generic map function
func Map[T any, U any](slice []T, transform func(T) U) []U {
    result := make([]U, len(slice))
    for i, v := range slice {
        result[i] = transform(v)
    }
    return result
}

func main() {
    // Example usage of SumSlice
    intSlice := []int{1, 2, 3, 4}
    floatSlice := []float64{1.1, 2.2, 3.3}
    fmt.Println("Sum of intSlice:", SumSlice(intSlice))
    fmt.Println("Sum of floatSlice:", SumSlice(floatSlice))

    // Example usage of Max
    fmt.Println("Max of intSlice:", Max(intSlice))

    // Example usage of Pair
    pair := Pair[int]{First: 10, Second: 20}
    fmt.Println("Original pair:", pair)
    fmt.Println("Swapped pair:", pair.Swap())

    // Example usage of Filter
    evenNumbers := Filter(intSlice, func(v int) bool { return v%2 == 0 })
    fmt.Println("Even numbers:", evenNumbers)

    // Example usage of Map
    doubled := Map(intSlice, func(v int) int { return v * 2 })
    fmt.Println("Doubled values:", doubled)
}
