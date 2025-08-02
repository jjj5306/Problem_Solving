/** 트리 1967 트리의 지름 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, ans = 0;
bool vis[10010];
vector<pair<int, int>> adj[10010];

// k번째 노드에서 DFS
void func(int k, int len)
{
    // base condition : 딱히 없음 모든 경우에 답 갱신해도 됨
    ans = max(len, ans);

    // 재귀식
    for (auto nxt : adj[k])
    {
        if (vis[nxt.first])
            continue;

        vis[nxt.first] = true;
        func(nxt.first, len + nxt.second);
        vis[nxt.first] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    int u, v, w;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    for (int i = 0; i < n; i++)
    {
        // i번에 대한 다른 모든 간선과의 DFS
        fill(vis, vis + n, 0);
        vis[i] = true;
        func(i, 0);
    }

    cout << ans;
}
