/** 2461 대표 선수 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, m;

int class_[1005][1005];
int p[1005];
int ans = 0x7f7f7f7f;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> class_[i][j];
    // 1. 각 반 오름차순 정렬
    for (int i = 0; i < n; i++)
        sort(class_[i], class_[i] + m);
    // 2. 각 반 별로 포인터를 둔다.

    // 3. 각 반의 현재 idx에서 최대, 최소를 가져온다.
    while (1)
    {
        int mx = -1, mn = 0x7f7f7f7f, idx;
        // 각 반의 제일 작은 얘들을 시작으로 max-min을 계산하는 것
        // max-min을 계속 구해나가는 것인데, 최소값을 가졌던 idx만 투포인터로 쭉 증가시키면 됨
        for (int i = 0; i < n; i++)
        {
            if (mn > class_[i][p[i]])
            {
                mn = class_[i][p[i]];
                idx = i;
            }
            if (mx < class_[i][p[i]])
                mx = class_[i][p[i]];
        }
        // 4. 그 차와 ans를 비교한다.
        // 5. 현재 최소인 반의 idx를 증가시킨다.
        // 6. idx가 끝까지 가면 종료
        ans = min(ans, mx - mn);
        p[idx]++;
        if (p[idx] == m)
            // 다른 idx는 체크하지 않아도 되나요? -> 현재 idx가 기존 최소이자 마지막이었는데, 어차피 다음 case는 존재하지 않음
            break;
    }
    cout << ans;
}
