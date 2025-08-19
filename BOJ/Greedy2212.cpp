/** 그리디 2212 센서 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, k, ans = 0;
int input[10010], dist[10010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
    }

    sort(input, input + n);

    // cout << "\n*******\n";
    // for (int i = 0; i < n; i++)
    //     cout << input[i] << ' ';
    // cout << "\n*******\n";

    for (int i = 0; i < n - 1; i++)
    {
        // 간격 계산
        dist[i] = input[i + 1] - input[i];
        ans += dist[i];
    }

    // 구간들의 합은 간격의 합으로 정의할 수 있음. 즉, [1, 9] 센서는 간격 8짜리의 센서인 것
    // k=5 -> input 집합을 5개의 파티션으로 분할
    // 분할된 파티션들 끼리는 이어질 필요가 없음.
    // 따라서 input 집합을 분할할 때 k-1 개의 간격을 제거할 수 있음.

    // k-1 개의 간격을 제거할 수 있다면, 가장 큰 값들을 제거하면 됨
    sort(dist, dist + n - 1);

    // cout << "\n*******\n";
    // for (int i = 0; i < n - 1; i++)
    //     cout << dist[i] << ' ';
    // cout << "\n*******\n";

    for (int i = n - 2; i >= 0; i--)
    {
        if (k == 1)
            break;
        // cout << i << ' ' << dist[i] << '\n';
        ans -= dist[i];
        k--;
    }
    cout << ans;
}
