- ## Approach 1:- Breadth First Search (Level Order Traversal)

    - ### Intuition
        The problem asks us to reverse the values of nodes at odd levels in a binary tree. We are given a binary tree where each node has two children, and we need to reverse the left and right children values at each odd level (1-based), while maintaining the structure of the tree.

        - #### Key Observations:
            - The levels of the tree are numbered starting from 0 (root at level 0). Odd levels (1-based) correspond to levels 1, 3, 5, etc., in 0-based indexing.
            - At each even level (0, 2, 4, etc.), we store the values of child nodes.
            - When we reach an odd level, we reverse the child node values for the parent nodes that were stored at the even level.

        - #### High-Level Idea:
            - Perform a level-order traversal (BFS) of the tree.
            - At even levels, store the values of the children of the nodes.
            - At odd levels, reverse the order of these stored values and assign them back to the parent nodes' children.
            - This approach ensures that the values at odd levels are reversed while the tree structure is preserved.

    - ### Approach
        1. **Level-Order Traversal (BFS)**: 
            - Use a queue to traverse the tree level by level.
            - Store the nodes along with their respective levels in the queue.
        
        2. **Processing Even and Odd Levels**:
            - At even levels, push the left and right child values onto a stack (i.e., `childNodes`).
            - At odd levels, pop the values from the stack and assign them to the left and right children of the parent nodes, effectively reversing the order of child nodes for that level.

        3. **Final Cleanup**:
            - After the main traversal is complete, ensure all remaining parent nodes at odd levels have their children reversed (since some odd-level nodes might not have been processed inside the loop).

        4. **Return the Modified Tree**:
            - After the traversal and reversal, return the root of the modified tree.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
            class Solution:
                def reverseOddLevels(self, root: Optional[TreeNode]) -> TreeNode:
                    # Initialize a queue for level-order traversal (BFS)
                    queue = []
                    # Initialize lists to temporarily store parent nodes and child node values
                    parentNodes = []
                    childNodes = []

                    # Start with the root node at level 0
                    queue.append((root, 0))

                    # While there are nodes in the queue, process each level
                    while queue:
                        # Get the current node and its level from the queue
                        currentNode, level = queue[0]
                        queue.pop(0)  # Dequeue the current node

                        # If the current node or its children do not exist, break the loop
                        if not currentNode or not currentNode.left or not currentNode.right: 
                            break

                        # Process nodes at even levels (0-based level, so odd levels are 1, 3, 5, etc.)
                        if level % 2 == 0:
                            # Save the current parent node
                            parentNodes.append(currentNode)
                            # Save the left and right child values to reverse later
                            childNodes.append(currentNode.left.val)
                            childNodes.append(currentNode.right.val)
                        else:
                            # If we're at an odd level, reverse the child node values for parent nodes
                            while parentNodes:
                                # Assign reversed child values to the parent nodes
                                parentNodes[0].left.val = childNodes[-1]
                                childNodes.pop()
                                parentNodes[0].right.val = childNodes[-1]
                                childNodes.pop()
                                
                                # Remove the processed parent node from the list
                                parentNodes.pop(0)

                        # Add left and right children to the queue with the next level incremented by 1
                        queue.append((currentNode.left, level + 1))
                        queue.append((currentNode.right, level + 1))

                    # After finishing the main loop, reverse any remaining odd-level child values
                    while parentNodes:
                        # Assign reversed child values to remaining parent nodes
                        parentNodes[0].left.val = childNodes[-1]
                        childNodes.pop()
                        parentNodes[0].right.val = childNodes[-1]
                        childNodes.pop()
                        
                        # Remove the processed parent node
                        parentNodes.pop(0)

                    # Return the modified tree with reversed values at odd levels
                    return root
            ```
        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity
        - **Level-Order Traversal (BFS)**: 
            - We traverse each node of the tree exactly once, processing each node in constant time.
        
        - **Processing Each Node**: 
            - For each node at even levels, we perform constant work (push the values onto a stack).
            - For each node at odd levels, we pop values from the stack and assign them to the parent node's children, which also takes constant time.

        Given **$N$** as the total number of nodes in the tree, the **time complexity** is: **$O(N)$**

    - ### Space Complexity
        - **Queue for BFS**: 
            - The queue stores nodes along with their levels. In the worst case, it stores all nodes at a given level. In a complete binary tree, the maximum number of nodes at any level is **$O(N/2)$**, so the space used by the queue is **$O(N)$**.
        
        - **Stack for Child Nodes**: 
            - The stack holds the child node values at even levels. In the worst case, it stores all child node values of the current level, which is also **$O(N/2)$**.

        Thus, the **space complexity** is dominated by the space required for the queue and stack, both of which take **$O(N)$** space.