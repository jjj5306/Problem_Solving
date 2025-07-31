/** Tree 20924 트리의 기둥과 가지 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int n, r, giga, ans = 0;
vector<pair<int, int>> tree[200010];
bool vis[200010];

void solve(int cur, int len)
{
    // cur 이웃에 대해 길이 계산

    // base condition : cur이 leaf임
    if (tree[cur].size() == 1 && cur != r)
    {
        ans = max(len, ans);
        return;
    }

    for (auto nxt : tree[cur])
    {
        if (vis[nxt.first])
            continue;

        vis[nxt.first] = true;
        solve(nxt.first, len + nxt.second);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> r;

    if (n == 1 && r == 1)
    {
        cout << "0 0";
        return 0;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }

    // 1. 기가 노드를 찾으며 기둥 길이도 구함

    // 루트에서 간선을 타고가면서 자식 수가 최초로 3개 이상인 곳을 찾으면 됨
    fill(vis, vis + n + 1, 0);
    int cur = r;
    vis[r] = true;

    // 1. 루트가 기가노드인 경우는 while문을 실행하지 않음
    if (tree[cur].size() == 1)
    {

        // 2. 자식이 3개 이상이면 기가노드
        while (tree[cur].size() < 3)
        {
            bool moved = false;
            for (auto nxt : tree[cur])
            {
                if (vis[nxt.first])
                    continue;

                vis[nxt.first] = true;
                ans += nxt.second;
                cur = nxt.first;
                moved = true;
            }
            if (!moved)
                break;
        }
    }
    giga = cur;

    cout << ans << '\n';

    // 2. 기가에서 리프까지 거리 구하기
    // dfs로 하면 됨.
    if (giga == 0)
        ans = 0;
    else
    {
        ans = 0;
        vis[giga] = true;
        solve(giga, 0);
    }

    cout << ans << '\n';
}