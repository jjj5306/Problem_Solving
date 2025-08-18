/** 그리디 21758 꿀따기 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, b1, b2, honey;
long long ans = 0, cur;
long long input[100010], sum_[100010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> input[i];

    sum_[0] = input[0];
    for (int i = 1; i < n; i++)
        sum_[i] += input[i] + sum_[i - 1]; // 누적합 계산

    // 누적합을 통해 두 벌의 위치와 벌통의 위치로 답을 O(1)로 계산 가능

    // case 1 벌 벌 벌통
    // 벌1은 제일 왼쪽, 벌통은 제일 오른쪽에 고정. 벌2는 모든 경우의 수 체크
    b1 = 0;
    honey = n - 1;
    for (b2 = 1; b2 < n - 1; b2++)
    {
        // 1. b1의 이동 경로 계산
        cur = sum_[honey] - sum_[b1] - input[b2];

        // 2. b2의 이동 경로 계산
        cur += sum_[honey] - sum_[b2];

        ans = max(ans, cur);
        // cout << b2 << ' ' << cur << '\n';
    }

    // case 2 벌통 벌 벌
    honey = 0;
    b1 = n - 1;
    for (b2 = 1; b2 < n - 1; b2++)
    {
        // 1. b1의 이동 경로 계산
        cur = sum_[b1 - 1] - input[b2];

        // 2. b2의 이동 경로 계산
        cur += sum_[b2 - 1];

        ans = max(ans, cur);
        // cout << b2 << ' ' << cur << '\n';
    }

    // case 3 벌 벌통 벌
    b1 = 0;
    b2 = n - 1;
    for (honey = 1; honey < n - 1; honey++)
    {
        // 1. b1 ~ cur 계산
        cur = sum_[honey] - sum_[b1];

        // 2. cur ~ b2 계산
        cur += sum_[b2 - 1] - sum_[honey - 1];

        ans = max(ans, cur);
        // cout << honey << ' ' << cur << '\n';
    }

    cout << ans;
}
