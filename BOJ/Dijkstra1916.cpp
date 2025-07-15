/** 다익스트라 1916 최소비용 구하기 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
int n, m, u, v;
vector<pair<int, int>> adj[1005];
int dist[1005];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({c, b});
    }
    fill(dist, dist + n + 1, INF);
    cin >> u >> v;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[u] = 0;
    pq.push({0, u});

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        if (cur.first != dist[cur.second])
            continue;

        for (auto nxt : adj[cur.second])
        {
            if (dist[nxt.second] <= dist[cur.second] + nxt.first)
                continue;
            dist[nxt.second] = dist[cur.second] + nxt.first;
            pq.push({dist[nxt.second], nxt.second});
        }
    }

    cout << dist[v];
}
