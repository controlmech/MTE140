/*
 * Author: Taha Aziz 20822878
 * Date: 2020-04-01
 * Description: MTE140 Practice Excercise #2 Step 2. Find Max Sum of Nodes Across Subtrees
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int INT_MIN = -2147483648;

struct BinaryTreeNode{
    int value;
    BinaryTreeNode* left = nullptr;
    BinaryTreeNode* right = nullptr;
};

int find_max_sum_of_nodes(BinaryTreeNode* T, int &temp_max_sum){
    if (!T)
        return 0;
    // Consider left and right subtrees
    int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);
    int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);

    // Consider subtrees that pass through two sides of a node
    int max1 = max(T->value, max(left_sum, right_sum) + T->value);
    int max2 = max(max1, left_sum + right_sum + T->value);

    // Update maximum
    temp_max_sum = max(temp_max_sum, max2);

    return max1;
}
int find_max_sum_of_nodes(BinaryTreeNode* T){
    int max_sum = INT_MIN;
    find_max_sum_of_nodes(T, max_sum);
    return max_sum;
}

void test1(){
    BinaryTreeNode node1;
    node1.value = 5;
    BinaryTreeNode node2;
    node2.value = 1;
    BinaryTreeNode node3;
    node3.value = -3;
    BinaryTreeNode node4;
    node4.value = 7;
    BinaryTreeNode node5;
    node5.value = 2;
    BinaryTreeNode node6;
    node6.value = 10;
    BinaryTreeNode node7;
    node7.value = -2;

    node1.left = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;
    node3.right = &node6;
    node5.left = &node7;
    cout << find_max_sum_of_nodes(&node1) << endl;
}

void test2(){
    BinaryTreeNode node1;
    node1.value = 8;
    BinaryTreeNode node2;
    node2.value = -4;
    BinaryTreeNode node3;
    node3.value = -10;
    BinaryTreeNode node4;
    node4.value = 2;
    BinaryTreeNode node5;
    node5.value = 9;
    BinaryTreeNode node6;
    node6.value = -1;
    BinaryTreeNode node7;
    node7.value = 7;
    BinaryTreeNode node8;
    node8.value = 3;

    node1.left = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;
    node3.left = &node6;
    node3.right = &node7;
    node4.left = &node8;
    cout << find_max_sum_of_nodes(&node1) << endl;
}

void test3(){
    BinaryTreeNode node_1;
    node_1.value = -3;
    BinaryTreeNode node2;
    node2.value = -1;
    BinaryTreeNode node3;
    node3.value = -5;
    BinaryTreeNode node4;
    node4.value = -2;
    BinaryTreeNode node5;
    node5.value = 8;
    BinaryTreeNode node6;
    node6.value = -10;
    BinaryTreeNode node7;
    node7.value = 1;
    BinaryTreeNode node8;
    node8.value = 3;
    BinaryTreeNode node9;
    node9.value = 9;
    BinaryTreeNode node10;
    node10.value = 4;
    BinaryTreeNode node11;
    node11.value = -6;
    BinaryTreeNode node12;
    node12.value = 7;
    BinaryTreeNode node13;
    node13.value = -4;

    node_1.left = &node2;
    node_1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;
    node3.left = &node6;
    node3.right = &node7;
    node4.left = &node8;
    node6.left = &node9;
    node7.right = &node10;
    node8.left = &node11;
    node8.right = &node12;
    node9.left = &node13;
    cout << find_max_sum_of_nodes(&node_1) << endl;
}

int main(){
    cout << "test1:" << endl;
    test1(); // 20 expected
    cout << "test2:" << endl;
    test2(); // 13 expected
    cout << "test3:" << endl;
    test3(); // 15 expected
    return 0;
}
