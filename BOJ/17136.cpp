/** 17136 색종이 붙이기 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int ans = 150;
int board[10][10];
bool vis[10][10]; // 덮은 곳
int paper_count[6] = {0, 5, 5, 5, 5, 5};

void execute(int k, int x, int y)
{
    // x, y에 k크기의 사각형 덮기
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            vis[x + i][y + j] = true;
        }
    }
}

void detach(int k, int x, int y)
{
    // x, y에 k크기의 사각형 덮기
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            vis[x + i][y + j] = false;
        }
    }
}

bool is_possible(int k, int x, int y)
{
    if (paper_count[k] <= 0)
        return false;
    // x, y에 k크기의 사각형을 덮을 수 있는지
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int cx = x + i, cy = y + j;
            if (cx < 0 || cx >= 10 || cy < 0 || cy >= 10 || vis[cx][cy] || !board[cx][cy])
                return false;
        }
    }
    return true;
}

// 재귀 함수 : 현재 cur 개의 색종이를 붙였고, i, j부터 탐색을 시작하면 됨
void func(int cur, int i, int j)
{
    // base condition 1 : 현재 센게 지금까지 답보다 크면 굳이 끝까지 X
    if (cur > ans)
        return;

    for (int x = i; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (!board[x][y])
                continue;
            // 이미 덮은 곳
            if (board[x][y] && vis[x][y])
                continue;
            // x, y에 k=5~1까지의 사각형을 덮어본다.
            for (int k = 5; k >= 1; k--)
            {
                // 덮을 수 있는지
                if (!is_possible(k, x, y))
                    continue;

                // 실제로 덮기
                paper_count[k]--;
                execute(k, x, y);
                func(cur + 1, x, y);

                paper_count[k]++;
                // 덮기 취소
                detach(k, x, y);
            }
            // 1을 발견했고, 다 붙여본 경우. 혹은 아무것도 못붙임
            return;
        }
    }
    ans = min(ans, cur);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            cin >> board[i][j];
    func(0, 0, 0);
    if (ans == 150)
        ans = -1;
    cout << ans;
}
