/** 3109 빵집 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int r, c;
char board[10010][503];
bool vis[10010][503];
int ans = 0;
// 방향 정의 대각선 위, 오른쪽, 대각선 아래
int dx[3] = {-1, 0, 1};
int dy[3] = {1, 1, 1};
bool is_success = false; // 현재 재귀가 성공했는지 아닌지

void func(int i, int j)
{
    // i행 j열부터 dfs
    if (is_success)
        return;

    // base condition : 탐색 완료
    if (j == c - 1)
    {
        ans++;
        is_success = true;
        return;
    }

    for (int dir = 0; dir < 3; dir++)
    {
        int nx = i + dx[dir];
        int ny = j + dy[dir];
        // 유효성 체크
        if (nx < 0 || ny < 0 || nx >= r || ny >= c || board[nx][ny] != '.')
            continue;
        // 방문체크
        if (vis[nx][ny])
            continue;

        vis[nx][ny] = true;
        func(nx, ny);
        // 다음 방향 체크 전에 성공했으면 더 이상 진행 X
        if (is_success)
            return;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < c; j++)
            board[i][j] = s[j];
    }

    // 0행부터 0열의 원소를 시작으로 DFS. 방향 우선순위는 대각선 위, 오른쪽, 대각선 아래
    // 다만, 그리디하게 가다가 경로가 실패한채로 끝났다면 백트래킹해서 이전 단계도 가봐야함.
    // 대신 한 번 방문한 곳은 방문하지 않아도 됨

    for (int i = 0; i < r; i++)
    {
        vis[i][0] = true;
        is_success = false;
        func(i, 0);
    }

    // for (int i = 0; i < r; i++)
    // {
    //     for (int j = 0; j < c; j++)
    //         cout << board[i][j] << ' ';
    //     cout << '\n';
    // }

    cout << ans;
}
