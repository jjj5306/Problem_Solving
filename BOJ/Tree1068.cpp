/** 트리 1068 트리 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, ans = 0, del, root = -1;
bool deleted[55];
vector<int> child[55]; // child[k] : k번째 노드의 자식
int parent[55];

void func(int k)
{
    // k번째 노드 제거

    // base condition : k가 리프 노드인 경우
    if (child[k].empty())
    {
        // cout << "target node : " << k << '\n';
        deleted[k] = true;
        return;
    }

    for (auto nxt = child[k].begin(); nxt != child[k].end(); nxt++)
    {
        // cout << "call : " << *nxt << '\n';
        func(*nxt);
    }
    // cout << "delete child[" << k << "]\n";
    child[k].clear();
    deleted[k] = true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int par;
        cin >> par;
        parent[i] = par;

        if (par == -1)
            root = i;
        else
            // i의 부모가 par
            child[par].push_back(i);
    }

    cin >> del;
    if (parent[del] == -1)
    {
        cout << "0";
        return 0;
    }
    else
    {
        // del의 부모에서 del을 지워야 함.
        for (auto it = child[parent[del]].begin(); it != child[parent[del]].end(); it++)
        {
            if (*it == del)
            {
                child[parent[del]].erase(it);
                break;
            }
        }
    }

    func(del);

    child[del].clear();

    // 리프 노드 개수 세기
    for (int i = 0; i < n; i++)
    {
        if (child[i].empty() && !deleted[i])
        {
            // cout << "leaf node : " << i << '\n';
            ans++;
        }
    }
    cout << ans;
}

/*
1. 지우는게 리프 노드임 -> 전체 개수 -1
2. 지우는게 누군가의 부모임 -> 자식들 다 순회하면서 제거. 리프인 경우 전체 개수 -1
재귀로 짜면 될듯

void func(int k) : k번째 노드 제거
base condition : k가 리프노드. -> 전체 개수 -1
재귀식 :
1. k의 자식 노드들 func(child)
2. k번째 노드 제거 (child가 null인거 확인 후 )
*/
