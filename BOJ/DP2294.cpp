/** DP 2294 동전 2 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, k;
int dp[10010], coin[103];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // dp[j] : 가치 j를 만들 때 사용할 최소 동전 개수
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> coin[i];

    fill(dp, dp + k + 1, 0x3f3f3f3f);
    dp[0] = 0; // base

    for (int i = 0; i < n; i++)
    {
        // cout << i << "\n";
        // i번째 코인을 고려했을 때 가치 j를 만들 수 있는 최소 동전 개수 계산
        for (int j = coin[i]; j <= k; j++)
        {
            // j 가치를 만드는 최소 경우의 수 :
            // 1. (coin[i] 사용 -> 1) + (dp[j-coin[i]])
            // 2. coin[i]를 사용하지 않고 기존 유지 -> dp[j]
            dp[j] = min(dp[j], dp[j - coin[i]] + 1);
            // cout << j << ' ' << dp[j] << '\n';
        }
    }

    if (dp[k] >= 0x3f3f3f3f)
        cout << -1;
    else
        cout << dp[k];
}
