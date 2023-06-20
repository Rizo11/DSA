// Mukhammadrizo Maribjonov DS-AI 4


#include <bits/stdc++.h>

using namespace std;

/* BST node */
struct Node {
    int value;

    // left node
    Node *left;

    // right node
    Node *right;
    int index = -1;
};

/* BST implementation with insert functionality */
class BST {
    private:
        Node *root;
        int _size;

    public:
        BST() {
            root = NULL;
            _size = 0;
        }


        /* inserts given value to the BTS tree */
        void insert(int value, vector<Node*>& inputs, int id) {
            Node *newNode = new Node();
            newNode->value = value;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->index = id;

            // if tree is empty
            if (root == NULL) {
                root = newNode;
                inputs.push_back(newNode);
            } else {

                Node *current = root;
                Node *parent;

                // loop till finding a place to insert
                while (true) {
                    parent = current;

                    if (value < current->value) {
                        current = current->left;

                        if (current == NULL) {
                            parent->left = newNode;
                            inputs.push_back(newNode);
                            break;
                        }
                    } else {
                        current = current->right;

                        if (current == NULL) {
                            parent->right = newNode;
                            inputs.push_back(newNode);
                            break;
                        }
                    }
                }
            }

            _size++;
        }

        /* returns the number of nodes in the tree */
        int size() {
            return _size;
        }
};

int main() {
    BST tree;
    int nOfElements = 0;
    cin >> nOfElements;
    vector<Node*> inputs;

    /* reading input from console */
    for (int i = 0; i < nOfElements; i++) {
        int input;
        cin >> input;
        tree.insert(input, inputs, i+1);
    }

    // print the number of the nodes
    cout << tree.size() << endl;
    for (int i = 0; i < nOfElements; i++) {

        // print the value of the node
        cout << inputs[i]->value << " ";


        // print the index of the left node
        if(inputs[i]->left == NULL) {
            cout << "-1 ";
        } else {
            cout << inputs[i]->left->index << " ";
        }


        // print the index of the right node
        if(inputs[i]->right == NULL) {
            cout << "-1\n";
        } else {
            cout << inputs[i]->right->index << endl;
        }
    }

    // print the index of the root
    cout << inputs[0]->index << endl;

    return 0;
}
