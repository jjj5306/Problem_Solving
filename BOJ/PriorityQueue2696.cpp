/** 우선순위 큐 2696 중앙값 구하기 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        priority_queue<int, vector<int>> left;                // 최대힙, 왼쪽을 담당함.
        priority_queue<int, vector<int>, greater<int>> right; // 최소힙, 오른쪽을 담당함.
        vector<int> ans;
        // 배열로 따지면 left.top() < 중앙값 < right.top() 인 셈.
        int m;
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            int x;
            cin >> x;

            left.push(x);

            // L과 R의 사이즈가 같거나 L이 1 더 커야함.
            if (left.size() == right.size())
                left.push(x);
            else
                right.push(x);

            // left의 모든 값들은 right 보다 작아야 함.
            while (!left.empty() && !right.empty() && left.top() > right.top())
            {
                int l = left.top(), r = right.top();
                left.pop();
                right.pop();
                left.push(r);
                right.push(l);
            }

            if (i % 2 == 1)
                // 홀수인 경우 left.top이 답
                ans.push_back(left.top());
        }
        cout << ans.size();
        for (int i = 0; i < ans.size(); i++)
        {
            if (i % 10 == 0)
                cout << '\n';
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}

/*
중앙값을 구하는데 O(log M)으로 구해야 함. 정렬을 통해서는 불가능함.
중앙값의 매커니즘을 살펴보면 원소의 개수가 5라면 배열을 정렬 했을 때
1, 2번째 값은 모두 중앙값의 왼쪽, 4, 5번째 값은 오른쪽에 위치함
그리고 중앙값 왼쪽, 오른쪽 원소의 개수는 같음.
또한 중앙값 왼쪽은 모두 중앙값보다 작고, 오른쪽은 중앙값보다 큼.
이는 우선순위 큐 두 개로 구현이 가능함.
*/
