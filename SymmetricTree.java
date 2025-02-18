// Definition for a binary tree node
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}

class Solution {
    // Main function to check if a tree is symmetric
    public boolean isSymmetric(TreeNode root) {
        if (root == null)  // An empty tree is symmetric
            return true;
        return isMirror(root.left, root.right);  // Check if left and right subtrees are mirrors
    }
    
    // Helper function to check if two trees are mirror images of each other
    private boolean isMirror(TreeNode t1, TreeNode t2) {
        if (t1 == null && t2 == null) return true; // Both nodes are null, so they are symmetric
        if (t1 == null || t2 == null) return false; // One of them is null, so they are not symmetric
        
        // Check if values are equal and their children are mirrors:
        // Left subtree of t1 should be a mirror of right subtree of t2
        // Right subtree of t1 should be a mirror of left subtree of t2
        return (t1.val == t2.val) 
            && isMirror(t1.left, t2.right) 
            && isMirror(t1.right, t2.left);
    }
}
