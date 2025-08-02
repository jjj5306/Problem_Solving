/** 트리 5639 이진 검색 트리 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<int> pre;

// solve : 왼쪽, 오른쪽, 루트 순서로 출력해야 함. pre는 루트, 왼쪽, 오른쪽 순서로 있음
// 함수 정의 : left ~ right의 범위에 대해 후위 순회
// base condition : left >= right면 출력 후 종료
// 재귀식
// left~right 범위면 left가 해당 범위의 루트임 따라서 root=left
// upper_bound(root) -> 오른쪽 서브트리의 첫 번째 index = deli
// 2. 왼쪽 자식 : solve(left+1, deli-1) -> left+1이 root의 왼쪽 트리의 루트
// 3. 오른쪽 자식 : solve(deli, end) -> deli의 자식이 있던 말던 끝까지 순회해야 함.

void solve(int left, int right)
{
    if (left > right)
    {
        return;
    }

    // deli : 구분자. 루트보다 큰 첫 번째 index
    int deli = left + 1;
    while (deli <= right && pre[deli] <= pre[left])
        deli++;

    // cout << "cur left : " << pre[left] << ", right : " << pre[right] << ", deli : " << pre[deli] << "\n";

    // 현재 트리의 왼쪽 서브 트리 범위 : left+1,deli-1
    solve(left + 1, deli - 1);
    // 현재 트리의 오른쪽 서브 트리 범위 : deli, end
    solve(deli, right);

    // 왼쪽 오른쪽 노드에 대한 호출이 다 끝나면 루트 호출
    cout << pre[left] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    while (cin >> n)
    {
        pre.push_back(n);
    }

    // 루트를 기준으로 루트보다 큰 수가 들어오는 순간 그 루트의 오른쪽 서브트리의 루트임
    // 후위 순회는 왼쪽-오른쪽-루트 순임
    // 따라서 가장 왼쪽 서브트리를 찾는데 이건 제일 작은 수가 됨.
    // 제일 작은 수의 왼쪽 수를 pre[k]라 하면
    // pre[k]의 부모 즉, pre[k-1]에 대해 upper_bound(pre[k-1])이 오른쪽 서브트리의 루트

    solve(0, pre.size() - 1);
}
