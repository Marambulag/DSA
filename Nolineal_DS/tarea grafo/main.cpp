#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<vector<pair<int, int>>> grafo(14); // Assuming 1-based index and 13 is the highest node

void initializeGraph() {
    grafo[1].push_back({2, 162});
    grafo[1].push_back({3, 72});
    grafo[2].push_back({6, 70});
    grafo[3].push_back({4, 91});
    grafo[3].push_back({5, 128});
    grafo[4].push_back({6, 75});
    grafo[4].push_back({8, 135});
    grafo[4].push_back({5, 103});
    grafo[5].push_back({4, 103});
    grafo[5].push_back({7, 74});
    grafo[6].push_back({12, 50});
    grafo[6].push_back({10, 78});
    grafo[7].push_back({8, 45});
    grafo[8].push_back({4, 135});
    grafo[8].push_back({9, 34});
    grafo[9].push_back({10, 105});
    grafo[9].push_back({11, 52});
    grafo[10].push_back({13, 47});
    grafo[11].push_back({13, 109});
    grafo[12].push_back({13, 44});
}

vector<int> dijkstra(int start, int destination) {
    vector<int> dist(14, INF);     // Distance from start to each node
    vector<int> parent(14, -1);    // To track the shortest path
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start}); // {distance, node}
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        // Debug: Print current node and distance
        cout << "Processing node " << u << " with distance " << d << endl;
        
        if (d > dist[u]) continue; // Ignore outdated entries in the priority queue

        for (auto &edge : grafo[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            // Debug: Print edge information
            cout << "  Checking edge (" << u << " -> " << v << ") with weight " << weight << endl;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
                
                // Debug: Print updated distance
                cout << "  Updated distance for node " << v << " to " << dist[v] << endl;
            }
        }
    }
    
    // Retrieve the path from start to destination (node 13 in this case)
    vector<int> path;
    for (int at = destination; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    
    if (dist[destination] == INF) {
        cout << "No path to node " << destination << endl;
        return {};
    }
    
    cout << "Shortest path to node " << destination << " has a distance of " << dist[destination] << endl;
    return path;
}

int main() {
    initializeGraph();
    int start = 1;         
    int destination = 13;  
    
    vector<int> path = dijkstra(start, destination);
    
    if (!path.empty()) {
        cout << "Path: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    return 0;
}


