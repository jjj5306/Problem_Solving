/** 플로이드 1956 운동 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int v, e;
int dist[405][405];
const int INF = 0x3f3f3f3f;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> v >> e;

    for (int i = 1; i <= v; i++)
        fill(dist[i], dist[i] + v + 1, INF);

    for (int i = 0; i < e; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = c;
    }

    // 최단경로 탐색 + 사이클까지 필요
    // 플로이드 알고리즘을 통해 a -> b의 모든 최단 거리를 구할 수 있음.
    // 여기서 사이클이라면 b -> a로 오는 경로까지 더해주면 사이클이 됨

    for (int i = 1; i <= v; i++)
        dist[i][i] = 0;

    for (int k = 1; k <= v; k++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
                // i->j를 k를 통해 가는게 더 짧은지
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // a -> b + b-> a가 가장 작은게 답.
    int ans = INF;
    for (int i = 1; i <= v; i++)
        for (int j = 1; j <= v; j++)
            if (i != j)
                ans = min(dist[i][j] + dist[j][i], ans);

    if (ans == INF)
        cout << "-1";
    else
        cout << ans;
}
