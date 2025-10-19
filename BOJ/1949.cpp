/**  **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n;
int vill[10010], dp[10010][2];
bool vis[10010];
vector<int> adj[10010];

void dfs(int k)
{
    // dp[i][j] = i번째 마을이 일반 마을일 때 / 우수 마을일 때 모든 서브트리를 계산해서 최대의 주민 수를 저장.
    // 점화식 : dp[i][0] = max(dp[nxt][0], dp[nxt][1])
    //         dp[i][1] = dp[nxt][0]
    if (vis[k])
        return;
    dp[k][0] = 0;
    dp[k][1] = vill[k];
    vis[k] = true;

    for (auto nxt : adj[k])
    {
        if (vis[nxt])
            continue;
        // dp 값 갱신 전에 DFS로 제일 끝부터 올라오면서 갱신
        dfs(nxt);
        dp[k][0] += max(dp[nxt][0], dp[nxt][1]);
        dp[k][1] += dp[nxt][0];
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> vill[i];

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);
    cout << max(dp[1][0], dp[1][1]);
}

/*
1. 우수 마을의 수는 정해져있지 않음.
2. 우수 마을 주민 수 합을 최대로 해야함.
3. 우수 마을끼리는 인접 X
4. 일반 마을의 이웃 중 최소 하나는 우수 마을이어야 함.

k번째 마을을 선택해서
1. 인접한 마을은 방문 X로 설정
2. 그 외의 마을들에 대해 방문.
3. 거기서 또 하나의 마을을 선택해서 우수 마을로 선정을 반복
DFS로 하나의 가지에 대해 모든 케이스를 고려해보면서 최대 주민 수를 정하면 됨.
또한 4번 조건은 무조건 가능한 우수 마을은 모두 우수 마을로 만드므로 신경쓰지 않아도 됨.

-> 현재 알고리즘은 시간초과가 남. 메모이제이션이 가능해보임.
case 1) 1번 마을이 우수 마을 -> 1번의 자식을 일반 마을로 설정
case 2) 1번 마을이 일반 마을 -> 1번의 자식은 일반 마을일수도, 우수 마을일수도 있음.
-> dp[i][j] = i번째 마을이 일반 마을일 때 / 우수 마을일 때 모든 서브트리를 계산해서 최대의 주민 수를 저장.
점화식 : dp[i][0] = max(dp[nxt][0], dp[nxt][1])
        dp[i][1] = dp[nxt][0]
계산 방법 : 1번 마을부터 dp[1][0], dp[1][1]을 DFS로 쭉쭉 내려가면서 계산.

*/
