from Solution import Solution
import unittest
from timeout_decorator import timeout

class TreeNode:
    def __init__(self, val = 0, left = None, right = 0):
        self.val = val
        self.left = left
        self.right = right


class UnitTest(unittest.TestCase):
    def setUp(self):
        self.__testcases = {1: ([2,3,5,8,13,21,34], [2,5,3,8,13,21,34]),
                            2: ([7,13,11], [7,11,13]),
                            3: ([0,1,2,0,0,0,0,1,1,1,1,2,2,2,2], [0,2,1,0,0,0,0,2,2,2,2,1,1,1,1])}
        self.__obj = Solution()
        return super().setUp()
    
    def __createTree(self, arr):
        root = TreeNode(arr[0])
        queue = [root]

        index, n = 1, len(arr)

        while index < n:
            node = queue[0]; queue.pop(0)

            node.left = TreeNode(arr[index])
            queue.append(node.left)
            index += 1

            if index < n:
                node.right = TreeNode(arr[index])
                queue.append(node.right)
                index += 1

        return root

    def __createList(self, root):
        result = []
        queue = [root]

        while queue:
            node = queue[0]; queue.pop(0)
            result.append(node.val)

            if node.left: queue.append(node.left)
            if node.right: queue.append(node.right)

        return result
    
    @timeout(0.5)
    def test_case_1(self):
        input, output = self.__testcases[1]
        input = self.__createTree(input)
        result = self.__obj.reverseOddLevels(input)
        result = self.__createList(result)
        
        self.assertTrue(all(r == o for r, o in zip(result, output)))

    @timeout(0.5)
    def test_case_2(self):
        input, output = self.__testcases[2]
        input = self.__createTree(input)
        result = self.__obj.reverseOddLevels(input)
        result = self.__createList(result)

        self.assertTrue(all(r == o for r, o in zip(result, output)))

    @timeout(0.5)
    def test_case_3(self):
        input, output = self.__testcases[3]
        input = self.__createTree(input)
        result = self.__obj.reverseOddLevels(input)
        result = self.__createList(result)

        self.assertTrue(all(r == o for r, o in zip(result, output)))

if __name__ == '__main__': unittest.main()