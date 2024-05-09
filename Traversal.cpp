#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest, weight;
};

class DisjointSet {
private:
    vector<int> parent;

public:
    DisjointSet(int size) {
        parent.resize(size, -1); // Initialize all elements with -1, indicating they are roots
    }

    // Find the root of the set containing the element
    int find(int element) {
        if (parent[element] == -1)
            return element;
        return find(parent[element]);
    }

    // Merge two sets containing elements a and b
    void merge(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB)
            parent[rootA] = rootB; // Set root of A's tree as B's root
    }
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int v, int e) : V(v), E(e) {}

    // Function to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        Edge edge;
        edge.src = src;
        edge.dest = dest;
        edge.weight = weight;
        edges.push_back(edge);
    }

    // Function to find MST using Kruskal's algorithm
    void kruskalMST() {
        // Sort edges in increasing order of their weights
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });

        // Create disjoint set for vertices
        DisjointSet ds(V);

        vector<Edge> result; // Stores the MST edges
        int edgeCount = 0;
        for (const Edge& edge : edges) {
            if (edgeCount >= V - 1) // MST has V-1 edges
                break;

            int srcRoot = ds.find(edge.src);
            int destRoot = ds.find(edge.dest);

            if (srcRoot != destRoot) {
                result.push_back(edge);
                ds.merge(srcRoot, destRoot);
                edgeCount++;
            }
        }

        // Print the MST edges
        cout << "Edges in MST:\n";
        for (const Edge& edge : result) {
            cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph graph(V, E);

    cout << "Enter edges (source destination weight):\n";
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    graph.kruskalMST();

    return 0;
}
