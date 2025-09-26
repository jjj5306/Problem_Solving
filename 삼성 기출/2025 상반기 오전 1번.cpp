#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <tuple>
#include <queue>
using namespace std;

int n, t;
string food[52][52];
int board[52][52];
int is_leader[52][52]; // 리더라면 그 그룹의 크기. 아니라면 0
bool vis[52][52];
bool is_unvalid[52][52];          // valid한 경우만 해당 턴에서 전파자가 됨. 즉, 방어 상태임을 표시함.
set<tuple<int, int, int, int>> s; // 리더의 정보를 음식 종류(단일인지) / 신앙심 / 행 / 열 저장

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool is_valid(int x, int y)
{
    return (x <= n && y <= n && x > 0 && y > 0);
}

int get_food_type(string f)
{
    // 단일 음식이면 1
    // 이중이면 2
    // 삼중이면 3
    if (f.length() == 1)
        return 1;
    else if (f.length() == 2)
        return 2;
    else
        return 3;
}

void bfs(int i, int j)
{
    string target = food[i][j];     // 같은 그룹으로 판단할 타겟
    pair<int, int> leader = {i, j}; // 초기 i, j를 리더로 설정
    int cnt = 1;                    // 그룹의 크기

    // BFS 시작
    vis[i][j] = true;
    queue<pair<int, int>> q;
    q.push({i, j});

    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if (!is_valid(nx, ny))
                continue;
            if (vis[nx][ny] || food[nx][ny] != target)
                continue;

            cnt++;
            vis[nx][ny] = true;
            q.push({nx, ny});

            // 리더 판단. 조건은 1. nx, ny가 더 큼. 2. 같은데 행이 더 작음. 3. 같은데 열이 더 작음
            if (board[leader.first][leader.second] < board[nx][ny] || (board[leader.first][leader.second] == board[nx][ny] && nx < leader.first) || (board[leader.first][leader.second] == board[nx][ny] && nx == leader.first && ny < leader.second))
                leader = {nx, ny};
        }
    }

    is_leader[leader.first][leader.second] = cnt;
}

void trans_defense_mode(int i, int j)
{
    // i, j를 방어 모드로 변경.
    is_unvalid[i][j] = true;
}

void strong_propagate(int &x, int i, int j, int cx, int cy)
{
    // cout << "process strong propagate : " << i << ", " << j << " -> " << cx << ", " << cy << " / cur x : " << x << '\n';
    // i, j에서 전파를 진행해서 cx, cy에 강한 전파를 하면 됨. 현재 신앙심은 x
    food[cx][cy] = food[i][j];
    board[cx][cy]++;
    x -= board[cx][cy];
}

void weak_propagate(int &x, int i, int j, int cx, int cy)
{
    // cout << "process weak propagate : " << i << ", " << j << " -> " << cx << ", " << cy << " / cur x : " << x << '\n';

    // i, j에서 전파를 진행해서 cx, cy에 약한 전파를 하면 됨. 현재 신앙심은 x

    // 1. 전파 대상은 전파자가 전파한 음식의 모든 기본 음식에도 관심을 가지게 됨.
    string str = food[cx][cy];
    for (char c1 : food[i][j])
    {
        for (char c2 : food[cx][cy])
        {
            if (c1 != c2 && str.find(c1) == string::npos)
            {
                str.push_back(c1);
            }
        }
    }
    sort(str.begin(), str.end());
    food[cx][cy] = str;

    // 2. 전파자는 간절함 0. 대상은 x만큼 증가
    board[cx][cy] += x;
    x = 0;
}

