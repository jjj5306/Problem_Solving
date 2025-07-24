/** 해시 21944 문제 추천 시스템 Version 2 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

int n, m, a, b, c;
map<pair<int, int>, int> mymap; // {난이도, 문제 번호} = 분류
map<int, int> problems;         // 문제 번호 = 난이도. m에서 삭제를 위함임

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    while (n--)
    {
        // 번호, 난이도, 분류 순으로 입력됨
        cin >> a >> b >> c;
        mymap.insert({{b, a}, c});
        problems.insert({a, b});
    }

    cin >> m;
    while (m--)
    {
        string command;
        cin >> command;
        if (command == "recommend")
        {
            int g, x;
            cin >> g >> x;
            if (x == 1)
            {
                // 알고리즘 분류가 g에 제일 어려운거
                auto it = mymap.end();
                bool flag = false;
                while (!flag)
                {
                    it--;
                    if (it->second == g)
                    {
                        cout << it->first.second << '\n';
                        flag = true;
                        break;
                    }
                }
            }
            else
            {
                // 알고리즘 분류 g에 제일 쉬운거
                for (auto it = mymap.begin(); it != mymap.end(); it++)
                {
                    if (it->second == g)
                    {
                        cout << it->first.second << '\n';
                        break;
                    }
                }
            }
        }
        else if (command == "recommend2")
        {
            int x;
            cin >> x;
            if (x == 1)
            {
                cout << (--mymap.end())->first.second << '\n';
            }
            else
            {
                cout << mymap.begin()->first.second << '\n';
            }
        }
        else if (command == "recommend3")
        {
            int x, l;
            cin >> x >> l;

            // 난이도가 l 이상 중 가장 쉬운 문제
            auto it = mymap.lower_bound({l, 0});
            if (x == 1)
            {
                // 난이도가 l 이상 중 가장 쉬운 문제
                // *it가 있다면 출력 없으면 -1 출력
                if (it == mymap.end())
                {
                    cout << "-1" << '\n';
                }
                else
                {
                    cout << it->first.second << '\n';
                }
            }
            else
            {
                // 난이도가 l 보다 작은 것 중 가장 어려운 문제
                // lower_bound로 찾은거에서 한 칸 뒤로가면 됨.

                // 예외 처리 1. 맵이 비어있으면 뒤로 갈 수 없음
                // 예외 처리 2. it이 begin이어도 뒤로 갈 수 없음
                // 그런데 맵이 비어있다는건 begin = end = it인 경우임
                if (it == mymap.begin())
                {
                    cout << "-1" << '\n';
                }
                else
                {
                    it--;
                    cout << it->first.second << '\n';
                }
            }
        }
        else if (command == "add")
        {
            cin >> a >> b >> c;
            mymap.insert({{b, a}, c});
            problems.insert({a, b});
        }
        else if (command == "solved")
        {
            int p;
            cin >> p;
            mymap.erase({problems[p], p});
            problems.erase(p);
        }
    }
}

/*
필요한 기능
1. 알고리즘 분류 별 가장 어려운 문제 (같으면 번호 크게) / 쉬운 문제 (같으면 번호 작게)
2. 분류 상관 없이 난이도
3. 분류 상관 없이 난이도인데 이건 lower bound 쓰면 됨.
4. 문제만 가지고 제거

필요한 자료구조는 1번 기능이 문제가 됨.
후보 1. 알고리즘 분류를 가지고 map, 값으로 set => log n으로 분류를 찾고 log n으로 제일 어려운 문제를 찾으면 검색은 되나 삭제가 거의 불가능
후보 2. map key로 {난이도, 문제 번호} 사용하고 value로 알고리즘 분류 저장하면 그냥 됨.
하나의 map에 {난이도, 문제 번호}해서 디폴트로 오름차순 선언 시. 가장 어렵고 문제 번호가 큰 문제 : 제일 뒤에 있음

1번 기능 : 맵 순회
2번 기능 : 맵으로 해결
3번 기능 : lower_bound
삭제, 추가 : 그냥
*/