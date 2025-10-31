#include <string>
#include <iostream>
#include <vector>

using namespace std;
int dp[102][102];

int solution(int m, int n, vector<vector<int>> puddles)
{
    int answer = 0;

    // 웅덩이 표시
    for (auto puddle : puddles)
    {
        dp[puddle[1]][puddle[0]] = -1;
    }

    dp[1][1] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // 현재 칸이 물웅덩이
            if (dp[i][j] == -1)
                continue;
            // 이전 행
            if (dp[i - 1][j] != -1)
                dp[i][j] += (dp[i - 1][j] % 1000000007);
            // 이전 열
            if (dp[i][j - 1] != -1)
                dp[i][j] += (dp[i][j - 1] % 1000000007);
        }
    }
    answer = (dp[n][m] % 1000000007);
    return answer;
}

/*
n행 m열에서 웅덩이를 피해서 학교까지 가자.
1,1이 시작임
dp[i][j]
1. 이전 행에서 오는 경우의 수
2. 이전 열에서 오는 경우의 수
** 웅덩이를 피해서 도달만 할 수 있다면 무조건 최단 경로임
*/