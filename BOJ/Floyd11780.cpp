/** 최단거리 11780 플로이드2 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, m;
int dist[105][105];
int nxt[105][105];
const int INF = 0x3f3f3f3f;

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
        dist[a][b] = min(dist[a][b], c);
        // nxt도 초기화. 첫 단계이므로 a->b 간선이 있으면 nxt[a][b] = b
        nxt[a][b] = b;
    }

    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    // k번째 원소가 중간에 거치는 원소
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                // k 번째 원소를 거치는 경우가 더 최단 거리인 경우
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    // nxt[i][j] = i -> j 로 갈 때 가장 먼저 방문할 노드이므로 nxt[i][k] 저장
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j] = nxt[i][k];
                }
            }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] == INF)
                cout << "0 ";
            else
                cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] == 0 || dist[i][j] == INF)
            {
                cout << "0\n";
                continue;
            }

            vector<int> path;
            int st = i;
            while (st != j)
            {
                path.push_back(st);
                st = nxt[st][j];
            }
            path.push_back(j);
            cout << path.size() << ' ';

            for (auto x : path)
                cout << x << ' ';
            cout << '\n';
        }
    }
}
