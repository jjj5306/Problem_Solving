/** Stack 2800 괄호 제거 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

string input;
int brackets = 0, cur = 1;
int idx[205];
stack<int> s;
bool unvalid[205];
vector<string> ans;

void func(int k)
{
    if (k > brackets)
    {
        string rt;
        for (int i = 0; i < input.size(); i++)
        {
            // idx[i]가 0이면 그냥 출력 혹은 unvalid[idx[i]]도 0이면 해당 괄호도 출력
            if (idx[i] == 0 || unvalid[idx[i]] == 0)
                rt.push_back(input[i]);
        }
        if (rt != input)
            ans.push_back(rt);
        return;
    }

    // 재귀식
    // 1. k번째 괄호 제거
    unvalid[k] = true;
    func(k + 1);
    // 2. k번째 괄호 살리기
    unvalid[k] = false;
    func(k + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> input;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(')
        {
            idx[i] = cur;
            s.push(cur++);
            brackets++;
        }
        else if (input[i] == ')')
        {
            idx[i] = s.top();
            s.pop();
        }
    }

    func(1);

    sort(ans.begin(), ans.end());

    // 중복 제거
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << '\n';
}
