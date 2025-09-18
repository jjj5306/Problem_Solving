/** DP 1943 동전 분배 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int dp[100001]; // dp[i] : i 가치를 만들 수 있는지

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 3;
    while (T--)
    {
        int n;
        cin >> n;

        int value[105], cnt[100005];
        int target = 0;

        for (int i = 0; i < n; i++)
        {
            int a, b;
            cin >> a >> b;
            value[i] = a;
            cnt[i] = b;
            target += a * b;
        }

        if (target % 2 != 0)
        {
            cout << 0 << '\n';
            continue;
        }
        else
            target /= 2;

        // dp 테이블 초기화
        fill(dp, dp + target + 1, -1);
        dp[0] = 0;

        for (int i = 0; i < n; i++)
        {
            // i번 동전까지 써서 j원을 만들 수 있는지 체크
            // dp[j]에는 i번 동전을 몇 번 쓰는지 저장하여 개수 이상의 동전을 사용하지 않도록 함
            for (int j = 1; j <= target; j++)
            {
                // case 1. 현재 동전을 안써도 됨
                if (dp[j] != -1)
                {
                    dp[j] = 0;
                    continue;
                }

                // case 2. 현재 동전을 써야함.
                if (j - value[i] >= 0 && dp[j - value[i]] != -1 && dp[j - value[i]] < cnt[i])
                    dp[j] = dp[j - value[i]] + 1;
            }
        }

        if (dp[target] != -1)
            cout << 1 << '\n';
        else
            cout << 0 << '\n';
    }
}

/*
n=100

배낭 문제랑 똑같음
목표 금액은 전체 합 / 2

*/