#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit)
{
    int answer = 0;

    // 1. 내림차순으로 Srot 해서
    // 2. 투포인터로 제일 무거운 사람 한 명, 가벼운 사람 한 명
    sort(people.begin(), people.end());

    int left = 0, right = people.size() - 1;
    while (left <= right)
    {
        if (people[right] + people[left] <= limit)
        {
            left++;
        }
        answer++;
        right--;
    }

    return answer;
}