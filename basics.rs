// main.rs

// 1. Entry point
fn main() {
    println!("--- Rust Basics Tutorial ---");
    // Extra: Shadowing
    let x = 5;
    let x = 6;
    println!("x = {}", x)
    // 2. Variables
    variables();

    // 3. Data Types
    data_types();

    // 4. Control Flow
    control_flow();

    // 5. Functions
    let sum = add(5, 3);
    println!("5 + 3 = {}", sum);

    // 6. Ownership & Borrowing
    ownership();

    // 7. Structs and Enums
    structs_enums();

    // 8. Pattern Matching
    pattern_matching();

    // 9. Vectors & Iteration
    vectors_and_loops();

    // 10. Option and Result
    option_result();

    // 11. Error Handling
    match read_file() {
        Ok(content) => println!("File content: {}", content),
        Err(e) => println!("Error reading file: {}", e),
    }

    // 12. Traits & Implementations
    traits();
}

// 2. Variables & mutability
fn variables() {
    let x = 10;
    let mut y = 5;
    println!("x = {}, y = {}", x, y);
    y += 1;
    println!("Updated y = {}", y);
}

// 3. Primitive Data Types
fn data_types() {
    let a: i32 = -42;
    let b: f64 = 3.14;
    let c: bool = true;
    let d: char = 'R';
    println!("a: {}, b: {}, c: {}, d: {}", a, b, c, d);
}

// 4. Control flow
fn control_flow() {
    let num = 7;
    if num < 5 {
        println!("Less than 5");
    } else {
        println!("Greater or equal to 5");
    }

    for i in 0..3 {
        println!("for loop: i = {}", i);
    }

    let mut count = 0;
    while count < 3 {
        println!("while loop: count = {}", count);
        count += 1;
    }
}

// 5. Functions
fn add(a: i32, b: i32) -> i32 {
    a + b
}

// 6. Ownership & Borrowing
fn ownership() {
    let s = String::from("hello");
    print_str(&s); // Borrowing
    println!("Still own s: {}", s);
}

fn print_str(s: &String) {
    println!("Borrowed: {}", s);
}

// 7. Structs and Enums
struct Person {
    name: String,
    age: u8,
}

enum Direction {
    Up,
    Down,
    Left,
    Right,
}

fn structs_enums() {
    let p = Person {
        name: String::from("Alice"),
        age: 30,
    };
    println!("{} is {} years old", p.name, p.age);

    let dir = Direction::Left;
    match dir {
        Direction::Up => println!("Going up"),
        Direction::Down => println!("Going down"),
        Direction::Left => println!("Going left"),
        Direction::Right => println!("Going right"),
    }
}

// 8. Pattern Matching
fn pattern_matching() {
    let number = Some(3);
    match number {
        Some(x) if x > 0 => println!("Positive number: {}", x),
        Some(_) => println!("Zero or negative"),
        None => println!("No number"),
    }
}

// 9. Collections
fn vectors_and_loops() {
    let v = vec![1, 2, 3];
    for val in &v {
        println!("Vector item: {}", val);
    }
}

// 10. Option & Result
fn option_result() {
    let maybe_num: Option<i32> = Some(10);
    if let Some(n) = maybe_num {
        println!("Option contains: {}", n);
    }

    let res: Result<i32, &str> = Ok(200);
    match res {
        Ok(val) => println!("Result is OK: {}", val),
        Err(msg) => println!("Result is Err: {}", msg),
    }
}

// 11. Error handling with Result
use std::fs::File;
use std::io::{self, Read};

fn read_file() -> Result<String, io::Error> {
    let mut file = File::open("example.txt")?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    Ok(contents)
}

// 12. Traits and Implementations
trait Greet {
    fn greet(&self);
}

struct Dog;
impl Greet for Dog {
    fn greet(&self) {
        println!("Woof!");
    }
}

fn traits() {
    let dog = Dog;
    dog.greet();
}
