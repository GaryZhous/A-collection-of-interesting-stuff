/*
  Design a Skiplist without using any built-in libraries.
  A skiplist is a data structure that takes O(log(n)) time to add, erase and search. Comparing with treap and red-black tree which has the same function and performance, the code length of Skiplist can be comparatively short and the idea behind Skiplists is just simple linked lists.
*/
use std::ptr;

const MAX_LEVEL: usize = 32;

struct Node {
    val: i32,
    // next[i] is the forward pointer at level i (0 = bottom)
    next: Vec<*mut Node>,
}

impl Node {
    fn new(val: i32, level: usize) -> Self {
        Self {
            val,
            next: vec![ptr::null_mut(); level],
        }
    }
}

pub struct Skiplist {
    head: *mut Node, // sentinel head
    level: usize,    // current highest level in use (>= 1)
    rng: u64,        // small built-in RNG (no external crates)
}

impl Skiplist {
    pub fn new() -> Self {
        let head = Box::into_raw(Box::new(Node::new(i32::MIN, MAX_LEVEL)));
        Self {
            head,
            level: 1,
            rng: 0x9E3779B97F4A7C15u64, // arbitrary non-zero seed
        }
    }

    // xorshift64* style RNG
    fn next_u64(&mut self) -> u64 {
        let mut x = self.rng;
        x ^= x >> 12;
        x ^= x << 25;
        x ^= x >> 27;
        self.rng = x;
        x.wrapping_mul(0x2545F4914F6CDD1D)
    }

    // geometric distribution with p=1/2
    fn random_level(&mut self) -> usize {
        let mut lvl = 1;
        while lvl < MAX_LEVEL && (self.next_u64() & 1) == 1 {
            lvl += 1;
        }
        lvl
    }

    pub fn search(&self, target: i32) -> bool {
        unsafe {
            let mut cur = self.head;
            // walk from top used level down to 0
            for i in (0..self.level).rev() {
                while !(*cur).next[i].is_null() && (*(*cur).next[i]).val < target {
                    cur = (*cur).next[i];
                }
            }
            let nxt = (*cur).next[0];
            !nxt.is_null() && (*nxt).val == target
        }
    }

    pub fn add(&mut self, num: i32) {
        unsafe {
            // update[i] will be the node right before insertion point at level i
            let mut update: [*mut Node; MAX_LEVEL] = [ptr::null_mut(); MAX_LEVEL];
            let mut cur = self.head;

            for i in (0..self.level).rev() {
                while !(*cur).next[i].is_null() && (*(*cur).next[i]).val < num {
                    cur = (*cur).next[i];
                }
                update[i] = cur;
            }

            let new_lvl = self.random_level();
            if new_lvl > self.level {
                for i in self.level..new_lvl {
                    update[i] = self.head;
                }
                self.level = new_lvl;
            }

            let node = Box::into_raw(Box::new(Node::new(num, new_lvl)));

            for i in 0..new_lvl {
                (*node).next[i] = (*update[i]).next[i];
                (*update[i]).next[i] = node;
            }
        }
    }

    pub fn erase(&mut self, num: i32) -> bool {
        unsafe {
            let mut update: [*mut Node; MAX_LEVEL] = [ptr::null_mut(); MAX_LEVEL];
            let mut cur = self.head;

            for i in (0..self.level).rev() {
                while !(*cur).next[i].is_null() && (*(*cur).next[i]).val < num {
                    cur = (*cur).next[i];
                }
                update[i] = cur;
            }

            let target = (*update[0]).next[0];
            if target.is_null() || (*target).val != num {
                return false;
            }

            let tgt_levels = (*target).next.len();
            for i in 0..self.level {
                if i < tgt_levels && (*update[i]).next[i] == target {
                    (*update[i]).next[i] = (*target).next[i];
                }
            }

            // free removed node
            drop(Box::from_raw(target));

            // reduce current level if top levels become empty
            while self.level > 1 && (*self.head).next[self.level - 1].is_null() {
                self.level -= 1;
            }
            true
        }
    }
}

impl Drop for Skiplist {
    fn drop(&mut self) {
        unsafe {
            // free all nodes via level 0 chain
            let mut cur = (*self.head).next[0];
            while !cur.is_null() {
                let next = (*cur).next[0];
                drop(Box::from_raw(cur));
                cur = next;
            }
            // free head sentinel
            drop(Box::from_raw(self.head));
            self.head = ptr::null_mut();
        }
    }
}
