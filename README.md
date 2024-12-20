- ## Approach 2:- Depth First Search

    - ### Intuition
        The problem requires us to reverse the values at odd levels (1-based indexing) of a binary tree while keeping the structure of the tree intact. The key observation here is that the structure of the tree must remain unchanged, and only the values at odd levels should be reversed.

        To achieve this, we can traverse the tree using a depth-first search (DFS) approach. During this traversal, we need to reverse the child node values at even levels (since even levels are 0-based indices for odd levels in 1-based indexing). 

        By swapping values at even levels during the DFS traversal, we can effectively reverse the odd-level nodes' values while maintaining the original tree structure.

    - ### Approach
        1. **DFS Traversal**:
            - Start at the root and recursively traverse the binary tree using DFS.
            - For each pair of left and right children at a given level, check if the level is even (0-based indexing). If it is, swap the values of the left and right nodes to reverse the values at that level.
        
        2. **Recursive Calls**:
            - After processing the current level, recursively move to the next level for both the left and right child nodes.
            - Make sure to handle all four possible child pairs at each level: (left.left, right.right) and (left.right, right.left).

        3. **Termination Condition**:   
            - The recursion terminates when we reach a level where either of the child nodes is `None`. This prevents the algorithm from trying to process missing nodes.

        4. **Return the Modified Tree**:
            - After the entire tree has been processed, return the modified root node.

        This approach ensures that we only reverse values at the required levels and maintain the tree structure.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
            class Solution:
                def reverseOddLevels(self, root: Optional[TreeNode]) -> TreeNode:
                    # Define a recursive DFS function to reverse values at odd levels
                    def DFS(level: int, left: Optional[TreeNode], right: Optional[TreeNode]) -> None:
                        # Base case: If either of the nodes is None, we return (no reversal needed)
                        if not left or not right: 
                            return
                        
                        # If we're at an even level (0-based index), swap the values of the left and right nodes
                        if level % 2 == 0:
                            # Swap the values of the two child nodes
                            left.val, right.val = right.val, left.val

                        # Recursively process the next level for the left and right children
                        # First call for the next level, going down left-left and right-right
                        DFS(level + 1, left.left, right.right)
                        # Second call for the next level, going down left-right and right-left
                        DFS(level + 1, left.right, right.left)
                    
                    # Start DFS from the root's left and right children at level 0
                    DFS(0, root.left, root.right)

                    # Return the modified root node, with values reversed at odd levels
                    return root
            ```
        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity
        - **Traversal**:
            - We visit each node of the tree exactly once. At each node, we perform a constant amount of work (checking the level and possibly swapping two values).
        
        - **Time Complexity**: **$O(N)$**, where **$N$** is the number of nodes in the tree.

    - ### Space Complexity
        - **Recursive Stack**:
            - Since the algorithm uses recursion, the space complexity is determined by the maximum depth of the recursion stack, which is equal to the height of the tree.

        - **Space Complexity**: **$O(H)$**, where **$H$** is the height of the tree. In the worst case, if the tree is highly unbalanced, the height could be equal to **$N$**, so the space complexity could be **$O(N)$**. However, for a balanced tree, the height would be **$O(log(N))$**, making the space complexity **$O(log(N))$**.