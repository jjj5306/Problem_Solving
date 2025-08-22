/** 해시 Registration system **/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int hashing(string s);
int find_table(string s, int key);
vector<vector<string>> table(1000, vector<string>(400));
vector<vector<int>> table_cnt(1000, vector<int>(400));
int length[1000] = {
    0,
}; // 각 테이블에 체이닝되어있는 원소 수를 나타낸다.
const int TABLE_SIZE = 1000;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        string s;
        cin >> s;

        int key = hashing(s);
        int cnt = find_table(s, key);

        // 이미 들어온 문자라면 출력
        if (cnt != -1)
        {
            cout << s << cnt << "\n";
        }
        else
        {
            // 들어온 적 없다면 OK출력 후 테이블 및 length 배열, table_cnt 갱신
            cout << "OK\n";
            table_cnt[key][length[key]] = 1;
            table[key][length[key]++] = s;
        }
    }
}

int hashing(string s)
{
    int key = 0;
    for (auto x : s)
    {
        key = (key * 31 + (int)x) % TABLE_SIZE;
    }
    return key % TABLE_SIZE;
}

int find_table(string s, int key)
{
    // table[key]에 s가 해당 s가 지금까지 출력된 횟수 리턴있으면  아니면 -1 리턴
    for (long i = 0; i < length[key]; i++)
        if (table[key][i] == s)
            return table_cnt[key][i]++;
    return -1;
}