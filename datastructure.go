// datastructure.go
// This file provides examples of useful data structures implemented in Go.

package main

import (
    "container/heap"
    "fmt"
)

// Stack implementation using slices
type Stack[T any] struct {
    elements []T
}

func (s *Stack[T]) Push(value T) {
    s.elements = append(s.elements, value)
}

func (s *Stack[T]) Pop() T {
    if len(s.elements) == 0 {
        panic("Stack is empty")
    }
    val := s.elements[len(s.elements)-1]
    s.elements = s.elements[:len(s.elements)-1]
    return val
}

func (s *Stack[T]) Peek() T {
    if len(s.elements) == 0 {
        panic("Stack is empty")
    }
    return s.elements[len(s.elements)-1]
}

func (s *Stack[T]) IsEmpty() bool {
    return len(s.elements) == 0
}

// Queue implementation using slices
type Queue[T any] struct {
    elements []T
}

func (q *Queue[T]) Enqueue(value T) {
    q.elements = append(q.elements, value)
}

func (q *Queue[T]) Dequeue() T {
    if len(q.elements) == 0 {
        panic("Queue is empty")
    }
    val := q.elements[0]
    q.elements = q.elements[1:]
    return val
}

func (q *Queue[T]) IsEmpty() bool {
    return len(q.elements) == 0
}

// Priority Queue using container/heap
type PriorityQueueItem[T any] struct {
    Value    T
    Priority int
}

type PriorityQueue[T any] []PriorityQueueItem[T]

func (pq PriorityQueue[T]) Len() int { return len(pq) }
func (pq PriorityQueue[T]) Less(i, j int) bool { return pq[i].Priority > pq[j].Priority }
func (pq PriorityQueue[T]) Swap(i, j int) { pq[i], pq[j] = pq[j], pq[i] }

func (pq *PriorityQueue[T]) Push(x any) {
    *pq = append(*pq, x.(PriorityQueueItem[T]))
}

func (pq *PriorityQueue[T]) Pop() any {
    old := *pq
    n := len(old)
    item := old[n-1]
    *pq = old[:n-1]
    return item
}

func (pq *PriorityQueue[T]) Peek() PriorityQueueItem[T] {
    return (*pq)[0]
}

// HashMap example using Go's built-in map
type HashMap[K comparable, V any] map[K]V

func (hm HashMap[K, V]) Get(key K) (V, bool) {
    val, exists := hm[key]
    return val, exists
}

func (hm HashMap[K, V]) Set(key K, value V) {
    hm[key] = value
}

func (hm HashMap[K, V]) Delete(key K) {
    delete(hm, key)
}

// Example usage of the data structures
func main() {
    // Stack example
    stack := Stack[int]{}
    stack.Push(10)
    stack.Push(20)
    fmt.Println("Stack Peek:", stack.Peek())
    fmt.Println("Stack Pop:", stack.Pop())

    // Queue example
    queue := Queue[string]{}
    queue.Enqueue("A")
    queue.Enqueue("B")
    fmt.Println("Queue Dequeue:", queue.Dequeue())

    // Priority Queue example
    pq := &PriorityQueue[string]{}
    heap.Init(pq)
    heap.Push(pq, PriorityQueueItem[string]{Value: "High", Priority: 3})
    heap.Push(pq, PriorityQueueItem[string]{Value: "Medium", Priority: 2})
    fmt.Println("Priority Queue Peek:", pq.Peek().Value)

    // HashMap example
    hashMap := HashMap[string, int]{}
    hashMap.Set("one", 1)
    if val, exists := hashMap.Get("one"); exists {
        fmt.Println("HashMap Get:", val)
    }
}
