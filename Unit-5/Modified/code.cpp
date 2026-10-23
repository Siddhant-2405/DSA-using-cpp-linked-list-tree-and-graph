#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Edge {
    int source, destination, weight;
};

class DSU {
    vector<int> parent, rankValue;

public:
    DSU(int n) {
        parent.resize(n);
        rankValue.assign(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y)
            return false;

        if (rankValue[x] < rankValue[y])
            swap(x, y);

        parent[y] = x;

        if (rankValue[x] == rankValue[y])
            rankValue[x]++;

        return true;
    }
};

void kruskal(int V, vector<Edge> edges,
             const vector<string>& equipment) {
    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) {
             return a.weight < b.weight;
         });

    DSU dsu(V);
    int totalCost = 0;
    int selectedCount = 0;

    cout << "\n--- MINIMUM SPANNING TREE ---\n";
    cout << "Selected Edges:\n";

    for (const Edge& e : edges) {
        if (dsu.unite(e.source, e.destination)) {
            totalCost += e.weight;
            selectedCount++;

            cout << equipment[e.source] << " -- "
                 << equipment[e.destination]
                 << " | Weight: " << e.weight
                 << " | Running Total: " << totalCost
                 << "\n";
        }
        else {
            cout << "Rejected: "
                 << equipment[e.source] << " -- "
                 << equipment[e.destination]
                 << " | Weight: " << e.weight
                 << " (Creates a cycle)\n";
        }
    }

    cout << "\nTotal Wiring Cost: " << totalCost << "\n";

    if (selectedCount == V - 1)
        cout << "A spanning tree can be formed.\n";
    else
        cout << "Graph is disconnected. "
             << "A spanning tree cannot be formed.\n";
}

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

    cout << "Enter equipment names:\n";
    for (int i = 0; i < V; i++) {
        cout << "Equipment " << i + 1 << ": ";
        cin >> equipment[i];
    }

    cout << "Enter number of wiring connections: ";
    cin >> E;

    if (E < 0) {
        cout << "Invalid number of connections.\n";
        return 0;
    }

    vector<Edge> edges;

    cout << "Enter connections as: source destination weight\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;

        cout << "Connection " << i + 1 << ": ";
        cin >> u >> v >> w;

        if (u < 1 || u > V || v < 1 || v > V ||
            u == v || w < 0) {
            cout << "Invalid connection. Try again.\n";
            i--;
            continue;
        }

        edges.push_back({u - 1, v - 1, w});
    }

    // Run Kruskal's algorithm initially
    kruskal(V, edges, equipment);

    // Modification A: Update an edge weight
    char choice;

    cout << "\nDo you want to update an edge weight? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int u, v, newWeight;
        bool found = false;

        cout << "Enter the two equipment numbers: ";
        cin >> u >> v;

        cout << "Enter the new weight: ";
        cin >> newWeight;

        if (u < 1 || u > V || v < 1 || v > V ||
            u == v || newWeight < 0) {
            cout << "Invalid update details.\n";
            return 0;
        }

        for (Edge& e : edges) {
            if ((e.source == u - 1 && e.destination == v - 1) ||
                (e.source == v - 1 && e.destination == u - 1)) {
                e.weight = newWeight;
                found = true;
                break;
            }
        }

        if (found) {
            cout << "\nRecalculating after weight update...\n";
            kruskal(V, edges, equipment);
        }
        else {
            cout << "Connection not found. No update performed.\n";
        }
    }

    return 0;
}
