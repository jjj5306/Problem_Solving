#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> input; // 진출, 진입

int solution(vector<vector<int>> routes)
{
    int answer = 0;

    // 경계에 설치하는 것이 가장 이득인 것은 자명하다.
    // 우선 진입 시점 경계를 고려하는 것은 답과는 거리가 멀다.
    // 진출 시점 경계만 고려해도 될 것 같다.
    // 진출 시점을 기준으로 정렬해서 간트 차트를 그리고, 수직선을 긋는다고 생각해보자.
    // 그리디하게 풀어도 될 것 같다.

    for (auto route : routes)
        input.push_back({route[1], route[0]});

    sort(input.begin(), input.end());

    int cur = input[0].first;
    answer++;

    for (int i = 1; i < input.size(); i++)
    {
        // cur : 현재 감시카메라가 감시하는 가장 오른쪽 영역
        if (input[i].second > cur)
        {
            answer++;
            cur = input[i].first;
        }
    }

    return answer;
}