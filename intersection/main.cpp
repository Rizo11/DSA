#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class point {
public:
    long double x;
    long double y;

    point(int x_, int y_) : x(x_), y(y_) {}
    friend ostream& operator<<(ostream&, const point& pt);

    bool operator==(const point p){
        if(x == p.x && y == p.y){
            return true;
        }
        else
            return false;
    }

    point(){}
};

ostream& operator<<(ostream& os, const point& pt)
{
    os << pt.x << " " << pt.y << " ";
    return os;
}

class line {
public:
    point start;
    point end;

    line(int xp, int yp, int xq, int yq) : start(xp, yp), end(xq, yq) {}

    friend ostream& operator<<(ostream&, const line& ln);

    bool intersect(line l) {
        if (shareEndpoint(l)) {
            return true;
        } else if (isParallelOrCoincide(l)) {
            long double t = ((start.x - l.start.x)*(l.start.y-l.end.y)-(start.y-l.start.y)*(l.start.x-l.end.x))/((start.x-end.x)*(l.start.y-l.end.y)-(start.y-end.y)*(l.start.x-l.end.x));
            long double u = ((start.x - l.start.x)*(start.y-end.y)-(start.y-l.start.y)*(start.x-end.x))/((start.x-end.x)*(l.start.y-l.end.y)-(start.y-end.y)*(l.start.x-l.end.x));
            if ( (t > 0 && t < 1) && (u > 0 && u < 1)) {
                return true;
            }

            return false;
        } else {
            return true;
        }
    }

    /* true if l is parallel to current line */
    bool isParallelOrCoincide (line l) {
        int parallel = (start.x - end.x)*(l.start.y - l.end.y) - (start.y - end.y)*(l.start.x-l.end.x);
        return parallel == 0;
    }

    bool intersect_g(line l) {
        long double t1a = (end.x - start.x == 0) ? (long double)(l.start.y - start.y) / (end.y - start.y) : (long double)(l.start.x - start.x) / (end.x - start.x);
        long double t1b = (end.x - start.x == 0) ? (long double)(l.end.y - start.y) / (end.y - start.y) : (long double)(l.end.x - start.x) / (end.x - start.x);
        long double t2a = (l.end.x - l.start.x == 0) ? (long double)(start.y - l.start.y) / (l.end.y - l.start.y) : (long double)(start.x - l.start.x) / (l.end.x - l.start.x);
        long double t2b = (l.end.x - l.start.x == 0) ? (long double)(end.y - l.start.y) / (l.end.y - l.start.y) : (long double)(end.x - l.start.x) / (l.end.x - l.start.x);

        if (fabs(t1a - t1b) < 0.00001 && fabs(t2a - t2b) < 0.00001) {
            // line segments coincide
            return true;
        } else if (fabs(t1a - t1b) < 0.00001 || fabs(t2a - t2b) < 0.00001) {
            // line segments are parallel
            return false;
        } else {
            long double t1a = (end.x - start.x == 0) ? (long double)(l.start.y - start.y) / (end.y - start.y) : (long double)(l.start.x - start.x) / (end.x - start.x);
            long double t2a = (l.end.x - l.start.x == 0) ? (long double)(start.y - l.start.y) / (l.end.y - l.start.y) : (long double)(start.x - l.start.x) / (l.end.x - l.start.x);

            if (t1a >= 0 && t1a <= 1 && t2a >= 0 && t2a <= 1) {
                // line segments intersect
                return true;
            } else {
                // line segments do not intersect
                return false;
            }
        }
    }

    bool intersect_n(line l) {
        long double t1a = (end.x - start.x == 0) ? (long double)(l.start.y - start.y) / (end.y - start.y) : (long double)(l.start.x - start.x) / (end.x - start.x);
        long double t2a = (l.end.x - l.start.x == 0) ? (long double)(start.y - l.start.y) / (l.end.y - l.start.y) : (long double)(start.x - l.start.x) / (l.end.x - l.start.x);

        if (t1a >= 0 && t1a <= 1 && t2a >= 0 && t2a <= 1) {
            // line segments intersect
            return true;
        } else {
            // line segments do not intersect
            return false;
        }
    }

