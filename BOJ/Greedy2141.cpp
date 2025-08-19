/** Greedy 2141 우체국 **/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<long long, long long>> villages(n);
    long long total_population = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> villages[i].first >> villages[i].second; // first: 위치, second: 인구
        total_population += villages[i].second;
    }

    // 1. 좌표를 기준으로 마을들을 정렬한다.
    sort(villages.begin(), villages.end());

    // 2. 모든 사람을 일렬로 세웠을 때, 중앙에 위치한 사람의 순서를 찾는다.
    long long median_person_rank = (total_population + 1) / 2;

    long long cumulative_population = 0;
    for (int i = 0; i < n; i++)
    {
        cumulative_population += villages[i].second;
        // 3. 누적 인구수가 중앙값 순서보다 크거나 같아지는 최초의 마을을 찾는다.
        if (cumulative_population >= median_person_rank)
        {
            cout << villages[i].first; // 해당 마을의 위치가 정답
            break;
        }
    }

    return 0;
}