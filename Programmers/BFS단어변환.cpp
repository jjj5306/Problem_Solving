#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

bool vis[55];

bool can_trans(string a, string b)
{
    // a, b가 서로 변환이 가능한지 체크
    int cnt = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            cnt++;
    }
    if (cnt == 1)
        return 1;
    else
        return 0;
}

// func : words[cur]로 cnt 번 trans 함
int func(string cur, int cnt, string target, vector<string> words)
{
    if (cur == target)
        return cnt;

    int rt = 0x3f3f3f3f;

    for (int i = 0; i < words.size(); i++)
    {
        if (vis[i] || !can_trans(cur, words[i]))
            continue;

        // cur -> i trans
        vis[i] = true;
        rt = min(rt, func(words[i], cnt + 1, target, words));
        vis[i] = false;
    }
    return rt;
}

int solution(string begin, string target, vector<string> words)
{
    int answer = 0x7f7f7f7f;

    // n이 매우 작으므로 매 step 마다 모든 단어를 순회하면서 변환해도 됨
    // 다만, 변환할 수 없는 경우가 문제. 아래의 두 케이스로 나눌 수 있음.
    // 1. target이 words에 없는 경우
    // 2. 한 번 방문한 words는 방문하지 않을 때, 한 iter가 지나고도 변화하지 않는 경우

    // 1번 경우 체크
    bool possible = false;
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == target)
        {
            possible = true;
            break;
        }
    }
    if (!possible)
        return 0;

    // 마치 DFS처럼 모든 경로를 탐색해야 함. 완전 탐색으로도 볼 수 있겠음.
    for (int i = 0; i < words.size(); i++)
    {
        if (can_trans(begin, words[i]))
        {
            vis[i] = true;

            int rt = func(words[i], 1, target, words);
            // cout<<"***********"<<' '<<rt<<'\n';
            if (rt != 0)
                answer = min(answer, rt);
            vis[i] = false;
        }
    }

    return answer;
}