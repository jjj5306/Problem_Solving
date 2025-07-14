/** 다익스트라 1504 특정한 최단 경로 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int n, e, s, v;
vector<pair<int, int>> adj[805];
const int INF = 0x1f1f1f1f;
int dist[805];

int dijkstra(int st, int en)
{
    // st~en 까지 가야함.
    fill(dist, dist + n + 1, INF);
    // 다익스트라 알고리즘 시작
    // 우선순위 큐 최소 힙 선언. weight, node 저장
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // start 집어 넣기
    pq.push({0, st});
    dist[st] = 0;

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        if (dist[cur.second] != cur.first)
            continue;

        for (auto nxt : adj[cur.second])
        {
            // cur의 이웃 노드 현재 최단 거리와 cur -> nxt 비교하여 cur -> nxt가 더 멀면 체크 X
            if (dist[nxt.second] < dist[cur.second] + nxt.first)
                continue;
            dist[nxt.second] = dist[cur.second] + nxt.first;
            pq.push({dist[nxt.second], nxt.second});
        }
    }

    if (dist[en] == INF)
        return -1;
    else
        return dist[en];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> e;

    while (e--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({c, b});
        adj[b].push_back({c, a});
    }

    cin >> s >> v;

    int ans1 = dijkstra(1, s) + dijkstra(s, v) + dijkstra(v, n);
    int ans2 = dijkstra(1, v) + dijkstra(v, s) + dijkstra(s, n);

    int ans = min(ans1, ans2);
    if (ans >= INF)
        cout << -1;
    else
        cout << ans;
}
