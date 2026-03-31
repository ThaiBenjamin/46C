#pragma once

template <typename T>
BinaryTree<T>::BinaryTree(TreeType type) : root_(nullptr), treeType_(type) {}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    destroy(root_);
}

template <typename T>
void BinaryTree<T>::destroy(Node* node) {
    if (!node) {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <typename T>
void BinaryTree<T>::insert(const T& item) {
    // TODO: implement insert of item for both BST and LLRB
    if(treeType_ == TreeType::BST){
        root_ = insertBST(root_, item);
    }
    else{
        root_ = insertLLRB(root_, item);
        
    }
    if(root_){
        root_->red = false;
    }
}

template <typename T>
int BinaryTree<T>::getHeight() const {
    return height(root_);
}

template <typename T>
const T* BinaryTree<T>::findMin() const {
    // TODO: implement findMin to find and return value associated with
    // minimum key for both BST and LLRB
    Node* minNode = findMinNode(root_);
    if(minNode == nullptr){
        return nullptr;
    }
    return &(minNode->value);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findMinNode(Node* node) const {
    // TODO: implement findMinNode helper to find and return pointer to node with
    // minimum key for both BST and LLRB
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template <typename T>
int BinaryTree<T>::height(Node* node) const {
    if (!node) {
        return 0;
    }
    const int left = height(node->left);
    const int right = height(node->right);
    return 1 + std::max(left, right);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::insertBST(Node* node, const T& item) {
    if (!node) {
        return new Node(item, false);
    }
    if (item < node->value) {
        node->left = insertBST(node->left, item);
    } else if (node->value < item) {
        node->right = insertBST(node->right, item);
    } else {
        node->value = item;
    }
    return node;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::insertLLRB(Node* node, const T& item) {
    // TODO: implement insert of item for LLRB while maintaining LLRB properties
    if(!node) {
        return new Node(item, true);
    }

    if(item < node->value){
        node->left = insertLLRB(node->left, item);
    }
    else if(item > node->value){
        node->right = insertLLRB(node->right, item);
    }
    else{
        node->value = item;
    }
    if(isRed(node->right) && !isRed(node->left)){
        node = rotateLeft(node);
    }
    if (isRed(node->left) && isRed(node->left->left)) {
        node = rotateRight(node);
    }
    if(isRed(node->left) && isRed(node->right)){
        flipColors(node);
    }

    return node;
}

template <typename T>
bool BinaryTree<T>::isRed(Node* node) const {
    // TODO: implement isRed to check if a node is red (for LLRB)
    if (!node){
        return false;
    }
    return node->red;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::rotateLeft(Node* node) {
    // TODO: implement rotateLeft to maintain LLRB properties
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->red = node->red;
    node->red = true;
    
    return temp;

}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::rotateRight(Node* node) {
    // TODO: implement rotateRight to maintain LLRB properties
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->red = node->red;
    node->red = true;

    return temp;
}

template <typename T>
void BinaryTree<T>::flipColors(Node* node) {
    // TODO: implement flipColors to maintain LLRB properties
    node->red = !node->red;
    node->left->red = !node->left->red;
    node->right->red = !node->right->red;
}

