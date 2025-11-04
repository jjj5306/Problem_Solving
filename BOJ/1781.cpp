/** 1781 컵라면 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

vector<pair<int, int>> input; // dead, value
int n, m = -1, ans = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int dead, v;
        cin >> dead >> v;
        input.push_back({dead, v});
        m = max(m, dead);
    }

    sort(input.begin(), input.end());

    int cur = n - 1; 
    //현재 추적중인 작업
    priority_queue<int> pq;

    for (int j = m; j > 0; j--)
    {
        //데드라인이 j일 이후인 문제들을 모두 우선순위 큐에 추가
        while(cur >=0 && input[cur].first >= j) {
            pq.push(input[cur].second);
            cur--;
        }
        //우선순위 큐에 있는 문제들은 모두 j일 이후에 데드라인이므로 모두 풀 수 있음
        //따라서 제일 값이 큰 것만 쏙쏙 풀면 됨
        if(!pq.empty()){
            ans += pq.top();
            pq.pop();
        }
    }

    cout << ans;
}

/*
현재 cur 일이라면 현재 풀 수 있는 문제 중 컵라면을 제일 많이 주는걸 풀면 된다.
-> 문제는 cur일에 cur+1일 까지가 데드라인인 작업을 푸는게 더 이득일 수 있다는 것이다.
따라서 전체 데드라인이 n일이라면 전체 일수를 고려해서 풀 수 있는 문제 중 가장 값어치가 높은 문제를 푼다
-> (데드라인, v)를 큰 것, 큰 것으로 우선순위 큐에 넣어서 풀면 된다.
*/
