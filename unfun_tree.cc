#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct TreeNode{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(): val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

struct ListNode{
  int val;
  ListNode* next;
  ListNode(): val(0), next(nullptr) {}
  ListNode(int x): val(x), next(nullptr) {}
  ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Tree_and_sh*t {
  public:
  int kthSmallest(TreeNode* root, int k){
    int leftCnt = count(root->left);
    if (leftCnt == k - 1) return root->val;
    if (leftCnt > k - 1) return kthSmallest(root->left, k);
    return kthSmallest(root.right, k - leftCnt - 1);
  }

  TreeNode* sortedListToBST(ListNode* head) { //this function sort a linkedlist to a BST
    if (head == nullptr) return null;
    if (head->next == nullptr) return new TreeNode(head->val);
    ListNode preMid = preMid(head);
    ListNode mid = preMid->next;
    preMid->next = nullptr;
    TreeNode* t = new TreeNode(mid->val);
    t->left = sortedListToBST(head);
    t->right = sortedListToBST(mid->next);
    return t;
   }
  private:
  int count(TreeNode node) {
    if (node == null) return 0;
    return 1 + count(node->left) + count(node->right);
  }

  ListNode* preMid(ListNode* head) {
    ListNode* slow = head, fast = head->next;
    ListNode* pre = head;
    while (fast != null && fast->next != null) {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    return pre;
  }
};
