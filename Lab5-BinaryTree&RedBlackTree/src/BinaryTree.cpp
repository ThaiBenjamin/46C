#include "BinaryTree.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

BinaryTree::~BinaryTree() { destroyTree(root_); }

// Shared random number generator
std::mt19937& BinaryTree::rng() {
    static std::mt19937 eng{std::random_device{}()};
    return eng;
}

// Recursively deletes all nodes in the tree
void BinaryTree::destroyTree(Node* x) {
    // TODO : Recursively delete all nodes in the tree.
    if(x != nullptr){
        destroyTree(x->left);
        destroyTree(x->right);
        delete x;
    }
    
}

// Helper: Recursively calculates the size of the tree
int BinaryTree::calculateSize(Node* x) const {
    // TODO : Return the number of nodes in the subtree rooted at x.
    if(x == nullptr){
        return 0;
    }

    else{
        return 1 + calculateSize(x->left) + calculateSize(x->right);
    }
}

// Returns the height of the tree
int BinaryTree::getHeight() const { return calculateHeight(root_); }

int BinaryTree::calculateHeight(Node* x) const {
    // TODO : Return the height of the subtree rooted at x.
    // Convention: empty tree has height -1.
    if(x == nullptr){
        return -1;
    }
    else{
        return 1 + std::max(calculateHeight(x->left),calculateHeight(x->right));
    }
}

std::string BinaryTree::visualizeTree() const {
    std::ostringstream oss;

    if (!root_) return "Tree is empty.\n";

    oss << "Tree Visualization (Level Order):\n";

    std::queue<Node*> q;
    q.push(root_);

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());

        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            if (current) {
                oss << current->item << " ";
                q.push(current->left);
                q.push(current->right);
            } else {
                oss << "null ";
            }
        }

        oss << "\n";
    }

    return oss.str();
}

int BinaryTree::deleteMax() {
    throw std::runtime_error("deleteMax() is only supported on HEAP trees");
}

int BinaryTree::peekMax() const {
    throw std::runtime_error("peekMax() is only supported on HEAP trees");
}

std::vector<int> BinaryTree::heapSort() {
    throw std::runtime_error("heapSort() is only supported on HEAP trees");
}

std::vector<int> BinaryTree::bstSort() const {
    throw std::runtime_error("bstSort() is only supported on BST trees");
}

// -------------------- BSTTree --------------------

int BSTTree::getSize() const {
    return calculateSize(root_);
}

void BSTTree::insert(int item) {
    root_ = insertBST(root_, item);
}

BinaryTree::Node* BSTTree::insertBST(Node* x, int item) {
    // TODO : Insert item into the BST rooted at x.
    // Ignore duplicates (do not insert if item already exists).
    if(x == nullptr){
        return new Node(item);
    }

    if(item < x->item){
        x->left = insertBST(x->left, item);
    }

    else if(item > x->item){
        x->right = insertBST(x->right, item);
    }

    return x;
}

BinaryTree::Node* BSTTree::findNode(int item) const {
    return findBST(root_, item);
}

BinaryTree::Node* BSTTree::findBST(Node* x, int item) const {
    // TODO : Find and return the node containing item in the BST.
    if(x == nullptr){
        return nullptr;
    }

    if(x->item == item){
        return x;
    }

    else if(item < x->item){
        return findBST(x->left, item);
    }
    else{
        return findBST(x->right, item);
    }

}

std::vector<int> BSTTree::bstSort() const {
    std::vector<int> sortedValues;
    bstSortHelper(root_, sortedValues);
    return sortedValues;
}

BSTTree BSTTree::createRandomTree(int nodes) {
    BSTTree tree;
    std::uniform_int_distribution<int> dist(0, RAND_INT_BOUND - 1);
    auto& eng = rng();
    for (int i = 0; i < nodes; ++i) tree.insert(dist(eng));
    return tree;
}

void BSTTree::analyzeRandomTreeHeights(int nodes, int trees) {
    int minHeight = RAND_INT_BOUND + 1;
    int maxHeight = 0;
    long long sum = 0;

    for (int i = 0; i < trees; ++i) {
        int height = createRandomTree(nodes).getHeight();
        minHeight = std::min(minHeight, height);
        maxHeight = std::max(maxHeight, height);
        sum += height;
    }

    int avgHeight = trees ? static_cast<int>(sum / trees) : 0;
    std::cout << trees << " " << nodes << "-node trees: "
              << "min_height=" << minHeight
              << ", max_height=" << maxHeight
              << ", avg_height=" << avgHeight << "\n";
}

std::vector<int> BSTTree::generateSortedOrder(int n) {
    std::vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) values.push_back(i);
    return values;
}

void BSTTree::generateBalancedOrder(const std::vector<int>& nodes, int start, int end, std::vector<int>& result) {
    if (start > end) return;
    int mid = start + (end - start) / 2;
    result.push_back(nodes[mid]);
    generateBalancedOrder(nodes, start, mid - 1, result);
    generateBalancedOrder(nodes, mid + 1, end, result);
}

