#include <iostream>
#include <stack>
#include <queue>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	if (!root)
		return;
	stack<BinarySearchTree::TaskItem*> s1;
	TaskItem* cur;
	s1.push(root);

	while (!root){
		cur = s1.top();
		s1.pop();
		if (cur->left) {
			s1.push(cur->left);
		}
		if (cur->right) {
			s1.push(cur->right);
		}
		delete cur;
		--size;
	}
	cur = NULL;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if(!root)
		return BinarySearchTree::TaskItem(-1, "N/A");

	TaskItem* cur = root;
	while(cur->right){
		cur = cur->right;
	}
	return *cur;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if(!root)
		return BinarySearchTree::TaskItem(-1, "N/A");

	TaskItem* cur = root;
	while(cur->left){
		cur = cur->left;
	}
	return *cur;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	if (!root)
        return -1;
    int height = -1;
    queue<TaskItem*> q;
    q.push(root);
    while (true)
    {
        int nodeCount = q.size();
        if (nodeCount == 0)
            return height;
        height++;

        // Dequeue all nodes of current level and Enqueue all nodes of next level
        while (nodeCount > 0)
        {
            TaskItem *cur = q.front();
            q.pop();
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
            nodeCount--;
        }
    }
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	int i = 0;
	print(root, i);
}

void BinarySearchTree::print(BinarySearchTree::TaskItem* T, int& i) const {
	if(T == NULL)
		return;
	else {
		print(T->left, i);
		i++;
		cout << i << " - " << T->priority << endl;
		print(T->right, i);
	}
}

// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	if (!root)
		return false;
	stack<BinarySearchTree::TaskItem*> s1;
	s1.push(root);
	TaskItem* cur;
    bool found = false;

	while (s1.size() && !found){
		cur = s1.top();
		if (*cur == val)
			found = true;
		s1.pop();
		if (cur->left)
			s1.push(cur->left);
		if (cur->right)
			s1.push(cur->right);
	}
	return found;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	if (!root){
		root = new TaskItem(val);
		size++;
		return true;
	}
	else if (exists(val))
		return false;

	TaskItem* cur = root;
	TaskItem* prev = cur;

	while (cur) {
		if (cur->priority > val.priority) {
			prev = cur;
			cur = cur->left;
		}
		else {
			prev = cur;
			cur = cur->right;
		}
	}
	if (prev->priority > val.priority)
		prev->left = new TaskItem(val);
	else
		prev->right = new TaskItem(val);
	size++;
    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val) {
	TaskItem* cur = root;
	TaskItem* prev_cur = NULL;
	if(!root)
		return false;
	else if(size == 1 && val == *root) {
		delete root;
		root = NULL;
		cur = NULL;
	}
	else if(!exists(val)) {
		cur = NULL;
		return false;
	}
	else {
		while((cur->right != NULL || cur->left != NULL) && !(*cur == val)) {
			if(val.priority > cur->priority) {
				prev_cur = cur;
				cur = cur->right;
			}
			else {
				prev_cur = cur;
				cur = cur->left;
			}
		}
		if(cur->right == NULL && cur->left == NULL) { //case 1
			delete cur;
			if(prev_cur->left == cur) //if cur is to the left of prev_cur
				prev_cur->left = cur->left;
			else //if cur is to the right of prev_cur
				prev_cur->right = cur->left;
			cur = NULL;
			prev_cur = NULL;
		}
		else if(cur->right == NULL) { //case 2
			if(prev_cur) { //if cur is not root
				if(prev_cur->left == cur) //if cur is to the left of prev_cur
					prev_cur->left = cur->left;
				else //if cur is to the right of prev_cur
					prev_cur->right = cur->left;
				delete cur;
				cur = NULL;
				prev_cur = NULL;
			}
			else { //if cur is root
				root = cur->left;
				delete cur;
				cur = NULL;
			}
		}
		else if(cur->left == NULL) { //case 2
			if(prev_cur) { //if cur is not root
				if(prev_cur->left == cur) //if cur is to the left of prev_cur
					prev_cur->left = cur->right;
				else //if cur is to the right of prev_cur
					prev_cur->right = cur->right;
				delete cur;
				cur = NULL;
				prev_cur = NULL;
			}
			else { //if cur is root
				root = cur->right;
				delete cur;
				cur = NULL;
			}
		}
		else { //case 3
			TaskItem* prev_pred = NULL;
			TaskItem* pred = cur->left;
			while(pred->right != NULL) {
				prev_pred = pred;
				pred = pred->right;
			}
			if(prev_cur) { //if cur is not root
				if(prev_cur->left == cur) { //if cur is to the left of prev_cur
					if(prev_pred) { //if predecessor is not cur->left
						prev_cur->left = pred;
						prev_pred->right = pred->left;
						pred->left = cur->left;
						pred->right = cur->right;
						delete cur;
						cur = NULL;
						prev_cur = NULL;
						pred = NULL;
						prev_pred = NULL;
					}
					else { //if predecessor is cur->left
						prev_cur->left = pred;
						pred->right = cur->right;
						delete cur;
						cur = NULL;
						prev_cur = NULL;
						pred = NULL;
						prev_pred = NULL;
					}
				}
				else { //if cur is to the right of prev_cur
					if(prev_pred) { //if predecessor is not cur->left
						prev_cur->right = pred;
						prev_pred->right = pred->left;
						pred->left = cur->left;
						pred->right = cur->right;
						delete cur;
						cur = NULL;
						prev_cur = NULL;
						pred = NULL;
						prev_pred = NULL;
					}
					else { //if predecessor is cur->left
						prev_cur->right = pred;
						pred->right = cur->right;
						delete cur;
						cur = NULL;
						prev_cur = NULL;
						pred = NULL;
						prev_pred = NULL;
					}
				}

			}
			else { //if cur is root
				if(prev_pred) { //if predecessor is not cur->left
					root = pred;
					prev_pred->right = pred->left;
					pred->left = cur->left;
					pred->right = cur->right;
					delete cur;
					cur = NULL;
					prev_cur = NULL;
					pred = NULL;
					prev_pred = NULL;
				}
				else { //if predecessor is cur->left
					root = pred;
					pred->right = cur->right;
					delete cur;
					cur = NULL;
					prev_cur = NULL;
					pred = NULL;
					prev_pred = NULL;
				}
			}
		}
	}
	size--;
    return true;
}
