#include <bits/stdc++.h>

using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;
    int index = -1;
};

class BST {
    private:
        Node *root;
        int _size;

    public:
        BST() {
            root = NULL;
            _size = 0;
        }

        void insert(int value, vector<Node*>& inputs, int id) {
            Node *newNode = new Node();
            newNode->value = value;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->index = id;

            if (root == NULL) {
                root = newNode;
                inputs.push_back(newNode);
            } else {
                Node *current = root;
                Node *parent;

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

        int size() {
            return _size;
        }
};

int main() {
    BST tree;
    int nOfElements = 0;
    cin >> nOfElements;
    vector<Node*> inputs;
    for (int i = 0; i < nOfElements; i++) {
        int input;
        cin >> input;
        tree.insert(input, inputs, i+1);
    }

    for (int i = 0; i < nOfElements; i++) {
        cout << inputs[i]->value << " ";

        if(inputs[i]->left == NULL) {
            cout << "-1 ";
        } else {
            cout << inputs[i]->left->index << " ";
        }

        if(inputs[i]->right == NULL) {
            cout << "-1\n";
        } else {
            cout << inputs[i]->right->index << endl;
        }
    }
    cout << tree.size() << endl;

    return 0;
}
