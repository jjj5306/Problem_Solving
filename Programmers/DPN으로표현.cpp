#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

// DFS와 같이 모든 연산을 다 해보는 수 밖에 없음.
// 이 과정에서 N을 세 번 쓴 연산을 생각해보면, N을 한 번 쓴 결과와 N을 두 번 쓴 결과에 대해서도 사칙연산을 수행해야 함.
// 따라서 N을 쓴 횟수에 따른 결과를 메모이제이션
// 저장에 있어서 중복된 값도 없고 딱히 정렬은 필요하지 않으므로 unordered_set 사용

unordered_set<int> dp[9]; // N을 1~7번 사용한 결과 저장

int func(int N, int number)
{
    // func : dp 배열 채우기
    if (N == number)
        return 1;

    int cur = 0;
    for (int i = 1; i <= 8; i++)
    {
        // N을 i번 사용한 결과 저장
        // dp[2] = dp[1]과 dp[1] 연산. or NN
        // dp[5] = dp[2], dp[3] or dp[1], dp[4] or NNNNN
        // dp[k] = dp[i], dp[j] / i+j = k
        cur = cur * 10 + N;
        dp[i].insert(cur);

        // dp[j], dp[i-j]의 사칙 연산 계산. j + i - j = i 이므로
        for (int j = 1; j < i; j++)
        {
            for (int n1 : dp[j])
            {
                for (int n2 : dp[i - j])
                {
                    dp[i].insert(n1 + n2);
                    dp[i].insert(n1 - n2);
                    dp[i].insert(n1 * n2);
                    if (n2 != 0)
                        dp[i].insert(n1 / n2);
                }
            }
        }
        // number 있는지
        if (dp[i].find(number) != dp[i].end())
            return i;
    }
    return -1;
}

int solution(int N, int number)
{
    int answer = 0;

    answer = func(N, number);

    return answer;
}