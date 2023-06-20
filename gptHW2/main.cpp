#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

struct Segment {
    Point p, q;
};

bool cmpX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool cmpY(const Point& a, const Point& b) {
    return a.y < b.y;
}

bool intersect(const Segment& a, const Segment& b) {
    return max(a.p.x, a.q.x) >= min(b.p.x, b.q.x) &&
           max(b.p.x, b.q.x) >= min(a.p.x, a.q.x) &&
           max(a.p.y, a.q.y) >= min(b.p.y, b.q.y) &&
           max(b.p.y, b.q.y) >= min(a.p.y, a.q.y) &&
           ((a.p.x - a.q.x) * (b.p.y - a.p.y) - (a.p.y - a.q.y) * (b.p.x - a.p.x)) *
           ((a.p.x - a.q.x) * (b.q.y - a.p.y) - (a.p.y - a.q.y) * (b.q.x - a.p.x)) <= 0 &&
           ((b.p.x - b.q.x) * (a.p.y - b.p.y) - (b.p.y - b.q.y) * (a.p.x - b.p.x)) *
           ((b.p.x - b.q.x) * (a.q.y - b.p.y) - (b.p.y - b.q.y) * (a.q.x - b.p.x)) <= 0;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n * 2);
    for (int i = 0; i < n; i++) {
        cin >> points[i * 2].x >> points[i * 2].y;
        cin >> points[i * 2 + 1].x >> points[i * 2 + 1].y;
    }
    sort(points.begin(), points.end(), cmpX);
    set<Segment, bool (*)(const Segment&, const Segment&)> active(cmpY);
    bool found = false;
    for (int i = 0; i < n * 2; i++) {
        if (points[i].x == points[i - 1].x) {
            continue;
        }
        for (auto it = active.begin(); it != active.end(); it++) {
            if (intersect(*it, Segment{points[i], {points[i].x, INT_MAX}})) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
        for (int j = i - 1; j >= 0 && points[i].x - points[j].x <= 1; j--) {
            if (points[i].y < points[j].y) {
                active.erase(Segment{points[j], points[j + 1]});
            } else if (points[i].y > points[j].y) {
                active.insert(Segment{points[j], points[j + 1]});
            }
        }
    }
    cout << (found ? "YES" : "NO") << endl;
    return 0;
}