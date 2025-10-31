#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>
using namespace std;

bool vis[205][205];
long long dp[205][205];
long long dp2[205][205];

long long calc(long long a, string oper, long long b)
{
    if (oper == "+")
        return a + b;
    else
        return a - b;
}

// 함수 정의 : i~j 범위의 모든 괄호쌍을 계산한다.
pair<long long, long long> func(int i, int j, vector<string> &arr)
{
    // base condition
    if (i == j)
        return {stoll(arr[i]), stoll(arr[i])};

    // DP
    if (vis[i][j])
        return {dp[i][j], dp2[i][j]};

    vis[i][j] = true;

    long long mx_ = LLONG_MIN, mn_ = LLONG_MAX;
    for (int k = i + 1; k < j; k += 2)
    {
        // k를 oper로 해서 계산
        // a k b 의 형태를 계산하면 됨
        pair<long long, long long> a, b;
        string oper = arr[k];
        a = func(i, k - 1, arr);
        b = func(k + 1, j, arr);

        if (oper == "+")
        {
            mx_ = max(mx_, a.first + b.first);   // max = max + max
            mn_ = min(mn_, a.second + b.second); // min = min + min
        }
        else
        {                                       // oper == "-"
            mx_ = max(mx_, a.first - b.second); // max = max - min
            mn_ = min(mn_, a.second - b.first); // min = min - max
        }
    }
    dp[i][j] = mx_;
    dp2[i][j] = mn_;
    return {mx_, mn_};
}

int solution(vector<string> arr)
{
    // arr : 홀수 idx에 숫자
    int answer = -1;
    answer = (int)func(0, arr.size() - 1, arr).first;
    return answer;
}

/*
모든 괄호쌍을 확인하며 최대값을 찾자.
dp[i][j] = i~j 범위에서 최대값
재귀적으로 메모이제이션 해가며 모든 쌍을 확인하는 것

*/