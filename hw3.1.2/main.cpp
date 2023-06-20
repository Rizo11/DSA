#include <bits/stdc++.h>

using namespace std;

const int INF = 100000; // maximum value of edge weight
const int INT_MAX1= 1000000;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    // V-> Number of vertices, E-> Number of edges
    int V, E;

    // graph is represented as an array of edges.
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[graph->E];
    return graph;
}

bool isNegCycleBellmanFord(struct Graph* graph, int src, int n)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Step 1: Initialize distances from src
    // to all other vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX1;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times.
    // A simple shortest path from src to any
    // other vertex can have at-most |V| - 1
    // edges
    vector<int> parent(n, -1);// initialize previous vertex array to -1

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (abs(weight) == INF) {
                continue;
            }

            if (dist[u] != INT_MAX1 && dist[u] + weight < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: check for negative-weight cycles.
    // The above step guarantees shortest distances
    // if graph doesn't contain negative weight cycle.
    // If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (abs(weight) == INF) {
            continue;
        }
        vector<int> out = vector<int>();
        if (dist[u] != INT_MAX1 && dist[u] + weight < dist[v]) {
            out.push_back(u);
            int iter = parent[u];
            while (n-- || iter != u) {
                out.push_back(iter);
                iter = parent[iter];
            }

            out.reserve(out.size());
            for (int j = 0; j < out.size(); ++j) {
                cout << out[j] << " ";
            }
            return true;
        }
    }

    return false;
}


int main() {
    int n = 0;
    cin >> n; // read number of vertices
    vector<int> prev(n, -1); // initialize previous vertex array to -1
    struct Graph* graph = createGraph(n, n);

    // read adjacency matrix and store graph
    int weight = 0;
    int counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> weight;
            graph->edge[counter].src = i;
            graph->edge[counter].dest = j;
            graph->edge[counter].weight = weight;
            counter++;
        }
    }

    // run Bellman-Ford algorithm to detect negative cycles
    if (isNegCycleBellmanFord(graph, 0, n))
        cout << "Yes";
    else
        cout << "No";

    return 0;
}
