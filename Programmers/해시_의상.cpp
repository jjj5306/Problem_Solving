#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int solution(vector<vector<string>> clothes)
{
    int answer = 1;
    map<string, int> m;

    // 카테고리 별 옷의 수 파악 후
    //(a+1)x(b+1)x(c+1)-1

    for (auto cloth : clothes)
    {
        m[cloth[1]]++;
        // cout<<"process "<<cloth[0]<<", category : "<<cloth[1]<<' '<<m[cloth[1]]<<'\n';
    }

    for (auto x : m)
    {
        // cout<<x.first<<' '<<x.second<<'\n';
        answer *= (x.second + 1);
    }

    answer--;

    return answer;
}