/** 플로이드 11562 백양로 브레이크 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, m;
int dist[255][255];
const int INF = 0x3f3f3f3f;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i <= n; i++)
        fill(dist[i], dist[i] + n + 1, INF);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        // c=0인 경우 단방향
        // 단방향의 길인 경우 a->b는 그냥 이동할 수 있지만 b->a는 1의 비용을 지불해야 갈 수 있음
        if (c == 0)
        {
            dist[a][b] = 0;
            dist[b][a] = 1;
        }
        else
        {
            dist[a][b] = 0;
            dist[b][a] = 0;
        }
    }

    for (int i = 0; i <= n; i++)
        dist[i][i] = 0;

    // a->b로 길이 존재하는 경우 그냥 가면 됨. 비용이 0이 될 것
    // a->b로 길이 없는 경우 바꾸면서 가야함.
    // 논리의 흐름이 최단 경로를 구하는 것과 동일함.
    for (int k = 1; k <= n; k++)
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);

    int k;
    cin >> k;
    while (k--)
    {
        int u, v;
        cin >> u >> v;
        cout << dist[u][v] << '\n';
    }
}
