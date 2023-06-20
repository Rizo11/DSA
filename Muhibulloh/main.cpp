#include <iostream>
#include <bits/stdc++.h>
#define int long long
using namespace std;

enum Dir
{
    LEFT,
    RIGHT
};

struct Segment
{
    int x1;
    int y1;
    int x2;
    int y2;
};

struct Point
{
    int x;
    int y;
    Dir dir;
    int ind;
};

bool operator<(const Point &lhs, const Point &rhs)
{
    return lhs.y == rhs.y ? lhs.x < rhs.x : lhs.y < rhs.y;
}

ostream &operator<<(ostream &stream, Segment &segment)
{
    stream << segment.x1 << " " << segment.y1 << " " << segment.x2 << " " << segment.y2;
    return stream;
}

bool pointInLine(int lx, int ly, int rx, int ry, int px, int py)
{
    if (min(lx, rx) <= px && px <= max(lx, rx) &&
        min(ly, ry) <= py && py <= max(ly, ry))
        return true;
    return false;
}

bool intersectParalel(Segment &a, Segment &b)
{
    if (pointInLine(a.x1, a.y1, a.x2, a.y2, b.x1, b.y1) ||
        pointInLine(a.x1, a.y1, a.x2, a.y2, b.x2, b.y2) ||
        pointInLine(b.x1, b.y1, b.x2, b.y2, a.x1, a.y1) ||
        pointInLine(b.x1, b.y1, b.x2, b.y2, a.x2, a.y2))
        return true;
}

bool intersectSegments(Segment &a, Segment &b)
{
    int den = (a.x1 - a.x2) * (b.y1 - b.y2) - (a.y1 - a.y2) * (b.x1 - b.x2);

    if (den == 0)
    {
        return intersectParalel(a, b);
    }
    else
    {
        int xp = (a.x1 * a.y2 - a.y1 * a.x2) * (b.x1 - b.x2) - (a.x1 - a.x2) * (b.x1 * b.y2 - b.y1 * b.x2);
        xp = xp / den;

        int yp = (a.x1 * a.y2 - a.y1 * a.x2) * (b.y1 - b.y2) - (a.y1 - a.y2) * (b.x1 * b.y2 - b.y1 * b.x2);
        yp = yp / den;

        if (pointInLine(a.x1, a.y1, a.x2, a.y2, xp, yp) && pointInLine(b.x1, b.y1, b.x2, b.y2, xp, yp))
            return true;
        else
            return false;
    }
}

void checkIntersection(Segment &a, Segment &b)
{
    if (intersectSegments(a, b))
    {
        cout << "INTERSECTION\n";
        cout << a << "\n"
             << b << "\n";
        exit(0);
    }
}

int n;


vector<Point> points;
vector<Segment> original;
vector<Segment> segments;

template <class T, class Compare>
void heapify(vector<T> &arr, int n, int i, Compare comp)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && comp(arr[smallest], arr[left]))
        smallest = left;

    if (right < n && comp(arr[smallest], arr[right]))
        smallest = right;

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest, comp);
    }
}

template <class T, class Compare>
void heapsort(vector<T> &arr, Compare comp)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comp);

    for (int i = n - 1; i >= 1; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, comp);
    }
}

void checkIntersection(int a, int b)
{
    if (intersectSegments(segments[a], segments[b]))
    {
        cout << "INTERSECTION\n";
        cout << original[a] << "\n"
             << original[b] << "\n";
        exit(0);
    }
}

template <typename T>
struct Node
{
    T val;
    int height;
    int size;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    Node(T val)
    {
        this->val = val;
        this->height = 1;
        this->size = 1;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
};

template <typename T>
class AVLTree
{
public:
    // private:
    Node<T> *root;

    int max(T a, T b)
    {
        return (a > b) ? a : b;
    }

    Node<T> *newNode(T key)
    {
        Node<T> *node = new Node<T>(key);
        node->val = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return node;
    }

