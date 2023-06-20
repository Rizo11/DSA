#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

template <typename V, typename E>
class Graph {
private:
    struct Edge {
        int to;
        E weight;
        Edge(int to, E weight) : to(to), weight(weight) {}
    };

    std::vector<std::vector<Edge>> adjacency_list;
    std::unordered_set<V> vertices;

public:
    void addVertex(V v) {
        if (vertices.find(v) == vertices.end()) {
            vertices.insert(v);
            adjacency_list.push_back({});
        }
    }

    void addEdge(V from, V to, E weight) {
        int index_from = getIndex(from);
        int index_to = getIndex(to);
        adjacency_list[index_from].push_back(Edge(index_to, weight));
    }

    bool isConnected() {
        if (vertices.empty()) {
            return true;
        }

        std::unordered_set<int> visited;
        std::stack<int> stack;
        stack.push(0);

        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();

            if (visited.find(current) == visited.end()) {
                visited.insert(current);

                for (const Edge& edge : adjacency_list[current]) {
                    stack.push(edge.to);
                }
            }
        }

        return visited.size() == vertices.size();
    }

private:
    int getIndex(V v) {
        auto it = vertices.find(v);
        if (it == vertices.end()) {
            throw std::invalid_argument("Vertex not found.");
        }
        return std::distance(vertices.begin(), it);
    }
};

int main() {
    int n;
    cin >> n;
    Graph<int, int> graph;

    for (int i = 0; i < n; ++i) {
        graph.addVertex(i);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int k = 0;
            cin >> k;
            graph.addEdge(i, j, 1);
        }
    }

    // Check if the graph is connected
    if (graph.isConnected()) {
        cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}