#include <vector>
#include <queue>
#include <stack>
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
        // Queue to store nodes along with their respective level
        queue<pair<TreeNode*, int>> q;
        // Queue to store parent nodes temporarily when we need to reverse the odd levels
        queue<TreeNode*> parentNodes;
        // Stack to temporarily store child node values for reversal at odd levels
        stack<int> childNodes;

        // Start with the root node at level 0
        q.push({root, 0});

        // Loop until all nodes are processed
        while(!q.empty()) {
            // Get the current node and its level from the queue
            TreeNode* currentNode = q.front().first;
            int level = q.front().second;
            q.pop(); // Remove the processed node from the queue

            // If current node or its children don't exist, exit the loop early
            if(!currentNode || !currentNode->left || !currentNode->right) break;

            // If we are at an even level (0-based indexing, odd levels are 1, 3, 5, etc.)
            if(level % 2 == 0) {
                // Save parent nodes for later processing
                parentNodes.push(currentNode);
                // Save child node values to stack to reverse later
                childNodes.push(currentNode->left->val);
                childNodes.push(currentNode->right->val);
            }
            else {
                // If we're at an odd level, reverse the child node values for the parent nodes
                while(!parentNodes.empty()) {
                    // Pop from the stack and assign to the parent node's children
                    parentNodes.front()->left->val = childNodes.top();
                    childNodes.pop();
                    parentNodes.front()->right->val = childNodes.top();
                    childNodes.pop();

                    // Remove the parent node from the queue after its children are reversed
                    parentNodes.pop();
                }
            }

            // Add left and right children to the queue with incremented level
            q.push({currentNode->left, level+1});
            q.push({currentNode->right, level+1});
        }

        // After finishing the queue, ensure the remaining nodes at the last level are reversed if needed
        while(!parentNodes.empty()) {
            parentNodes.front()->left->val = childNodes.top();
            childNodes.pop();
            parentNodes.front()->right->val = childNodes.top();
            childNodes.pop();

            parentNodes.pop();
        }

        // Return the modified root node
        return root;
    }
};