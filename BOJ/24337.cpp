/** 그리디 24337 가희와 탑 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>
using namespace std;

int n, a, b;
deque<int> ans;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> a >> b;

    if (a + b - 1 > n)
    {
        cout << -1;
        return 0;
    }

    if (a >= b)
    {
        // 1 2 ... a까지 채우기
        for (int i = 1; i <= a; i++)
        {
            ans.push_back(i);
        }

        // 1 2 ... a 뒤에 b-1 b-2 .. .1 채우기
        for (int i = b - 1; i >= 1; i--)
        {
            ans.push_back(i);
        }
    }
    else
    {
        // 1 2 ... a-1까지 채우기
        for (int i = 1; i < a; i++)
        {
            ans.push_back(i);
        }

        // 1 2 ... a-1 뒤에 b b-1 b-2 .. .1 채우기
        for (int i = b; i >= 1; i--)
        {
            ans.push_back(i);
        }
    }

    // 1 2 ... max ... 2 1 까지 현재 a+b-1개 채웠고 총 n개가 되어야하니 n-a-b+1개 만큼 채우면 됨
    int tmp;
    if (a == 1)
    {
        tmp = ans[0];
        ans.pop_front();
    }
    for (int i = 1; i <= n - a - b + 1; i++)
        ans.push_front(1);

    if (a == 1)
        ans.push_front(tmp);

    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
}

/*
가희가 볼 수 있는게 a개
단비가 볼 수 있는게 b개

a >= b
1 2 3  ... a b-1 b-2 ... 1

a < b
1 2 ... a-1 b b-1 b-2 ... 1

=> 이상적인 형태이다. 그런데 이렇게만 하면 건물의 개수는 딱 a+b-1개일때이다.
a+b개보다 이상의 건물은 처리할 수 없다.
그런 케이스들은 사전순이기에 1을 제일 앞에 끼우면 된다. 1은 무효로 생각하면 앞에 아무리 끼워도 답에 변화가 없기 때문이다.
다만!! a가 1인 케이스는 조금 다르다. 1이 무효가 아니게 된다. a가 1이면 b가 0 index에 오므로 그 다음에 끼워 넣어야 한다.

다시...
a >= b
(여기에 1을 끼워서 n개를 맞춰야 한다.) 1 2 3 ... a b-1 b-2 ... 1

a < b
1 2 ... a-1 b b-1 b-2 ... 1



*/