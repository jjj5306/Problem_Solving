/** 플로이드 1507 궁금한 민호 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n;
int dist[25][25];
int adj[25][25];
int ans = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> dist[i][j];
            adj[i][j] = dist[i][j];
        }

    // i -> j의 최단 경로와 i -> k -> j 경로를 비교.
    // 1번 케이스 : dist[i][j]가 더 큼 : 잘못됨. dist[i][j]가 더 크다면 최단 경로는 dist[i][k]+dist[k][j]를 썼어야 함.
    // 2번 케이스 : 두 값이 같음 : dist[i][j]는 직접적인 간선이 없고 k를 경유하는 간선임
    // 3번 케이스 : dist[i][k] + dist[k][j]가 더 큼 : 직접적인 간선이 존재함
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            // k는 i와 같으면 안됨. 1 -> 1 -> 2를 체크하는 경우 무조건 값이 1->2와 같아짐. 그렇다면 1->2 간선이 존재하던 아니던 없애버림
            if (k == i)
                continue;
            for (int j = 1; j <= n; j++)
            {
                // k는 j와도 같으면 안됨. i와 j가 같은 경우는 굳이 체크할 필요가 없음
                if (k == j || i == j)
                    continue;

                int cur = dist[i][k] + dist[k][j];
                if (dist[i][j] > cur)
                {
                    // 1번 케이스
                    cout << "-1";
                    return 0;
                }
                else if (dist[i][j] == cur)
                {
                    // 2번 케이스. 간선 제거
                    adj[i][j] = 0;
                    adj[j][i] = 0;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            ans += adj[i][j];
    cout << ans / 2;
}
