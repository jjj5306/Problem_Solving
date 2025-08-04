/** 트리 3584 가장 가까운 공통 조상 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int height[10010];
vector<int> childs[10010];

void dfs(int cur, int h)
{
    // cur의 높이 기록
    height[cur] = h;

    for (auto nxt : childs[cur])
        dfs(nxt, h + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        // DFS로 루트부터 선회하며 모든 노드의 높이 저장
        // 타겟 노드인 a, b로부터 한칸씩 높이를 올리며 부모를 찾아감
        // 그 부모가 같아지면 그 노드가 답
        // 이를 위해서는 부모, 루트, 높이가 필요

        int n;
        cin >> n;

        int parent[10010];
        bool is_root[10010]; // 루트면 1
        fill(is_root, is_root + n + 1, true);

        for (int i = 0; i <= n; i++)
            childs[i].clear();

        for (int i = 0; i < n - 1; i++)
        {
            int par, child;
            cin >> par >> child;
            parent[child] = par;          // par[k] : k의 부모
            childs[par].push_back(child); // childs[k] : k의 자식
            // adj : child -> par 만 저장
            is_root[child] = false;
        }

        int root;
        // 루트 찾기
        for (int i = 1; i <= n; i++)
        {
            if (is_root[i])
            {
                root = i;
                break;
            }
        }

        // DFS로 각 노드의 높이 체크
        fill(height, height + n + 1, 0);
        dfs(root, 0);

        // cout << "root : " << root << '\n';
        // for (int i = 1; i <= n; i++)
        //     cout << "height of " << i << " node : " << height[i] << '\n';

        int a, b;
        cin >> a >> b;

        // a, b의 높이가 같아질때까지 맞추기
        if (height[a] > height[b])
        {
            while (height[a] != height[b])
                a = parent[a];
        }
        else if (height[a] < height[b])
        {
            while (height[a] != height[b])
                b = parent[b];
        }

        while (a != b)
        {
            a = parent[a];
            b = parent[b];
        }

        cout << a << '\n';
    }
}
