#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Depth First Search (Recursive)
    void dfsRecursiveUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int i : adj[v]) {
            if (!visited[i])
                dfsRecursiveUtil(i, visited);
        }
    }

    void dfsRecursive(int start) {
        vector<bool> visited(V, false);
        dfsRecursiveUtil(start, visited);
    }

    // Depth First Search (Iterative)
    void dfsIterative(int start) {
        vector<bool> visited(V, false);
        stack<int> stack;

        stack.push(start);

        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();

            if (!visited[v]) {
                cout << v << " ";
                visited[v] = true;

                for (int i : adj[v]) {
                    if (!visited[i])
                        stack.push(i);
                }
            }
        }
    }

    // Breadth First Search (Recursive)
    void bfsRecursiveUtil(queue<int>& q, vector<bool>& visited) {
        if (q.empty())
            return;

        int v = q.front();
        q.pop();
        cout << v << " ";

        for (int i : adj[v]) {
            if (!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }

        bfsRecursiveUtil(q, visited);
    }

    void bfsRecursive(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        bfsRecursiveUtil(q, visited);
    }

    // Breadth First Search (Iterative)
    void bfsIterative(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int i : adj[v]) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
};

int main() {
    int V = 5; // Number of vertices
    Graph g(V);

    // Adding edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    cout << "Depth First Search (Recursive): ";
    g.dfsRecursive(0);
    cout << endl;

    cout << "Depth First Search (Iterative): ";
    g.dfsIterative(0);
    cout << endl;

    cout << "Breadth First Search (Recursive): ";
    g.bfsRecursive(0);
    cout << endl;

    cout << "Breadth First Search (Iterative): ";
    g.bfsIterative(0);
    cout << endl;

    return 0;
}
