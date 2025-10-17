/** 1450 냅색문제 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, c;
long long ans = 0;
int arr[32];

// st부터 en-1까지 모든 조합을 찾는 함수.
void func(vector<int> &v, int st, int en, int cnt)
{
    if (cnt > c)
        return;
    if (st >= en)
    {
        v.push_back(cnt);
        return;
    }
    func(v, st + 1, en, cnt + arr[st]);
    func(v, st + 1, en, cnt);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> c;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> A;
    vector<int> B;

    // 중간에서 만나기
    // 배열을 두 개로 쪼개서. 최대 15개씩으로 배열의 범위를 줄인다.
    // 하나의 배열 A에 대해 해당 배열의 가능한 모든 조합을 찾는다. 2^15 이므로 시간 초과가 나지 않음.
    // A, B를 채운 뒤 B를 정렬하고 C-A[i]를 upper_bound로 B에서 찾는다. 해당 index를 k라 하면 B[n/2+1]~[k]까지가 답

    func(A, 0, n / 2, 0);
    func(B, n / 2, n, 0);
    sort(B.begin(), B.end());

    for (auto a : A)
    {
        ans += upper_bound(B.begin(), B.end(), c - a) - B.begin();
    }

    cout << ans;
}
