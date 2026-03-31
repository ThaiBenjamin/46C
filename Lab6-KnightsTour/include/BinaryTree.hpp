#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <algorithm>

template <typename T>
class BinaryTree {
public:
    enum class TreeType { BST, LLRB };

    // Constructs the tree with desired balancing strategy.
    explicit BinaryTree(TreeType type = TreeType::BST);

    // Destructor to clean up memory.
    ~BinaryTree();

    // Inserts an item into the tree.
    void insert(const T& item);
    // Returns the height of the tree.
    int getHeight() const;
    // Finds and returns a pointer to the item with minimum key in the tree.
    const T* findMin() const;

private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        bool red;
        explicit Node(const T& v, bool isRed = true)
            : value(v), left(nullptr), right(nullptr), red(isRed) {}
    };

    Node* root_;
    TreeType treeType_;

    void destroy(Node* node);
    int height(Node* node) const;
    // Plain BST insertion.
    Node* insertBST(Node* node, const T& item);
    // Left-leaning red-black insertion.
    Node* insertLLRB(Node* node, const T& item);

    bool isRed(Node* node) const;
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    void flipColors(Node* node);
    Node* findMinNode(Node* node) const;
};

#include "BinaryTree.tpp"

#endif // BINARYTREE_HPP