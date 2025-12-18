/*
You are asked to design a file system that allows you to create new paths and associate them with different values.

The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string "" and "/" are not.

Implement the FileSystem class:
  1. bool createPath(string path, int value) Creates a new path and associates a value to it if possible and returns true. Returns false if the path already exists or its parent path doesn't exist.
  2. int get(string path) Returns the value associated with path or returns -1 if the path doesn't exist.
*/

use std::collections::HashMap;

struct FileSystem {
    // Maps full path -> associated value
    mp: HashMap<String, i32>,
}

impl FileSystem {
    fn new() -> Self {
        FileSystem {
            mp: HashMap::new(),
        }
    }

    fn create_path(&mut self, path: String, value: i32) -> bool {
        // Path must be non-empty and not just "/"
        if path.is_empty() || path == "/" {
            return false;
        }

        // If already exists, cannot create
        if self.mp.contains_key(&path) {
            return false;
        }

        // Compute parent path:
        // "/a"      -> parent is "" (special: allowed, since root is implicit)
        // "/a/b"    -> parent is "/a"
        let parent = match path.rfind('/') {
            Some(0) => "",                // last '/' is the leading one => parent is root (implicit)
            Some(i) => &path[..i],        // slice up to last '/'
            None => return false,         // invalid path format (should always have '/')
        };

        // If parent is not root-implicit, it must exist
        if !parent.is_empty() && !self.mp.contains_key(parent) {
            return false;
        }

        // Create it
        self.mp.insert(path, value);
        true
    }

    fn get(&self, path: String) -> i32 {
        *self.mp.get(&path).unwrap_or(&-1)
    }
}
