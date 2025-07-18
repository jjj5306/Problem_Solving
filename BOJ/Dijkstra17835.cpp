/** 다익스트라 17835 면접보는 승범이네 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int n, m, k;
vector<pair<long long, int>> adj[100005];
long long dist[100005];
const long long INF = 0x7f7f7f7f7f7f;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // 일반적인 다익스트라라면 모든 도시에 대해 K번 도시까지의 구해야 함. -> 시간 초과
    // 그렇다면 반대로 면접장 -> 다른 모든 도시는 한 번의 다익스트라로 가능.
    // 하지만 면접장이 여러 개임. 즉, 시작점이 여러 개지만 특별히 다른 점 없이 모든 면접장을 우선순위 큐에 넣으면
    // 한 면접장에서 다른 도시까지의 거리를 구할 수 있음.
    // 그렇다면 왜 간선을 뒤집어서 생각해야 할까? 다른 도시 -> 면접장을 한 번의 다익스트라로는 풀 수 없을까?
    // 한 도시 -> 면접장은 모든 출발점에서 특정 면접장까지의 거리를 구하는 것임. 이는 다익스트라를 N번 적용시켜야 함을 뜻함.
    // 반면 뒤집어서 면접장 -> 모든 도시는 다익스트라와 동일함.

    cin >> n >> m >> k;

    fill(dist, dist + n + 1, INF);

    while (m--)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        // 실제로는 a -> b 지만 b -> a로 저장
        adj[b].push_back({c, a});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    while (k--)
    {
        int a;
        cin >> a;
        pq.push({0, a});
        dist[a] = 0;
    }

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        if (cur.first != dist[cur.second])
            continue;

        for (auto nxt : adj[cur.second])
        {
            if (dist[nxt.second] <= cur.first + nxt.first)
                continue;
            dist[nxt.second] = cur.first + nxt.first;
            pq.push({dist[nxt.second], nxt.second});
        }
    }

    long long ans = dist[1], ans_idx = 1;
    for (int i = 2; i <= n; i++)
    {
        if (dist[i] > ans)
        {
            ans = dist[i];
            ans_idx = i;
        }
    }
    cout << ans_idx << '\n'
         << ans;
}
