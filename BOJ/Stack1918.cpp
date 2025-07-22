/** 스택 1918 후위 표기식 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

stack<char> s;
string input, ans;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> input;

    for (auto x : input)
    {
        // x가 알파벳인 경우
        if ('A' <= x && x <= 'Z')
        {
            ans.push_back(x);
            continue;
        }

        if (x == '(')
        {
            // 괄호도 스택에 넣어서 똑같이 처리하되, 닫는 괄호가 나오면 여는 괄호까지 다 pop 하면서 처리
            s.push(x);
        }
        else if (x == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                ans.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if (x == '*' || x == '/')
        {
            // A/B*C = ABC*/
            // A*B + C*D = AB*CD*+
            // A / (B*C+D) = ABC*D+/
            // A / (B+C*D-E) = ABCD*+E-/A

            // 위의 예시처럼 *, /는 *, /에 대해서만 출력
            // (의 경우 )에서 일괄 처리하기에 건드리면 안됨.
            while (!s.empty() && (s.top() == '*' || s.top() == '/'))
            {
                ans.push_back(s.top());
                s.pop();
            }
            s.push(x);
        }
        else if (x == '+' || x == '-')
        {
            // +, -는 스택에 있는게 (만 아니면 다 출력해도 됨.
            while (!s.empty() && s.top() != '(')
            {
                ans.push_back(s.top());
                s.pop();
            }
            s.push(x);
        }
    }
    while (!s.empty())
    {
        ans.push_back(s.top());
        s.pop();
    }

    cout << ans;
}
