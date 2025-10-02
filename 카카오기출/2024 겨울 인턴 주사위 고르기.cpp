#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
int n;

// i=0~n까지 중 select=flag이고, vis[i]=false인 i에 대해 res에 dice[i]를 더함.
void calc(vector<vector<int>> &dice, vector<bool> &select, bool flag, vector<int> &res, int i)
{

    for (i++; i < n; i++)
    {
        // dice[i]의 모든 수를 res에 더한다.
        if (select[i] != flag)
            continue;
        vector<int> tmp = res;
        res.clear();
        // res의 모든 수 res[k]에 dice[i][j]를 더한다.
        // res에는 지금까지의 모든 경우의 수가 정해져있다.
        // 따라서 res에 dice[i][j]를 더한다는 것은 j번째 수에 대한 경우의 수를 계산한 것.
        // 즉 dice[i][j]를 더하기 전 res는 남겨뒀다가 j번째 수를 더하고 나서 다시 초기화해야함.
        for (int k = 0; k < tmp.size(); k++)
            for (int j = 0; j < dice[i].size(); j++)
            {
                res.push_back(tmp[k] + dice[i][j]);
            }
    }
}

int func(vector<vector<int>> &dice, vector<bool> &select)
{
    // select[i]=false -> i번째 주사위를 A가 선택한 것.
    //  1. A의 주사위에 대해 가능한 모든 수를 중복을 포함해서 다 저장한다.
    //  2. B도 마찬가지로 다 저장한다.
    //  3. A를 모든 수를 순회하며 하나당 B의 모든 수를 순회하여 A가 더 큰 경우를 계산한다.

    vector<int> A;
    vector<int> B;
    int rt = 0;

    // A 초기값 세팅
    int i;
    for (i = 0; i < n; i++)
        if (select[i] == false)
        {
            A = dice[i];
            break;
        }
    calc(dice, select, false, A, i);

    // B 초기값 세팅
    for (i = 0; i < n; i++)
        if (select[i] == true)
        {
            B = dice[i];
            break;
        }
    calc(dice, select, true, B, i);

    // A, B 비교
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B.size(); j++)
        {
            if (A[i] > B[j])
                rt++;
        }
    }

    return rt;
}

vector<int> solution(vector<vector<int>> dice)
{
    vector<int> answer;
    int ans = 0;

    // n개의 주사위. 각 주사위는 1~n 범위의 수를 가짐.
    n = dice.size();

    // A는 자신이 승리할 확률이 가장 높아지도록 n/2개의 주사위를 가져감.
    // 완전탐색으로 모든 경우의 수를 계산. n/2 C 2
    // A가 가져가지 않은 주사위는 반드시 B가 가져감.
    // vector<bool> select(n)=false -> A가 가져감. true -> B가 가져감
    // select를 보고 승의 개수만 비교하면 됨. 어차피 확률의 분모는 모두 같음.

    vector<bool> select(n);
    fill(select.begin(), select.begin() + n / 2, false);
    fill(select.begin() + n / 2, select.end(), true);

    do
    {
        int cur = func(dice, select);

        if (ans < cur)
        {
            // 답 갱신
            ans = cur;
            answer.clear();
            for (int i = 0; i < n; i++)
                if ((!select[i]))
                    answer.push_back(i + 1);
        }

    } while (next_permutation(select.begin(), select.end()));

    return answer;
}