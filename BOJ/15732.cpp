/** 파라미터 서치 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int n, k, d;
int rules[10005][3]; // A번부터 B번까지 C의 간격

long long count_(int box)
{
    // 1~box까지 도토리 개수 구하기
    long long rt = 0;
    for (int i = 0; i < k; i++)
    {
        long long a = rules[i][0], b = rules[i][1], c = rules[i][2];
        if (a > box)
            continue;
        // a~b까지 간격 c
        b = min(box, (int)b); // b가 box보다 크면 안됨. box까지만 탐색해야함.
        rt += (b - a) / c + 1;
    }
    return rt;
}

int func()
{
    // 파라미터릭 서치로 1~mid의 범위에 도토리를 모두 넣으며 개수를 구함.
    // 구한 개수가 cnt라 했을 때 cnt가 d보다 작다면 mid+1~en에 대해 다시 mid 갱신
    // cnt가 d보다 같거나 크다면 st~mid에 대해 다시 mid 갱신
    int st = 1, en = n;
    while (st < en)
    {
        int mid = (st + en) / 2;
        if (count_(mid) >= d)
            en = mid;
        else
            st = mid + 1;
    }
    return st;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k >> d;
    for (int i = 0; i < k; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        rules[i][0] = a;
        rules[i][1] = b;
        rules[i][2] = c;
    }

    cout << func();
}
