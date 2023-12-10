#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    int to;
    long long weight;
};

long long dijkstra(const vector<vector<Edge>> &graph, int start, int end) {
    int n = graph.size();
    vector<long long> dist(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        long long u_dist = pq.top().first;
        pq.pop();

        if (u_dist > dist[u]) {
            continue;
        }

        for (const Edge &e : graph[u]) {
            int v = e.to;
            long long weight = e.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[end];
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    in >> n >> m;

    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        in >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    in.close();

    long long shortestPath = dijkstra(graph, 1, n);
    out << shortestPath << endl;

    out.close();

    return 0;
}
