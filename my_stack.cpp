#include <iostream>
#include <cstdlib>

#define default_size 10

class Stack{
  public:
  Stack(int size = default_size){
    this->arr = new int[size];
    this->cap = size;
    this->top = -1;
  }

  ~Stack(){
    delete[] this->arr;
  }

  void push(int stuff){
    if (isFull()){
        cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    arr[++top] = stuff;
  }

  int pop(){
    if (isEmpty()){
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    return arr[top--];
  }

  int peek(){
    if (!isEmpty())
       return arr[top];
    exit(EXIT_FAILURE);
  }

  int size(){
    return top + 1;
  }

  bool isEmpty(){
    return top == -1;
  }

  bool isFull(){
    return top == cap - 1;
  }

  private:
  int* arr;
  int top;
  int cap;
}
