#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int dp[1000002][2];
int n;

int solution(vector<int> money)
{
    int answer = 0;

    n = money.size();
    // dp[k][0] 채우기 : 시작점을 털었을 때
    dp[0][0] = money[0];
    dp[1][0] = money[0];
    // dp[2][0] 부터는 시작점을 안턴게 경로로 선택될 수 있다.
    // 하지만 시작점을 털지 않은 경우에는 끝점을 털던 말던 상관이 없기에 그대로 점화식을 적용해도 된다.

    for (int i = 2; i < n - 1; i++)
    {
        dp[i][0] = max(dp[i - 2][0] + money[i], dp[i - 1][0]);
    }

    // dp[k][1] 채우기 : 시작점을 안털었을 때
    dp[0][1] = 0;
    dp[1][1] = money[1];
    for (int i = 2; i < n; i++)
    {
        dp[i][1] = max(dp[i - 2][1] + money[i], dp[i - 1][1]);
    }

    answer = max(dp[n - 2][0], dp[n - 1][1]);

    return answer;
}

/*
dp[k] = k번까지 고려했을 때 최대값
dp[k] = dp[k-2]+money[k] or dp[k-1]
=> 문제가 되는 부분이 끝점과 시작점이다.
dp[k]에는 시작점을 털었는지, 아닌지에 대한 정보가 없다.
dp[k][0] : 시작점을 털었을 때 -> dp[n-2]까지만 계산
dp[k][1] : 시작점을 안털었을 때 -> 초기값을 다르게 세팅

*/