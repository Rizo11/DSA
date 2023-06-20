#include <bits/stdc++.h>

using namespace std;

enum point_t {
    start_t,
    end_t,
    cross_t
};

class Point {
public:
    double x;
    double y;
    point_t p_type;
    Point(int x, int y, point_t type) : x(x), y(y), p_type(type) {}

    Point() {}

    bool operator > (Point const& pt)
    {
        if (this->y > pt.y) {
            return true;
        } else if (this->y == pt.y && this->x > pt.x) {
            return true;
        } else {
            return false;
        }
    }

    bool operator < (Point const& pt) const
    {
        if (this->y < pt.y) {
            return true;
        } else if (this->y == pt.y && this->x < pt.x) {
            return true;
        } else {
            return false;
        }
    }

    bool operator == (Point const& pt)
    {
        if (this->y == pt.y && this->x == pt.x) {
            return true;
        } else {
            return false;
        }
    }

    friend ostream& operator<<(ostream& os, const Point& sg);
};

ostream& operator<<(ostream& os, const Point& pt)
{
    os << pt.x << " " << pt.y << " " << '/';

    return os;
}

class Segment {
public:
    Point start_p;
    Point end_p;
    Segment(Point start_, Point end_) : start_p(start_), end_p(end_) {}

    Segment() {}

    double getKey() {
        double dy = this->end_p.y - this->start_p.y;
        double dx = this->end_p.x - this->start_p.x;
        return (dy)/(dx);
    }

    friend ostream& operator<<(ostream& os, const Segment& sg);
};

ostream& operator<<(ostream& os, const Segment& sg)
{
    os << sg.start_p.x << " " << sg.start_p.y << " " << '/';
    os << sg.end_p.x << " " << sg.end_p.y << " " << '/';

    return os;
}

// Node Declaration
template < typename T>
class AVL_Node {
public:
    T data;
    AVL_Node *left;
    AVL_Node *right;
    int height;

    AVL_Node(T data_) : data(data_) {}
    AVL_Node() {}
};

template < typename T>
class AVLTree {
public:
    AVL_Node<T> *root;

    AVLTree() {
        root = NULL;
    }

    int height(AVL_Node<T> *node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }

    int getBalance(AVL_Node<T> *node) {
        if (node == NULL) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    AVL_Node<T> *rightRotate(AVL_Node<T> *y) {
        AVL_Node<T> *x = y->left;
        AVL_Node<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVL_Node<T> *leftRotate(AVL_Node<T> *x) {
        AVL_Node<T> *y = x->right;
        AVL_Node<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVL_Node<T> * insert(AVL_Node<T> *node, T data) {
        if (node == NULL) {
            return new AVL_Node<T>(data);
        }

        if (data > node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data) {
            return rightRotate(node);
        }

        if (balance < -1 && data > node->right->data) {
            return leftRotate(node);
        }

        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVL_Node<T> *minValueNode(AVL_Node<T> *node) {
        AVL_Node<T> *current = node;

        while (current->left != NULL) {
            current = current->left;
        }

        return current;
    }

    AVL_Node<T> *deleteNode(AVL_Node<T> *root, T data) {
        // Base case: empty tree
        if (root == nullptr) {
            return root;
        }

        // If the key to be deleted is smaller than the root's key,
        // then it lies in the left subtree
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        }
            // If the key to be deleted is greater than the root's key,
            // then it lies in the right subtree
        else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        }
            // If key is same as root's key, then this node must be deleted
        else {
            // Node with only one child or no child
            if (root->left == nullptr || root->right == nullptr) {
                AVL_Node<T>* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else { // One child case
                    *root = *temp; // Copy the contents of the non-empty child
                }
                delete temp;
            }
            else { // Node with two children: get the inorder successor (smallest in the right subtree)
                AVL_Node<T>* temp = findMin(root->right);

                // Copy the inorder successor's data to this node
                root->data = temp->data;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->data);
            }
        }

        // If the tree had only one node, then return
        if (root == nullptr) {
            return root;
        }

        // Update the height of the current node
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        // Check if this node became unbalanced
        int balance = getBalance(root);

        // Left Left case
        if (balance > 1 && getBalance(root->left) >= 0) {
            return rotateRight(root);
        }

        // Left Right case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right case
        if (balance < -1 && getBalance(root->right) <= 0) {
            return rotateLeft(root);
        }

        // Right Left case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void display(AVL_Node<T>  *root, int level)
    {
        /*if (root != NULL) {
            if (root->right != nullptr) {
                display(root->right, indent + 4);
            }
            if (indent > 0) {
                std::cout << std::setw(indent) << " ";
            }
            if (root->right != nullptr) {
                std::cout << " /\n" << std::setw(indent) << " ";
            }
            std::cout << root->satellite_data << "\n ";
            if (root->left != nullptr) {
                std::cout << std::setw(indent) << " " << " \\\n";
                display(root->left, indent + 4);
            }
        }*/
        int i;
        if (root != NULL) {
            display(root->right, level + 1);
            printf("\n");
            if (root == root)
                cout << "Root -> ";
            for (i = 0; i < level && root != root; i++) {

                cout << "        ";
            }
            int j;

            cout << root->data;
            display(root->left, level + 1);
        }
    }
};

bool contains(vector<Point> alphabet, Point word) {
    if (std::find(alphabet.begin(), alphabet.end(), word) == alphabet.end())
    {
        return false;
    }

    return true;
}


template <typename T>
class PriorityQueue {
private:
    vector<T> heap;

    void heapify_up(int i) {
        int parent = (i - 1) / 2;
        if (i > 0 && heap[i] < heap[parent]) {
            swap(heap[i], heap[parent]);
            heapify_up(parent);
        }
    }

    void heapify_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify_down(smallest);
        }
    }

public:
    void insert(T key) {
        heap.push_back(key);
        heapify_up(heap.size() - 1);
    }