// -------------------- HeapTree --------------------

HeapTree::HeapTree() {
    heapArray_.push_back(0); // index 0 unused
}

int HeapTree::getSize() const {
    return static_cast<int>(heapArray_.size()) - 1;
}

void HeapTree::insert(int item) {
    insertHeapArray(item);
    arrayToTree();
}

void HeapTree::insertHeapArray(int item) {
    // TODO : Insert into heapArray_ and restore heap order.
    heapArray_.push_back(item);
    swimArray(heapArray_, getSize());
}

void HeapTree::swimArray(std::vector<int>& heapArray, int index) {
    // TODO : Swim the element at index up to restore heap order.
    while(index > 1 && heapArray[index] > heapArray[index/2]){
        std::swap(heapArray[index], heapArray[index/2]);
        index = index/2;
    }
}

void HeapTree::sinkArray(std::vector<int>& heapArray, int index) {
    // TODO : Sink the element at index down to restore heap order.
    int size = static_cast<int>(heapArray.size()) - 1;

    while(2 * index <= size){
        int largerChild = 2 * index;

        if(largerChild + 1 <= size && heapArray[largerChild + 1] > heapArray[largerChild]){
            largerChild++;
        }

        if (heapArray[index] >= heapArray[largerChild]) {
            break;
        }

        std::swap(heapArray[index], heapArray[largerChild]);
        index = largerChild;
    }
}

int HeapTree::deleteMax() {
    // TODO : Remove and return the maximum element from the heap.
    // You may want to use deleteMaxArray(...) and sinkArray(...).
    if (getSize() == 0) {
        throw std::runtime_error("Heap is empty");
    }

    int maxValue = deleteMaxArray(heapArray_);
    arrayToTree();
    return maxValue;
}

int HeapTree::peekMax() const {
    if (getSize() == 0) {
        throw std::runtime_error("Heap is empty");
    }
    return heapArray_[1];
}

int HeapTree::deleteMaxArray(std::vector<int>& heapArray) {
    // TODO : Delete and return max from heapArray (1-indexed).
    int size = static_cast<int>(heapArray.size()) - 1;

    int max = heapArray[1];
    std::swap(heapArray[1], heapArray[size]);
    heapArray.pop_back();

    if(size > 1){
        sinkArray(heapArray, 1);
    }

    return max;
}

std::vector<int> HeapTree::heapSort() {
    // TODO : Return all heap elements in ascending order.
    // Requirement: do not destroy the original heap.
    std::vector<int> copy = heapArray_;
    std::vector<int> sortedArray;

    while(static_cast<int>(copy.size()) > 1){
        sortedArray.push_back(deleteMaxArray(copy));
    }

    std::reverse(sortedArray.begin(), sortedArray.end());
    return sortedArray;
}

void HeapTree::arrayToTree() {
    destroyTree(root_);
    root_ = nullptr;
    if (getSize() > 0) {
        root_ = arrayToTreeHelper(1);
    }
}

BinaryTree::Node* HeapTree::arrayToTreeHelper(int index) {
    // TODO : Build the pointer-based tree from heapArray_ (1-indexed).
    if(index > getSize()){
        return nullptr;
    }

    Node* node = new Node(heapArray_[index]);

    node->left = arrayToTreeHelper(index*2);
    node->right = arrayToTreeHelper(index*2+1);

    return node;
}

BinaryTree::Node* HeapTree::findHeap(Node* node, int item) const {
    // TODO : Find and return the node containing item in the heap tree.
    if(node == nullptr){
        return nullptr;
    }

    if(node->item == item){
        return node;
    }

    Node* findLeft = findHeap(node->left, item);
    if(findLeft != nullptr){
        return findLeft;
    }
    
    return findHeap(node->right, item);
    
}

BinaryTree::Node* HeapTree::findNode(int item) const {
    return findHeap(root_, item);
}

std::string HeapTree::visualizeTree() const {
    std::ostringstream oss;

    if (!root_) return "Tree is empty.\n";

    oss << "Tree Visualization (Level Order):\n";
    if (static_cast<int>(heapArray_.size()) > 1) {
        oss << "Heap Array: [";
        for (int i = 1; i < static_cast<int>(heapArray_.size()); i++) {
            oss << heapArray_[i];
            if (i < static_cast<int>(heapArray_.size()) - 1) oss << ", ";
        }
        oss << "]\n";
    }

    std::queue<Node*> q;
    q.push(root_);

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());

        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            if (current) {
                oss << current->item << " ";
                q.push(current->left);
                q.push(current->right);
            } else {
                oss << "null ";
            }
        }

        oss << "\n";
    }

    return oss.str();
}

// Helper: Recursively traverse BST to get sorted values
void BinaryTree::bstSortHelper(Node* node, std::vector<int>& sortedValues) const {
    // TODO : In-order traversal to append values in sorted order.
    if(node == nullptr){
        return;
    }
    bstSortHelper(node->left, sortedValues);   
    sortedValues.push_back(node->item);        
    bstSortHelper(node->right, sortedValues); 
}
