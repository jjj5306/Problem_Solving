/** 스택 22866 탑 보기 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

stack<pair<int, int>> s1, s2; //{건물 번호, 높이}
int n;
int building[100010];
pair<int, int> ans[100010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> building[i];

    // 오른쪽 -> 왼쪽 순회
    // i번째 건물에서 오른쪽 방향으로 볼 수 있는 건물들
    // 7 x 4,8 8 6,8 8 x
    // 오른쪽에서부터 진행
    // i번째 건물이 i+1번째 건물보다 낮다면 -> continue
    // i번째 건물이 i+1번째 건물보다 같거나 높다면 -> 오른쪽 방향으로 자신보다 낮은 건물들 다 제거
    // 그냥 스택으로 하면 됨. 왜냐하면 한 방향으로만 삭제가 일어남
    int i;
    s1.push({n - 1, building[n - 1]});

    for (i = n - 2; i >= 0; i--)
    {
        if (building[i] >= building[i + 1])
            while (!s1.empty() && building[i] >= s1.top().second)
                s1.pop();

        ans[i].first += s1.size();
        if (!s1.empty())
            ans[i].second = s1.top().first;

        // if (!s1.empty())
        //     cout << s1.size() << ' ' << s1.top().first + 1 << '\n';
        // else
        //     cout << 0 << ' ' << 0 << '\n';

        s1.push({i, building[i]});
    }

    // 왼쪽 -> 오른쪽 순회 (왼쪽 방향으로 볼 수 있는 것들)
    s2.push({0, building[0]});

    for (i = 1; i < n; i++)
    {
        if (building[i] >= building[i - 1])
            while (!s2.empty() && building[i] >= s2.top().second)
                s2.pop();

        ans[i].first += s2.size();

        if (!s2.empty() && (ans[i].second == 0 || abs(ans[i].second - i) >= abs(i - s2.top().first)))
            ans[i].second = s2.top().first;

        // if (!s2.empty())
        //     cout << s2.size() << ' ' << s2.top().first + 1 << '\n';
        // else
        //     cout << 0 << ' ' << 0 << '\n';

        s2.push({i, building[i]});
    }
    for (int i = 0; i < n; i++)
        if (ans[i].first == 0)
            cout << 0 << '\n';
        else
            cout << ans[i].first << ' ' << ans[i].second + 1 << '\n';
}

/*
10만개의 건물에 대해 순회
i번째 건물의 좌우 중 자신보다 큰고 가까운 건물 출력
완전탐색 : n^2 -> 불가능
max : 높이 7 -> 높이 7인 건물은 답이 X



반대로 왼쪽 방향만 생각해보면
왼쪽에서부터 진행하면서 똑같이

*/
