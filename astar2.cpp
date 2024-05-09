#include <bits/stdc++.h>
using namespace std;
// Node class
class Node
{
public:
    int x, y;      // Node position
    int f, g, h;   // f = g + h
    bool obstacle; // Is the node an obstacle?
    bool closed;   // Is the node closed?
    Node *parent;  // Parent node

    Node(int x, int y, bool obstacle = false) : x(x), y(y), obstacle(obstacle), closed(false), parent(nullptr) {}

    bool isObstacle() const { return obstacle; }
};

// Function to calculate the heuristic
int heuristic(Node *start, Node *end)
{
    return abs(start->x - end->x) + abs(start->y - end->y);
}

// A* algorithm
vector<Node *> aStar(vector<vector<Node>> &grid, Node *start, Node *end)
{
    // Priority queue of nodes to visit, sorted by f value
    auto compareNodes = [](Node *a, Node *b)
    { return a->f > b->f; };
    priority_queue<Node *, vector<Node *>, decltype(compareNodes)> openList(compareNodes);
    set<Node *> openSet; // Additional data structure to keep track of nodes in the open list

    // Add the start node to the open list
    start->g = 0;
    start->h = heuristic(start, end);
    start->f = start->g + start->h;
    openList.push(start);
    openSet.insert(start); // Add to the open set

    while (!openList.empty())
    {
        // Get the node with the lowest f value
        Node *current = openList.top();
        openList.pop();

        // If this node is the end node, we have found a solution
        if (current == end)
        {
            // Reconstruct the path and return
            vector<Node *> path;
            while (current != nullptr)
            {
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Mark the node as closed
        current->closed = true;

        // Generate children
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                // Skip the parent node
                if (dx == 0 && dy == 0)
                    continue;

                int x = current->x + dx;
                int y = current->y + dy;

                // Check if the position is valid
                if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size())
                {
                    Node *child = &grid[x][y];

                    // Check if the node is not an obstacle and not closed
                    if (!child->isObstacle() && !child->closed)
                    {
                        // Calculate g, h, and f
                        int g = current->g + 1;
                        int h = heuristic(child, end);
                        int f = g + h;

                        // If the child is in the open list and the g is higher, skip
                        if (openSet.find(child) != openSet.end() && g >= child->g)
                            continue;
                        child->parent = current;
                        child->g = g;
                        child->h = h;
                        child->f = f;
                        openList.push(child);
                        openSet.insert(child); // Add to the open set
                    }
                }
            }
        }
    }

    // No solution found
    return {};
}

void displayGrid(const vector<vector<Node>> &grid)
{
    vector<Node> obstacles;
    for (const auto &row : grid)
    {
        for (const auto &node : row)
        {
            if (node.obstacle)
            {
                cout << "0 ";
                obstacles.push_back(node);
            }
            else
            {
                cout << "1 ";
            }
        }
        cout << '\n';
    }
    cout<<'\n';
    for(auto &node: obstacles){
        cout << "Obstacle at: (" << node.x << ", " << node.y << ")\n";
    }
    cout<<'\n';
}

int main()
{
    // Create a 10x10 grid
    vector<vector<Node>> grid(10, vector<Node>(10, Node(0, 0)));

    // Initialize the grid nodes with their correct positions
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            grid[i][j] = Node(i, j);
            if ((i == 5 && j > 2 && j < 7) || (j == 5 && i > 2 && i < 7))
            {
                grid[i][j].obstacle = true;
            }
        }
    }

    // Set start and end nodes
    Node *start = &grid[0][0];
    Node *end = &grid[9][9];

    // Call the A* function
    vector<Node *> path = aStar(grid, start, end);
    // Display the grid
    displayGrid(grid);
    // Print the path
    if (!path.empty())
    {
        cout << "Path found:\n";
        for (Node *node : path)
        {
            cout << "(" << node->x << ", " << node->y << ")\n";
        }
    }
    else
    {
        cout << "No path found.\n";
    }

    return 0;
}