#include <iostream>
#include <algorithm>
#include <set>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

typedef struct {
    Point left, right;
}my_Segment;

bool operator<(const Point &a, const Point &b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

bool operator<(const my_Segment &a, const my_Segment &b) {
    return a.left < b.left;
}

long double slope(const Point &a, const Point &b) {
    return (long double) ((b.y - a.y) / (long double)(b.x - a.x));
}

long double y_intercept(const Point &a, const Point &b) {
    return (long double) ((long double)(a.y) - (slope(a, b) * (long double)(a.x)));
}

bool intersect(const my_Segment &a, const my_Segment &b) {
    my_Segment a_ = a;
    my_Segment b_ = b;
    if (a_.left.x > a_.right.x) {
        swap(a_.left, a_.right);
    }
    if (b_.left.x > b_.right.x) {
        swap(b_.left, b_.right);
    }
    long double mi1 = slope(a_.left, a_.right);
    long double b1 = y_intercept(a_.left, a_.right);
    long double mi2 = slope(b_.left, b_.right);
    long double b2 = y_intercept(b_.left, b_.right);
//    if (a_.left.x == b_.left.x && a_.left.y == b_.left.y) return true;
//    if (a_.right.x == b_.right.x && a_.right.y == b_.right.y) return true;
   if (mi1 == mi2) {
		if (b1 != b2) {
            return false;
        }
        bool l = a_.left.y >= b_.left.y && a_.left.y <= b_.right.y;
        bool m = a_.right.y >= b_.left.y && a_.right.y <= b_.right.y;
        bool n = b_.left.y >= a_.left.y && b_.left.y <= a_.right.y;
        bool o = b_.right.y >= a_.left.y && b_.right.y <= a_.right.y;
 
        if (l || m || n || o) {
            return true;
        }
        return false;
   }

    long double x = (long double) ((b2 - b1) / (mi1 - mi2));

    if (x < max(a_.left.x, b_.left.x) || x > min(a_.right.x, b_.right.x)) {
        return false;
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    vector<my_Segment> segments = vector<my_Segment>(n);

    for (int i = 0; i < n; i++) {
        cin >> segments[i].left.x >> segments[i].left.y >> segments[i].right.x >> segments[i].right.y;
//        if (segments[i].left.x > segments[i].right.x) {
//            swap(segments[i].left, segments[i].right);
//        }
    }

    sort(segments.begin(), segments.end());

    set<my_Segment> status;
    bool found_intersection = false;

    for (int i = 0; i < n; i++) {
        if (segments[i].left.x == segments[i].right.x) continue;

        auto it = status.lower_bound(segments[i]);

        if (it != status.end() && intersect(segments[i], *it)) {
            found_intersection = true;
            cout << "INTERSECTION" << endl;
            cout << segments[i].left.x << " " << segments[i].left.y << " " << segments[i].right.x << " " << segments[i].right.y << endl;
            cout << (*it).left.x << " " << (*it).left.y << " " << (*it).right.x << " " << (*it).right.y << endl;
            return 0;
        }

        if (it != status.begin() && intersect(segments[i], *prev(it))) {
            my_Segment s = *(prev(it));
            found_intersection = true;
            cout << "INTERSECTION" << endl;
            cout << segments[i].left.x << " " << segments[i].left.y << " " << segments[i].right.x << " " << segments[i].right.y << endl;
            cout << s.left.x << " " << s.left.y << " " << s.right.x << " " << s.right.y << endl;

            return 0;
        }

        status.insert(segments[i]);
    }

    cout << "NO INTERSECTIONS" << endl;

    return 0;
}