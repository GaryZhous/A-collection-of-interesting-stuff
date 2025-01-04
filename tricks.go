package main

import "fmt"

func main(){
  a, b, n := 1, 2, 3
  
  //Multiply n by 2
  n = n << 1
  
  //Divide n by 2
  n = n >> 1
  
  //Swap a and b
  a, b = b, a  //a ^= b ^= a ^= b in c/c++
  
  //equal to the largest power of 2 that divides x
  n & -n
}

func isPowerOfTwo(x int) bool {
    // Handle edge case for 0 and negative numbers
    if x <= 0 {
        return false
    }
    // Check if x is a power of two using bitwise AND
    return (x & (x - 1)) == 0
}
