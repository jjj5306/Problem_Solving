/** 스택 2504 괄호의 값 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

stack<char> s;
string input;
int ans = 0, tmp = 1;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> input;

    for (int i = 0; i < input.size(); i++)
    {
        // case 1. (인 경우 그 뒤에 나오는 쌍들에 모두 2를 곱해줄 예정. 즉 ((( ~~~ 라면 ~~~에 8을 곱해줘야 함.
        if (input[i] == '(')
        {
            tmp *= 2;
            s.push('(');
            // cout << "case 1 - i : " << i << " tmp : " << tmp << '\n';
        }
        // case 2. [인 경우 마찬가지
        else if (input[i] == '[')
        {
            tmp *= 3;
            s.push('[');
            // cout << "case 2 - i : " << i << " tmp : " << tmp << '\n';
        }
        else if (input[i] == ')')
        {
            // 잘못된 괄호인 경우
            if (s.empty() || s.top() != '(' || i == 0)
            {
                // 종료 케이스. 잘못된 괄호.
                cout << '0';
                return 0;
            }

            // 이전이 (여서 () 이렇게 매칭된 경우 답을 한 번 계산해줘야 함.
            if (input[i - 1] == '(')
                ans += tmp;
            tmp /= 2;
            s.pop();
            // cout << "case 3 - i : " << i << " tmp : " << tmp << '\n';
        }
        else
        {
            // 잘못된 괄호인 경우
            if (s.empty() || s.top() != '[' || i == 0)
            {
                // 종료 케이스. 잘못된 괄호.
                cout << '0';
                return 0;
            }

            // 이전이 (여서 () 이렇게 매칭된 경우 답을 한 번 계산해줘야 함.
            if (input[i - 1] == '[')
                ans += tmp;
            tmp /= 3;
            s.pop();
            // cout << "case 4 - i : " << i << " tmp : " << tmp << '\n';
        }
    }

    if (!s.empty())
    {
        // 종료 케이스. 잘못된 괄호.
        cout << '0';
        return 0;
    }
    cout << ans;
}
