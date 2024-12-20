#include "Solution.hpp"
#include <iostream>

struct testcase {
    vector<int> input, output;
};

class UnitTest {
private:
    vector<testcase> testcases;
    Solution sol;
    TreeNode* createTree(vector<int> arr) {
        TreeNode* root = new TreeNode(arr[0]);
        queue<TreeNode*> q; q.push(root);
        int index = 1, n = arr.size();

        while(index < n) {
            TreeNode* node = q.front(); q.pop();
            node->left = new TreeNode(arr[index++]);
            q.push(node->left);
            if(index < n) { node->right = new TreeNode(arr[index++]); q.push(node->right); } 
        }

        return root;
    }

    vector<int> createList(TreeNode* root) {
        vector<int> arr;
        queue<TreeNode*> q; q.push(root);

        while(!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            arr.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }

        return arr;
    }

public:
    UnitTest() {
        testcases = {{{2,3,5,8,13,21,34},{2,5,3,8,13,21,34}},
                     {{7,13,11},{7,11,13}},
                     {{0,1,2,0,0,0,0,1,1,1,1,2,2,2,2},{0,2,1,0,0,0,0,2,2,2,2,1,1,1,1}}};
    }

    void test() {
        for(int index = 0; index < testcases.size(); ++index) {
            vector<int> input = testcases[index].input, output = testcases[index].output;
            TreeNode* root = createTree(input);

            root = sol.reverseOddLevels(root);
            vector<int> result = createList(root);

            bool matched = true;
            for(int index = 0; index < result.size(); ++index)
                if(output[index] != result[index]) { matched = false; break; }

            cout << "TestCase " << index+1 << ": " << ((matched)?"true":"false") << endl;
        }
    }
};

int main() {
    UnitTest test;
    test.test();
}