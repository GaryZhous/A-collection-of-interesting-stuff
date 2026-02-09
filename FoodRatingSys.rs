/**
 * Your FoodRatings object will be instantiated and called as such:
 * let obj = FoodRatings::new(foods, cuisines, ratings);
 * obj.change_rating(food, newRating);
 * let ret_2: String = obj.highest_rated(cuisine);
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
    // cuisine -> heap of candidates (may contain stale entries)
    cuisine_heaps: HashMap<String, BinaryHeap<Entry>>,
}

impl FoodRatings {
    fn new(foods: Vec<String>, cuisines: Vec<String>, ratings: Vec<i32>) -> Self {
        let mut food_info = HashMap::new();
        let mut cuisine_heaps: HashMap<String, BinaryHeap<Entry>> = HashMap::new();

        for i in 0..foods.len() {
            let food = foods[i].clone();
            let cuisine = cuisines[i].clone();
            let rating = ratings[i];

            food_info.insert(food.clone(), (cuisine.clone(), rating));
            cuisine_heaps
                .entry(cuisine)
                .or_insert_with(BinaryHeap::new)
                .push(Entry { rating, name: food });
        }

        Self {
            food_info,
            cuisine_heaps,
        }
    }

    fn change_rating(&mut self, food: String, new_rating: i32) {
        // food must exist
        let (cuisine, rating_ref) = {
            let (c, r) = self.food_info.get_mut(&food).unwrap();
            *r = new_rating;
            (c.clone(), new_rating)
        };

        // push new version; old heap entries become stale and will be cleaned lazily
        self.cuisine_heaps
            .get_mut(&cuisine)
            .unwrap()
            .push(Entry {
                rating: rating_ref,
                name: food,
            });
    }

    fn highest_rated(&mut self, cuisine: String) -> String {
        let heap = self.cuisine_heaps.get_mut(&cuisine).unwrap();

        loop {
            let top = heap.peek().unwrap().clone();
            let (_c, cur_rating) = self.food_info.get(&top.name).unwrap();

            if *cur_rating == top.rating {
                return top.name;
            }
            // stale entry; discard and keep going
            heap.pop();
        }
    }
}
