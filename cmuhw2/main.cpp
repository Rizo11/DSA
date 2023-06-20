#include <iostream>
#include <queue>
#include <set>

using namespace std;



enum point_t {
    start_t,
    end_t,
    cross_t
};
class Segment;
class Point {
public:
    double x = 0;
    double y = 0;
    point_t p_type;
    Point(int x, int y, point_t type) : x(x), y(y), p_type(type) {}
    Segment* partOf = NULL;
    Point() {}

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
ostream& operator<<(ostream& os, const Point& pt)
{
    os << pt.x << " " << pt.y << " " << '/';

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

    bool operator < (Segment const& pt) const
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
        /*if (this->y == pt.y && this->x == pt.x) {
            return true;
        } else {
            return false;
        }*/

        return true;
    }

    friend ostream& operator<<(ostream& os, const Segment& sg);
};

ostream& operator<<(ostream& os, const Segment& sg)
{
    os << sg.start_p.x << " " << sg.start_p.y << " " << '/';
    os << sg.end_p.x << " " << sg.end_p.y << " " << '/';

    return os;
}
bool intersect(const Segment &a, const Segment &b) {
    Segment a_ = a;
    Segment b_ = b;
    if (a_.start_p.x > a_.end_p.x) {
        swap(a_.start_p, a_.end_p);
    }
    if (b_.start_p.x > b_.end_p.x) {
        swap(b_.start_p, b_.end_p);
    }
    long double mi1 = slope(a_.start_p, a_.end_p);
    long double b1 = y_intercept(a_.start_p, a_.end_p);
    long double mi2 = slope(b_.start_p, b_.end_p);
    long double b2 = y_intercept(b_.start_p, b_.end_p);
    if (a_.start_p.x == b_.start_p.x && a_.start_p.y == b_.start_p.y) return true;
    if (a_.end_p.x == b_.end_p.x && a_.end_p.y == b_.end_p.y) return true;
    if (mi1 == mi2) {
        if (b1 != b2) {
            return false;
        }
        bool l = a_.start_p.y >= b_.start_p.y && a_.start_p.y <= b_.end_p.y;
        bool m = a_.end_p.y >= b_.start_p.y && a_.end_p.y <= b_.end_p.y;
        bool n = b_.start_p.y >= a_.start_p.y && b_.start_p.y <= a_.end_p.y;
        bool o = b_.end_p.y >= a_.start_p.y && b_.end_p.y <= a_.end_p.y;

        if (l || m || n || o) {
            return true;
        }
        return false;
    }

    long double x = (long double) ((b2 - b1) / (mi1 - mi2));

    bool xOnY = a_.start_p.y == mi2*a_.start_p.x + b2;
    bool xOnY2 = a_.end_p.y == mi2*a_.end_p.x + b2;
    bool yOnX = b_.start_p.y == mi1*b_.start_p.x + b1;
    bool yOnX2 = b_.start_p.y == mi1*b_.end_p.x + b1;

    if (xOnY || xOnY2 || yOnX || yOnX2) {
        return true;
    }

    if (x < max(a_.start_p.x, b_.start_p.x) || x > min(a_.end_p.x, b_.end_p.x)) {
        return false;
    }

    return true;
}

int main() {
    int n = 0;
    cin >> n;
    priority_queue<Point> eventQueue;
    vector<Segment> segments = vector<Segment>();
    for ( int i = 0; i < n; i++) {
        int x, y, x2, y2;
        cin >> x >> y >> x2 >> y2;
        Point start_p = Point(x, y, start_t);
        Point end_p = Point(x2, y2, end_t);
        Segment s = Segment(start_p, end_p);
        segments.push_back(s);

        start_p.partOf= &segments[i];
        segments[i].start_p = start_p;
        end_p.partOf= &segments[i];
        segments[i].end_p = end_p;


        eventQueue.push(start_p);
        eventQueue.push(end_p);
    }

    set<Segment> sl;
    while (!eventQueue.empty()) {
        Point e = eventQueue.top();
        eventQueue.pop();
        if (e.p_type == start_t) {
            Segment s = *(e.partOf);
            auto itr = sl.insert(s);
            if (++itr.first != sl.end()) {
                if (intersect(s, *itr.first)) {
                    cout << "INTERSECTION" << endl;
                    cout << s.start_p.x << " " << s.start_p.y << " " << s.end_p.x << " " << s.end_p.y << endl;
                    cout << (*itr.first).start_p.x << " " << (*itr.first).start_p.y << " " << (*itr.first).end_p.x << " " << (*itr.first).end_p.y << endl;
                    return 0;
                }

            }
            if (--itr.first != sl.begin()) {
                if (intersect(s, *itr.first)) {
                    cout << "INTERSECTION" << endl;
                    cout << s.start_p.x << " " << s.start_p.y << " " << s.end_p.x << " " << s.end_p.y << endl;
                    cout << (*itr.first).start_p.x << " " << (*itr.first).start_p.y << " " << (*itr.first).end_p.x << " " << (*itr.first).end_p.y << endl;
                    return 0;
                }

            }
        } else if (e.p_type == end_t) {
            Segment s = *(e.partOf);
            auto itr = sl.insert(s);
            if (++itr.first != sl.end()) {
                Segment suc = itr.first;
                --itr.first;
                if (--itr.first != sl.begin()) {
                    if (intersect(s, *itr.first)) {
                        cout << "INTERSECTION" << endl;
                        cout << s.start_p.x << " " << s.start_p.y << " " << s.end_p.x << " " << s.end_p.y << endl;
                        cout << (*itr.first).start_p.x << " " << (*itr.first).start_p.y << " " << (*itr.first).end_p.x << " " << (*itr.first).end_p.y << endl;
                        return 0;
                    }

                }

            }
        }

    }
    return 0;
}
