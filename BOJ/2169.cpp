/** 2169 로봇 조종하기 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, m;
int board[1001][1001];
int dp[1001][1001];
int dp2[1001][1001];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> board[i][j];
        }
    }

    // dp[i][j] = 위, 왼쪽에서 오는 것. dp[i][j-1], dp[i-1][j]
    // 이렇게 해버리면 오른쪽에서 오는 것은 계산할 수 없음.
    // 하지만 여전히 아래에서 위로는 이동이 안되므로 오른쪽에서 오는 경우의 수는 같은 행에서 밖에 없음.
    // 즉, dp2[i][j] = 오른쪽, 위에서 오는 것으로 설정하고 오른쪽부터 채워나간다면 반례가 존재하지 않음

    fill(&dp[0][0], &dp[n + 1][m + 1], -0x3f3f3f3f);
    fill(&dp2[0][0], &dp2[n + 1][m + 1], -0x3f3f3f3f);

    // 1행은 왼쪽부터 채워나가야 함.
    dp[1][0] = 0;
    dp[0][1] = 0;
    dp2[1][0] = 0;
    dp2[0][1] = 0;

    for (int i = 1; i <= m; i++)
    {
        dp[1][i] = dp[1][i - 1] + board[1][i];
        dp2[1][i] = dp2[1][i - 1] + board[1][i];
    }

    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // dp[i][j] 채우기.
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + board[i][j];
        }
        for (int j = m; j > 0; j--)
        {
            // dp2[i][j] 채우기.
            dp2[i][j] = max(dp2[i - 1][j], dp2[i][j + 1]) + board[i][j];
        }
        for (int j = 1; j <= m; j++)
        {
            // dp[i][j] 갱신.
            dp[i][j] = max(dp[i][j], dp2[i][j]);
            dp2[i][j] = dp[i][j];
        }
    }

    cout << dp[n][m];
}
