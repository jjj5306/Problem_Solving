/** 다익스트라 11779 최소비용 구하기 2 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int v, e, st, en;

vector<pair<int, int>> adj[1005];
const int INF = 0x3f3f3f3f;
int d[1005];   // 최단 거리 테이블
int pre[1005]; // 경로 복원 테이블

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> v >> e;
    fill(d, d + v + 1, INF);

    while (e--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // 최소 힙

    cin >> st >> en;
    d[st] = 0;
    pq.push({d[st], st});

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();

        // d[cur]과 우선순위 큐 정점이 다른 경우
        if (d[cur.second] != cur.first)
            continue;
        for (auto nxt : adj[cur.second])
        {
            if (d[nxt.second] <= d[cur.second] + nxt.first)
                continue;
            // cur을 거쳐 nxt로 가는게 더 가까운 경우
            d[nxt.second] = d[cur.second] + nxt.first;
            pq.push({d[nxt.second], nxt.second});

            // d가 업데이트 될 때 pre 업데이트
            pre[nxt.second] = cur.second;
        }
    }

    cout << d[en] << '\n';

    deque<int> ans;
    int cur = en;
    while (cur != st)
    {
        ans.push_front(cur);
        cur = pre[cur];
    }
    ans.push_front(cur);

    cout << ans.size() << '\n';
    for (auto x : ans)
        cout << x << ' ';
}
