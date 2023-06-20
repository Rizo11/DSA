#include <iostream>
#include <vector>
#include <climits>
#include <set>

using namespace std;

const int INF = INT_MAX;

string NegativeCycleDetector(vector<vector<int>>& Graph, int source) {
    int n = Graph.size();
    vector<int> d(n, INF);
    d[source] = 0;
    set<int> neg_vertices = set<int>();
    for (int i = 1; i < n; i++) {
        bool flag = false;
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (Graph[u][v] != INF && d[u] + Graph[u][v] < d[v] && abs(Graph[u][v]) == 100000) {
                    d[v] = d[u] + Graph[u][v];
                    flag = true;
//                    neg_vertices.insert(v);
                }
            }
        }
        if (!flag) {
            /*for (auto v : neg_vertices) {
                cout << ++v << " ";
            }
            cout << endl;*/
            break;
        }
    }
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (Graph[u][v] != INF && d[u] + Graph[u][v] < d[v]) {
                neg_vertices.insert(u);
                neg_vertices.insert(v);
            }
        }
    }

    for (auto v : neg_vertices) {
        cout << v << " ";
    }
    cout << endl;

    return "No Negative Cycle";
}

int main() {
    vector<vector<int>> Graph = vector<vector<int>>();

    int n = 0;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        vector<int> tmp = vector<int>();
        int value = 0;
        for (int j = 0; j < n; ++j) {
            cin >> value;
            tmp.push_back(value);
        }
        Graph.push_back(tmp);
    }
    int source = 0;
    string result = NegativeCycleDetector(Graph, source);
    cout << result << endl;
    return 0;
}
