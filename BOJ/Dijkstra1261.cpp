/** 다익스트라 1261 알고스팟 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
#include <queue>
using namespace std;

int n, m;
int dist[105][105], board[105][105];
const int INF = 0x3f3f3f3f;
// 벽을 부수는 횟수만 생각하면 되기에 굳이 vis를 둘 필요가 없음.

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> n;

    for (int i = 1; i <= n; i++)
    {
        // board[i] 입력 받기
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++)
        {
            board[i][j] = s[j - 1] - '0';
        }
    }

    for (int i = 0; i <= n; i++)
        fill(dist[i], dist[i] + m + 1, INF);

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    // 최소 힙. 튜플로 weight, x, y저장
    dist[1][1] = 0;
    pq.push({0, 1, 1});

    while (!pq.empty())
    {
        int cx, cy, cw;
        tie(cw, cx, cy) = pq.top();
        pq.pop();

        if (dist[cx][cy] != cw)
            continue;

        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cx + dx[dir];
            int ny = cy + dy[dir];

            // 다음 칸 유효성 체크
            if (nx > n || nx < 1 || ny > m || ny < 1)
                continue;

            int nw = cw + board[nx][ny]; // nx, ny 까지 갈 때 비용 (부수는 벽의 수)
            if (nw >= dist[nx][ny])
                continue;
            dist[nx][ny] = nw;
            pq.push({nw, nx, ny});
        }
    }

    cout << dist[n][m];
}
