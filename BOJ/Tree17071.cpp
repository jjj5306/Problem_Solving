/** 트리 17073 나무 위의 빗물 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, w, leaf = 0;
int adj[500010]; // 간선의 수 저장

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> w;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u]++;
        adj[v]++;
    }

    for (int i = 2; i <= n; i++)
    {
        if (adj[i] == 1)
            leaf++;
    }

    // 하나의 leaf node에서 기대값은 w/leaf임.
    //  leaf개의 노드에 대한 평균은 w/leaf * leaf / leaf 이므로 w/leaf가 정답
    double ans = w / (double)leaf;
    cout.precision(6);
    cout << fixed << ans;
}
