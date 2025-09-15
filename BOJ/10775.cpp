/** 10755 공항 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

int input[100010];
int g, p, ans = 0; // 게이트 수, 비행기 수
set<int> s;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> g >> p;

    for (int i = 1; i <= p; i++)
        cin >> input[i];

    for (int i = 1; i <= g; i++)
        s.insert(i);

    for (int i = 1; i <= p; i++)
    {
        // i번째 비행기를 현재 비어있는 게이트 중 가장 큰 게이트에 삽입한다.
        if (s.empty())
            break;

        auto idx = s.upper_bound(input[i]);
        if (idx == s.begin())
            break;

        idx--;

        if (*idx > input[i])
            break;

        s.erase(idx);
        ans++;
    }

    cout << ans;
}

/*
완전탐색 -> 불가능

그리디하게 가능한 게이트 중 가장 큰 번호에 배치하는 것이 전략
why?
1. 그 뒤에 자기보다 큰 번호가 나오면 -> 쭉 배치 가능
2. 그 뒤에 자기보다 작은 번호가 나오면 -> 앞을 비워뒀기에 효율적으로 배치 가능

n^2으로 배치해서는 안됨
log N or 상수 시간으로 해야함

1. Set에 모든 비어있는 게이트를 넣는다.
2. k번째 비행기에 대해 input[k]를 upper bound로 찾는다.
3. 찾은 index--
4. 최종 index의 값이 input[k]보다 크다면 도킹할 게이트가 없는 것이다.
5. 있다면 그 게이트를 제거하고 ans++

*/