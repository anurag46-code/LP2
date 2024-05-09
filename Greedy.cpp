#include <bits/stdc++.h>
using namespace std;

// Function for selection sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_index])
                min_index = j;
        swap(arr[min_index], arr[i]);
    }
}

// Function for Prim's algorithm
void primMST(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> parent(V);
    vector<int> key(V, INT_MAX);
    vector<bool> mstSet(V, false);

    // Priority queue to store vertices with minimum key value
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    parent[0] = -1;
    pq.push({0, 0}); // Pushing source vertex with key 0

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        mstSet[u] = true;

        // Update key value and parent index of adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
                pq.push({key[v], v});
            }
        }
    }

    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
}

int main() {
    int choice;
    do {
        cout << "1. Selection Sort\n2. Prim's Algorithm\n3. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int n;
                cout << "Enter the number of elements: ";
                cin >> n;
                vector<int> arr(n);
                cout << "Enter the elements: ";
                for (int i = 0; i < n; i++)
                    cin >> arr[i];
                selectionSort(arr);
                cout << "Sorted array: ";
                for (int i = 0; i < n; i++)
                    cout << arr[i] << " ";
                cout << "\n";
                break;
            }
            case 2: {
                int V, E;
                cout << "Enter the number of vertices and edges: ";
                cin >> V >> E;
                vector<vector<int>> graph(V, vector<int>(V, 0));
                cout << "Enter the edges (source, destination, weight): \n";
                for (int i = 0; i < E; i++) {
                    int src, dest, weight;
                    cin >> src >> dest >> weight;
                    graph[src][dest] = weight;
                    graph[dest][src] = weight;
                }
                primMST(graph);
                break;
            }
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
