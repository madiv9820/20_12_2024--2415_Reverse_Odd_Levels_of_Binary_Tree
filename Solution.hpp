#include <vector>
#include <queue>
#include <functional>
using namespace std;

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        // Define a recursive DFS function to reverse values at odd levels
        function<void(int, TreeNode*, TreeNode*)> DFS = [&](int level, TreeNode* left, TreeNode* right) -> void {
            // Base case: if either of the nodes is null, return (no reversal needed)
            if(!left || !right) return;

            // If we are at an even level (0-based index), reverse the values of the left and right nodes
            if(level % 2 == 0) {
                // Swap the values of the left and right child nodes
                int temp = left->val;
                left->val = right->val;
                right->val = temp;
            }

            // Recursive DFS call to process the next level of nodes (left-left, right-right)
            DFS(level + 1, left->left, right->right);
            // Recursive DFS call to process the next level of nodes (left-right, right-left)
            DFS(level + 1, left->right, right->left);
        };

        // Start the DFS traversal from the root's left and right children, at level 0
        DFS(0, root->left, root->right);

        // Return the modified root node with reversed values at odd levels
        return root;
    }
};