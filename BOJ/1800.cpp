/**  **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int n, p, k, ans = -1;
vector<pair<int, int>> adj[1002];

int func(int mid)
{
    // mid보다 크면 weight를 1로 생각
    vector<int> dist(n + 1, 0x7f7f7f7f);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();

        // dist[cur.second]와 우선순위 큐의 정점이 다른 경우
        if (dist[cur.second] < cur.first)
            continue;
        for (auto nxt : adj[cur.second])
        {
            int nxt_cost = cur.first + (nxt.first > mid);
            if (dist[nxt.second] > nxt_cost)
            {
                // 갱신
                dist[nxt.second] = nxt_cost;
                pq.push({nxt_cost, nxt.second});
            }
        }
    }

    return dist[n];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> p >> k;
    for (int i = 0; i < p; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    int left = 0, right = 1000000;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (func(mid) <= k)
        {
            ans = mid;
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    cout << ans;
}

/*
1~N번 연결
K개의 선은 공짜
나머지 선 중 가장 비싼 것을 구하기.

다익스트라 -> ElogE. E=10000
K개의 선이 공짜라서 단순 다익스트라로는 불가능함.

결정 문제로 바꿔서 남은 것 중 최대 비용을 mid로 한다면 연결이 가능한가?를 보면 된다.
1~n까지를 연결해서 mid 초과인 간선을 셌을 때 K 이상이라면?
-> mid는 현재보다 크다.
아니라면 mid는 현재보다 작다.

경로를 구하는 것은. 케이블 비용이 mid 보다 크다면 가중치를 1로 두고, 아니라면 0으로 둬서 다익스트라로 구할 수 있다.

*/
