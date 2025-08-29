#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace std;

tuple<int, int, int> edge[102];
vector<int> p(102, -1);
// p[k]가 0보다 작으면 해당 그룹의 크기이고 k가 해당 그룹의 루트
// p[k]=u, u>=0 이면 u가 해당 그룹의 루트

int find(int x)
{
    // x가 대표 노드인 경우
    if (p[x] < 0)
        return x;
    p[x] = find(p[x]);
    return p[x];
}

bool is_diff_group(int u, int v)
{
    u = find(u);
    v = find(v);

    if (u == v)
        return 0; // 같은 그룹

    if (p[u] == p[v])
        p[u]--; // 두 그룹 크기가 같으면 임의로 u의 크기를 늘림
    if (p[u] < p[v])
        p[v] = u;
    else
        p[u] = v;

    return 1;
}

int solution(int n, vector<vector<int>> costs)
{
    int answer = 0;

    // MST. 특정 정점 시작이 아니므로 크루스칼

    // 1. 2차원 벡터 -> tuple (cost, u, v), 노드 수 세기
    int edge_idx = 0;
    for (auto cost : costs)
    {
        edge[edge_idx++] = {cost[2], cost[0], cost[1]};
    }

    // 2. edge cost 오름차순으로 정렬
    sort(edge, edge + costs.size());

    // 3. 노드의 수 - 1 개의 간선을 추가할 때까지 간선을 선택
    // 선택된 간선이 같은 그룹이면 추가 X

    int cnt = 0;

    for (int i = 0; i < costs.size(); i++)
    {
        int u, v, cost;
        tie(cost, u, v) = edge[i];

        if (!is_diff_group(u, v))
            continue;

        answer += cost;
        cnt++;
        // cout<<cnt<<' '<<answer<<' '<<u<<' '<<v<<' '<<cost<<'\n';
        if (cnt == n - 1)
            break;
    }

    return answer;
}