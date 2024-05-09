#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

typedef pair<int, int> pii; // Pair of vertex and weight

class Graph {
private:
    int V;
    vector<vector<pii>> adj;

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Assuming undirected graph
    }

    // Prim's algorithm for MST using priority queue
    void primsMST() {
        priority_queue<pii, vector<pii>, greater<pii>> pq; // Min-Heap for edges (weight, vertex)
        vector<int> key(V, numeric_limits<int>::max()); // Key values used to pick minimum weight edge
        vector<int> parent(V, -1); // Array to store MST

        // Start with vertex 0
        pq.push({0, 0});
        key[0] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Update MST set
            if (parent[u] != -1)
                cout << parent[u] << " - " << u << " : " << key[u] << endl;

            // Update key values and push adjacent vertices to priority queue
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.push({key[v], v});
                }
            }
        }
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph graph(V);

    cout << "Enter edges (source destination weight):\n";
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    cout << "Edges in Minimum Spanning Tree (MST):\n";
    graph.primsMST();

    return 0;
}