void propagate(int x, int i, int j)
{
    // i, j에서 전파 진행.
    int dir = (x + 1) % 4;
    int cx = i + dx[dir];
    int cy = j + dy[dir];
    string target = food[i][j];

    // cout << "start propagate " << dir << ' ' << i << ' ' << j << ' ' << cx << ' ' << cy << '\n';

    while (is_valid(cx, cy) && x > 0)
    {
        // 1. 같은 종류
        if (target == food[cx][cy])
        {
            // cout << "pass : " << i << ", " << j << " -> " << cx << ", " << cy << " / cur x : " << x << '\n';
            cx += dx[dir];
            cy += dy[dir];
            continue;
        }

        // 2. 강한 전파
        if (board[cx][cy] < x)
        {
            strong_propagate(x, i, j, cx, cy);
            // 전파 대상이 리더라면 해당 리더는 방어 모드로 변경
            if (is_leader[cx][cy] != 0)
                trans_defense_mode(cx, cy);
        }
        // 3. 약한 전파
        else if (board[cx][cy] >= x)
        {
            weak_propagate(x, i, j, cx, cy);
            // 전파 대상이 리더라면 해당 리더는 방어 모드로 변경
            if (is_leader[cx][cy] != 0)
                trans_defense_mode(cx, cy);
            break;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> t;

    for (int i = 1; i <= n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < n; j++)
            food[i][j + 1] = str[j];
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> board[i][j];

    while (t--)
    {
        // 1. 아침. -> 모든 신앙심 1씩 증가
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                board[i][j]++;

        // 2. 점심
        // 2.1. 그룹을 만들고 대표를 set에 저장. 그룹 크기도 구해야 함. (BFS)

        // 자료구조 초기화
        s.clear();
        for (int i = 0; i <= n; i++)
        {
            fill(is_leader[i], is_leader[i] + n + 1, 0);
            fill(vis[i], vis[i] + n + 1, false);
            fill(is_unvalid[i], is_unvalid[i] + n + 1, false);
        }

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (vis[i][j] == false)
                    bfs(i, j);

        // is_leader 확인용 출력
        // for (int i = 1; i <= n; i++)
        //     for (int j = 1; j <= n; j++)
        //         if (is_leader[i][j] != 0)
        //             cout << i << ", " << j << " is leader. And the size of group is " << is_leader[i][j] << '\n';

        // leader 정보 확인용 출력
        // for (auto x : s)
        // {
        //     int a, b, c, d;
        //     tie(a, b, c, d) = x;
        //     cout << "food type : " << a << ", board[" << c << "][" << d << "] = " << b << '\n';
        // }

        // 2.2. 전체 배열을 순회하며 리더라면 크기-1만큼 추가. 아니라면 1씩 감소 set에 리더의 정보 = 음식 타입 신앙심, 행, 열 튜플로 저장
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (is_leader[i][j])
                {
                    board[i][j] += (is_leader[i][j] - 1);
                    s.insert({get_food_type(food[i][j]), -board[i][j], i, j});
                }
                else
                    board[i][j]--;
            }
        }

        // board 확인용 출력
        // for (int i = 1; i <= n; i++)
        // {
        //     for (int j = 1; j <= n; j++)
        //     {
        //         if (is_leader[i][j])
        //             cout << board[i][j] << "* ";
        //         else
        //             cout << board[i][j] << ' ';
        //     }
        //     cout << '\n';
        // }

        // 3. 저녁.
        for (auto cur : s)
        {
            int food_type, x, i, j;
            tie(food_type, x, i, j) = cur;
            x *= -1;
            if (is_unvalid[i][j])
                continue;

            // 현재 리더의 신앙심 초기화
            board[i][j] = 1;
            // cout << "call propagate " << x - 1 << ' ' << i << ' ' << j << '\n';
            propagate(x - 1, i, j);
        }
        // // board 확인용 출력
        // for (int i1 = 1; i1 <= n; i1++)
        // {
        //     for (int j1 = 1; j1 <= n; j1++)
        //     {
        //         cout << board[i1][j1] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << "\n";

        // // food 확인용 출력
        // for (int i1 = 1; i1 <= n; i1++)
        // {
        //     for (int j1 = 1; j1 <= n; j1++)
        //     {
        //         cout << food[i1][j1] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << "\n";

        // 4. 답 구하기
        // T : 민트
        // CMT, CT, MT, CM, M, C, T 순서
        int ans[7] = {
            0,
        };
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (food[i][j] == "CMT")
                    ans[0] += board[i][j];
                else if (food[i][j] == "CT")
                    ans[1] += board[i][j];
                else if (food[i][j] == "MT")
                    ans[2] += board[i][j];
                else if (food[i][j] == "CM")
                    ans[3] += board[i][j];
                else if (food[i][j] == "M")
                    ans[4] += board[i][j];
                else if (food[i][j] == "C")
                    ans[5] += board[i][j];
                else if (food[i][j] == "T")
                    ans[6] += board[i][j];
            }
        }
        for (auto x : ans)
            cout << x << ' ';
        cout << '\n';
    }
}
