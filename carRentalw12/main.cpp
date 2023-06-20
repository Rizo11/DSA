// Mukhammadrizo Maribjonov DS-AI 4
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <map>


using namespace std;

template<typename T>
class BinaryMinHeap {
public:
    BinaryMinHeap() {}

    bool empty() const {
        return data_.empty();
    }

    void push(const T& element) {
        data_.push_back(element);
        bubbleUp(size() - 1);
    }

    void pop() {
        if (size() > 1) {
            std::swap(data_.front(), data_.back());
        }
        data_.pop_back();
        bubbleDown(0);
    }

    T top() const {
        return data_.front();
    }

    size_t size() const {
        return data_.size();
    }

private:
    std::vector<T> data_;

    size_t leftChild(size_t index) const {
        return 2 * index + 1;
    }

    size_t rightChild(size_t index) const {
        return 2 * index + 2;
    }

    size_t parent(size_t index) const {
        return (index - 1) / 2;
    }

    bool hasLeftChild(size_t index) const {
        return leftChild(index) < size();
    }

    bool hasRightChild(size_t index) const {
        return rightChild(index) < size();
    }

    bool hasParent(size_t index) const {
        return index > 0;
    }

    T& at(size_t index) {
        return data_.at(index);
    }

    const T& at(size_t index) const {
        return data_.at(index);
    }

    void bubbleUp(size_t index) {
        while (hasParent(index) && at(index) < at(parent(index))) {
            std::swap(at(index), at(parent(index)));
            index = parent(index);
        }
    }

    void bubbleDown(size_t index) {
        while (hasLeftChild(index)) {
            size_t smallerChildIndex = leftChild(index);
            if (hasRightChild(index) && at(rightChild(index)) < at(smallerChildIndex)) {
                smallerChildIndex = rightChild(index);
            }
            if (at(index) < at(smallerChildIndex)) {
                break;
            } else {
                std::swap(at(index), at(smallerChildIndex));
            }
            index = smallerChildIndex;
        }
    }
};


struct Vertex {
    string name;
    int penalty;

    bool operator==(const Vertex& other) const {
        return name == other.name;
    }

    bool operator!=(const Vertex& other) const {
        return name != other.name;
    }

    bool operator > (const Vertex& other) const {
        return this->penalty > other.penalty;
    }

    bool operator < (const Vertex& other) const {
        return this->penalty < other.penalty;
    }
};

namespace std {
    template <>
    struct hash<Vertex> {
        size_t operator()(const Vertex& v) const {
            // use a combination of the name and penalty fields for the hash value
            return hash<string>()(v.name) ^ hash<int>()(v.penalty);
        }
    };
}

struct Edge {
    Vertex from;
    Vertex to;
    double cost;
    bool operator>(const Edge &other) const {
        return cost < other.cost;
    }

    bool operator==(const Edge& other) const {
        return cost == other.cost;
    }

    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }

    double getWeight() const {
        return cost;
    }

    Edge(double cost_) {
        cost = cost_;
    }

    Edge() {
        cost = -1;
    }
};

template<typename V, typename E>
class Graph {
private:
    // implementation details
    unordered_map<V, vector<E>> vertices_;
    vector<V> verticesOfGraph = vector<V>();
    bool empty() const {
        return vertices_.empty();
    }

    E getEdge(const V& src, const V& dest) const {
        auto edges = vertices_.at(src);
        for (const auto& edge : edges) {
            if (edge.to == dest) {
                return edge;
            }
        }
        return E();
    }

    E getEdge(const V& src, Graph<V, E>& mst) const {
        auto edges = vertices_.at(src);
        vector<V> allVertices = mst.getVertices();
        for (const auto& edge : edges) {
            V vertex = edge.to.name != src.name? edge.to : edge.from;

            if(find(allVertices.begin(), allVertices.end(), vertex) != allVertices.end()) {
                return edge;
            }
        }
        return E();
    }

public:
    vector<V> getVertices() {
        return verticesOfGraph;
    }


