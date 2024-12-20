from typing import Optional

class TreeNode:
    def __init__(self, val = 0, left = None, right = 0):
        self.val = val
        self.left = left
        self.right = right

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