#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

priority_queue<int, vector<int>> maxq;
priority_queue<int, vector<int>, greater<int>> minq;
map<int, bool> m;

vector<int> solution(vector<string> operations)
{
    vector<int> answer;

    for (auto operation : operations)
    {
        if (operation[0] == 'I')
        {
            int cur = stoi(operation.substr(2));
            maxq.push(cur);
            minq.push(cur);
            m[cur] = true;

            // cout << maxq.top()<<' '<<minq.top()<<" 1\n";
        }
        else
        {
            if (operation[2] == '1')
            {
                // 최대값 삭제

                // 큐가 비어있는지 체크
                if (maxq.empty())
                    continue;

                // 최대 힙 sync 맞추기 (삭제된 것 실제 삭제)
                int cur = maxq.top();
                while (!m[cur] && !maxq.empty())
                {
                    maxq.pop();
                    cur = maxq.top();
                }

                if (maxq.empty())
                    continue;

                maxq.pop();
                m[cur] = false;
                if (minq.top() == cur)
                    minq.pop();

                // cout << maxq.top()<<' '<<minq.top()<<" 2\n";
            }
            else
            {
                // 최소값 삭제
                if (minq.empty())
                    continue;

                int cur = minq.top();
                while (!m[cur] && !minq.empty())
                {
                    minq.pop();
                    cur = minq.top();
                }

                if (minq.empty())
                    continue;

                minq.pop();
                m[cur] = false;
                if (maxq.top() == cur)
                    maxq.pop();

                // cout << maxq.top()<<' '<<minq.top()<<" 3\n";
            }
        }
    }

    // 출력 전 각 큐 싱크 맞추기
    int cur;

    if (!minq.empty())
    {
        cur = minq.top();
        while (!m[cur] && !minq.empty())
        {
            minq.pop();
            cur = minq.top();
        }
    }

    if (!maxq.empty())
    {
        cur = maxq.top();
        while (!m[cur] && !maxq.empty())
        {
            maxq.pop();
            cur = maxq.top();
        }
    }

    if (maxq.empty() && minq.empty())
    {
        answer.push_back(0);
        answer.push_back(0);
    }
    else if (maxq.empty() && !minq.empty())
    {
        answer.push_back(minq.top());
        answer.push_back(minq.top());
    }
    else if (!maxq.empty() && minq.empty())
    {
        answer.push_back(maxq.top());
        answer.push_back(maxq.top());
    }
    else
    {
        answer.push_back(maxq.top());
        answer.push_back(minq.top());
    }

    return answer;
}
