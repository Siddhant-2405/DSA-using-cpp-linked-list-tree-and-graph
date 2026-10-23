#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int source;
    int destination;
    int cost;
};

// Disjoint Set Union (DSU)
class DSU {
private:
    vector<int> parent;
    vector<int> rankValue;

public:
    DSU(int n) {
        parent.resize(n);
        rankValue.resize(n, 0);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return false;
        }

        if (rankValue[rootX] < rankValue[rootY]) {
            parent[rootX] = rootY;
        }
        else if (rankValue[rootX] > rankValue[rootY]) {
            parent[rootY] = rootX;
        }
        else {
            parent[rootY] = rootX;
            rankValue[rootX]++;
        }

        return true;
    }
};

int main() {
    int V, E;

    cout << "HOSPITAL EQUIPMENT WIRING SYSTEM\n";

    cout << "Enter number of equipment units: ";
    cin >> V;

    if (V <= 0) {
        cout << "Invalid number of equipment units.\n";
        return 0;
    }

    vector<string> equipment(V);

    cout << "\nEnter equipment names:\n";
    for (int i = 0; i < V; i++) {
        cout << "Equipment " << i + 1 << ": ";
        cin >> equipment[i];
    }

    cout << "\nEnter number of possible wiring connections: ";
    cin >> E;

    if (E < 0) {
        cout << "Invalid number of connections.\n";
        return 0;
    }

    vector<Edge> edges;

    cout << "\nEnter connections using equipment numbers "
         << "and wiring cost.\n";

    cout << "Example: 1 2 100\n";

    for (int i = 0; i < E; i++) {
        int u, v, cost;

        cout << "Connection " << i + 1 << ": ";
        cin >> u >> v >> cost;

        if (u < 1 || u > V ||
            v < 1 || v > V ||
            u == v || cost < 0) {
            cout << "Invalid connection. Enter it again.\n";
            i--;
            continue;
        }

        edges.push_back({u - 1, v - 1, cost});
    }

    // Sort edges by increasing cost
    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b) {
             return a.cost < b.cost;
         });

    DSU dsu(V);

    vector<Edge> selectedEdges;
    vector<Edge> rejectedEdges;

    int totalCost = 0;

    // Apply Kruskal's Algorithm
    for (const Edge &edge : edges) {
        if (dsu.unite(edge.source, edge.destination)) {
            selectedEdges.push_back(edge);
            totalCost += edge.cost;
        }
        else {
            rejectedEdges.push_back(edge);
        }
    }

    cout << "\n========== SELECTED WIRING CONNECTIONS ==========\n";

    for (const Edge &edge : selectedEdges) {
        cout << equipment[edge.source] << " -- "
             << equipment[edge.destination]
             << " : Cost = " << edge.cost << "\n";
    }

    cout << "\nTotal Minimum Wiring Cost = "
         << totalCost << "\n";

    if (selectedEdges.size() != static_cast<size_t>(V - 1)) {
        cout << "\nWarning: All equipment units cannot be connected "
             << "because the graph is disconnected.\n";
    }

    cout << "\n========== REJECTED EDGES (CYCLES) ==========\n";

    if (rejectedEdges.empty()) {
        cout << "No edges were rejected due to cycles.\n";
    }
    else {
        for (const Edge &edge : rejectedEdges) {
            cout << equipment[edge.source] << " -- "
                 << equipment[edge.destination]
                 << " : Cost = " << edge.cost
                 << " (Rejected: Creates a cycle)\n";
        }
    }

    return 0;
}
