#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::Node Node;
typedef BinarySearchTree::DataType DataType;

BinarySearchTree::Node::Node(DataType newval) {
     left = nullptr;
     right = nullptr;
     val = newval;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    //will never be called on empty tree though
    if (n == nullptr){
        return -1;
    }
    if(size() ==1){
        return 0;
    }
    int leftdepth = getNodeDepth(n->left) + 1;
    int rightdepth = getNodeDepth(n->right) + 1;

    if(leftdepth > rightdepth){
        return leftdepth;
    } else return rightdepth;
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
   std::queue<Node*> queue;

   if (root_ != nullptr){
       queue.push(root_);
   }

   while (!queue.empty()){
       Node* current = queue.front();
       queue.pop();

       if (current->left != nullptr){
           queue.push(current->left);
       }
       if (current->right != nullptr){
           queue.push(current->right);
       }
       delete current;

   }
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node *temp = root_;
    while(temp->right != nullptr){
        temp = temp->right;
    }
    return temp->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node *temp = root_;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp->val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const {
    std::queue<Node*> queue;

    if (root_ != nullptr){
        queue.push(root_);
    }

    while(!queue.empty()){
        Node *temp = queue.front();
        queue.pop();
        std::cout << temp->val << " ";

        if (temp->left != nullptr){
            queue.push(temp->left);
        }
        if (temp->right != nullptr){
            queue.push(temp->right);
        }
    }
}

bool BinarySearchTree::exists(DataType val) const {
    Node *temp = root_;
    while (temp != nullptr){
        if (temp->val == val){
            return true;
        } else if (temp->val > val){
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {

    if (root_ == nullptr){
        root_ = new Node(val);
        size_++;
        return true;
    }
    Node *newnode = new Node(val);
    Node *temp;
    Node *current = root_;

    while (current != nullptr){
        if (current->val == val){
            return false;
        } else if (current->val > val){
            temp = current;
            current = current->left;
        } else{
            temp = current;
            current = current->right;
        }
    }

    if (temp->val > val){
        temp->left = newnode;
    } else temp->right = newnode;

    size_++;
    return true;
}


bool BinarySearchTree::remove(DataType val) {

    if (root_ == nullptr){
        return false;
    }

    Node *current = root_;
    Node *parent = root_;
    bool isleftchild = false;
    bool found = false;

    while (current != nullptr){
        if (current->val == val){
            found = true;
            break;
        } else if (val < current->val){
            parent = current;
            current = current->left;
            isleftchild = true;
        }
        else {
            parent = current;
            current = current->right;
            isleftchild = false;
        }
    }

    if (found == false){
        return false;
    }


    if (current->right != nullptr && current->left != nullptr){

        Node* pred = current->left;
        Node* predparent = current;
        while (pred->right != nullptr) {
            predparent = pred;
            pred = pred->right;
        }

        current->val = pred->val;

        if (predparent == current) {
            predparent->left = pred->left;
        } else {
            predparent->right = pred->left;
        }
        delete pred;
        size_--;
    } else {

        Node* child;
        if (current->left != nullptr) {
            child = current->left;
        }
        else {
            child = current->right;
        }

        if (current == root_) {
            root_ = child;
        } else if (isleftchild) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        if (current == root_) {
            delete root_;
            root_ = nullptr;
        }

        delete current;
        size_--;
    }
    return true;
}