    int findMin() {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty.");
        }
        return heap[0];
    }

    void deleteMin() {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty.");
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
    }

    bool isEmpty() {
        return heap.empty();
    }

    int getNext() {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty.");
        }
        int next = heap[0];
        deleteMin();
        return next;
    }
};

int main() {
    vector<Segment> segments = vector<Segment>();
    AVLTree<Point> tree = AVLTree<Point>();
    AVL_Node<Point> *root = NULL;
    int n = 0;
    cin >> n;
    for ( int i = 0; i < n; i++) {
        int x, y, x2, y2;
        cin >> x >> y >> x2 >> y2;
        Point start_p = Point(x, y, start_t);
        Point end_p = Point(x2, y2, end_t);
        Segment s = Segment(start_p, end_p);
        segments.push_back(s);
    }
    set<Segment> intersections = set<Segment> ();
    AVLTree<Point> pointQueue;
    AVL_Node<Point>* pqRoot = NULL;
    vector<Point> pointQueue2 = vector<Point>();

    AVLTree<Segment> statusQueue;
    AVL_Node<Segment>* sqRoot = NULL;

    // insert sentinels
    Segment sg = Segment(Point(-3000000, 3000000, start_t), Point(-3000000, -3000000, end_t));
    sqRoot = statusQueue.insert(sqRoot, sg);

    sg = Segment(Point(3000000, 3000000, start_t), Point(3000000, -3000000, end_t));
    sqRoot = statusQueue.insert(sqRoot, sg);

    for (auto sg : segments) {
        if (!contains(pointQueue2, sg.start_p)) {
            pointQueue2.push_back(sg.start_p);
            pqRoot = pointQueue.insert(pqRoot, sg.start_p);
        }
        if (!contains(pointQueue2, sg.end_p)) {
            pointQueue2.push_back(sg.end_p);
            pqRoot = pointQueue.insert(pqRoot, sg.end_p);
        }
        set<Point> LowerP = set<Point>();
        set<Point> UpperP = set<Point>();
        set<Point> Cross = set<Point>();
        LowerP.insert(sg.end_p);
        UpperP.insert(sg.start_p);
    }

    while (pqRoot != NULL) {

    }

    return 0;
}
