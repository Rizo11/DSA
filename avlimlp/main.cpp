#include <bits/stdc++.h>

using namespace std;


enum point_t {
    start_t,
    end_t,
    cross_t
};
class Point {
public:
    long long x;
    long long y;
    Point(double x_, double y_, point_t pType, int index) : x(x_), y(y_), p_type(pType), index(index) {}
    point_t p_type;
    int index;
    Point() {
        this->index = -1;
    }

    bool operator > (Point const& pt)
    {
        if (this->x > pt.x) {
            return true;
        } else if (this->x == pt.x && this->y > pt.y) {
            return true;
        } else {
            return false;
        }
    }

    bool operator < (Point const& pt) const
    {
        if (this->x < pt.x) {
            return true;
        } else if (this->x == pt.x && this->y < pt.y) {
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
struct Event {
    Point p;
    Event(int x, int y, point_t t, int i) : p(x, y, t, i) {}
    Event() {
        p = Point(0, 0, cross_t, -1);
    }
    Event(Point p_) {
        p = p_;
    }
    // This is for maintaining the order in set.
    bool operator < (const Event& e) const {
        if(p.y == e.p.y) return  p.x < e.p.x;
        return p.y < e.p.y;
    }

    bool operator > (const Event& e) const {
        if(p.y == e.p.y) return  p.x > e.p.x;
        return p.y > e.p.y;
    }

    bool operator == (const Event& e) const {
        return (p.y == e.p.y && p.x == e.p.x);
    }
};
ostream& operator<<(ostream& os, const Point& pt)
{
    os << pt.x << " " << pt.y;

    return os;
}

long double y_intercept(const Point &a, const Point &b);

long double slope(const Point &a, const Point &b);

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
    bool operator > (Segment const& pt)
    {
        long double mi1 = slope(this->start_p, this->end_p);
        long double b1 = y_intercept(this->start_p, this->end_p);
        long double mi2 = slope(pt.start_p, pt.end_p);
        long double b2 = y_intercept(pt.start_p, pt.end_p);
        long double this_y = mi1*pt.start_p.x + b1;
        if (this_y > pt.start_p.y) {
            return true;
        }
        return false;
    }

    bool operator < (Segment const& pt)
    {
        long double mi1 = slope(this->start_p, this->end_p);
        long double b1 = y_intercept(this->start_p, this->end_p);
        long double mi2 = slope(pt.start_p, pt.end_p);
        long double b2 = y_intercept(pt.start_p, pt.end_p);
        long double this_y = mi1*pt.start_p.x + b1;
        if (this_y < pt.start_p.y) {
            return true;
        }
        return false;
    }

    bool operator == (Segment const& pt)
    {
        long double mi1 = slope(this->start_p, this->end_p);
        long double b1 = y_intercept(this->start_p, this->end_p);
        long double mi2 = slope(pt.start_p, pt.end_p);
        long double b2 = y_intercept(pt.start_p, pt.end_p);
        long double this_y = mi1*pt.start_p.x + b1;
        if (this_y == pt.start_p.y) {
            return true;
        }

        return false;
    }

    friend ostream& operator<<(ostream& os, const Segment& sg);
};

ostream& operator<<(ostream& os, const Segment& sg)
{
    os << sg.start_p << " " << sg.end_p;

    return os;
}

template <typename T>
class PriorityQueue {
public:
    std::vector<T> heap;

    void heapifyUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (heap[i] < heap[p]) {
                std::swap(heap[i], heap[p]);
                i = p;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int i) {
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
            std::swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void insert(const T& val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    const T& findmin() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap.front();
    }

    void deletemin() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        heap.front() = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    bool isEmpty() {
        return heap.empty();
    }
};


template <typename T>
// data structure that represents a node in the tree
struct Node {
    T data; // holds the key
    Node *parent; // pointer to the parent
    Node *left; // pointer to left child
    Node *right; // pointer to right child
    int bf; // balance factor of the node
};

template <typename T>
typedef Node<T> *NodePtr;

template <typename T>
// class AVLTree implements the operations in AVL tree
class AVLTree {
private:
    NodePtr root;

    // initializes the nodes with appropirate values
    // all the pointers are set to point to the null pointer
    void initializeNode(NodePtr node, int key) {
        node->data = key;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->bf = 0;
    }

    void preOrderHelper(NodePtr node) {
        if (node != nullptr) {
            cout<<node->data<<" ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(NodePtr node) {
        if (node != nullptr) {
            inOrderHelper(node->left);
            cout<<node->data<<" ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(NodePtr node) {
        if (node != nullptr) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout<<node->data<<" ";
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == nullptr || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    NodePtr deleteNodeHelper(NodePtr node, int key) {
        // search the key
        if (node == nullptr) return node;
        else if (key < node->data) node->left = deleteNodeHelper(node->left, key);
        else if (key > node->data) node->right = deleteNodeHelper(node->right, key);
        else {
            // the key has been found, now delete it

            // case 1: node is a leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }

                // case 2: node has only one child
            else if (node->left == nullptr) {
                NodePtr temp = node;
                node = node->right;
                delete temp;
            }

            else if (node->right == nullptr) {
                NodePtr temp = node;
                node = node->left;
                delete temp;
            }

                // case 3: has both children
            else {
                NodePtr temp = minimum(node->right);
                node->data = temp->data;
                node->right = deleteNodeHelper(node->right, temp->data);
            }

        }

        // Write the update balance logic here
        // YOUR CODE HERE

        return node;
    }




    // update the balance factor the node
    void updateBalance(NodePtr node) {
        if (node->bf < -1 || node->bf > 1) {
            rebalance(node);
            return;
        }

        if (node->parent != nullptr) {
            if (node == node->parent->left) {
                node->parent->bf -= 1;
            }

            if (node == node->parent->right) {
                node->parent->bf += 1;
            }

            if (node->parent->bf != 0) {
                updateBalance(node->parent);
            }
        }
    }

    // rebalance the tree
    void rebalance(NodePtr node) {
        if (node->bf > 0) {
            if (node->right->bf < 0) {
                rightRotate(node->right);
                leftRotate(node);
            } else {
                leftRotate(node);
            }
        } else if (node->bf < 0) {
            if (node->left->bf > 0) {
                leftRotate(node->left);
                rightRotate(node);
            } else {
                rightRotate(node);
            }
        }
    }

    void printHelper(NodePtr root, string indent, bool last) {
        // print the tree structure on the screen
        if (root != nullptr) {
            cout<<indent;
            if (last) {
                cout<<"R----";
                indent += "     ";
            } else {
                cout<<"L----";
                indent += "|    ";
            }

            cout<<root->data<<"( BF = "<<root->bf<<")"<<endl;

            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    AVLTree() {
        root = nullptr;
    }

    // Pre-Order traversal
    // Node->Left Subtree->Right Subtree
    void preorder() {
        preOrderHelper(this->root);
    }

    // In-Order traversal
    // Left Subtree -> Node -> Right Subtree
    void inorder() {
        inOrderHelper(this->root);
    }

    // Post-Order traversal
    // Left Subtree -> Right Subtree -> Node
    void postorder() {
        postOrderHelper(this->root);
    }

    // search the tree for the key k
    // and return the corresponding node
    NodePtr searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }

    // find the node with the minimum key
    NodePtr minimum(NodePtr node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // find the node with the maximum key
    NodePtr maximum(NodePtr node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // find the successor of a given node
    NodePtr successor(NodePtr x) {
        // if the right subtree is not null,
        // the successor is the leftmost node in the
        // right subtree
        if (x->right != nullptr) {
            return minimum(x->right);
        }

        // else it is the lowest ancestor of x whose
        // left child is also an ancestor of x.
        NodePtr y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    // find the predecessor of a given node
    NodePtr predecessor(NodePtr x) {
        // if the left subtree is not null,
        // the predecessor is the rightmost node in the
        // left subtree
        if (x->left != nullptr) {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != nullptr && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    // rotate left at node x
    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;

        // update the balance factor
        x->bf = x->bf - 1 - max(0, y->bf);
        y->bf = y->bf - 1 + min(0, x->bf);
    }

    // rotate right at node x
    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;

        // update the balance factor
        x->bf = x->bf + 1 - min(0, y->bf);
        y->bf = y->bf + 1 + max(0, x->bf);
    }

    // insert the key to the tree in its appropriate position
    void insert(int key) {
        // PART 1: Ordinary BST insert
        NodePtr node = new Node;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->data = key;
        node->bf = 0;
        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != nullptr) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        // y is parent of x
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        // PART 2: re-balance the node if necessary
        updateBalance(node);

    }

    NodePtr getRoot(){
        return this->root;
    }

    // delete the node from the tree
    NodePtr deleteNode(int data) {
        NodePtr deletedNode =  deleteNodeHelper(this->root, data);
        return deletedNode;
    }

    // print the tree structure on the screen
    void prettyPrint() {
        printHelper(this->root, "", true);
    }

};

bool operator<(const Segment &a, const Segment &b) {
    return a.start_p < b.end_p;
}

long double slope(const Point &a, const Point &b) {
    return (long double) ((b.y - a.y) / (long double)(b.x - a.x));
}

long double y_intercept(const Point &a, const Point &b) {
    return (long double) ((long double)(a.y) - (slope(a, b) * (long double)(a.x)));
}


int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}
// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;

    return false;
}

bool CheckForIntersection(PriorityQueue<Point>, Segment s, Segment successor_of_s) {
    Point p1 = s.start_p, q1 = s.end_p, p2 = successor_of_s.start_p, q2 = successor_of_s.end_p;

    if (p1 == p2 || p1 == p2 || q1 == p2 || q1 == q2) {
        return true;
    }
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}


/*class Event {
public:
    int x, y;
    point_t type;
    int index;
    Event(int x, int y, point_t l, int i) : x(x), y(y), type(l), index(i) {}

    // This is for maintaining the order in set.
    bool operator<(const Event& e) const {
        if(y==e.y)return x<e.x;
        return y < e.y;
    }
};*/
int main() {
    int n = 0;
    cin >> n;
    /*AVLTree<int> tr = AVLTree<int>();
    for(int i = 0; i < n; i++) {
        tr.Insert(i);
    }
    int a = tr.FindPredecessor(4);
    a = tr.FindPredecessor(0);
    a = tr.FindPredecessor(2);
    a = tr.FindSuccessor(0);
    a = tr.FindSuccessor(2);
    a = tr.FindSuccessor(4);*/

    PriorityQueue<Point> eventQueue;
    vector<Segment> segments = vector<Segment>();
    for ( int i = 0; i < n; i++) {
        int x, y, x2, y2;
        cin >> x >> y >> x2 >> y2;
        Point start_p = Point(x, y, start_t, i);
        Point end_p = Point(x2, y2, end_t, i);
        Segment s = Segment(start_p, end_p);
        segments.push_back(s);

        if (start_p > end_p) {
            Point tmp = start_p;
            start_p = end_p;
            start_p.p_type = start_t;
            end_p = tmp;
            end_p.p_type = end_t;
        }
        eventQueue.insert(start_p);
        eventQueue.insert(end_p);

    }

    AVLTree<Event> sweepingLine;
    Segment s1;
    Segment s2;
    bool isIntersect = false;

//    sort(eventQueue.heap.begin(), eventQueue.heap.end(), [](Point &e1, Point &e2) {return e1.x < e2.x;});

    while (!eventQueue.isEmpty()) {

        Event event = Event(eventQueue.findmin());
        eventQueue.deletemin();

        if (event.p.p_type == start_t) {

            sweepingLine.Insert(event);
            int suc_ind = sweepingLine.FindSuccessor(event).p.index;
            int pred_ind = sweepingLine.FindPredecessor(event).p.index;

            if (suc_ind != -1) {
                isIntersect = CheckForIntersection(eventQueue, segments[suc_ind], segments[event.p.index]);
            }
            if (isIntersect) {
                cout << "INTERSECTION" << endl;
                cout << segments[suc_ind] << endl;
                cout << segments[event.p.index] << endl;
                return 0;
            }
            if (pred_ind != -1) {
                isIntersect = CheckForIntersection(eventQueue, segments[pred_ind], segments[event.p.index]);
            }
            if (isIntersect) {
                cout << "INTERSECTION" << endl;
                cout << segments[pred_ind] << endl;
                cout << segments[event.p.index] << endl;
                return 0;
            }

        } else if (event.p.p_type == end_t) {
            Point leftPair = Point(segments[event.p.index].start_p.x, segments[event.p.index].start_p.y, start_t, event.p.index);
            sweepingLine.Insert(leftPair);

            int suc_ind = sweepingLine.FindSuccessor(leftPair).p.index;
            int pred_ind = sweepingLine.FindPredecessor(leftPair).p.index;


//            int suc_ind = sweepingLine.FindSuccessor(event).p.index;
//            int pred_ind = sweepingLine.FindPredecessor(event).p.index;

            if (suc_ind != -1 && pred_ind != -1) {
                isIntersect = CheckForIntersection(eventQueue, segments[pred_ind], segments[suc_ind]);
            }
            if (isIntersect) {
                cout << "INTERSECTION" << endl;
                cout << segments[pred_ind] << endl;
                cout << segments[suc_ind] << endl;
                return 0;
            }
            sweepingLine.Delete(leftPair);
//            sweepingLine.Delete(event);
        }
    }

    cout << "NO INTERSECTIONS" << endl;
    return 0;
}



