#ifndef BinaryTree__HPP
#define BinaryTree__HPP

#include <random>
#include <string>
#include <sstream>
#include <queue>
#include <iostream>
#include <vector>

class BinaryTree {
public:
    static constexpr int RAND_INT_BOUND = 300; // Upper bound for random integers

    BinaryTree() = default;
    virtual ~BinaryTree();

    virtual std::string typeName() const = 0;

    // Tree operations on the whole tree
    virtual int getSize() const = 0;
    int getHeight() const;
    virtual void insert(int item) = 0;
    virtual std::string visualizeTree() const;

    class Node {
    public:
        int item;
        Node* left;
        Node* right;

        explicit Node(int v) : item(v), left(nullptr), right(nullptr) {}
        std::string toString() const { return std::to_string(item); }
    };

    virtual Node* findNode(int item) const = 0;

    // Optional operations; subclasses override what they support.
    virtual int deleteMax();
    virtual int peekMax() const;
    virtual std::vector<int> heapSort();

    virtual std::vector<int> bstSort() const;

protected:
    Node* root_ { nullptr };

    static std::mt19937& rng();

    int calculateSize(Node* x) const; 
    int calculateHeight(Node* x) const; 
    void destroyTree(Node* x); 

    void bstSortHelper(Node* node, std::vector<int>& sortedValues) const;
};

class BSTTree final : public BinaryTree {
public:
    BSTTree() = default;
    ~BSTTree() override = default;

    std::string typeName() const override { return "BST"; }

    int getSize() const override;
    void insert(int item) override;
    Node* findNode(int item) const override;

    std::vector<int> bstSort() const override;

    static BSTTree createRandomTree(int nodes);
    static void analyzeRandomTreeHeights(int nodes, int trees);
    static std::vector<int> generateSortedOrder(int n);
    static void generateBalancedOrder(const std::vector<int>& nodes, int start, int end, std::vector<int>& result);

private:
    Node* insertBST(Node* x, int item);
    Node* findBST(Node* x, int item) const;
};

class HeapTree final : public BinaryTree {
public:
    HeapTree();
    ~HeapTree() override = default;

    std::string typeName() const override { return "HEAP"; }

    int getSize() const override;
    void insert(int item) override;
    Node* findNode(int item) const override;
    std::string visualizeTree() const override;

    int deleteMax() override;
    int peekMax() const override;
    std::vector<int> heapSort() override;

private:
    // Array representation for heap (1-indexed, position 0 unused)
    std::vector<int> heapArray_;

    void insertHeapArray(int item);
    int deleteMaxArray(std::vector<int>& heapArray);
    void swimArray(std::vector<int>& heapArray, int index);
    void sinkArray(std::vector<int>& heapArray, int index);

    void arrayToTree();
    Node* arrayToTreeHelper(int index);
    Node* findHeap(Node* x, int item) const;
};

#endif // BinaryTree__HPP