    vector<E> outgoingEdges(const V& vertex) const {
        vector<E> edges;
        auto it = vertices_.find(vertex);
        if (it != vertices_.end()) {
            for (const auto& edge : it->second) {
                edges.push_back(edge);
            }
        }
        return edges;
    }

    // public interface
    V findVertex(string name) {
        vector<V> vertices = getVertices();
        for (auto v : vertices) {
            if (v.name == name) {
                return v;
            }
        }

        return V();
    }
    void insertEdge(E& edge) {
        if (vertices_.find(edge.from) == vertices_.end() || vertices_.find(edge.to) == vertices_.end()) {
            throw std::invalid_argument("One or both vertices not in graph.");
        }
        vertices_[edge.from].push_back(edge);
        vertices_[edge.to].push_back(edge);
    }

    void insertVertex(const V& vertex) {
        // If the vertex is already in the graph, do nothing
        if (vertices_.count(vertex) > 0) {
            return;
        }

        // Add the vertex to the graph and initialize an empty vector of edges
        vertices_.insert(make_pair(vertex, vector<Edge>()));
        verticesOfGraph.push_back(vertex);
    }

    vector<vector<E>> getMSTs() {
        vector<std::vector<E>> allMSTs;
        map<V, bool> visited;

        for (const auto& vertex : this->getVertices()) {

            // if not visited
            if (visited.find(vertex) == visited.end()) {
                std::vector<E> mstEdges;
                Graph<V, E> mst;
                mst.insertVertex(vertex);
                visited[vertex] = true;
//                priority_queue<pair<E, V>, std::vector<std::pair<E, V>>, std::greater<>> pq;
                BinaryMinHeap<pair<E, V>> pq;

                for (auto& edge : this->outgoingEdges(vertex)) {
                    pq.push({edge, edge.to.name != vertex.name ? edge.to : edge.from});
                }
                while (!pq.empty()) {
                    auto [weight, current] = pq.top();
                    pq.pop();

                    // if already visited
                    if (visited.find(current) != visited.end()) {
                        continue;
                    }

                    visited[current] = true;
                    mstEdges.push_back(weight);
                    mst.insertVertex(current);

                    if (mst.getVertices().size() > 1) {
                        /*auto edgeToMST = this->getEdge(current, mst);
                        if (edgeToMST.cost != -1) {
                            mst.insertEdge(edgeToMST);
                        }*/
                        mst.insertEdge(weight);
                    }
                    for (auto& edge : this->outgoingEdges(current)) {
                        auto destination = edge.to.name != current.name ? edge.to : edge.from;

                        // if not visited
                        if (visited.find(destination) == visited.end()) {
                            pq.push({edge, destination});
                        }
                    }
                }
                allMSTs.push_back(mstEdges);
            }
        }
        return allMSTs;
    }
};

int main() {
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    int N;
    cin >> N;

    Graph<Vertex, Edge> carRental = Graph<Vertex, Edge>();

    for (int i = 0; i < N; ++i) {
        string command;
        cin >> command;
        if (command == "ADD") {
            string name;
            int penalty;
            cin >> name >> penalty;

            carRental.insertVertex({name, penalty});
        } else if (command == "CONNECT") {
            string from, to;
            double distance;
            cin >> from >> to >> distance;
            Edge e;
            Vertex fromV = carRental.findVertex(from);
            Vertex toV = carRental.findVertex(to);
            e.from = fromV;
            e.to = toV;
            e.cost = distance/(fromV.penalty + toV.penalty);
            carRental.insertEdge(e);
        } else if (command == "PRINT_MIN") {
            vector<vector<Edge>> mst = carRental.getMSTs();
            for (auto edges : mst) {
                for (auto e : edges) {
                    cout << e.from.name << ":" << e.to.name << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}