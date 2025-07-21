/** 스택 22942 데이터 체커 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <tuple>
using namespace std;

stack<tuple<int, int, int>> s;
vector<tuple<int, int, int>> arr;
int n;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int p, r;
        cin >> p >> r;
        arr.push_back({p - r, 0, i});
        arr.push_back({p + r, 1, i});
    }

    sort(arr.begin(), arr.end());

    // 한 원의 시작점을 여는 괄호로, 끝점을 닫는 괄호로 생각하여 스택으로 괄호 문제처럼 풀면 됨.
    for (int i = 0; i < 2 * n; i++)
    {
        int x, is_start, idx;
        tie(x, is_start, idx) = arr[i];

        if (!is_start)
        {
            // cout << "i : " << i << " x : " << x << " idx : " << idx << '\n';
            s.push(arr[i]);
        }
        else
        {
            int x2, is_end, cur;
            tie(x2, is_end, cur) = s.top();
            s.pop();
            // cout << "i : " << i << " x : " << x << " idx : " << idx << " cur : " << cur << '\n';

            if (cur != idx)
            {
                cout << "NO";
                return 0;
            }
        }
    }
    cout << "YES";
}
