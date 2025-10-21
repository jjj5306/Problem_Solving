/** 16639 괄호 추가하기 3 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>
using namespace std;

long long n;
long long dp[20][20];
long long dp2[20][20];
bool is_visited[20][20];
string s;

long long calc(long long a, long long b, char op)
{
    if (op == '*')
        return a * b;
    else if (op == '+')
        return a + b;
    else
        return a - b;
}

pair<long long, long long> func(int i, int j)
{
    // dp[i][j]를 계산
    // base condition : 원본 숫자 반환
    if (i == j)
        return {s[i] - '0', s[i] - '0'};

    // 이미 계산했는지 체크
    if (is_visited[i][j])
        return {dp[i][j], dp2[i][j]};

    // dp[i][j] 계산
    is_visited[i][j] = true;

    long long max_ = LLONG_MIN, min_ = LLONG_MAX;
    for (int k = i + 1; k < j; k += 2)
    {
        // s[k]를 연산자로 기준으로 해서 앞 뒤 계산
        char op = s[k];
        pair<long long, long long> A = func(i, k - 1), B = func(k + 1, j);
        // 앞 뒤 계산이 완료되었고, dp[i][j]를 이제 갱신
        // A max, A min, B max, B min에 대한 모든 연산을 수행해야 함.
        vector<long long> res;
        res.push_back(calc(A.first, B.first, op));
        res.push_back(calc(A.first, B.second, op));
        res.push_back(calc(A.second, B.first, op));
        res.push_back(calc(A.second, B.second, op));

        sort(res.begin(), res.end());
        max_ = max(max_, res.back());
        min_ = min(min_, res.front());
    }
    dp[i][j] = max_;
    dp2[i][j] = min_;
    return {max_, min_};
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s;

    // dp[i][i] = s[i]
    for (int i = 0; i < n; i += 2)
    {
        dp[i][i] = s[i] - '0';
        dp2[i][i] = s[i] - '0';
    }

    cout << func(0, n - 1).first;
}

/*
묶은걸 또 묶을 수 있고 한 번에 여러 연산자를 묶을 수 있다. 따라서 완전 탐색은 절대 불가능하다. 구현이 가능한지 조차 모르겠다.
전형적인 divide-and-conquer로 접근할 수 있을 것 같다.
3+8*7-9*2
1. 3 + 8*7-9*2
2. 3+8 * 7-9*2
3. 3+8*7 - 9 ...
4. ....
이런식으로 [0,i][i+1,n-1]까지를 쭉 나누는 것이다. 재귀적으로 생각해서 나눈 부분은 알아서 최대값이 구해졌다고 친다면 5개의 케이스만에 최대값을 구할 수 있다.
하나의 [0,i]와 같은 청크에서도 똑같이 다 나눠본다. 메모이제이션도 딱 쓸 수 있을 것 같다. 재귀적으로 [0,i]를 구할 때 [0,2]을 쓰고 [0,4]를 구할 때 [0,2]을 쓰고 이런게 가능하기 때문이다.

먼저 한 가지 정해두고 가자. 0번 index부터 짝수 index에는 숫자가 홀수 index에는 연산자가 저장되어 있다. 따라서 [1,i]의 i는 반드시 짝수이다.
DP 식을 정의해보자.
dp[i][j] = [i, j] 범위에서 최대값
dp2[i][j] = [i, j] 범위에서 최소값 -> 최소값이 필요한 이유는 (음수) * (음수)가 최대가 될 수 있기 때문이다. 연산자가 *면 음수도 고려해야 한다.
점화식 : dp[i][j] = 재귀적으로 쭉쭉 타고 올라오면서 자동으로 구해짐. A 연산자 B 형태이기에 A, B의 최대 최소를 각각 모든 쌍을 고려해서 계산하여 최대, 최소 갱신

괄호가 어디에던 들어갈 수 있으므로 곱하기의 연산 우선순위는 고려하지 않아도 된다!

*/