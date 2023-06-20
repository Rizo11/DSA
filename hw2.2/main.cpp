// Mukhammadrizo Maribjonov DS-AI 4
// reference: https://www.geeksforgeeks.org/given-a-set-of-line-segments-find-if-any-two-segments-intersect/
// referene: www.geeksforgeeks.org

/*   Applications; Computer graphics: In computer graphics, segments are commonly used to represent lines, and the detection of
 * Finding intersections between these segments is a fundamental operation for many algorithms, such as hidden line removal, ray tracing, and collision detection.
    Geographical information systems: In geographic information systems, segments are often used to represent
    roads, rivers and other linear features. Detecting intersections between these segments is important for tasks such as routing, navigation and spatial analysis.
    Robotics: In robotics, segments can represent the arms or limbs of a robot, and detecting intersections between these segments is important for
    between these segments is important for tasks such as motion planning, collision avoidance and grasping.
    VLSI design: In Very Large Scale Integration (VLSI) design, segments can represent wires or paths in a circuit.
    Detecting intersections between these segments is important for tasks such as layout design, routing and verification.
    Computational Geometry: In computational geometry, segment intersection is a fundamental problem that is
    is used as a building block for many other algorithms, such as polygon triangulation, Voronoi diagrams and Delaunay triangulations.

    The sweeping line algorithm is a powerful technique for efficiently solving the segment intersection problem.
    By using a horizontal sweep line to scan the segments from left to right, the algorithm can find all intersections between the segments in
    between the segments in O(n log n) time, where n is the number of segments. This algorithm is widely used in practice,
    and has many variations and extensions for different applications.
    */

#include <bits/stdc++.h>

using namespace std;


enum point_t {
    start_t,
    end_t,
    cross_t
};
class Point {
public:
    int x;
    int y;
    Point(double x_, double y_, point_t pType, int index) : x(x_), y(y_), p_type(pType), index(index) {}
    point_t p_type;
    int index;
    Point() {
        this->y = 0;
        this->y = 0;
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

    // true if e bigger than current event
    bool operator < (const Event& e) const {
        if(p.y == e.p.y) return  p.x < e.p.x;
        return p.y < e.p.y;
    }


    // true if current event is bigger than e
    bool operator > (const Event& e) const {
        if(p.y == e.p.y) return  p.x > e.p.x;
        return p.y > e.p.y;
    }

    // true if current and e events are equal
    bool operator == (const Event& e) const {
        return (p.y == e.p.y && p.x == e.p.x);
    }
};

ostream& operator<<(ostream& os, const Point& pt)
{
    os << pt.x << " " << pt.y;

    return os;
}

class Segment {
public:
    Point start_p;
    Point end_p;
    Segment(Point start_, Point end_) : start_p(start_), end_p(end_) {}

    Segment() {}

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

    const T deletemin() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        T res = heap.front();
        heap.front() = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return res;
    }

    bool isEmpty() {
        return heap.empty();
    }
};


template<typename T>
struct AVLNode {
    T data;
    int height;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;
    AVLNode(T data) {
        this->data = data;
        this->height = 1;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }
};

template <typename T>
class AVLTree {
public:
    AVLTree() {
        root = NULL;
    }

    // O (log n)
    void Insert(T data) {
        AVLNode<T>* newNode = new AVLNode<T>(data);
        root = InsertNode(newNode, root);
    }

    // O (log n)
    void Delete(T data) {
        root = DeleteNode(root, data);
    }

    // O (log n)
    T FindSuccessor(T data) const {
        AVLNode<T> *node = FindNode(root, data);
        if (node == NULL) {
            return T();
        }
        AVLNode<T> *successor = GetSuccessor(node);
        if (successor == NULL) {
            return T();
        }
        return successor->data;
    }

