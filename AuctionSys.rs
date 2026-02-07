/**
 * Your AuctionSystem object will be instantiated and called as such:
 * let obj = AuctionSystem::new();
 * obj.add_bid(userId, itemId, bidAmount);
 * obj.update_bid(userId, itemId, newAmount);
 * obj.remove_bid(userId, itemId);
 * let ret_4: i32 = obj.get_highest_bidder(itemId);
 */
use std::collections::{BinaryHeap, HashMap};

struct AuctionSystem {
    // (user_id, item_id) -> current bid amount
    cur: HashMap<(i32, i32), i32>,
    // item_id -> max-heap of (bid_amount, user_id)
    // tuple ordering makes it max by bid_amount, then by user_id (tie-breaker)
    heaps: HashMap<i32, BinaryHeap<(i32, i32)>>,
}

impl AuctionSystem {
    fn new() -> Self {
        Self {
            cur: HashMap::new(),
            heaps: HashMap::new(),
        }
    }

    fn add_bid(&mut self, user_id: i32, item_id: i32, bid_amount: i32) {
        // Replace if exists: just overwrite in `cur` and push the new entry to heap.
        self.cur.insert((user_id, item_id), bid_amount);
        self.heaps
            .entry(item_id)
            .or_insert_with(BinaryHeap::new)
            .push((bid_amount, user_id));
    }

    fn update_bid(&mut self, user_id: i32, item_id: i32, new_amount: i32) {
        // Guaranteed to exist
        self.cur.insert((user_id, item_id), new_amount);
        self.heaps
            .entry(item_id)
            .or_insert_with(BinaryHeap::new)
            .push((new_amount, user_id));
    }

    fn remove_bid(&mut self, user_id: i32, item_id: i32) {
        // Guaranteed to exist
        self.cur.remove(&(user_id, item_id));
        // No heap removal needed (lazy deletion)
    }

    fn get_highest_bidder(&mut self, item_id: i32) -> i32 {
        let heap_opt = self.heaps.get_mut(&item_id);
        if heap_opt.is_none() {
            return -1;
        }
        let heap = heap_opt.unwrap();

        while let Some(&(amt, uid)) = heap.peek() {
            match self.cur.get(&(uid, item_id)) {
                Some(&current_amt) if current_amt == amt => {
                    return uid; // valid top
                }
                _ => {
                    heap.pop(); // stale entry; discard
                }
            }
        }

        -1
    }
}
