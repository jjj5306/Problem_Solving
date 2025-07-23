/** 해시 21942 부품 대여장 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

long long n, f, deadline = 0;
string dead;
long long months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
map<pair<string, string>, long long> m;
map<string, long long> ans;

long long trans(long long mon, long long day, long long hour, long long minute)
{
    // 1. mon -> day
    for (long long i = 1; i < mon; i++)
    {
        day += months[i];
    }
    if (mon != -1) // mon이 -1인 경우는 dead line 계산임. 그 경우 날짜가 아닌 실제 일수가 들어오기에 1을 빼면 안됨.
        day--;     // 1일부터 시작이므로 하나 빼줘야 함. 예를 들어 1월2일은 2일치를 계산하는게 아니라 1일치를 계산해야 함.

    // 2. day -> hour
    hour += day * 24;

    // 3. hour -> minute
    minute += hour * 60;

    return minute;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> dead >> f;

    // dead line : day/hour:min 형식.
    // -> 총 k분으로 변환이 가능함.
    long long month, day, hours, minutes;

    deadline = trans(-1, stoi(dead.substr(0, 3)), stoi(dead.substr(4, 2)), stoi(dead.substr(7, 2)));

    for (long long i = 0; i < n; i++)
    {
        string start1, start2, stuff, person;
        cin >> start1 >> start2 >> stuff >> person;

        // 먼저 날짜 계산
        long long cur = trans(stoi(start1.substr(5, 2)), stoi(start1.substr(8, 2)), stoi(start2.substr(0, 2)), stoi(start2.substr(3, 2)));

        if (m.find({person, stuff}) == m.end())
        {
            // person이 stuff를 빌리는 경우. 즉 맵에 person, stuff가 없음
            m.insert({{person, stuff}, cur});
        }
        else
        {
            // person이 stuff를 반납하는 경우. 즉 맵에 존재함
            cur -= m[{person, stuff}];
            // 패널티 계산
            if (cur > deadline)
            {
                if (ans.find(person) == ans.end())
                    ans.insert({person, (cur - deadline) * f});
                else
                    ans.at(person) += (cur - deadline) * f;
            }
            m.erase({person, stuff});
        }
    }

    if (ans.empty())
    {
        cout << "-1";
        return 0;
    }
    for (auto x : ans)
        cout << x.first << ' ' << x.second << '\n';
}
