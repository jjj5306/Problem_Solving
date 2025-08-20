#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays)
{
    vector<int> answer;

    // 1. 속한 노래가 가장 많이 재생된 장르 찾기
    // map의 key로 장르 string, 값은 plays의 장르별 합으로 두기 nlogn
    // 이 map을 vector로 옮기기 nlogn
    // vector : pair<int, string> greater로 정렬 -> nlogn
    map<string, int> m;
    map<string, set<pair<int, int>, greater<pair<int, int>>>> m2;

    for (int i = 0; i < plays.size(); i++)
    {
        m[genres[i]] += plays[i];
        m2[genres[i]].insert({plays[i], -i});
    }

    vector<pair<int, string>> v;

    for (auto x : m)
        v.push_back({x.second, x.first});

    sort(v.rbegin(), v.rend());

    // v : 가장 많이 재생된 장르 순서대로 정렬됨
    // 2. 해당 장르에서 수록곡 2개 선택
    // 이를 위해 map key : genre / value : set({재생 수, 고유 번호}) 사용

    // 3. v.second를 순회하며
    for (int i = 0; i < v.size(); i++)
    {
        // v[i].second 장르에 대한 수록곡 두 개 출력
        int cnt = 0;
        for (auto x : m2[v[i].second])
        {
            if (cnt == 2)
                break;
            answer.push_back(-x.second);
            cnt++;
        }
    }

    return answer;
}