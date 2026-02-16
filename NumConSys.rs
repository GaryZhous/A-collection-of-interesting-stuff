/**
 * Your NumberContainers object will be instantiated and called as such:
 * let obj = NumberContainers::new();
 * obj.change(index, number);
 * let ret_2: i32 = obj.find(number);
 */
use std::cmp::Reverse;
use std::collections::{BinaryHeap, HashMap};

struct NumberContainers {
    idx_to_num: HashMap<i32, i32>,
    num_to_heap: HashMap<i32, BinaryHeap<Reverse<i32>>>, // min-heap via Reverse
}

impl NumberContainers {
    fn new() -> Self {
        Self {
            idx_to_num: HashMap::new(),
            num_to_heap: HashMap::new(),
        }
    }

    fn change(&mut self, index: i32, number: i32) {
        // Update current mapping
        self.idx_to_num.insert(index, number);

        // Push index into that number's heap
        self.num_to_heap
            .entry(number)
            .or_insert_with(BinaryHeap::new)
            .push(Reverse(index));
    }

    fn find(&mut self, number: i32) -> i32 {
        let heap_opt = self.num_to_heap.get_mut(&number);
        if heap_opt.is_none() {
            return -1;
        }
        let heap = heap_opt.unwrap();

        // Pop stale indices until the top is valid
        while let Some(&Reverse(i)) = heap.peek() {
            match self.idx_to_num.get(&i) {
                Some(&cur) if cur == number => return i, // valid smallest index
                _ => {
                    heap.pop(); // stale, discard
                }
            }
        }

        -1
    }
}
