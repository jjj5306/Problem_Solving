/** 트리 9489 사촌 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, k;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (1)
    {
        cin >> n >> k;
        if (n == 0 && k == 0)
            return 0;

        int cur;
        cin >> cur;

        int cur_par = -1, k_idx;
        int input[1010], par[1010], height[1010];

        input[0] = cur;
        height[0] = 0;
        par[0] = -1; // edge case

        for (int i = 1; i < n; i++)
        {
            cin >> cur;

            if (cur == k)
            {
                k_idx = i;
            }

            // i번째 노드의 값은 cur.
            input[i] = cur;

            if (input[i - 1] + 1 == cur)
            {
                // i번째 노드가 연속된 숫자라면 prev와 부모, 높이가 같음
                height[i] = height[i - 1];
                par[i] = cur_par;
            }
            else
            {
                // i번째 노드가 연속되지 않은 숫자라면 prev의 부모의 다음 노드가 부모.
                // 높이의 경우 부모 + 1을 하면 됨.
                par[i] = ++cur_par;
                if (par[i] == -1)
                    height[i] = height[0] + 1;
                else
                    height[i] = height[par[i]] + 1;
            }
        }

        // for (int i = 1; i < n; i++)
        // cout << i << " node's value : " << input[i] << ", par : " << input[par[i]] << ", height : " << height[i] << '\n';

        // k_idx의 부모의 부모는 같고, 부모는 다른 노드 찾기
        int ans = 0, k_par = par[k_idx], k_parpar = par[par[k_idx]];
        for (int i = 1; i < n; i++)
        {
            // 부모의 부모가 없는 경우
            if (par[par[i]] == -1)
                continue;
            if (par[par[i]] == k_parpar && par[i] != k_par)
                ans++;
        }
        cout << ans << '\n';
    }
}
