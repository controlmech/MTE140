/*
 * Author: Taha Aziz 20822878
 * Date: 2020-04-01
 * Description: MTE140 Practice Excercise #2 Step 1. Find and Print Sum of Nodes
 */

#include <iostream>
#include <string>

using namespace std;

struct BinaryTreeNode{
    int value;
    BinaryTreeNode* left = nullptr;
    BinaryTreeNode* right = nullptr;
};

void find_and_print_sum_of_nodes(BinaryTreeNode* T, int desired_sum, int cur_sum, string buffer){
    if (!T)
        return;
    int new_sum = cur_sum + T->value;
    string new_buffer = buffer + to_string(T->value) + " ";

    // Check sum
    if (desired_sum == new_sum)
        cout << new_buffer << endl;

    // Traverse all nodes recursively
    find_and_print_sum_of_nodes(T->left, desired_sum, new_sum, new_buffer);
    find_and_print_sum_of_nodes(T->right, desired_sum, new_sum, new_buffer);

    // Start again at each node once since paths can start at any node
    if (buffer == ""){
        find_and_print_sum_of_nodes(T->left, desired_sum, 0, "");
        find_and_print_sum_of_nodes(T->right, desired_sum, 0, "");
    }
}

void test1(int desired_sum){
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
    find_and_print_sum_of_nodes(&node1, desired_sum, 0, "");
}

void test2(int desired_sum){
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
    find_and_print_sum_of_nodes(&node1, desired_sum, 0, "");
}

void test3(int desired_sum){
    BinaryTreeNode node1;
    node1.value = -3;
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
    node12.value = -4;

    node1.left = &node2;
    node1.right = &node3;
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
    find_and_print_sum_of_nodes(&node1, desired_sum, 0, "");
}

int main(){
    cout << "test1:" << endl;
    test1(6); // 2 different paths expected
    cout << "test1.1:" << endl;
    test1(10); // 1 path expected
    cout << "test1.2:" << endl;
    test1(3); // 1 path expected
    cout << "test2:" << endl;
    test2(5); // 3 different paths expected
    cout << "test3:" << endl;
    test3(-3); // 6 different paths expected
    return 0;
}
