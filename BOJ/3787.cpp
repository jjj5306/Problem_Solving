/** dp 3687 성냥개비 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;
long long n;
long long dp[105];
vector<int> v;

void func(long long k)
{
    if (k == 0)
        return;
    if (k == 3)
    {
        v.push_back(7);
        return;
    }
    v.push_back(1);
    func(k - 2);
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long T;
    cin >> T;

    // 초기 dp값 채우기
    // 6은 0으로 작용할때도 있고, 6으로 작용할때도 있음.
    memset(dp, 0x7f, sizeof(dp));
    dp[1] = 9;
    dp[2] = 1;
    dp[3] = 7;
    dp[4] = 4;
    dp[5] = 2;
    dp[6] = 6;
    dp[7] = 8;

    // add[k] = k개를 사용할 때 숫자

    long long add[8] = {0, 0, 1, 7, 4, 2, 0, 8};

    for (int i = 8; i <= 100; i++)
    {
        for (int j = 2; j <= 7; j++)
        {
            // dp[i-j] 값 뒤에 숫자를 하나 이어 붙여서 최솟값 갱신
            dp[i] = min(dp[i], dp[i - j] * 10 + add[j]);
        }
    }

    while (T--)
    {
        cin >> n;
        cout << dp[n] << ' ';
        v.clear();
        func(n);
        for (auto it = v.rbegin(); it != v.rend(); ++it)
            cout << *it;
        cout << '\n';
    }
}