    // O (log n)
    T FindPredecessor(T data) const {
        AVLNode<T> *node = FindNode(root, data);
        if (node == NULL) {
            return T();
        }
        AVLNode<T> *predecessor = GetPredecessor(node);
        if (predecessor == NULL) {
            return T();
        }
        return predecessor->data;
    }


private:
    AVLNode<T> *root;


    int GetHeight(AVLNode<T> *node) const {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }
    int GetBalanceFactor(AVLNode<T> *node) const {
        if (node == NULL) {
            return 0;
        }
        return GetHeight(node->left) - GetHeight(node->right);
    }
    AVLNode<T> *RightRotate(AVLNode<T> *y) {
        AVLNode<T> *x = y->left;
        AVLNode<T> *z = x->right;

        x->right = y;
        y->left = z;
        x->parent = y->parent;
        y->parent = x;
        if (z) {
            z->parent = y;
        }

        y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
        x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

        return x;
    }
    AVLNode<T> *LeftRotate(AVLNode<T> *x) {
        AVLNode<T> *y = x->right;
        AVLNode<T> *z = y->left;

        y->left = x;
        x->right = z;
        y->parent = x->parent;
        x->parent = y;
        if (z) {
            z->parent = x;
        }

        x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
        y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

        return y;
    }
    AVLNode<T> *InsertNode(AVLNode<T> *newNode, AVLNode<T>* parent) {
        if (!parent) {
            return newNode;
        }

        if (newNode->data < parent->data) {
            AVLNode<T>* nN = InsertNode(newNode, parent->left);
            parent->left = nN;
            parent->left->parent = parent;
        }
        else if (newNode->data > parent->data) {
            AVLNode<T>* nN = InsertNode(newNode, parent->right);
            parent->right = nN;
            parent->right->parent = parent;
        }
        else return parent; // no duplicate nodes allowed

        parent->height = std::max(GetHeight(parent->left), GetHeight(parent->right)) + 1;

        int bf = GetBalanceFactor(parent);

        // left-left case
        if (bf > 1 && newNode->data < parent->left->data)
            return RightRotate(parent);

        // left-right case
        if (bf > 1 && newNode->data > parent->left->data) {
            parent->left = LeftRotate(parent->left);
            return RightRotate(parent);
        }

        // right-right case
        if (bf < -1 && newNode->data > parent->right->data)
            return LeftRotate(parent);

        // right-left case
        if (bf < -1 && newNode->data < parent->right->data) {
            parent->right = RightRotate(parent->right);
            return LeftRotate(parent);
        }

        return parent;
    }
    AVLNode<T>* minimum(AVLNode<T>* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }
    AVLNode<T> *DeleteNode(AVLNode<T> *node, T data) {

        // Base case: empty tree
        if (node == NULL) {
            return node;
        }
        if ( data < node->data )
            node->left = DeleteNode(node->left, data);

        else if( data > node->data )
            node->right = DeleteNode(node->right, data);

            // if key is same as node's key, then
            // This is the node to be deleted
        else
        {
            // node with only one child or no child
            if( (node->left == NULL) ||
                (node->right == NULL) ) {
                AVLNode<T> *temp = node->left ?
                                   node->left :
                                   node->right;

                // No child case
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else // One child case
                {
                    AVLNode<T>* parentTMP = node->parent;
                    *node = *temp;
                    node->parent = parentTMP;
                }
                delete temp;
            }
            else
                {
                // node with two children: Get the inorder
                // successor (smallest in the right subtree)
                AVLNode<T>* temp = minimum(node->right);

                // Copy the inorder successor's
                // data to this node
                node->data = temp->data;

                // Delete the inorder successor
                node->right = DeleteNode(node->right,
                                         temp->data);
            }
        }
        if (node == NULL) {
            return node;
        }

        // Update the height of the current node
        node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));

        // Check if this node is unbalanced
        int balance = GetBalanceFactor(node);

        // If this node is unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && GetBalanceFactor(node->left) >= 0) {
            return RightRotate(node);
        }

        // Left Right Case
        if (balance > 1 && GetBalanceFactor(node->left) < 0) {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && GetBalanceFactor(node->right) <= 0) {
            return LeftRotate(node);
        }

        // Right Left Case
        if (balance < -1 && GetBalanceFactor(node->right) > 0) {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }
    AVLNode<T> *FindNode(AVLNode<T>* node, T data) const {
        if (node == NULL || node->data == data) {
            return node;
        }
        if (data < node->data) {
            return FindNode(node->left, data);
        }
        return FindNode(node->right, data);
    }
    AVLNode<T> *GetSuccessor(AVLNode<T> *node) const {
        if (node == NULL) return NULL;
        if (node->right != NULL) {
            node = node->right;
            while (node->left != NULL) node = node->left;
            return node;
        } else {
            AVLNode<T> *parent = node->parent;
            if (node == parent) {
                return NULL;
            }
            while (parent != NULL && node == parent->right) {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
    }

    AVLNode<T> *GetPredecessor(AVLNode<T> *node) const {
        if (node == NULL) return NULL;
        if (node->left != NULL) {
            node = node->left;
            while (node->right != NULL) node = node->right;
            return node;
        } else {
            AVLNode<T> *parent = node->parent;
            if (node == parent) {
                return NULL;
            }
            while (parent != NULL && node == parent->left) {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
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

/* true if 2 segments intersect */
bool CheckForIntersection(Segment s, Segment successor_of_s) {
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

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long int n = 0;
    cin >> n;

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
    bool isIntersect = false;

    // complexity of sweepline algorithm is O (n log n)
    while (!eventQueue.isEmpty()) {

        // I am using heap sort. Every deleted form priority queue element is a sorted element.
        // Heap sort works in O (n log n)
        Event event = Event(eventQueue.deletemin());

        if (event.p.p_type == start_t) {

            sweepingLine.Insert(event);
            int suc_ind = sweepingLine.FindSuccessor(event).p.index;

            if (suc_ind != -1) {
                isIntersect = CheckForIntersection(segments[suc_ind], segments[event.p.index]);
            }
            if (isIntersect) {
                cout << "INTERSECTION" << endl;
                cout << segments[suc_ind] << endl;
                cout << segments[event.p.index] << endl;
                return 0;
            }

            int pred_ind = sweepingLine.FindPredecessor(event).p.index;
            if (pred_ind != -1) {
                isIntersect = CheckForIntersection( segments[pred_ind], segments[event.p.index]);
            }
            if (isIntersect) {
                cout << "INTERSECTION" << endl;
                cout << segments[event.p.index] << endl;
                cout << segments[pred_ind] << endl;
                return 0;
            }

        } else if (event.p.p_type == end_t) {

            Point leftPair = Point(segments[event.p.index].start_p.x, segments[event.p.index].start_p.y, start_t, event.p.index);

            if (event.p == leftPair) {
                leftPair = Point(segments[event.p.index].end_p.x, segments[event.p.index].end_p.y, start_t, event.p.index);
                sweepingLine.Delete(leftPair);
                continue;
            } else {
                sweepingLine.Insert(leftPair);
            }

            int suc_ind = sweepingLine.FindSuccessor(leftPair).p.index;
            if (suc_ind == -1) {
                sweepingLine.Delete(leftPair);
                continue;
            }
            int pred_ind = sweepingLine.FindPredecessor(leftPair).p.index;


            if (suc_ind != -1 && pred_ind != -1) {
                isIntersect = CheckForIntersection(segments[pred_ind], segments[suc_ind]);
            }
            if (isIntersect) {
                cout << "INTERSECTION" << endl;
                cout << segments[suc_ind] << endl;
                cout << segments[pred_ind] << endl;
                return 0;
            }
            sweepingLine.Delete(leftPair);
        }
    }

    cout << "NO INTERSECTIONS" << endl;
    return 0;
}



