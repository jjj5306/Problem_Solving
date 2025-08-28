#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

queue<int> q;
bool vis[102];
vector<int> adj[102];

int func(int k, int n, vector<vector<int>> &wires)
{
    // wires[k]를 끊었을 때 BFS를 돌려 답 계산
    int rt1 = 0, rt2 = 0;

    fill(vis, vis + 101, false);

    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;

        // i노드를 시작으로 BFS.
        int cnt = 1; // cnt : BFS 탐색 노드 개수
        vis[i] = true;
        q.push(i);

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            for (auto nxt : adj[cur])
            {
                if (vis[nxt])
                    continue;
                // k번째 간선인지 체크
                if (cur == wires[k][0] && nxt == wires[k][1])
                    continue;
                if (cur == wires[k][1] && nxt == wires[k][0])
                    continue;

                q.push(nxt);
                vis[nxt] = true;
                cnt++;
            }
        }
        if (rt1 == 0)
            rt1 = cnt;
        else
            rt2 = cnt;
    }

    return abs(rt1 - rt2);
}

int solution(int n, vector<vector<int>> wires)
{
    int answer = 0x7f7f7f7f;

    // 완전 탐색 -> n개의 케이스
    // 한 번의 탐색에서 BFS -> n^2
    // n=100 이므로 효율성 OK

    // 먼저 wires -> adj로 변경
    for (auto wire : wires)
    {
        adj[wire[0]].push_back(wire[1]);
        adj[wire[1]].push_back(wire[0]);
    }

    for (int k = 0; k < wires.size(); k++)
    {
        answer = min(answer, func(k, n, wires));
    }

    return answer;
}