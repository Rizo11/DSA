// Mukhammadrizo Maribjonov DS-AI 4

#include <bits/stdc++.h>

using namespace std;

template<typename T, typename S>
class MyGraph {
public:
    
    int nOfVertices_;
//    vector<vector<pair<T, S>>> mapMatrix;
    unordered_map<T, vector<pair<T, S>>> mapMatrix;

//    MyGraph(int mapMatrix) : nOfVertices_(mapMatrix), mapMatrix(nOfVertices_, vector<T>(nOfVertices_)) {}

    MyGraph() {}

    void addVertex(const T& label) {
        if (mapMatrix.find(label) == mapMatrix.end()) {
            mapMatrix[label] = std::vector<std::pair<T, S>>();
        }
    }

    void addEdge(const T& from, const T& to, const S& weight) {
        mapMatrix[from].push_back(std::make_pair(to, weight));
    }

    // connect city i and city j
    void newEdge(int i, int j, T weight) {
        mapMatrix[i][j] = weight;
    }

    // true if all cities every city is reachable from every other city
    bool isReachable(int src, int dest) {
        
        vector<bool> visitedCities(nOfVertices_, false);
        DFS(src, visitedCities);
        return visitedCities[dest];
    }

    // depth first search to find connectedness of graph
    void DFS(int vertex, vector<bool> &visitedCities) {
        visitedCities[vertex] = true;
        for (int i = 0; i < nOfVertices_; i++) {
            if (mapMatrix[vertex][i] != 0 && !visitedCities[i]) {
                DFS(i, visitedCities);
            }
        }
    }
};

int main() {
    int N;
    cin >> N;

    MyGraph<int, int> G(N);

    // read input
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int weight;
            cin >> weight;
            if (weight != 0) {
                G.newEdge(i, j, weight);
            }
        }
    }

    bool isAllReachable = true;

    // check each city for reachability to any other city
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!G.isReachable(i, j)) {
                isAllReachable = false;
                break;
            }
        }
        if (!isAllReachable) {
            break;
        }
    }

    // print result
    if (isAllReachable) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}