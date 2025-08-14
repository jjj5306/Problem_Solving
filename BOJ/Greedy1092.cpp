/** 그리디 1092 배 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int n, m;
vector<int> limit, box;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        limit.push_back(a);
    }

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int a;
        cin >> a;
        box.push_back(a);
    }

    // 가장 강한 크레인이 가장 무거운 무게를 들기
    sort(box.rbegin(), box.rend());
    sort(limit.rbegin(), limit.rend());

    // 처리할 수 없는 경우 체크
    if (limit[0] < box[0])
    {
        cout << "-1";
        return 0;
    }

    int ans = 0;

    while (!box.empty())
    {
        ans++;
        int j = 0;
        // i 컨테이너가 j 박스를 담당
        for (int i = 0; i < n && j < box.size();)
        {
            // i 컨테이너가 j 박스를 옮길 수 있는 경우
            if (limit[i] >= box[j])
            {
                box.erase(box.begin() + j);
                i++;
            }
            else
            {
                // 다음 박스로 다시 시도
                j++;
            }
        }
    }

    cout << ans;
}
