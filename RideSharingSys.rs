/**
 * Your RideSharingSystem object will be instantiated and called as such:
 * let obj = RideSharingSystem::new();
 * obj.add_rider(riderId);
 * obj.add_driver(driverId);
 * let ret_3: Vec<i32> = obj.match_driver_with_rider();
 * obj.cancel_rider(riderId);
 */
use std::cell::RefCell;
use std::collections::{HashSet, VecDeque};

struct RideSharingSystem {
    riders_q: RefCell<VecDeque<i32>>,
    drivers_q: RefCell<VecDeque<i32>>,
    waiting_riders: RefCell<HashSet<i32>>, // riders that are still waiting (not matched, not canceled)
}

impl RideSharingSystem {
    fn new() -> Self {
        Self {
            riders_q: RefCell::new(VecDeque::new()),
            drivers_q: RefCell::new(VecDeque::new()),
            waiting_riders: RefCell::new(HashSet::new()),
        }
    }

    fn add_rider(&self, rider_id: i32) {
        // If you want to allow duplicates, remove this check.
        let mut waiting = self.waiting_riders.borrow_mut();
        if waiting.insert(rider_id) {
            self.riders_q.borrow_mut().push_back(rider_id);
        }
    }

    fn add_driver(&self, driver_id: i32) {
        self.drivers_q.borrow_mut().push_back(driver_id);
    }

    fn match_driver_with_rider(&self) -> Vec<i32> {
        // Clean canceled/already-matched riders from the front (lazy deletion).
        {
            let waiting = self.waiting_riders.borrow();
            let mut rq = self.riders_q.borrow_mut();
            while let Some(&front) = rq.front() {
                if waiting.contains(&front) {
                    break;
                }
                rq.pop_front();
            }
        }

        // Now check if both sides are available.
        let mut dq = self.drivers_q.borrow_mut();
        if dq.is_empty() {
            return vec![-1, -1];
        }

        let mut rq = self.riders_q.borrow_mut();
        if rq.is_empty() {
            return vec![-1, -1];
        }

        let driver_id = dq.pop_front().unwrap();
        let rider_id = rq.pop_front().unwrap();
        self.waiting_riders.borrow_mut().remove(&rider_id);

        vec![driver_id, rider_id]
    }

    fn cancel_rider(&self, rider_id: i32) {
        // If rider is waiting, mark as not waiting; queue cleanup is lazy.
        self.waiting_riders.borrow_mut().remove(&rider_id);
    }
}
