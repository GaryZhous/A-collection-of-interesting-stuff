// inheritance.rs
// Rust does not support traditional class-based inheritance like OOP languages.
// Instead, it uses TRAITS to achieve polymorphism and code reuse.

use std::fmt::{Debug, Display};
use std::cmp::PartialOrd;
use async_trait::async_trait; // Requires `async-trait` crate

// ---------- BASIC TRAIT USAGE ----------
trait Animal: Debug {
    fn speak(&self);
    fn name(&self) -> &str;
}

#[derive(Debug, PartialEq, PartialOrd)]
struct Dog {
    name: String,
}

#[derive(Debug, PartialEq, PartialOrd)]
struct Cat {
    name: String,
}

impl Animal for Dog {
    fn speak(&self) {
        println!("{} says: Woof!", self.name);
    }
    fn name(&self) -> &str {
        &self.name
    }
}

impl Animal for Cat {
    fn speak(&self) {
        println!("{} says: Meow!", self.name);
    }
    fn name(&self) -> &str {
        &self.name
    }
}

// ---------- TRAIT COMPOSITION ----------
trait Pet: Animal + Walker {
    fn cuddle(&self) {
        println!("{} wants to cuddle!", self.name());
    }
}

impl<T> Pet for T
where
    T: Animal + Walker + Debug
{
}

// ---------- DEFAULT TRAIT METHODS ----------
trait Walker {
    fn walk(&self) {
        println!("{} is walking...", self.name());
    }
    fn name(&self) -> &str;
}

impl Walker for Dog {
    fn name(&self) -> &str {
        &self.name
    }
}

impl Walker for Cat {
    fn name(&self) -> &str {
        &self.name
    }
}

// ---------- ASYNC TRAIT ----------
#[async_trait]
trait AsyncTrick {
    async fn do_trick(&self);
}

#[async_trait]
impl AsyncTrick for Dog {
    async fn do_trick(&self) {
        println!("{} rolls over!", self.name);
    }
}

#[async_trait]
impl AsyncTrick for Cat {
    async fn do_trick(&self) {
        println!("{} jumps through a hoop!", self.name);
    }
}

// ---------- ADVANCED: TRAIT OBJECTS & DYNAMIC DISPATCH ----------
fn make_animal_speak(animal: &dyn Animal) {
    animal.speak();
}

// ---------- ADVANCED: GENERICS WITH TRAIT BOUNDS ----------
fn perform_walk<T>(creature: &T)
where
    T: Walker
{
    creature.walk();
}

fn compare_animals<T>(a: T, b: T)
where
    T: PartialOrd + Display,
{
    if a < b {
        println!("{} is less than {}", a, b);
    } else {
        println!("{} is greater than or equal to {}", a, b);
    }
}

// ---------- ADVANCED: TRAIT COMPOSITION FUNCTION ----------
fn pet_behavior<T>(pet: &T)
where
    T: Pet,
{
    pet.walk();
    pet.cuddle();
    pet.speak();
}

#[tokio::main]
async fn main() {
    let dog = Dog { name: String::from("Buddy") };
    let cat = Cat { name: String::from("Whiskers") };

    // Trait object usage
    let animals: Vec<&dyn Animal> = vec![&dog, &cat];
    for animal in animals {
        make_animal_speak(animal);
    }

    // Trait with default method
    perform_walk(&dog);
    perform_walk(&cat);

    // Trait composition in action
    pet_behavior(&dog);
    pet_behavior(&cat);

    // Async trait usage
    dog.do_trick().await;
    cat.do_trick().await;

    // Comparable constraint
    compare_animals(3.5, 7.1);
    compare_animals("Alice", "Bob");
}

/*
Output:
Buddy says: Woof!
Whiskers says: Meow!
Buddy is walking...
Whiskers is walking...
Buddy is walking...
Buddy wants to cuddle!
Buddy says: Woof!
Whiskers is walking...
Whiskers wants to cuddle!
Whiskers says: Meow!
Buddy rolls over!
Whiskers jumps through a hoop!
3.5 is less than 7.1
Alice is less than Bob
*/
