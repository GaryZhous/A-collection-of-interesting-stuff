/*
We will use a file-sharing system to share a very large file which consists of m small chunks with IDs from 1 to m.

When users join the system, the system should assign a unique ID to them. The unique ID should be used once for each user, but when a user leaves the system, the ID can be reused again.

Users can request a certain chunk of the file, the system should return a list of IDs of all the users who own this chunk. If the user receives a non-empty list of IDs, they receive the requested chunk successfully.

Implement the FileSharing class:
1. FileSharing(int m) Initializes the object with a file of m chunks.
2. int join(int[] ownedChunks): A new user joined the system owning some chunks of the file, the system should assign an id to the user which is the smallest positive integer not taken by any other user. Return the assigned id.
3. void leave(int userID): The user with userID will leave the system, you cannot take file chunks from them anymore.
4. int[] request(int userID, int chunkID): The user userID requested the file chunk with chunkID. Return a list of the IDs of all users that own this chunk sorted in ascending order.
*/

use std::cmp::Reverse;
use std::collections::{BTreeSet, BinaryHeap, HashMap, HashSet};

struct FileSharing {
    // chunk_owners[c] = sorted set of user IDs who own chunk (c+1)
    chunk_owners: Vec<BTreeSet<i32>>,

    // user_chunks[u] = set of chunks owned by user u
    user_chunks: HashMap<i32, HashSet<i32>>,

    // reusable ids (min-heap via Reverse)
    free_ids: BinaryHeap<Reverse<i32>>,
    next_id: i32,
}

impl FileSharing {
    fn new(m: i32) -> Self {
        let m_usize = m as usize;
        Self {
            chunk_owners: vec![BTreeSet::new(); m_usize],
            user_chunks: HashMap::new(),
            free_ids: BinaryHeap::new(),
            next_id: 1,
        }
    }

    fn join(&mut self, owned_chunks: Vec<i32>) -> i32 {
        // smallest available id
        let id = if let Some(Reverse(x)) = self.free_ids.pop() {
            x
        } else {
            let x = self.next_id;
            self.next_id += 1;
            x
        };

        // record chunks owned by this user
        let mut set = HashSet::new();
        for &chunk in &owned_chunks {
            set.insert(chunk);

            // add user to chunk owners (chunk IDs are 1..m)
            let idx = (chunk - 1) as usize;
            self.chunk_owners[idx].insert(id);
        }

        self.user_chunks.insert(id, set);
        id
    }

    fn leave(&mut self, user_id: i32) {
        // remove user from all chunk owner sets
        if let Some(chunks) = self.user_chunks.remove(&user_id) {
            for chunk in chunks {
                let idx = (chunk - 1) as usize;
                self.chunk_owners[idx].remove(&user_id);
            }
            // user_id becomes reusable
            self.free_ids.push(Reverse(user_id));
        }
    }

    fn request(&mut self, user_id: i32, chunk_id: i32) -> Vec<i32> {
        let idx = (chunk_id - 1) as usize;

        // owners BEFORE possibly granting the chunk to requester
        let owners: Vec<i32> = self.chunk_owners[idx].iter().copied().collect();

        // if someone has it, requester receives it and becomes an owner too
        if !owners.is_empty() {
            if let Some(chunks) = self.user_chunks.get_mut(&user_id) {
                // if they didn't already have it, add both directions
                if chunks.insert(chunk_id) {
                    self.chunk_owners[idx].insert(user_id);
                }
            }
        }

        owners
    }
}
