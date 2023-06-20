#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

struct Point {
    int x, y;
};

class Segment{
public:
    Point left, right;
    Segment() {}
};

bool operator<(const Point &a, const Point &b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

bool operator<(const Segment &a, const Segment &b) {
    return a.left < b.left;
}

double slope(const Point &a, const Point &b) {
    return (double)(b.y - a.y) / (b.x - a.x);
}

double y_intercept(const Point &a, const Point &b) {
    return a.y - slope(a, b) * a.x;
}

bool intersect(const Segment &a, const Segment &b) {
    double mi1 = slope(a.left, a.right);
    double b1 = y_intercept(a.left, a.right);
    double mi2 = slope(b.left, b.right);
    double b2 = y_intercept(b.left, b.right);

    if (mi1 == mi2) return false;

    double x = (b2 - b1) / (mi1 - mi2);

    if (x < max(a.left.x, b.left.x) || x > min(a.right.x, b.right.x)) {
        return false;
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    vector<Segment> segments = vector<Segment>(n);

    for (int i = 0; i < n; i++) {
        cin >> segments[i].left.x >> segments[i].left.y >> segments[i].right.x >> segments[i].right.y;
        if (segments[i].left.x > segments[i].right.x) {
            swap(segments[i].left, segments[i].right);
        }
    }

    sort(segments.begin(), segments.end());

    set<Segment> status;
    bool found_intersection = false;

    for (int i = 0; i < n; i++) {
        if (segments[i].left.x == segments[i].right.x) continue;

        auto it = status.lower_bound(segments[i]);

        if (it != status.end() && intersect(segments[i], *it)) {
            found_intersection = true;
            cout << "INTERSECTION" << endl;
            cout << segments[i].left.x << " " << segments[i].left.y << " " << segments[i].right.x << " " << segments[i].right.y << endl;
            cout << (*it).left.x << " " << (*it).left.y << " " << (*it).right.x << " " << (*it).right.y << endl;
            break;
        }

        if (it != status.begin() && intersect(segments[i], *prev(it))) {
            found_intersection = true;
            cout << "INTERSECTION" << endl;
            cout << segments[i].left.x << " " << segments[i].left.y << " " << segments[i].right.x << " " << segments[i].right.y << endl;
            Segment s = *(prev(it));
            cout << s.left.x << " " << s.left.y << " " << s.right.x << " " << s.right.y << endl;
            break;
        }

        status.insert(segments[i]);
    }

    if (found_intersection) {
    } else {
        cout << "NO INTERSECTIONS" << endl;
    }

    return 0;
}
