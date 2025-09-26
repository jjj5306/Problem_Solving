#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <set>
using namespace std;

int n, q, cnt = 1;
int board[20][20];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
bool vis[20][20]; // for bfs
int group[55];
// 군집 크기 저장용. 가장 큰 군집 중 가장 먼저 온 군집을 알아야 함.
// 따라서 set으로 {-크기, index} 저장 -> 구현 복잡도 증가 및 어차피 이미 있는 군집인지 체크하려면 map을 쓰던가 순회를 하던가 해야하는데 그것도 똑같이 O(q) 이므로
// 간단하게 일반 배열로 선언하고 매 번 순회를 돌면서 가장 큰 크기 찾기.

int bfs(int i, int j)
{
    // k번 미생물의 크기 리턴
    int k = board[i][j], rt = 1;

    queue<pair<int, int>> q;
    q.push({i, j});
    vis[i][j] = true;

    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];

            // 유효성 체크
            if (nx >= n || ny >= n || nx < 0 || ny < 0)
                continue;
            if (vis[nx][ny] || board[nx][ny] != k)
                continue;

            rt++;
            q.push({nx, ny});
            vis[nx][ny] = true;
        }
    }
    return rt;
}

void erase_(int k)
{
    // k번 군집이면 0으로 만들기
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == k)
                board[i][j] = 0;
    // BFS로 개선 가능
}

bool can_move(int x, int y, int i, int j, int (&tmp)[20][20])
{
    // board[x][y] -> tmp[i][j] 가능한지 체크
    // cout << "****** " << board[x][y] << ' ' << x << ' ' << y << ' ' << i << ' ' << j << '\n';
    for (int r = 0; r < n; r++)
    {
        for (int q = 0; q < n; q++)
        {
            if (board[q][r] != board[x][y])
                continue;
            // q-x, r-y가 i, j가 되어야 함
            if ((q - x + i) >= n || (r - y + j) >= n || (q - x + i) < 0 || (r - y + j) < 0 || tmp[q - x + i][r - y + j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void move(int k, int x, int y, int (&tmp)[20][20])
{
    // k번 군집을 tmp로 옮기기
    // x좌표가 최대한 작은 것. -> 열이 가장 작은 것
    // 겹친다면 y좌표가 가장 작은 것. -> 행이 가장 큰 것 (상하반전을 해야 예시와 똑같이 출력되므로)
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            //(x, y) -> (i, j)에 옮길 수 있는지

            if (can_move(x, y, i, j, tmp))
            {
                // cout << "****** " << board[x][y] << ' ' << x << ' ' << y << ' ' << i << ' ' << j << '\n';
                // 옮기기
                for (int q = 0; q < n; q++)
                {
                    for (int r = 0; r < n; r++)
                    {
                        if (board[q][r] == board[x][y])
                            tmp[q - x + i][r - y + j] = board[x][y];
                    }
                }
                return;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int r1, r2, c1, c2;
    cin >> n >> q;

    while (q--)
    {
        // 실험 1회 진행
        // 1. 미생물 투입
        cin >> c1 >> r1 >> c2 >> r2;
        // board[r1][c1]부터 board[r2-1][c2-1]을 채우는 것.

        for (int i = r1; i < r2; i++)
            for (int j = c1; j < c2; j++)
                board[i][j] = cnt;

        cnt++;

        // 투입 완료. 미생물 소각 판단 -> BFS. 어차피 추후 군집의 크기가 필요하므로 BFS + 크기 저장
        fill(group, group + 55, 0);
        for (int i = 0; i < n; i++)
            fill(vis[i], vis[i] + n, false);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] != 0 && !vis[i][j])
                {
                    // 방문하지 않았고, 미생물이 있음.
                    // 해당 칸의 크기가 이미 재져있다면 소각 대상
                    if (group[board[i][j]] != 0)
                        erase_(board[i][j]);
                    else
                        group[board[i][j]] = bfs(i, j);
                }
            }
        }

        // 2. 배양 용기 이동
        int tmp[20][20]; // 새로운 용기
        for (int i = 0; i < 20; i++)
            fill(tmp[i], tmp[i] + 20, 0);

        bool vis2[55] = {
            false,
        }; // 미생물 옮겼는지

        for (int k = 1; k < cnt; k++)
        {
            // 총 cnt번 옮겨야 함
            // 어떤 미생물 옮길지
            int target = -1, max_size = -1;
            for (int iter = 1; iter < cnt; iter++)
                if (group[iter] > max_size && !vis2[iter])
                {
                    max_size = group[iter];
                    target = iter;
                }

            if (target == -1)
                continue;

            vis2[target] = true;
            // target의 제일 왼쪽 하단을 알아야 함.
            int start_i = -1, start_j = -1;
            bool found = false;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (board[i][j] == target)
                    {
                        start_i = i;
                        start_j = j;
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
            }

            // target 옮기기
            if (start_i != -1)
            {
                move(target, start_i, start_j, tmp);
            }
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                board[i][j] = tmp[i][j];

        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         cout << board[i][j] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << "\n";

        // 3. 실험 결과 기록
        // 무리 중 상하좌우 맞닿은 면이 있는 무리를 구한다.
        // 모든 칸을 순회하며 상하좌우 확인. 맞닿은 면이 있다면 -> set에 추가하여 중복 방지
        int ans = 0;
        set<pair<int, int>> adj;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 0)
                    continue;
                for (int dir = 0; dir < 4; dir++)
                {
                    int ni = i + dx[dir];
                    int nj = j + dy[dir];

                    if (ni < 0 || ni >= n || nj < 0 || nj >= n)
                        continue;

                    if (board[i][j] == board[ni][nj] || board[ni][nj] == 0)
                        continue;

                    if (adj.find({board[i][j], board[ni][nj]}) != adj.end() || adj.find({board[ni][nj], board[i][j]}) != adj.end())
                        continue;

                    adj.insert({board[i][j], board[ni][nj]});
                    ans += group[board[i][j]] * group[board[ni][nj]];
                }
            }
        }
        cout << ans << '\n';
    }
}
