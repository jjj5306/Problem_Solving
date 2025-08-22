#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

bool vis[205];

int solution(int n, vector<vector<int>> computers)
{
    int answer = 0;
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        if (vis[i])
            continue;
        answer++;

        // bfs
        vis[i] = true;
        q.push(i);

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            // cout << "cur : "<<cur<<", ans : " <<answer<<'\n';

            for (int j = 0; j < n; j++)
            {
                // i와 연결된 노드를 찾기 위해 computers[i][j] 체크
                if (i == j || computers[cur][j] == 0 || vis[j])
                    continue;

                vis[j] = true;
                q.push(j);
                j = -1;
            }
        }
    }

    return answer;
}