    /* true id l share endpoint with current line */
    bool shareEndpoint (line l) {
        return this->start == l.start || this->start == l.end || this->end == l.start || this->end == l.end;
    }
};

ostream& operator<<(ostream& os, const line& ln)
{
    os << ln.start << ln.end << endl;
    return os;
}

/* reads input from console and returns vector of lines*/
vector<line> readInput() {
    int n = 0;
    cin >> n;
    vector<line> lines = vector<line>();
    for (int i = 0; i < n; ++i) {
        int xp, yp, xq, yq;
        cin >> xp >> yp >> xq >> yq;
        lines.push_back(line(xp, yp, xq, yq));
    }

    return lines;
}

long double ccw(point A, point B, point C) {
    return (C.y-A.y) * (B.x-A.x) > (B.y-A.y) * (C.x-A.x);
}

bool intersect(line AB, line CD) {
    return ccw(AB.start,CD.start,CD.end) != ccw(AB.end,CD.start,CD.end) and ccw(AB.start,AB.end,CD.start) != ccw(AB.start,AB.end,CD.end);
}

// Function to calculate cross product of two 2D vectors
long double cross_product(point a, point b, point c) {
    long double x1 = b.x - a.x;
    long double y1 = b.y - a.y;
    long double x2 = c.x - a.x;
    long double y2 = c.y - a.y;
    return (x1 * y2) - (x2 * y1);
}

// Function to check if two line segments coincide
bool segments_coincide(point p1, point q1, point p2, point q2) {
    // Find the direction of the two line segments
    long double dir1 = cross_product(p2, q2, p1);
    long double dir2 = cross_product(p2, q2, q1);
    long double dir3 = cross_product(p1, q1, p2);
    long double dir4 = cross_product(p1, q1, q2);

    // Check if the endpoints of one line segment lie on the other line segment
    if ((dir1 == 0) && (dir2 == 0) && (dir3 == 0) && (dir4 == 0)) {
        // Check if the two line segments overlap
        if ((p1.x <= max(q2.x, p2.x)) && (p2.x <= max(q1.x, p1.x)) &&
            (p1.y <= max(q2.y, p2.y)) && (p2.y <= max(q1.y, p1.y))) {
            return true;
        }
    }

    return false;
}

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool on_segment(point p, point q, point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
        return true;
    }
    return false;
}

// Find orientation of triplets (p, q, r)
int orientation(point p, point q, point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) {
        return 0; // Collinear
    }
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

bool segments_intersect(point p1, point q1, point p2, point q2) {
    // Find orientations of segments p1q1 and p2q2
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) {
        return true;
    }

    // Special Cases
    if (o1 == 0 && on_segment(p1, p2, q1)) {
        return true;
    }

    if (o2 == 0 && on_segment(p1, q2, q1)) {
        return true;
    }

    if (o3 == 0 && on_segment(p2, p1, q2)) {
        return true;
    }

    if (o4 == 0 && on_segment(p2, q1, q2)) {
        return true;
    }

    return false; // Doesn't fall in any of the above cases
}


int main() {

    vector<line> lines = readInput();

    for (int i = 0; i < lines.size(); i++) {
        for (int j = i + 1; j < lines.size(); j++) {

            // line_i and line_j intersect ?
            if (intersect(lines[i], lines[j])) {
                cout << "INTERSECTION" << endl;
                cout << lines[i] << lines[j];
                return 0;
            } else if (segments_coincide(lines[i].start, lines[i].end, lines[j].start, lines[j].end)) {
                cout << "INTERSECTION" << endl;
                cout << lines[i] << lines[j];
                return 0;
            }/* else if (segments_intersect(lines[i].start, lines[i].end, lines[j].start, lines[j].end)) {
                cout << "INTERSECTION" << endl;
                cout << lines[i] << lines[j];
                return 0;
            }*/
        }
    }
    cout << "NO INTERSECTIONS" << endl;
    return 0;
}
