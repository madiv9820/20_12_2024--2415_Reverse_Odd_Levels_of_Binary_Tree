from typing import Optional

class TreeNode:
    def __init__(self, val = 0, left = None, right = 0):
        self.val = val
        self.left = left
        self.right = right

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