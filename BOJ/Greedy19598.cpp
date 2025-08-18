/** 그리디 19598 최소 회의실 개수 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int n, ans = 1;
vector<pair<int, int>> input;
priority_queue<int, vector<int>, greater<int>> pq; // 최소힙

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    int st, en;
    for (int i = 0; i < n; i++)
    {
        cin >> st >> en;
        input.push_back({st, en});
    }

    sort(input.begin(), input.end());

    // 시작 시간이 가장 빠른 회의부터 끝나는 시간을 pq에 넣기.
    // pq는 최소힙이므로 현재 회의 시작 시간이 pq.top보다 같거나 크다면 pq.pop
    // 현재 회의 시작 시간이 pq.top 보다 작다면 pq.push, ans++

    pq.push(input[0].second);

    for (int i = 1; i < n; i++)
    {
        // i번째 회의 처리
        // cout << i << ' ' << input[i].first << ' ' << pq.top() << '\n';
        if (pq.top() <= input[i].first)
            pq.pop();
        else
            ans++;
        pq.push(input[i].second);
    }

    cout << ans;
}
