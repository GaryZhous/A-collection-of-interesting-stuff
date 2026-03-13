/*
Design a food rating system that can do the following:
- Modify the rating of a food item listed in the system.
- Return the highest-rated food item for a type of cuisine in the system.

Implement the FoodRatings class:
1. FoodRatings(String[] foods, String[] cuisines, int[] ratings): Initializes the system.
   Each food[i] belongs to cuisines[i] and has an initial rating of ratings[i].
2. void changeRating(String food, int newRating): Changes the rating of the food item named food.
3. String highestRated(String cuisine): Returns the name of the food item that has the highest
   rating for the given type of cuisine. If there is a tie, return the item that is
   lexicographically smaller.
*/

use std::cmp::Ordering;
use std::collections::{BinaryHeap, HashMap};

#[derive(Clone, Eq, PartialEq)]
struct Entry {
    rating: i32,
    name: String,
}

// BinaryHeap in Rust is a max-heap.
// We want: higher rating first; if tie, lexicographically smaller name first.
// So for ties, we treat smaller name as "greater" in heap ordering.
impl Ord for Entry {
    fn cmp(&self, other: &Self) -> Ordering {
        match self.rating.cmp(&other.rating) {
            Ordering::Equal => other.name.cmp(&self.name), // reverse for lexicographically smaller first
            ord => ord,
        }
    }
}

impl PartialOrd for Entry {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct FoodRatings {
    // food -> (cuisine, rating)
    food_info: HashMap<String, (String, i32)>,
    // cuisine -> max-heap of candidates (may contain stale entries)
    cuisine_heaps: HashMap<String, BinaryHeap<Entry>>,
}

impl FoodRatings {
    fn new(foods: Vec<String>, cuisines: Vec<String>, ratings: Vec<i32>) -> Self {
        let mut food_info = HashMap::new();
        let mut cuisine_heaps: HashMap<String, BinaryHeap<Entry>> = HashMap::new();

        for ((food, cuisine), rating) in foods.into_iter().zip(cuisines).zip(ratings) {
            food_info.insert(food.clone(), (cuisine.clone(), rating));
            cuisine_heaps
                .entry(cuisine)
                .or_default()
                .push(Entry { rating, name: food });
        }

        Self {
            food_info,
            cuisine_heaps,
        }
    }

    fn change_rating(&mut self, food: String, new_rating: i32) {
        // food must exist; update the canonical rating in food_info
        let cuisine = {
            let (cuisine, rating) = self.food_info.get_mut(&food).unwrap();
            *rating = new_rating;
            cuisine.clone()
        };

        // push new entry; the outdated heap entries become stale and are cleaned lazily
        self.cuisine_heaps
            .get_mut(&cuisine)
            .unwrap()
            .push(Entry { rating: new_rating, name: food });
    }

    fn highest_rated(&mut self, cuisine: String) -> String {
        let heap = self.cuisine_heaps.get_mut(&cuisine).unwrap();

        while let Some(top) = heap.peek().cloned() {
            let (_, cur_rating) = self.food_info.get(&top.name).unwrap();
            if *cur_rating == top.rating {
                return top.name;
            }
            // stale entry; discard and keep going
            heap.pop();
        }

        unreachable!("cuisine {:?} has no valid food entries", cuisine)
    }
}

fn main() {
    let foods = vec!["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"]
        .into_iter()
        .map(String::from)
        .collect();
    let cuisines = vec!["korean", "japanese", "japanese", "greek", "japanese", "korean"]
        .into_iter()
        .map(String::from)
        .collect();
    let ratings = vec![9, 12, 8, 15, 14, 7];

    let mut sys = FoodRatings::new(foods, cuisines, ratings);

    // highest rated japanese: ramen (rating 14)
    assert_eq!(sys.highest_rated("japanese".to_string()), "ramen");
    // highest rated korean: kimchi (rating 9)
    assert_eq!(sys.highest_rated("korean".to_string()), "kimchi");

    // change sushi's rating to 16
    sys.change_rating("sushi".to_string(), 16);
    // now sushi (16) is highest rated japanese
    assert_eq!(sys.highest_rated("japanese".to_string()), "sushi");

    // raise ramen to 16 — tie with sushi; lexicographically "ramen" < "sushi"
    sys.change_rating("ramen".to_string(), 16);
    assert_eq!(sys.highest_rated("japanese".to_string()), "ramen");

    println!("All assertions passed.");
}
