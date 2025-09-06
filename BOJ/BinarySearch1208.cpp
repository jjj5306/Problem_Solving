/** 이분 탐색 1208 부분수열의 합 2 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

long long n, s, ans = 0, en;
long long arr[45];
vector<long long> A;
vector<long long> B;

void func1(long long k, long long sum_)
{
    // k번째 수에 대해 부분합 계산. 지금까지의 결과 sum_,  A 집합에 저장
    if (en == k)
    {
        A.push_back(sum_);
        return;
    }

    func1(k + 1, sum_);
    func1(k + 1, sum_ + arr[k]);
}

void func2(long long k, long long sum_)
{
    // k번째 수에 대해 부분합 계산. 지금까지의 결과 sum_,  A 집합에 저장
    if (en == k)
    {
        B.push_back(sum_);
        return;
    }

    func2(k + 1, sum_);
    func2(k + 1, sum_ + arr[k]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s;
    for (long long i = 0; i < n; i++)
        cin >> arr[i];

    sort(arr, arr + n);

    // 수열을 두 집합으로 나눠서 부분 합을 모두 저장한다. -> 완전탐색 -> 2^20 -> 1,000,000 번 연산
    en = n / 2;
    func1(0, 0);

    en = n;
    func2(n / 2, 0);

    sort(B.begin(), B.end());

    for (auto x : A)
        ans += upper_bound(B.begin(), B.end(), s - x) - lower_bound(B.begin(), B.end(), s - x);

    if (s == 0)
        ans--;

    cout << ans;
}
