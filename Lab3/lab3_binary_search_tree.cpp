#include <iostream>
#include <queue>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

void BinarySearchTree::clean_up(BinarySearchTree::TaskItem* n ) {
    if (n == NULL) return;
    clean_up(n->left);
    clean_up(n->right);
    delete n;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	clean_up(root);
	root = NULL;
	size = 0;
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
        return 0;

    int height = 0;
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

// PURPOSE: Helper function for print
void BinarySearchTree::print(BinarySearchTree::TaskItem* T) const {
	if (T == NULL) return;
	print(T->left);
	cout << T->priority << " ";
	print(T->right);
} // NEW

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	print(root);
	cout << endl;
}

// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
    TaskItem* cur = root;

    while(cur){
        if(*cur == val)
            return true;
        if(cur->priority < val.priority)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	if(exists(*n))
		return -1;

	TaskItem* cur = root;
	int count = 0;

	while(cur){
		if(cur == n)
			cur = NULL;
		if(cur->priority < n->priority)
			cur = cur->left;
		else
			cur = cur->right;
		count++;
	}
	return count;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    TaskItem** cur = &root;
    while(*cur){
        if (val.priority == (*cur)->priority)
            return false;
        if (val.priority > (*cur)->priority)
            cur = &((*cur)->right);
        else
            cur = &((*cur)->left);
    }
    *cur = new TaskItem(val);
    size++;
    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
    if (!root)
        return false;
    TaskItem** cur = &root;
    TaskItem** parent;
    bool right;
    while(val.priority != (*cur)->priority){
        if (val.priority > (*cur)->priority){
            if ((*cur)->right){
                parent = cur;
                cur = &((*cur)->right);
                right = true;
            }
            else
                return false;
        }
        else if (val.priority < (*cur)->priority){
            if ((*cur)->left){
                parent = cur;
                cur = &((*cur)->left);
                right = false;
            }
            else
                return false;
        }
    }
    cout << "right: " << right << endl;
    cout << (*cur)->priority << " " << (*parent)->priority << endl;
    if (!((*cur)->left) && !((*cur)->right)){
        delete *cur;
        *cur = NULL;
    }
    else if ((*cur)->left && !((*cur)->right)){
        if (right)
            (*parent)->right = (*cur)->left;
        else
            (*parent)->left = (*cur)->left;
    }
    else if (!((*cur)->left) && (*cur)->right){
        if (right)
            (*parent)->right = (*cur)->right;
        else
            (*parent)->left = (*cur)->right;
    }
    else{
        TaskItem** temp = &((*cur)->right);
        TaskItem** temp_parent;
        while((*temp)->left){
            temp_parent = temp;
            temp = &((*temp)->left);
        }
        if (right)
            (*parent)->right = *temp;
        else
            (*parent)->left = *temp;
        (*temp)->left = (*cur)->left;
        (*temp)->right = (*cur)->right;
        (*temp_parent)->left = nullptr;
        delete *cur;
        *cur = NULL;
    }
    size--;
    return true;
}
