#include <bits/stdc++.h>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjList;

public:
    Graph(int vertices) {
        adjList.resize(vertices);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void BFSRecursive(queue<int>& q, unordered_set<int>& visited) {
        if (q.empty()) return;

        int current = q.front();
        q.pop();
        cout << current << " ";

        for (int neighbor : adjList[current]) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }

        BFSRecursive(q, visited);
    }

    void BFS(int start) {
        unordered_set<int> visited;
        queue<int> q;
        q.push(start);
        visited.insert(start);

        cout << "BFS traversal starting from node " << start << ": ";
        BFSRecursive(q, visited);
        cout << endl;
    }

    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(adjList.size(), false);
        cout << "DFS traversal starting from node " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }
};

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices and edges: ";
    cin >> vertices >> edges;

    Graph g(vertices);

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter the start node for traversal: ";
    cin >> start;

    g.BFS(start);
    g.DFS(start);

    return 0;
}