    int height(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int size(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->size;
    }

    int balanceFactor(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    void update(Node<T>* node)
    {
        node->height = max(height(node->left), height(node->right)) + 1;
        node->size = size(node->left) + size(node->right) + 1;
    }

    Node<T>* rotateLeft(Node<T>* node)
    {
        Node<T>* pivot = node->right;
        pivot->parent = node->parent;
        node->right = pivot->left;
        if (pivot->left != nullptr)
        {
            pivot->left->parent = node;
        }
        pivot->left = node;
        node->parent = pivot;
        update(node);
        update(pivot);
        return pivot;
    }

    Node<T>* rotateRight(Node<T>* node)
    {
        Node<T>* pivot = node->left;
        pivot->parent = node->parent;
        node->left = pivot->right;
        if (pivot->right != nullptr)
        {
            pivot->right->parent = node;
        }
        pivot->right = node;
        node->parent = pivot;
        update(node);
        update(pivot);
        return pivot;
    }

    Node<T>* balance(Node<T>* node)
    {
        update(node);
        int balance = balanceFactor(node);
        if (balance > 1)
        {
            if (balanceFactor(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        else if (balance < -1)
        {
            if (balanceFactor(node->right) > 0)
            {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    Node<T>* deleteNode(Node<T>* root, T key)
    {
        if (root == NULL)
        {
            return root;
        }
        if (key < root->val)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->val)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                Node<T>* temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                {
                    *root = *temp;
                    delete temp;
                }
            }
            else
            {
                Node<T>* temp = root->right;
                while (temp->left != NULL)
                {
                    temp = temp->left;
                }
                root->val = temp->val;

                root->right = deleteNode(root->right, temp->val);
            }

            if (root == NULL)
            {
                return root;
            }

            root->height = 1 + max(height(root->left), height(root->right));

            T balance = balanceFactor(root);

            if (balance > 1 && balanceFactor(root->left) >= 0)
            {
                return rotateRight(root);
            }
            if (balance > 1 && balanceFactor(root->left) < 0)
            {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }

            if (balance < -1 && balanceFactor(root->right) <= 0)
            {
                return rotateLeft(root);
            }

            if (balance < -1 && balanceFactor(root->right) > 0)
            {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }

            return root;
        }
    }


    Node<T>* insert(Node<T>* node, T val)
    {
        if (node == nullptr)
        {
            return new Node(val);
        }
        if (val < node->val)
        {
            Node<T>* left = insert(node->left, val);
            left->parent = node;
            node->left = left;
        }
        else
        {
            Node<T>* right = insert(node->right, val);
            right->parent = node;
            node->right = right;
        }
        return balance(node);
    }

    Node<T>* find(Node<T>* node, T val)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (val == node->val)
        {
            return node;
        }
        else if (val < node->val)
        {
            return find(node->left, val);
        }
        else
        {
            return find(node->right, val);
        }
    }

    Node<T>* lowerBound(Node<T>* node, T val)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->val == val)
        {
            return node;
        }
        else if (node->val > val)
        {
            if (node->left == nullptr)
            {
                return node;
            }
            else
            {
                return lowerBound(node->left, val);
            }
        }
        else
        {
            if (node->right == nullptr)
            {
                return nullptr;
            }
            else
            {
                Node<T>* lower = lowerBound(node->right, val);
                if (lower == nullptr)
                {
                    return node;
                }
                else
                {
                    return lower;
                }
            }
        }
    }

    Node<T>* begin(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->left == nullptr)
        {
            return node;
        }
        return begin(node->left);
    }

    Node<T>* end(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->right == nullptr)
        {
            return node;
        }
        return end(node->right);
    }

    // public:
    AVLTree()
    {
        root = nullptr;
    }
    void insert(T val)
    {
        root = insert(root, val);
    }

    Node<T>* find(T val)
    {
        return find(root, val);
    }

    Node<T>* lowerBound(T val)
    {
        return lowerBound(root, val);
    }

    T end()
    {
        Node<T>* node = end(root);
        return node == nullptr ? T() : node->val;
    }

    Node<T>* next(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->right != nullptr)
        {
            Node<T>* curr = node->right;
            while (curr->left != nullptr)
            {
                curr = curr->left;
            }
            return curr;
        }
        else
        {
            Node<T>* curr = node;
            while (curr->parent != nullptr && curr->parent->right == curr)
            {
                curr = curr->parent;
            }
            return curr->parent;
        }
    }

    Node<T>* next(T val)
    {
        auto node = find(val);
        return next(node);
    }

    Node<T>* previous(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->left != nullptr)
        {
            Node<T>* curr = node->left;
            while (curr->right != nullptr)
            {
                curr = curr->right;
            }
            return curr;
        }
        else
        {
            Node<T>* curr = node;
            while (curr->parent != nullptr && curr->parent->left == curr)
            {
                curr = curr->parent;
            }
            return curr->parent;
        }
    }

    T begin()
    {
        Node<T>* node = begin(root);
        return node == nullptr ? T() : node->val;
    }

    Node<T>* previous(T val)
    {
        auto node = find(val);
        return previous(node);
    }
};



AVLTree<Point> s;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        int x1, y1;
        int x2, y2;
        cin >> x1 >> y1;
        cin >> x2 >> y2;

        original.push_back({x1, y1, x2, y2});
        if (x1 == x2 ? y1 > y2 : x1 > x2)
        {
            swap(x1, x2);
            swap(y1, y2);
        }
        points.push_back({x1, y1, LEFT, i - 1});
        points.push_back({x2, y2, RIGHT, i - 1});
        segments.push_back({x1, y1, x2, y2});
    }

    heapsort(points, [](Point &lhs, Point &rhs)
             { return make_tuple(lhs.x, lhs.y, lhs.dir) < make_tuple(rhs.x, rhs.y, rhs.dir); });

    for (Point point : points)
    {
        if (point.dir == LEFT)
        {
            auto next = s.next(point);
            auto prev = s.previous(point);

            if (next != nullptr)
            {
                checkIntersection(next->val.ind, point.ind);
            }
            else if (prev != nullptr)
            {
                checkIntersection(prev->val.ind, point.ind);
            }

            s.insert(point);
        }
        else
        {
            int ind = point.ind;

            auto it = s.find(Point{segments[ind].x1, segments[ind].y1, LEFT, ind});

            if (it == nullptr)
                continue;

            auto next = it;
            ++next;
            auto prev = it;
            if (prev != nullptr)
                prev--;
            else
                prev = nullptr;

            if (next != nullptr && prev != nullptr)
            {
                checkIntersection(prev->val.ind, next->val.ind);
            }
            s.deleteNode(it, it->val);
        }
    }
    cout << "NO INTERSECTIONS";

    return 0;
}