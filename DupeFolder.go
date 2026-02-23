/**
  Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths, where paths[i] is an array representing an absolute path to the ith folder in the file system.
  For example, ["one", "two", "three"] represents the path "/one/two/three".
  Two folders (not necessarily on the same level) are identical if they contain the same non-empty set of identical subfolders and underlying subfolder structure. The folders do not need to be at the root level to be identical. If two or more folders are identical, then mark the folders as well as all their subfolders.  
  For example, folders "/a" and "/b" in the file structure below are identical. They (as well as their subfolders) should all be marked:
  /a
  /a/x
  /a/x/y
  /a/z
  /b
  /b/x
  /b/x/y
  /b/z
  However, if the file structure also included the path "/b/w", then the folders "/a" and "/b" would not be identical. Note that "/a/x" and "/b/x" would still be considered identical even with the added folder.
  Once all the identical folders and their subfolders have been marked, the file system will delete all of them. The file system only runs the deletion once, so any folders that become identical after the initial deletion are not deleted.
  
  Return the 2D array ans containing the paths of the remaining folders after deleting all the marked folders. The paths may be returned in any order.
*/

type Trie struct {
	serial   string           // current node structure's serialized representation
	children map[string]*Trie // current node's child nodes
}

func deleteDuplicateFolder(paths [][]string) [][]string {
	root := &Trie{children: make(map[string]*Trie)} // root node
	// build a trie tree
	for _, path := range paths {
		cur := root
		for _, node := range path {
			if _, ok := cur.children[node]; !ok {
				cur.children[node] = &Trie{children: make(map[string]*Trie)}
			}
			cur = cur.children[node]
		}
	}

	freq := make(map[string]int) // hash table records the occurrence times of each serialized representation
	// post-order traversal based on depth-first search, calculate the serialized representation of each node structure
	var construct func(*Trie)
	construct = func(node *Trie) {
		if len(node.children) == 0 {
			return // if it is a leaf node, no operation is needed.
		}
		v := make([]string, 0, len(node.children))
		for folder, child := range node.children {
			construct(child)
			v = append(v, folder+"("+child.serial+")")
		}
		sort.Strings(v)
		node.serial = strings.Join(v, "")
		freq[node.serial]++
	}
	construct(root)
	ans := make([][]string, 0)
	path := make([]string, 0)
	// operate the trie, delete duplicate folders
	var operate func(*Trie)
	operate = func(node *Trie) {
		if freq[node.serial] > 1 {
			return // if the serialization representation appears more than once, it needs to be deleted
		}

		if len(path) > 0 {
			tmp := make([]string, len(path))
			copy(tmp, path)
			ans = append(ans, tmp)
		}

		for folder, child := range node.children {
			path = append(path, folder)
			operate(child)
			path = path[:len(path)-1]
		}
	}
	operate(root)

	return ans
}
