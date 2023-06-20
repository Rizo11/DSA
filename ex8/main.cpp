#include <iostream>
#include <bits/stdc++.h>

using namespace std;


class Node {
public:
    int value = 0;
    int index = -1;
    Node *left;
    Node *right;
    Node *parent;

    Node(int input, int id) : value(input), index(id) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    Node() {}
};
    Node* Insert(Node * node, int key, int id) {
        // If BST doesn't exist
        // create a new node as root
        // or it's reached when
        // there's no any child node
        // so we can insert a new node here
        if (node == NULL) {
            node = new Node();
            node->value = key;
            node->left = NULL;
            node->right = NULL;
            node->parent = NULL;
            node->index = id;
        }
            // If the given key is greater than
            // node's key then go to right subtree
        else if (node->value < key) {
            node->right = Insert(node->right, key, id);
            node->right->parent = node;
        }
            // If the given key is smaller than
            // node's key then go to left subtree
        else if (node->value > key){
            node->left = Insert(node->left, key, id);
            node->left->parent = node;
        } else {
            return node;
        }
    }
};

/*
class binTree {
public:
    Node* Root;
    int size = 0;
    binTree() {
        Root = nullptr;
    }

    Node* insert(int value, int id) {
        Node* root = Root;
        if (root == nullptr) {
            Node* newNode = new Node(value, id);
            root = newNode;
            size++;
            return root;
        } else {
            while(root != nullptr) {
                if (root->value > value) {
                    if (root->left == nullptr) {
                        root->left = new Node(value, id);
                        root->parent = root;
                        size++;
                        return root->left;
                    }
                    root = root->left;
                } else if (root->value < value){
                    if (root->right == nullptr) {
                        root->right = new Node(value, id);
                        root->parent = root;
                        size++;
                        return root->right;
                    }
                    root = root->right;
                } else if (root->value == value) {
                    return root;
                }
            }
        }
    }



    */
/* returns successor of node, c in example of a,c *//*

    Node* successor(Node* root) {
        if (root->right != nullptr) {
            return subtreeFirst(root->right);
        } else {
            while (root != root->parent->left) {
                root = root->parent;
            }

            return root;
        }
    }

    */
/* returns min of given subtree *//*

    Node* subtreeFirst(Node* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }
};
*/


int main() {
    int numberOfLine = 0;
    cin >> numberOfLine;
    Node* bts = nullptr;
    vector<Node*> inputs;
    for (int i = 0; i < numberOfLine; ++i) {
        int input = 0;
        cin >> input;
        inputs.push_back(Insert(bts, input, i+1));
    }

    cout << bst.size << endl;
    for (Node* n : inputs) {
        cout << n->value << " " << n->left->index << " " << n->right->index << endl;
    }
    cout << inputs[0]->index << endl;

    return 0;
}
