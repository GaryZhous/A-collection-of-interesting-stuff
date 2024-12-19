package main

import "fmt"

// Define the Node struct
type Node struct {
    value int
    next  *Node // unlike java, doing this without a pointer will cause infinite recursion
}

// Define the LinkedList struct
type LinkedList struct {
    head *Node
}

// Add a node at the end of the list, associate a method to the struct
func (ll *LinkedList) Append(value int) {
    newNode := &Node{value: value}
    if ll.head == nil {
        ll.head = newNode // If the list is empty, set the head to the new node
        return
    }
    current := ll.head
    for current.next != nil {
        current = current.next // Traverse to the end of the list
    }
    current.next = newNode // Add the new node at the end
}

// Display all elements in the linked list, associate another method to the struct
func (ll *LinkedList) Display() {
    current := ll.head
    for current != nil {
        fmt.Printf("%d -> ", current.value)
        current = current.next
    }
    fmt.Println("nil") // Indicate the end of the list
}

// Delete a node with a specific value, the last metho associated to the Node struct
func (ll *LinkedList) Delete(value int) {
    if ll.head == nil {
        fmt.Println("List is empty")
        return
    }

    if ll.head.value == value {
        ll.head = ll.head.next // If the head is the node to be deleted, move the head
        return
    }

    current := ll.head
    for current.next != nil && current.next.value != value {
        current = current.next // Traverse the list to find the node to delete
    }

    if current.next == nil {
        fmt.Println("Value not found in the list")
        return
    }

    current.next = current.next.next // Remove the node by skipping it
}

func main() {
    // Create a new linked list
    ll := LinkedList{}

    // Append elements to the list
    ll.Append(10)
    ll.Append(20)
    ll.Append(30)

    // Display the list
    fmt.Println("Linked list after adding nodes:")
    ll.Display()

    // Delete a node
    ll.Delete(20)
    fmt.Println("Linked list after deleting 20:")
    ll.Display()

    // Try deleting a non-existent value
    ll.Delete(40)
}
