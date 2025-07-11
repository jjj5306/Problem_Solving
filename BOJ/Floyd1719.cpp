/** 플로이드 1719 택배 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int INF = 0x3f3f3f3f;
int n, m;
int dist[205][205];
int nxt[205][205];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        fill(dist[i], dist[i] + n + 1, INF);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = c;
        dist[b][a] = c;
        nxt[a][b] = b;
        nxt[b][a] = a;
    }

    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    // 경유하는 경우가 더 좋은 경우
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                cout << "- ";
            else
                cout << nxt[i][j] << ' ';
        }
        cout << '\n';
    }
}
